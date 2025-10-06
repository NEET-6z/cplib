#include "template.hpp"

template<typename T> struct dsu_weighted {
    vector<int> p;
    vector<T> w;
    dsu_weighted(int n): p(n, -1), w(n, 0) {}
    bool same(int a, int b) { return leader(a) == leader(b); }
    int leader(int a) {
        return p[a] < 0 ? a : (leader(p[a]), w[a] += w[p[a]], p[a] = leader(p[a]));
    }
    int size(int a) { return -p[leader(a)]; }
    int merge(int a, int b, long c) {
        c += weight(a), c -= weight(b);
        a = leader(a), b = leader(b);
        if(a == b) return a;
        if(p[a] > p[b]) swap(a, b), c *= -1;
        p[a] += p[b];
        p[b] = a;
        w[b] = c;
        return a;
    }
    T weight(int a) {
        leader(a);
        return w[a];
    }
};