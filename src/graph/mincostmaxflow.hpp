#include "../template.hpp"

struct MCMF {
    const long INF=numeric_limits<long>::max()/4;
    struct E {
        int to, rev;
        long cap, cost, flow;
    };
    int n;
    vector<vector<E>> g;
    vector<long> d, h;
    vector<E*> p;
    vector<int> vis;

    MCMF(int n):n(n), g(n), d(n), h(n), p(n), vis(n){}

    void add_edge(int s, int t, long cap, long cost){
        if(s==t) return;
        g[s].push_back({t, (int)g[t].size(), cap, cost, 0});
        g[t].push_back({s, (int)g[s].size()-1, 0, -cost, 0});
    }

    //負の辺がある場合
    void setpi(int s){
        fill(all(h), INF);
        h[s]=0;
        bool upd=true;
        rep(_, n){
            if(!upd) break;
            upd=false;
            rep(v, n) if(h[v]!=INF){
                for(auto& e:g[v]) if(e.cap&&h[e.to]>h[v]+e.cost){
                        h[e.to]=h[v]+e.cost;
                        upd=true;
                    }
            }
        }
        assert(!upd);
        for(auto& x:h) if(x==INF) x=0;
    }

    bool path(int s, int t){
        fill(all(d), INF);
        fill(all(p), nullptr);
        fill(all(vis), 0);
        using P=pair<long, int>;
        priority_queue<P, vector<P>, greater<P>> q;
        d[s]=0;
        q.push({0, s});
        while(!q.empty()){
            auto [x, v]=q.top();q.pop();
            if(vis[v]) continue;
            vis[v]=1;
            for(auto& e:g[v]){
                long nd=x+e.cost+h[v]-h[e.to];
                if(e.cap>e.flow&&nd<d[e.to]){
                    d[e.to]=nd;
                    p[e.to]=&e;
                    q.push({nd, e.to});
                }
            }
        }
        if(d[t]==INF) return false;
        rep(v, n) if(d[v]!=INF) h[v]+=d[v];
        return true;
    }

    pair<long, long> maxflow(int s, int t){
        long f=0, c=0;
        while(path(s, t)){
            long add=INF;
            for(int v=t;v!=s;v=g[v][p[v]->rev].to)
                add=min(add, p[v]->cap-p[v]->flow);
            f+=add;
            c+=add*(h[t]-h[s]);
            for(int v=t;v!=s;v=g[v][p[v]->rev].to){
                E* e=p[v];
                e->flow+=add;
                g[v][e->rev].flow-=add;
            }
        }
        return {f, c};
    }
};