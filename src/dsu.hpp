#include "template.hpp"

struct dsu {
    vector<int> p;
    dsu(int n): p(n, -1) {}
    bool same(int a, int b) { return leader(a) == leader(b); }
    int leader(int a) { return p[a] < 0 ? a : p[a] = leader(p[a]); }
    int size(int a) { return -p[leader(a)]; }
    int merge(int a, int b) {
        a = leader(a), b = leader(b);
        if(a == b) return a;
        if(p[a] > p[b]) swap(a, b);
        p[a] += p[b];
        p[b] = a;
        return a;
    }
};