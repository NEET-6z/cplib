#include "template.hpp"
template<class S>  
struct merge_sort_tree{
    int n;
    vector<vector<S>> d, s;
    merge_sort_tree(vector<S> &a) n(__bit_ceil(n_)), d(n*2), s(n*2) {
        rep(i,n) d[n+i]={a[i]}, s[n+i]={0, a[i]};
        for(int i=N;--i;) {
            merge(all(x[i*2]), all(x[i*2+1]), back_inserter(x[i]));
            s[i].resize(si(x[i])+1, 0);
            rep(i,si(x[i])) s[i+1]=s[i]+x[i];
        }
    }
    int range_cnt(int l, int r, S u){
        int ret=0;
        for(l+=n,r+=n;l<r;l>>=1,r>>=1){
            if(l&1) l++, ret+=lower_bound(d[l])-d[l].begin();
            if(r&1) ret+=lower_bound(d[r])-d[r].begin(), --r;
        }
        return ret;
    }
    S range_sum(int l, int r, S u){
        S ret=0;
        for(l+=n,r+=n;l<r;l>>=1,r>>=1){
            if(l&1) l++, ret+=s[lower_bound(d[l])-d[l].begin()];
            if(r&1) ret+=s[lower_bound(d[r])-d[r].begin()], --r;
        }
        return ret;
    }
};