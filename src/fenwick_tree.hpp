#pragma once
#include "template.hpp"

template<class T> struct fenwick_tree {
    vector<T> a;
    fenwick_tree(int n): a(n + 1, 0) {}
    void add(int i, T x) {
        i++;
        while(i < si(a)) a[i] += x, i += i & -i;
    }
    T sum(int r) {
        T s = 0;
        while(r) s += a[r], r -= r & -r;
        return s;
    }
    T sum(int l, int r) { return sum(r) - sum(l); }

    //sum(0,x+1)がw以上になるような最小のxを返す(各要素は正の数)
    int lower_bound(T w) {
        if(w <= 0) return 0;
        int x = 0, N = si(a) - 1;
        for(int k = 1 << __lg(N); k >>= 1;) {
            if(x + k <= N - 1 && a[x + k] < w) {
                w -= a[x + k];
                x += k;
            }
        }
        return x;
    }
};