#include "../graph/mincostflow.hpp"


template<class Cap, class Cost> struct mincostflow_lower {
    struct E { int from, idx;Cap low, high; };
    int n;
    mincostflow<Cap, Cost> mf;
    vector<Cap> bal;
    vector<E> edges;
    Cost base_cost=0;
    bool solved=false, feasible=false;

    explicit mincostflow_lower(int n):n(n), mf(n+2), bal(n, 0){
        static_assert(is_signed_v<Cap>&&is_signed_v<Cost>);
    }

    void add_edge(int from, int to, Cap low, Cap high, Cost cost){
        assert(!solved&&0<=from&&from<n&&0<=to&&to<n&&from!=to);
        assert(0<=low&&low<=high&&0<=cost);
        edges.push_back({from, (int)mf.g[from].size(), low, high});
        mf.add_edge(from, to, high-low, cost);
        bal[from]-=low;bal[to]+=low;
        base_cost+=Cost(low)*cost;
    }

    optional<pair<Cap, Cost>> flow(int s, int t, Cap F=-1){
        assert(!solved&&0<=s&&s<n&&0<=t&&t<n&&s!=t&&(F==-1||F>=0));
        solved=true;
        int SS=n, TT=n+1;

        int ti=-1, srev=-1;
        if(F==-1){
            ti=mf.g[t].size();srev=mf.g[s].size();
            mf.add_edge(t, s, numeric_limits<Cap>::max()/4, 0);
        }

        Cap need=0;
        for(int v=0;v<n;v++){
            Cap q=0;
            if(F!=-1){if(v==s) q-=F;if(v==t) q+=F;}
            Cap d=q-bal[v];
            if(d<0) mf.add_edge(SS, v, -d, 0), need-=d;
            else if(d>0) mf.add_edge(v, TT, d, 0);
        }
        auto [sent, cost]=mf.flow(SS, TT, need);
        if(sent!=need) return nullopt;
        feasible=true;
        Cost total=base_cost+cost;

        if(F==-1){
            mf.g[t][ti].cap=0;
            mf.g[s][srev].cap=0;
            total+=mf.flow(s, t).second;
        }

        auto f=get_flows();
        Cap tot=0;
        for(size_t i=0;i<edges.size();i++){
            if(edges[i].from==s) tot+=f[i];
            if(mf.g[edges[i].from][edges[i].idx].to==s) tot-=f[i];
        }
        return pair{tot, total};
    }

    vector<Cap> get_flows()const {
        assert(solved&&feasible);
        vector<Cap> ans;
        for(auto& e:edges) ans.push_back(e.high-mf.g[e.from][e.idx].cap);
        return ans;
    }
};
