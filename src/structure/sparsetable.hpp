#pragma once
#include "../template.hpp"

template<typename T> struct SparseTable {
    function<T(T,T)> f;
    vector<vector<T>> st;
    vector<int> bt;
    SparseTable(const vector<T> v={T{}},
                const function<T(T,T)>& f_=[] (T a,T b){return min(a,b);}):
        f(f_){
        int n=si(v);
        bt.resize(n+1,0);
        for(int i=2;i<=n;i++){
            bt[i]=bt[i>>1]+1;
        }
        int l=bt[n]+1;
        st.resize(l,vector<T>(n));
        st[0]=v;
        rep(k,l-1){
            rep(i,n-(1<<(k+1))+1){st[k+1][i]=f(st[k][i],st[k][i+(1<<k)]);}
        }
    }
    T prod(int l,int r){
        int k=bt[r-l];
        return f(st[k][l],st[k][r-(1<<k)]);
    }
};
