#include "../template.hpp"

template <class E, class S, S (*merge)(S, S), S (*up)(S, E), S (*id)()>
struct ReRooting {
    ReRooting(int N){
        this->N=N;
        this->G.resize(N);
    };

    void add_edge(E e){G[e.from].push_back(e);}

    void dfs1(int v, int p=-1){
        S res=id();
        for(E e : G[v]){
            if(e.to==p) continue;
            dfs1(e.to, v);
            res=merge(res, up(dp1[e.to], e));
        }
        dp1[v]=res;
        return;
    }

    void dfs2(int v, int p=-1){
        int cn=si(G[v]);

        vector<S> prodl(cn+1, id()), prodr(cn+1, id());
        for(int i=1;i<=cn;i++){
            if(G[v][i-1].to==p)
                prodl[i]=merge(prodl[i-1], dp2[v]);
            else
                prodl[i]=
                    merge(prodl[i-1], up(dp1[G[v][i-1].to], G[v][i-1]));
        }

        for(int i=cn-1;i>=0;i--){
            if(G[v][i].to==p)
                prodr[i]=merge(prodr[i+1], dp2[v]);
            else
                prodr[i]=merge(prodr[i+1], up(dp1[G[v][i].to], G[v][i]));
        }

        for(int i=0;i<cn;i++){
            if(G[v][i].to==p) continue;
            E e=G[v][i];
            swap(e.from, e.to);
            dp2[G[v][i].to]=up(merge(prodl[i], prodr[i+1]), e);
            dfs2(G[v][i].to, v);
        }
    }

    void build(){
        dp1.assign(N, id());
        dp2.assign(N, id());

        dfs1(0);
        dfs2(0);
    }

    S query(int a){return merge(dp1[a], dp2[a]);}

    int N;
    vector<vector<E>> G;
    vector<S> dp1;
    vector<S> dp2;
};

// vector<long> A;
// struct E {
//     int to, from;
// };
// struct S {
//     long sum;
// };

// S merge(S a, S b){return S{a.sum+b.sum};}
// S up(S a, E e){return S{max(0l, a.sum+A[e.to]+A[e.from])};}
// S id(){return S{0};};
