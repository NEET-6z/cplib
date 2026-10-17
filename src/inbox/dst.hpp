#include "../template.hpp"

template<typename T,typename F> struct sptable {
    const F f;
    vector<vector<T>> a;
    vector<int> l;

    sptable(const vector<T>& v,F f):f(f){
        int m=0;
        while((1<<m)<=si(v)) ++m;
        a.resize(m,vector<T>(si(v),T()));
        rep(i,si(v)) a[0][i]=v[i];
        for(int i=1;i<m;i++){
            int s=1<<i;
            for(int j=0;j<si(v);j+=s*2){
                int t=min(j+s,(int)si(v));
                a[i][t-1]=v[t-1];

                for(int k=t-2;k>=j;k--) a[i][k]=f(v[k],a[i][k+1]);
                if(si(v)<=t) break;
                a[i][t]=v[t];
                int r=min(t+s,(int)si(v));
                for(int k=t+1;k<r;k++) a[i][k]=f(a[i][k-1],v[k]);
            }
        }
        l.resize(1<<m);
        for(int i=2;i<si(l);i++) l[i]=l[i>>1]+1;
    }

    T query(int x,int y){
        if(x>=--y) return a[0][x];
        int p=l[x^y];
        return f(a[p][x],a[p][y]);
    }
};