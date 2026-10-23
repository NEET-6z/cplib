#include "../template.hpp"

template<typename T> struct dsu_w {
    vector<int> p;
    vector<T> w;
    dsu_w(int n):p(n, -1), w(n, T(0)){}
    bool same(int a, int b){return leader(a)==leader(b);}
    int leader(int a){
        if(p[a]<0) return a;
        int r=leader(p[a]);
        w[a]+=w[p[a]];
        return p[a]=r;;
    }
    int size(int a){return -p[leader(a)];}
    int merge(int a, int b, T c){       //w[a]+c=w[b]
        c+=weight(a), c-=weight(b);
        a=leader(a), b=leader(b);
        if(a==b) return a;
        if(p[a]>p[b]) swap(a, b), c=-c;
        p[a]+=p[b];
        p[b]=a;
        w[b]=c;
        return a;
    }
    T weight(int a){
        leader(a);
        return w[a];
    }
};