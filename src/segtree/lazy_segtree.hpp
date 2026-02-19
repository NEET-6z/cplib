#pragma once
#include "../template.hpp"

template<class S,S (*op)(S,S),S (*e)(),class F,S (*mpp)(F,S),F (*cmpo)(F,F),F (*id)()>
class lazy_segtree {
    int n,log;
    vector<S> d;
    vector<F> lz;
    void update(int k){d[k]=op(d[2*k],d[2*k+1]);}
    void all_apply(int k,F f){
        d[k]=mpp(f,d[k]);
        if(k<n) lz[k]=cmpo(f,lz[k]);
    }
    void push(int k){
        all_apply(2*k,lz[k]);
        all_apply(2*k+1,lz[k]);
        lz[k]=id();
    }
    void PUSH(int k){
        for(int i=log;--i;) push(k>>i);
    }
public:
    lazy_segtree():lazy_segtree(1){}
    explicit lazy_segtree(int n):lazy_segtree(vector<S>(n,e())){}
    explicit lazy_segtree(const vector<S> &v):
        n(__bit_ceil(si(v))),
        log(__countr_zero(n)),
        d(2*n,e()),
        lz(2*n,id()){
        rep(i,si(v)) d[n+i]=v[i];
        for(int i=n;--i;) update(i);
    }
    void set(int p,S x){
        p+=n;
        PUSH(p);
        d[p]=x;
        for(int i=1;i<=log;i++) update(p>>i);
    }
    S get(int p){
        p+=n;
        PUSH(p);
        return d[p];
    }
    S prod(int l,int r){
        if(l==r) return e();
        l+=n,r+=n;
        for(int i=log+1;--i;){
            if(((l>>i)<<i)!=l) push(l>>i);
            if(((r>>i)<<i)!=r) push((r-1)>>i);
        }
        S sml=e(),smr=e();
        for(;l<r;l>>=1,r>>=1){
            if(l&1) sml=op(sml,d[l++]);
            if(r&1) smr=op(d[--r],smr);
        }
        return op(sml,smr);
    }
    void apply(int p,F f){
        p+=n;
        PUSH(p);
        d[p]=mpp(f,d[p]);
        for(int i=1;i<=log;i++) update(p>>i);
    }
    void apply(int l,int r,F f){
        if(l==r) return;
        l+=n,r+=n;

        for(int i=log+1;--i;){
            if(((l>>i)<<i)!=l) push(l>>i);
            if(((r>>i)<<i)!=r) push((r-1)>>i);
        }
        int ml=l,mr=r;
        for(;l<r;l>>=1,r>>=1){
            if(l&1) all_apply(l++,f);
            if(r&1) all_apply(--r,f);
        }
        l=ml,r=mr;
        for(int i=1;i<=log;i++){
            if(((l>>i)<<i)!=l) update(l>>i);
            if(((r>>i)<<i)!=r) update((r-1)>>i);
        }
    }
};