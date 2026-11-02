#include "../template.hpp"
extern "C" const char* __asan_default_options(){
    return "detect_leaks=0";
}

template<class K, class S, auto op, auto e, class F, auto mpp, auto cmpo, auto id>
struct Treap {
    struct Node {
        K key;S val, sum;F lz=id();int sz=1;unsigned pri=rng();Node *l=0, *r=0;
        Node(K k, S x):key(k), val(x), sum(x){}
        static unsigned rng(){static mt19937 g(random_device{}());return g();}
    };
    using P=Node*;
    P root=0;

    static int sz(P t){return t?t->sz:0;}
    static S sm(P t){return t?t->sum:e();}
    static void upd(P t){
        t->sz=sz(t->l)+1+sz(t->r);
        t->sum=op(op(sm(t->l), t->val), sm(t->r));
    }
    static void apply(P t, const F& f){
        if(!t) return;
        t->val=mpp(t->val, f);t->sum=mpp(t->sum, f);
        t->lz=cmpo(f, t->lz);
    }
    static void push(P t){
        if(t->lz!=id()){apply(t->l, t->lz);apply(t->r, t->lz);t->lz=id();}
    }
    static P mg(P a, P b){
        if(!a||!b) return a?a:b;
        if(a->pri>b->pri){push(a);a->r=mg(a->r, b);upd(a);return a;}
        push(b);b->l=mg(a, b->l);upd(b);return b;
    }
    static void sp(P t, K k, P& a, P& b){
        if(!t){a=b=0;return;}
        push(t);
        if(t->key<k){a=t;sp(t->r, k, t->r, b);}
        else{b=t;sp(t->l, k, a, t->l);}
        upd(t);
    }
    static P er(P t, K k){
        if(!t) return 0;
        push(t);
        if(t->key==k) return mg(t->l, t->r);
        if(k<t->key) t->l=er(t->l, k);
        else t->r=er(t->r, k);
        upd(t);return t;
    }

    static Treap join(Treap l, Treap r){Treap t;t.root=mg(l.root, r.root);return t;}
    pair<Treap, Treap> split(K k){Treap a, b;sp(root, k, a.root, b.root);root=0;return {a, b};}

    void insert(K k, S x){P a, b;root=er(root, k);sp(root, k, a, b);root=mg(mg(a, new Node(k, x)), b);}
    void erase(K k){root=er(root, k);}
    S* find(K k){
        P t=root;
        while(t&&!(t->key==k)){push(t);t=k<t->key?t->l:t->r;}
        return t?&t->val:0;
    }
    P at(int k){
        P t=root;
        for(;;){
            push(t);
            int s=sz(t->l);
            if(k==s) return t;
            if(k<s) t=t->l;
            else k-=s+1, t=t->r;
        }
    }
    int lower_bound(K k){
        int r=0;
        for(P t=root;t; ){
            if(t->key<k) r+=sz(t->l)+1, t=t->r;
            else t=t->l;
        }
        return r;
    }
    int upper_bound(K k){
        int r=0;
        for(P t=root;t; ){
            if(!(k<t->key)) r+=sz(t->l)+1, t=t->r;
            else t=t->l;
        }
        return r;
    }
    S fold(K l, K r){
        P a, b, c;
        sp(root, l, a, b);sp(b, r, b, c);
        S ret=sm(b);
        root=mg(mg(a, b), c);
        return ret;
    }
    void update(K l, K r, F f){
        P a, b, c;
        sp(root, l, a, b);sp(b, r, b, c);
        apply(b, f);
        root=mg(mg(a, b), c);
    }
    S all_prod(){return sm(root);}
    int size(){return sz(root);}
    bool empty(){return !root;}

    template<class G> int max_right(K l, G f){
        P a, b;
        sp(root, l, a, b);
        int r=sz(a);
        S acc=e();
        for(P t=b;t; ){
            push(t);
            S x=op(acc, sm(t->l));
            if(!f(x)){t=t->l;continue;}
            x=op(x, t->val);
            if(!f(x)){r+=sz(t->l);break;}
            acc=x;r+=sz(t->l)+1;t=t->r;
        }
        root=mg(a, b);
        return r;
    }
    template<class G> int min_left(K r, G f){
        P a, b;
        sp(root, r, a, b);
        int l=sz(a);
        S acc=e();
        for(P t=a;t; ){
            push(t);
            S x=op(sm(t->r), acc);
            if(!f(x)){t=t->r;continue;}
            x=op(t->val, x);
            if(!f(x)){l-=sz(t->r);break;}
            acc=x;l-=sz(t->r)+1;t=t->l;
        }
        root=mg(a, b);
        return l;
    }
};