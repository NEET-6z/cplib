#include "../template.hpp"

extern "C" const char* __asan_default_options(){
    return "detect_leaks=0";
}
template <class S, auto op, auto e, class F, auto mpp, auto cmpo, auto id>
struct persistent_lazy_segtree {
    struct Node {
        S d;
        F lz;
        Node *l, *r;
    };
    using NP=Node*;


private:
    int n{};

    NP make_node(const S& d, const F& lz, NP l, NP r)const {
        return new Node{d, lz, l, r};
    }

    NP merge(NP l, NP r)const {return make_node(op(l->d, r->d), id(), l, r);}

    NP build(int l, int r, const vector<S>& v)const {
        if(l+1==r) return make_node(v[l], id(), nullptr, nullptr);
        NP lp=build(l, (l+r)/2, v);
        NP rp=build((l+r)/2, r, v);
        return merge(lp, rp);
    }
    NP all_apply(NP k, const F& f)const {
        return make_node(mpp(f, k->d), cmpo(f, k->lz), k->l, k->r);
    }
    NP push(NP k)const {
        if(k->l==nullptr) return k;
        assert(k->r!=nullptr);
        if(k->lz==id()) return k;
        NP nl=all_apply(k->l, k->lz);
        NP nr=all_apply(k->r, k->lz);
        return make_node(k->d, id(), nl, nr);
    }
    NP apply(int a, int b, const F& f, NP k, int l, int r)const {
        if(r<=a||b<=l) return k;
        if(a<=l&&r<=b) return all_apply(k, f);
        k=push(k);
        NP nl=apply(a, b, f, k->l, l, (l+r)>>1);
        NP nr=apply(a, b, f, k->r, (l+r)>>1, r);
        return merge(nl, nr);
    }


    NP set(int a, const S& x, NP k, int l, int r)const {
        if(r<=a||a+1<=l) return k;
        if(a<=l&&r<=a+1) return make_node(x, id(), nullptr, nullptr);
        k=push(k);
        return merge(set(a, x, k->l, l, (l+r)>>1), set(a, x, k->r, (l+r)>>1, r));
    }

    S prod(int a, int b, NP k, int l, int r, const F& carry)const {
        if(r<=a||b<=l) return e();
        if(a<=l&&r<=b) return mpp(carry, k->d);
        F next=cmpo(carry, k->lz);
        return op(prod(a, b, k->l, l, (l+r)>>1, next), prod(a, b, k->r, (l+r)>>1, r, next));
    }

public:
    persistent_lazy_segtree() = default;

    explicit persistent_lazy_segtree(int n):n(n){
    }

    NP build(const vector<S>& v)const {
        assert(n==si(v));
        assert(n>=1);
        return build(0, n, v);
    }

    NP set(NP t, int k, const S& x)const {
        assert(0<=k&&k<n);
        return set(k, x, t, 0, n);
    }
    NP apply(NP t, int l, int r, const F& f)const {
        return apply(l, r, f, t, 0, n);
    }

    S get(NP t, int k)const {
        return prod(k, k+1, t, 0, n, id());
    }


    S prod(NP t, int l, int r)const {
        return prod(l, r, t, 0, n, id());
    }
};
