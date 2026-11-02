#pragma once
#include "../template.hpp"

template<class K, class T>
struct IntervalSet {
    const K INF=numeric_limits<K>::max()/2;
    map<pair<K, K>, T> st;
    function<void(K, K, T, bool)> f;
    IntervalSet(function<void(K, K, T, bool)> f):f(f){ //true: add / false:erase
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
            f(a, b, v, 0);
            if(a<l){
                st[{a, l}]=v;
                f(a, l, v, 1);
            }
            if(r<b){
                st[{r, b}]=v;
                f(r, b, v, 1);
            }
        }
    }
    void insert(K l, K r, T v){
        if(l>=r) return;
        erase(l, r);

        { //valueが同じ区間が隣接した時マージするか
            auto it=st.lower_bound({l, -INF});
            if(it!=st.begin()&&prev(it)->fi.se==l&&prev(it)->se==v){
                auto prv=prev(it);
                l=prv->fi.fi;
                f(prv->fi.fi, prv->fi.se, prv->se, 0);
                st.erase(prv);
            }

            it=st.lower_bound({r, -INF});
            if(it!=st.end()&&it->fi.fi==r&&it->se==v){
                f(it->fi.fi, it->fi.se, it->se, 0);
                r=it->fi.se;
                st.erase(it);
            }
        }
        st[{l, r}]=v;
        f(l, r, v, 1);
    }
    bool in(K x){
        auto it=--st.upper_bound({x, INF});
        return x<it->fi.se;
    }
};
