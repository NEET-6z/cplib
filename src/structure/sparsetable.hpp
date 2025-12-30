#pragma once
#include "../template.hpp"

template<typename T> struct SparseTable {
    function<T(T,T)> f;
    vector<vector<int>> st;
    SparseTable(const vector<T> v={0},
                const function<T(T,T)>& f_=[] (T a,T b){return min(a,b);}):
        f(f_){
        int n=si(v);
        int l=32-__builtin_clz(n);
        st.resize(l,vector<T>(n));
        st[0]=v;
        rep(k,l-1){
            rep(i,n-(1<<(k+1))+1){st[k+1][i]=f(st[k][i],st[k][i+(1<<k)]);}
        }
    }
    T prod(int l,int r){
        int k=31-__builtin_clz(r-l);
        return f(st[k][l],st[k][r-(1<<k)]);
    }
};