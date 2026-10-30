#pragma once
#include "segtree.hpp"

template<typename K, class S, S (*op)(S, S), S (*e)()> struct segtree_2d {
    int n;
    vector<segtree<S, op, e>> d;
    vector<K> xs;
    vector<vector<K>> ys;
    vector<pair<K, K>> xp;
    vector<vector<pair<K, K>>> yp;
    segtree_2d(){}
    void add_point(K x, K y){xp.push_back({x, y});}

    void build(){
        sort(all(xp));
        xp.erase(unique(all(xp)), xp.end());
        n=1;
        while(n<si(xp)) n<<=1;
        for(auto [x, y]:xp) xs.push_back(x);
        yp.resize(2*n);
        ys.resize(2*n);
        rep(i, si(xp)){
            yp[n+i]={make_pair(xp[i].se, xp[i].fi)};
            ys[n+i]={xp[i].se};
        }
        for(int i=n;--i;){
            merge(all(yp[i*2]), all(yp[i*2+1]), back_inserter(yp[i]));
            merge(all(ys[i*2]), all(ys[i*2+1]), back_inserter(ys[i]));
        }
        d.resize(2*n);
        for(int i=1;i<2*n;i++){
            d[i]=segtree<S, op, e>(si(yp[i]));
        }
    }

    void set(K x, K y, S v){
        int k=lbi(xp, make_pair(x, y));
        assert(k!=si(xp)&&xp[k].fi==x&&xp[k].se==y);
        for(k+=n;k;k>>=1){
            int id=lbi(yp[k], make_pair(y, x));
            assert(id!=si(yp[k]));
            d[k].set(id, v);
        }
    }
    S get(K x, K y){
        int k=lbi(xp, make_pair(x, y));
        assert(k!=si(xp)&&xp[k].fi==x&&xp[k].se==y);
        k+=n;
        int id=lbi(yp[k], make_pair(y, x));;
        assert(id!=si(yp[k]));
        return d[k].get(id);
    }
    void apply(K x, K y, S v){
        set(x, y, op(get(x, y), v));
    }

    S range(K lv, K rv, K dv, K uv){
        if(dv>=uv) return e();
        int l=lbi(xs, lv);
        int r=lbi(xs, rv);
        S sml=e(), smr=e();
        for(l+=n, r+=n;l<r;l>>=1, r>>=1){
            if(l&1){
                int li=lbi(ys[l], dv);
                int ri=lbi(ys[l], uv);
                sml=op(sml, d[l].prod(li, ri));
                l++;
            }
            if(r&1){
                --r;
                int li=lbi(ys[r], dv);
                int ri=lbi(ys[r], uv);
                smr=op(d[r].prod(li, ri), smr);
            }
        }
        return op(sml, smr);
    }
};
