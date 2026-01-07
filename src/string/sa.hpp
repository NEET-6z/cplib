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