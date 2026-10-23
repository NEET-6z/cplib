#pragma once
#include "../template.hpp"


template<class T>
vector<int> suffix_array(vector<T>& s){
    int n=s.size();
    assert(n>0);
    vector<int> sa(n);
    vector<T> rnk=s, tmp(n, 0);
    iota(sa.begin(), sa.end(), 0);
    for(int k=1;k<n;k<<=1){
        auto cmp=[&](int x, int y){
            if(rnk[x]!=rnk[y]) return rnk[x]<rnk[y];
            if(y+k>=n) return false;
            if(x+k>=n) return true;
            return rnk[x+k]<rnk[y+k];
        };
        sort(sa.begin(), sa.end(), cmp);
        tmp[sa[0]]=0;
        for(int i=1;i<n;i++) tmp[sa[i]]=tmp[sa[i-1]]+(cmp(sa[i-1], sa[i])?1:0);
        swap(tmp, rnk);
    }
    return sa;
}

template<class T>
vector<int> lcp_array(vector<T>& S, vector<int>& sa){
    int n=si(S);
    assert(n>0);
    vector<int> rsa(n, 0), lcp(n-1, 0);
    rep(i, n) rsa[sa[i]]=i;
    int h=0;
    rep(i, n){
        if(rsa[i]==0){
            h=0;
            continue;
        }
        int p=sa[rsa[i]-1];
        if(h>0) h--;
        while(p+h<n&&i+h<n&&S[p+h]==S[i+h]){
            h++;
        }
        lcp[rsa[i]-1]=h;
    }
    return lcp;
}
