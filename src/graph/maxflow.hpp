#include "../template.hpp"

template<class Cap> struct maxflow {
    struct edge {
        int to,rev;
        Cap cap;
        bool isr;
    };
    int n;
    vector<vector<edge>> g;
    vector<int> level,iter;
    maxflow(int n_):n(n_),g(n),level(n),iter(n){}
    void add_edge(int fr,int to,Cap cap){
        int a=si(g[fr]),b=si(g[to]);
        g[fr].push_back({to,b,cap,0});
        g[to].push_back({fr,a,0,1});
    }
    bool bfs(int s,int t){
        fill(all(level),-1);
        queue<int> q;
        level[s]=0;
        q.push(s);
        while(si(q)){
            int v=q.front();
            q.pop();
            for(auto& e:g[v]) if(e.cap>0&&level[e.to]<0){
                level[e.to]=level[v]+1;
                if(e.to==t) return true;
                q.push(e.to);
            }
        }
        return level[t]>=0;
    }
    Cap dfs(int v,int t,Cap f){
        if(v==t) return f;
        for(int& i=iter[v];i<si(g[v]);i++){
            edge& e=g[v][i];
            if(e.cap<=0||level[v]>=level[e.to]) continue;
            Cap d=dfs(e.to,t,min(f,e.cap));
            if(d<=0) continue;
            e.cap-=d;
            g[e.to][e.rev].cap+=d;
            return d;
        }
        return 0;
    }
    Cap flow(int s,int t){
        Cap ret=0,inf=numeric_limits<Cap>::max()/2;
        while(bfs(s,t)){
            fill(all(iter),0);
            while(true){
                Cap f=dfs(s,t,inf);
                if(f==0) break;
                ret+=f;
            }
        }
        return ret;
    }
    vector<int> mincut(int s){
        vector<int> vis(n);
        queue<int> q;
        vis[s]=1;
        q.push(s);
        while(si(q)){
            int v=q.front();
            q.pop();
            for(auto& e:g[v]) if(e.cap>0&&!vis[e.to]){
                vis[e.to]=1;
                q.push(e.to);
            }
        }
        return vis;
    }
};
