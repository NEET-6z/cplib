#pragma once
#include "../template.hpp"

template<typename T> vector<int> z_algorithm(const T& S){
    int n=si(S);
    if(n==0) return {};
    vector<int> z(n);
    z[0]=n;
    for(int i=1,l=0,r=0;i<n;i++){
        if(i<r) z[i]=min(r-i,z[i-l]);
        while(i+z[i]<n and S[z[i]]==S[i+z[i]]) z[i]++;
        if(i+z[i]>r){
            l=i;
            r=i+z[i];
        }
    }
    return z;
}