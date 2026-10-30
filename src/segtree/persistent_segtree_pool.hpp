#include "../template.hpp"

template <class S, auto op, auto e>
struct persistent_segtree {
    struct Node {
        S d;
        int l, r;
    };
    using NP=int;
private:
    int n{};
    vector<Node> pl;

    NP make_node(const S& d, NP l, NP r){
        pl.push_back(Node{d, l, r});
        return si(pl)-1;
    }

    NP merge(NP l, NP r){return make_node(op(pl[l].d, pl[r].d), l, r);}


    NP build(int l, int r, const vector<S>& v){
        if(l+1==r) return make_node(v[l], -1, -1);
        NP lp=build(l, (l+r)/2, v);
        NP rp=build((l+r)/2, r, v);
        return merge(lp, rp);
    }

    NP set(int a, const S& x, NP k, int l, int r){
        if(r<=a||a+1<=l) return k;
        if(a<=l&&r<=a+1) return make_node(x, -1, -1);
        return merge(set(a, x, pl[k].l, l, (l+r)>>1), set(a, x, pl[k].r, (l+r)>>1, r));
    }

    NP apply(int a, const S& x, NP k, int l, int r){
        if(r<=a||a+1<=l) return k;
        if(a<=l&&r<=a+1) return make_node(op(pl[k].d, x), -1, -1);
        return merge(apply(a, x, pl[k].l, l, (l+r)>>1), apply(a, x, pl[k].r, (l+r)>>1, r));
    }

    S prod(int a, int b, NP k, int l, int r)const {
        if(r<=a||b<=l) return e();
        if(a<=l&&r<=b) return pl[k].d;
        return op(prod(a, b, pl[k].l, l, (l+r)>>1), prod(a, b, pl[k].r, (l+r)>>1, r));
    }

    template <class F>
    int max_right_(int a, F& f, S& acc, NP k, int l, int r)const {
        if(r<=a) return n;
        if(a<=l){
            S nx=op(acc, pl[k].d);
            if(f(nx)){
                acc=nx;
                return n;
            }
            if(l+1==r) return l;
        }
        int m=(l+r)>>1;
        int res=max_right_(a, f, acc, pl[k].l, l, m);
        if(res!=n) return res;
        return max_right_(a, f, acc, pl[k].r, m, r);
    }

    template <class F>
    int min_left_(int b, F& f, S& acc, NP k, int l, int r)const {
        if(b<=l) return -1;
        if(r<=b){
            S nx=op(pl[k].d, acc);
            if(f(nx)){
                acc=nx;
                return -1;
            }
            if(l+1==r) return l;
        }
        int m=(l+r)>>1;
        int res=min_left_(b, f, acc, pl[k].r, m, r);
        if(res!=-1) return res;
        return min_left_(b, f, acc, pl[k].l, l, m);
    }
public:
    persistent_segtree() = default;

    explicit persistent_segtree(int n):n(n){}

    NP build(const vector<S>& v){
        assert(n==si(v));
        assert(n>=1);
        return build(0, n, v);
    }

    NP set(NP t, int k, const S& x){
        return set(k, x, t, 0, n);
    }

    S get(NP t, int k)const {
        int l=0, r=n;
        while(l+1<r){
            int p=(l+r)/2;
            if(k<p){
                t=pl[t].l;
                r=p;
            }
            else{
                t=pl[t].r;
                l=p;
            }
        }
        return pl[t].d;
    }

    NP apply(NP t, int k, const S& x){
        return apply(k, x, t, 0, n);
    }

    S prod(NP t, int l, int r)const {
        return prod(l, r, t, 0, n);
    }

    S all_prod(NP t)const {return pl[t].d;}

    template <class F>
    int max_right(NP t, int l, F f)const {
        assert(0<=l&&l<=n);
        S acc=e();
        assert(f(acc));
        if(l==n) return n;
        return max_right_(l, f, acc, t, 0, n);
    }

    template <class F>
    int min_left(NP t, int r, F f)const {
        assert(0<=r&&r<=n);
        S acc=e();
        assert(f(acc));
        if(r==0) return 0;
        return min_left_(r, f, acc, t, 0, n)+1;
    }
};
