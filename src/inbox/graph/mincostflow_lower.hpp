#include "../template.hpp"



enum Objective {
    MINIMIZE = 1,
    MAXIMIZE = -1,
};
enum class Status {
    OPTIMAL,
    INFEASIBLE,
};
/*
https://misawa.github.io/others/flow/library_design.html
負辺/負サイクル/流量下限付き最小費用流
add_vertices(n) 初期化
add_edge(from, to, lower, upper, cost): 流量上下限つきの辺を追加 (EdgePtr を返す)
add_supply(v, amount) / add_demand(v, amount): 湧出し/吸込み
pair<Status, Cost> solve(): 最小費用b-フロー
tuple<Status, Cost, Flow> solve(s, t): 最小費用最大流
solve は1インスタンスにつき1回だけ(2回目は assert で落ちる)
add_edgeが辺のポインタを返すのでvector edges(n, vector<MCF::EdgePtr>(n));などとしてメモっとけば流量の復元ができる
*/
template <class Flow, class Cost, Objective objective=Objective::MINIMIZE>
class MinCostFlow {
    using V_id=int;
    struct Edge {
        V_id src, dst;
        Flow flow, cap;
        Cost cost;
        int rev;
        Flow residual_cap()const {return cap-flow;}
    };

public:
    class EdgePtr {
        friend class MinCostFlow;
        const MinCostFlow *ins;
        V_id v;
        int e;
        EdgePtr(const MinCostFlow *ins, V_id v, int e):ins(ins), v(v), e(e){}
        const Edge &edge()const {return ins->g[v][e];}
        const Edge &rev()const {return ins->g[edge().dst][edge().rev];}

public:
        EdgePtr() = default;
        V_id src()const {return v;}
        V_id dst()const {return edge().dst;}
        Flow flow()const {return edge().flow;}
        Flow lower()const {return -rev().cap;}
        Flow upper()const {return edge().cap;}
        Cost cost()const {return edge().cost;}
        Cost gain()const {return -edge().cost;}
    };

private:
    int n=0;
    bool used=false;
    vector<vector<Edge>> g;
    vector<Flow> b;
    Cost farthest;
    vector<Cost> potential, dist;
    vector<Edge *> parent;
    vector<V_id> ex, de;  // 超過頂点 / 不足頂点

    void push(Edge& e, Flow f){e.flow+=f;g[e.dst][e.rev].flow-=f;}
    Cost rc(const Edge& e){return e.cost+potential[e.src]-potential[e.dst];}

    bool dual(){
        dist.assign(n, numeric_limits<Cost>::max());
        parent.assign(n, nullptr);
        ex.erase(remove_if(begin(ex), end(ex), [&](V_id v) {return b[v]<=0;}), end(ex));
        de.erase(remove_if(begin(de), end(de), [&](V_id v) {return b[v]>=0;}), end(de));
        priority_queue<pair<Cost, int>, vector<pair<Cost, int>>, greater<>> pq;
        for(V_id v : ex) pq.emplace(dist[v]=0, v);
        farthest=0;
        size_t cnt=0;
        while(!pq.empty()){
            auto [d, u]=pq.top();
            pq.pop();
            if(dist[u]<d) continue;
            farthest=d;
            if(b[u]<0) ++cnt;
            if(cnt>=de.size()) break;
            for(auto& e : g[u]){
                if(e.residual_cap()<=0) continue;
                Cost nd=d+rc(e);
                if(nd>=dist[e.dst]) continue;
                pq.emplace(dist[e.dst]=nd, e.dst);
                parent[e.dst]=&e;
            }
        }
        for(V_id v=0;v<n;++v) potential[v]+=min(dist[v], farthest);
        return cnt>0;
    }

    void primal(){
        for(V_id t : de){
            if(dist[t]>farthest) continue;
            Flow f=-b[t];
            V_id v;
            for(v=t;parent[v];v=parent[v]->src) f=min(f, parent[v]->residual_cap());
            f=min(f, b[v]);
            if(f<=0) continue;
            for(v=t;parent[v];){
                Edge& e=*parent[v];
                push(e, f);
                V_id u=e.src;
                if(e.residual_cap()<=0) parent[v]=nullptr;
                v=u;
            }
            b[t]+=f;
            b[v]-=f;
        }
    }

    pair<Status, Cost> run(){
        potential.resize(n);
        ex.clear(), de.clear();
        for(auto& es : g) for(auto& e : es){
                Flow c=e.residual_cap();
                if(rc(e)<0||c<0){push(e, c);b[e.src]-=c;b[e.dst]+=c;}
            }
        for(V_id v=0;v<n;++v) if(b[v]) (b[v]>0?ex:de).push_back(v);
        while(dual()) primal();
        Cost val=0;
        for(auto& es : g) for(auto& e : es) val+=e.flow*e.cost;
        return {ex.empty()&&de.empty()?Status::OPTIMAL:Status::INFEASIBLE, val/2/objective};
    }

public:
    vector<V_id> add_vertices(int k){
        vector<V_id> r(k);
        iota(begin(r), end(r), n);
        n+=k;
        g.resize(n), b.resize(n);
        return r;
    }
    V_id add_vertex(){return add_vertices(1)[0];}

    EdgePtr add_edge(V_id s, V_id d, Flow lo, Flow up, Cost c){
        assert(lo<=up);
        int e=g[s].size(), re=s==d?e+1:g[d].size();
        g[s].push_back({s, d, 0, up, c*objective, re});
        g[d].push_back({d, s, 0, -lo, -c*objective, e});
        return {this, s, e};
    }
    void add_supply(V_id v, Flow x){b[v]+=x;}
    void add_demand(V_id v, Flow x){b[v]-=x;}
    const vector<Cost> &dual_variables()const {return potential;}

    pair<Status, Cost> solve(){
        assert(!used);
        used=true;
        return run();
    }

    tuple<Status, Cost, Flow> solve(V_id s, V_id t){
        assert(!used&&s!=t);
        used=true;
        const Flow lim=numeric_limits<Flow>::max()/4;
        auto inf=[&] {    // s から出る残余容量の合計(飽和加算)
            Flow r=min(abs(b[s]), lim);
            for(auto& e : g[s]){Flow x=max<Flow>(e.residual_cap(), 0);r=r>lim-x?lim:r+x;}
            return r;
        };
        add_edge(t, s, 0, inf(), 0);
        const auto [st, cv]=run();
        Cost val=cv;
        Flow f=0;
        if(st==Status::OPTIMAL){
            Flow x=inf();
            b[s]+=x, b[t]-=x;
            val=run().second;
            f=b[t]+x;
        }
        g[s].pop_back(), g[t].pop_back();
        return {st, val, f};
    }
};


template <class Flow, class Cost>
using MaxGainFlow=MinCostFlow<Flow, Cost, Objective::MAXIMIZE>;
using Flow=long long;
using Cost=__int128_t;
using MCF=MinCostFlow<Flow, Cost>;