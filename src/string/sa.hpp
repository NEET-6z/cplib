#pragma once
#include "../template.hpp"

vector<int> suffix_array(string S){
    int N=si(S);
    vector<int> rank(N+1),tmp(N+1),sa(N+1);
    rep(i,N+1){
        sa[i]=i;
        rank[i]=i<N?S[i]:-1;
    }
    for(int k=1;k<=N;k*=2){
        auto comp=[&](int i,int j) {
            if(rank[i]!=rank[j]) return rank[i]<rank[j];
            int ri=(i+k<=N)?rank[i+k]:-1;
            int rj=(j+k<=N)?rank[j+k]:-1;
            return ri<rj;
        };
        sort(all(sa),comp);
        tmp[sa[0]]=0;
        for(int i=1;i<=N;i++){
            tmp[sa[i]]=tmp[sa[i-1]]+(comp(sa[i-1],sa[i])?1:0);
        }
        rep(i,N+1){
            rank[i]=tmp[i];
        }
    }
    sa.erase(sa.begin());
    return sa;
}

vector<int> lcp_array(string S,vector<int> sa){
    int n=si(S);
    vector<int> rsa(n,0),lcp(n,0);
    rep(i,n) rsa[sa[i]]=i;
    int h=0;
    rep(i,n-1){
        int p=sa[rsa[i]];
        if(h>0) h--;
        for(;p+h<n&&i+h<n;++h){
            if(S[p+h]!=S[i+h]) break;
        }
        lcp[rsa[i]]=h;
    }
    lcp.pop_back();
    return lcp;
}
