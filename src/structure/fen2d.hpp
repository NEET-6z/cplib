#include "fenwick_tree.hpp"

template<typename K,typename T>
struct Fen2D {
    int n;
    vector<pair<K,K>> ps;
    vector<K> xz;
    vector<vector<int>> ys;
    vector<fenwick_tree<T>> bit;

    void add_point(K x,K y){
        ps.emplace_back(x,y);
    }
    void build(){
        xz.resize(si(ps));
        rep(i,si(ps)) xz[i]=ps[i].fi;
        sort(all(xz));
        xz.erase(unique(all(xz)),xz.end());
        n=si(xz);
        bit.resize(n+1);
        ys.resize(n+1);
        sort(all(ps));
        for(int i=0,j=0;i<n;i++) for(;j<si(ps)&&ps[j].fi<=xz[i];ps[j++].fi=i);
        for(auto &[x,y]: ps) for(int i=x+1;i<=n;i+=i& -i) ys[i].push_back(y);
        for(int i=1;i<=n;i++){
            sort(all(ys[i]));
            ys[i].erase(unique(all(ys[i])),ys[i].end());
            bit[i]=fenwick_tree<T>(si(ys[i]));
        }
    }
    void add(K x,K y,T w){
        x=lower_bound(all(xz),x)-xz.begin();
        for(int i=x+1;i<=n;i+=i& -i){
            int j=lower_bound(all(ys[i]),y)-ys[i].begin();
            bit[i].add(j,w);
        }
    }
    T sum(K x,K y){
        x=lower_bound(all(xz),x)-xz.begin();
        T s=0;
        for(;x;x-=x& -x){
            int j=lower_bound(ys[x].begin(),ys[x].end(),y)-ys[x].begin();
            s+=bit[x].sum(j);
        }
        return s;
    }
    T sum(K l,K r,K d,K u){
        return sum(r,u)-sum(l,u)-sum(r,d)+sum(l,d);
    }
};
