#pragma once
#include "template.hpp"

template<class S, bool EnableSum = 0> struct merge_sort_tree {
    int n;
    vector<vector<S>> d, s;
    merge_sort_tree(vector<S>& a): n(__bit_ceil(si(a))), d(n * 2), s(n * 2) {
        rep(i, si(a)) d[n + i] = {a[i]}, s[n + i] = {S(), a[i]};
        for(int i = n; --i;) {
            merge(all(d[i * 2]), all(d[i * 2 + 1]), back_inserter(d[i]));
            if(!EnableSum) continue;
            s[i].resize(si(d[i]) + 1, S());
            rep(j, si(d[i])) s[i][j + 1] = s[i][j] + d[i][j];
        }
    }
    int range_cnt(int l, int r, S& u) {
        int ret = 0;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l & 1) ret += lower_bound(all(d[l]), u) - d[l].begin(), l++;
            if(r & 1) --r, ret += lower_bound(all(d[r]), u) - d[r].begin();
        }
        return ret;
    }
    S range_sum(int l, int r, S& u) {
        assert(EnableSum);
        S ret = 0;
        for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if(l & 1) ret += s[l][lower_bound(all(d[l]), u) - d[l].begin()], l++;
            if(r & 1) --r, ret += s[r][lower_bound(all(d[r]), u) - d[r].begin()];
        }
        return ret;
    }
};