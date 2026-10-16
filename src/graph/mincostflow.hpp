#include "../template.hpp"

template<class Cap,class Cost> struct mcf_graph {
    struct E {
        int to,rev;
        Cap cap;
        Cost cost;
        bool isr;
    };
    int n;
    vector<vector<E>> g;

    mcf_graph(int n=0):n(n),g(n){}

    void add_edge(int v,int to,Cap cap,Cost cost){
        assert(0<=cap&&0<=cost&&v!=to);
        g[v].push_back({to,(int)g[to].size(),cap,cost,false});
        g[to].push_back({v,(int)g[v].size()-1,0,-cost,true});
    }

    pair<Cap,Cost> flow(int s,int t,Cap lim=numeric_limits<Cap>::max()){
        Cap flow=0;
        Cost cost=0;
        vector<Cost> h(n),dist(n);
        vector<int> pv(n),pe(n);

        while(flow<lim){
            fill(dist.begin(),dist.end(),numeric_limits<Cost>::max());
            priority_queue<pair<Cost,int>,vector<pair<Cost,int>>,greater<pair<Cost,int>>> pq;
            dist[s]=0;
            pq.push({0,s});

            while(!pq.empty()){
                auto [d,v]=pq.top();
                pq.pop();
                if(dist[v]!=d) continue;
                for(int i=0;i<(int)g[v].size();i++){
                    E &e=g[v][i];
                    if(!e.cap) continue;
                    Cost nd=d+e.cost+h[v]-h[e.to];
                    if(dist[e.to]>nd){
                        dist[e.to]=nd;
                        pv[e.to]=v;
                        pe[e.to]=i;
                        pq.push({nd,e.to});
                    }
                }
            }

            if(dist[t]==numeric_limits<Cost>::max()) break;
            for(int v=0;v<n;v++)
                if(dist[v]<numeric_limits<Cost>::max()) h[v]+=dist[v];

            Cap add=lim-flow;
            for(int v=t;v!=s;v=pv[v]) add=min(add,g[pv[v]][pe[v]].cap);

            for(int v=t;v!=s;v=pv[v]){
                E &e=g[pv[v]][pe[v]];
                e.cap-=add;
                g[v][e.rev].cap+=add;
            }

            flow+=add;
            cost+=add*h[t];
        }

        return {flow,cost};
    }
    void output(){
        for(int v=0;v<n;v++){
            for(E& e : g[v]){
                if(!e.isr){
                    int from=v;
                    int to=e.to;
                    Cap amount=g[to][e.rev].cap;
                    cout<<from<<" -> "<<to<<" : "<<amount<<" ( "<<e.cost<<" )"<<endl;
                }
            }
        }
    }
};