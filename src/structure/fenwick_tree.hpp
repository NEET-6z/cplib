#pragma once
#include "../template.hpp"

template<class T> struct fenwick_tree {
    vector<T> a;
    fenwick_tree():a(1,0){}
    fenwick_tree(int n):a(n+1,0){}
    void add(int i,T x){
        for(i++;i<si(a);i+=i&-i) a[i]+=x;
    }
    T sum(int r){
        T s=0;
        for(;r;r-=r& -r) s+=a[r];
        return s;
    }
    T sum(int l,int r){return sum(r)-sum(l);}

    int lower_bound(T w){
        if(w<=0) return 0;
        int x=0,k=1;
        while(k<si(a))k<<=1;
        for(;k;k>>=1){
            if(x+k<si(a)&&a[x+k]<w){
                w-=a[x+k];
                x+=k;
            }
        }
        return x+1;
    }
};