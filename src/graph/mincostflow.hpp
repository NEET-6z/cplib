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

    PrimalDual(int V):G(V), INF(numeric_limits<cost_t>::max()){}

    void add_edge(int from, int to, flow_t cap, cost_t cost){
        G[from].emplace_back(E{to, cap, cost, si(G[to]), false});
        G[to].emplace_back(E{from, 0, -cost, si(G[from])-1, true});
    }

    cost_t min_cost_flow(int s, int t, flow_t f){
        int V=si(G);
        cost_t ret=0;
        using Pi=pair<cost_t, int>;
        priority_queue<Pi, vector<Pi>, greater<Pi>> que;
        P.assign(V, 0);  //init_potential(s)
        pe.assign(V, -1);
        pv.assign(V, -1);

        while(f>0){
            mc.assign(V, INF);
            que.emplace(0, s);
            mc[s]=0;
            while(!que.empty()){
                Pi p=que.top();
                que.pop();
                if(mc[p.se]<p.fi) continue;
                rep(i, si(G[p.se])){
                    E& e=G[p.se][i];
                    cost_t nextCost=mc[p.se]+e.cost+P[p.se]-
                                     P[e.to];
                    if(e.cap>0&&mc[e.to]>nextCost){
                        mc[e.to]=nextCost;
                        pv[e.to]=p.se, pe[e.to]=i;
                        que.emplace(mc[e.to], e.to);
                    }
                }
            }
            if(mc[t]==INF) return -1;
            rep(v, V) if(mc[v]!=INF) P[v]+=mc[v];
            flow_t addflow=f;
            for(int v=t;v!=s;v=pv[v]){
                addflow=min(addflow, G[pv[v]][pe[v]].cap);
            }
            f-=addflow;
            ret+=addflow*P[t];
            for(int v=t;v!=s;v=pv[v]){
                E& e=G[pv[v]][pe[v]];
                e.cap-=addflow;
                G[v][e.rev].cap+=addflow;
            }
        }
        return ret;
    }
    //負辺対応
    void init_potential(int s){
        int V=si(G);
        P.assign(V, INF);
        P[s]=0;
        rep(i, V-1){
            bool update=false;
            rep(v, V){
                if(P[v]==INF) continue;
                for(auto& e : G[v]){
                    if(e.cap>0&&
                       P[e.to]>P[v]+e.cost){
                        P[e.to]=P[v]+e.cost;
                        update=true;
                    }
                }
            }
            if(!update) break;
        }
        rep(v, V) if(P[v]==INF) P[v]=0;
    }

    void output(){
        rep(i, si(G)){
            for(auto& e : G[i]){
                if(e.isrev) continue;
                auto& rev_e=G[e.to][e.rev];
                cout<<i<<"->"<<e.to<<" (flow: "<<rev_e.cap<<"/"
                    <<rev_e.cap+e.cap<<")"<<endl;
            }
        }
    }
};