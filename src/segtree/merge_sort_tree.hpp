#pragma once
#include "../template.hpp"

template<class S> struct merge_sort_tree {
    int n;
    vector<vector<S>> d;
    merge_sort_tree(vector<S>& a){
        n=1;
        while(n<si(a)) n<<=1;
        d.resize(n*2);
        rep(i, si(a)) d[n+i]={a[i]};
        for(int i=n;--i;){
            merge(all(d[i*2]), all(d[i*2+1]), back_inserter(d[i]));
        }
    }
    int range_cnt(int l, int r, S& u){
        int ret=0;
        for(l+=n, r+=n;l<r;l>>=1, r>>=1){
            if(l&1) ret+=lbi(d[l], u), l++;
            if(r&1) --r, ret+=lbi(d[r], u);
        }
        return ret;
    }
};
