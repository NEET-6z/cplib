#pragma once
#include "../template.hpp"

//https://github.com/KentaroMatsushita/icpc_library
template<class T> struct fenwick_tree {
    vector<T> a;
    fenwick_tree():a(1){}
    fenwick_tree(int n):a(n+1){}
    void add(int i, T x){
        for(i++;i<si(a);) a[i]+=x, i+=i& -i;
    }
    T sum(int r){
        T s=0;
        while(r) s+=a[r], r-=r& -r;
        return s;
    }
    T sum(int l, int r){return sum(r)-sum(l);}

    int lower_bound(T w){
        int x=0, N=si(a)-1;
        for(int k=1<<__lg(N);k;k>>=1){
            if(x+k<=N&&a[x+k]<w){
                w-=a[x+k];
                x+=k;
            }
        }
        return x+1;
    }
};