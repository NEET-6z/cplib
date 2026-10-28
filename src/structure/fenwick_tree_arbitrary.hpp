#include "../template.hpp"

template<class G>
struct fenwick_tree_arbitrary {
    using T=typename G::T;
    vector<T> a;
    fenwick_tree_arbitrary():fenwick_tree_arbitrary(1){}
    fenwick_tree_arbitrary(int n):a(n+1, G::id()){}
    void add(int i, T x){
        for(i++;i<si(a);i+=i& -i)
            a[i]=G::op(a[i], x);
    }
    T sum(int r){
        T s=G::id();
        for(;r;r-=r& -r)
            s=G::op(s, a[r]);
        return s;
    }
    T sum(int l, int r){
        return G::op(sum(r), G::inv(sum(l)));
    }
    template<class Comp=less<T>>
    int lower_bound(T w, Comp comp=Comp{}){
        if(!comp(G::id(), w)) return 0;
        int x=0, k=1;
        while(k<si(a)) k<<=1;
        T s=G::id();
        for(;k;k>>=1){
            if(x+k<si(a)){
                T ns=G::op(s, a[x+k]);
                if(comp(ns, w)){
                    s=ns;
                    x+=k;
                }
            }
        }
        return x+1;
    }
};

/*
struct AddGroup {
    using T = long;
    static T id() { return 0; }
    static T op(T a, T b) { return a + b; }
    static T inv(T a) { return -a; }
};
*/