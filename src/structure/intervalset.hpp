#pragma once
#include "../template.hpp"

template<class K, class T>
struct IntervalSet {
    const K INF=numeric_limits<K>::max()/2;
    map<pair<K, K>, T> st;
    function<void(K,K,T,bool)> f;
    IntervalSet(function<void(K,K,T,bool)> f): f(f) { //true: add / false:erase
        st[{-INF, -INF}]=T();
        st[{INF, INF}]=T();
    };
    void erase(K l, K r){
        if(l>=r) return;
        auto it=--st.lower_bound({l, -INF});
        if(it->fi.se<=l) it++;
        while(it->fi.fi<r){
            auto [k, v]=*it;
            auto [a, b]=k;
            it=st.erase(it);
            f(a,b,v,0);
            if(a<l) {
                st[{a,l}]=v;
                f(a,l,v,1);
            }
            if(r<b) {
                st[{r,b}]=v;
                f(r,b,v,1);
            }
        }
    }
    void insert(K l, K r, T v){
        if(l>=r) return;
        erase(l, r);
        st[{l,r}]=v;
        f(l,r,v,1);
    }
    bool in(K x){
        auto it=--st.lower_bound({x+1, -INF});
        return x<it->fi.se;
    }
};
