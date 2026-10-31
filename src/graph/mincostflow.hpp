#include "../template.hpp"

template <typename flow_t, typename cost_t>
struct PrimalDual {
    struct E {
        int to, rev;
        flow_t cap;
        cost_t cost;
        bool isr;
    };

    vector<vector<E>> G;
    vector<cost_t> P, mc;
    vector<int> pv, pe;
    const cost_t INF;

    PrimalDual(int V):G(V), P(V, 0), INF(numeric_limits<cost_t>::max()){}

    void add_edge(int from, int to, flow_t cap, cost_t cost){
        G[from].push_back(E{to, (int)G[to].size(), cap, cost, false});
        G[to].push_back(E{from, (int)G[from].size()-1, 0, -cost, true});
    }

    pair<flow_t, cost_t> flow(int s, int t, flow_t f){
        int V=G.size();
        flow_t sent=0;
        cost_t ret=0;
        using Pi=pair<cost_t, int>;
        priority_queue<Pi, vector<Pi>, greater<Pi>> que;
        pe.assign(V, -1);
        pv.assign(V, -1);

        while(f>0){
            mc.assign(V, INF);
            mc[s]=0;
            que.emplace(0, s);
            while(!que.empty()){
                auto [d, v]=que.top();
                que.pop();
                if(mc[v]<d) continue;
                for(int i=0;i<(int)G[v].size();i++){
                    E& e=G[v][i];
                    if(e.cap<=0) continue;
                    cost_t nc=d+e.cost+P[v]-P[e.to];
                    if(mc[e.to]>nc){
                        mc[e.to]=nc;
                        pv[e.to]=v, pe[e.to]=i;
                        que.emplace(nc, e.to);
                    }
                }
            }
            if(mc[t]==INF) break;
            for(int v=0;v<V;v++) if(mc[v]!=INF) P[v]+=mc[v];
            flow_t add=f;
            for(int v=t;v!=s;v=pv[v]) add=min(add, G[pv[v]][pe[v]].cap);
            f-=add;
            sent+=add;
            ret+=add*(P[t]-P[s]);
            for(int v=t;v!=s;v=pv[v]){
                E& e=G[pv[v]][pe[v]];
                e.cap-=add;
                G[v][e.rev].cap+=add;
            }
        }
        return {sent, ret};
    }

    cost_t min_cost_flow(int s, int t, flow_t f){
        auto [sent, cost]=flow(s, t, f);
        return sent==f?cost:-1;
    }

    pair<flow_t, cost_t> min_cost_max_flow(int s, int t){
        return flow(s, t, numeric_limits<flow_t>::max());
    }
    //負辺対応(流す前に呼ぶ)
    void init_potential(int s){
        int V=G.size();
        P.assign(V, INF);
        P[s]=0;
        for(int i=0;i<V-1;i++){
            bool update=false;
            for(int v=0;v<V;v++){
                if(P[v]==INF) continue;
                for(auto& e : G[v]){
                    if(e.cap>0&&P[e.to]>P[v]+e.cost){
                        P[e.to]=P[v]+e.cost;
                        update=true;
                    }
                }
            }
            if(!update) break;
        }
        for(int v=0;v<V;v++) if(P[v]==INF) P[v]=0;
    }

    void output(){
        for(int i=0;i<(int)G.size();i++)
            for(auto& e : G[i]){
                if(e.isr) continue;
                auto& r=G[e.to][e.rev];
                cout<<i<<"->"<<e.to<<" (flow: "<<r.cap<<"/"
                    <<r.cap+e.cap<<")"<<endl;
            }
    }
};