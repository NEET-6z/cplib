#pragma once
#include "../template.hpp"

template<class S,auto op,auto e,class F,auto mpp,auto cmpo,auto id>
class lazy_segtree {
    int n,log;
    vector<S> d;
    vector<F> lz;
    void update(int k){d[k]=op(d[k*2],d[k*2+1]);}
    void all_apply(int k,F f){
        d[k]=mpp(f,d[k]);
        if(k<n) lz[k]=cmpo(f,lz[k]);
    }
    void push(int k){
        all_apply(k*2,lz[k]);
        all_apply(k*2+1,lz[k]);
        lz[k]=id();
    }
    void UPDATE(int k){
        for(int i=1;i<log;i++) update(k>>i);
    }
    void PUSH(int k){
        for(int i=log;--i;) push(k>>i);
    }
public:
    lazy_segtree(int n):lazy_segtree(vector<S>(n,e())){}
    lazy_segtree(vector<S> a){
        n=log=1;
        while(n<si(a)) n*=2,log++;
        d.resize(2*n,e());
        lz.resize(2*n,id());
        for(auto [i,v]:views::zip(views::iota(n),a)) d[i]=v;
        for(int i=n;--i;) update(i);
    }
    void set(int p,S x){
        p+=n;
        PUSH(p);
        d[p]=x;
        UPDATE(p);
    }
    S get(int p){
        p+=n;
        PUSH(p);
        return d[p];
    }
    S prod(int l,int r){
        if(l>=r) return e();
        l+=n,r+=n;
        for(int i=log;--i;){
            if((l>>i)<<i!=l) push(l>>i);
            if((r>>i)<<i!=r) push((r-1)>>i);
        }
        S sl=e(),sr=e();
        for(;l<r;l>>=1,r>>=1){
            if(l&1) sl=op(sl,d[l++]);
            if(r&1) sr=op(d[--r],sr);
        }
        return op(sl,sr);
    }
    void apply(int p,F f){
        p+=n;
        PUSH(p);
        d[p]=mpp(f,d[p]);
        UPDATE(p);
    }
    void apply(int l,int r,F f){
        if(l>=r) return;
        l+=n,r+=n;
        for(int i=log;--i;){
            if((l>>i)<<i!=l) push(l>>i);
            if((r>>i)<<i!=r) push((r-1)>>i);
        }
        int ml=l,mr=r;
        for(;l<r;l>>=1,r>>=1){
            if(l&1) all_apply(l++,f);
            if(r&1) all_apply(--r,f);
        }
        l=ml,r=mr;
        for(int i=1;i<log;i++){
            if((l>>i)<<i!=l) update(l>>i);
            if((r>>i)<<i!=r) update((r-1)>>i);
        }
    }
};