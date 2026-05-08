#pragma once
#include "../template.hpp"


template<typename T> struct li_chao_tree {
    struct Line {
        T a,b;
        T get(T x) const {return a*x+b;}
    };
    int n;
    T INF;
    vector<T> xs;
    vector<Line> seg;
    li_chao_tree(const vector<T> &x,T inf):INF(inf){
        xs=x;
        assert(si(xs));
        sort(all(xs));
        xs.erase(unique(all(xs)),xs.end());
        n=1;
        while(n<si(xs)) n<<=1;
        xs.resize(n,xs.back());
        seg.assign(2*n,{0,INF});
    }
    void add_line(Line f){add_line(f,1,0,n);}
    void add_segment(Line f,T l,T r){
        int L=lower_bound(all(xs),l)-xs.begin();
        int R=lower_bound(all(xs),r)-xs.begin();
        add_segment(f,L,R,1,0,n);
    }
    T get(T x){
        int k=lower_bound(all(xs),x)-xs.begin();
        assert(k<n&&xs[k]==x);
        T ret=INF;
        for(k+=n;k;k>>=1) ret=min(ret,seg[k].get(x));
        return ret;
    }
    void add_line(Line f,int k,int l,int r){
        if(r-l<=0) return ;
        int m=(l+r)/2;
        T xl=xs[l],xm=xs[m],xr=xs[r-1];
        Line g=seg[k];
        bool lb=f.get(xl)<g.get(xl);
        bool mb=f.get(xm)<g.get(xm);
        bool rb=f.get(xr)<g.get(xr);
        if(mb){
            swap(seg[k],f);
            swap(g,f);
        }
        if(r-l==1) return;
        if(lb!=mb) add_line(f,k*2,l,m);
        if(rb!=mb) add_line(f,k*2+1,m,r);
    }
    void add_segment(Line f,int a,int b,int k,int l,int r){
        if(b<=l||r<=a) return;
        if(a<=l&&r<=b){
            add_line(f,k,l,r);
            return;
        }
        int m=(l+r)/2;
        add_segment(f,a,b,k*2,l,m);
        add_segment(f,a,b,k*2+1,m,r);
    }
};