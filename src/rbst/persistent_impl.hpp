#include "../template.hpp"

template<class S, int MAX_N=1000000>
struct Treap {
    struct Node {
        long sz=1;Node *l=0, *r=0;unsigned pri;S val;
        Node() = default;
        Node(S x):pri(rng()), val(x){}
        static unsigned rng(){static mt19937 g(random_device{}());return g();}
    };
    using P=Node*;
    inline static Node pool[MAX_N];
    inline static int ptr=0;
    static P new_node(S x){assert(ptr<MAX_N);P t=&pool[ptr++];*t=Node(x);return t;}
    static P clone(P t){assert(ptr<MAX_N);P n=&pool[ptr++];*n=*t;return n;}
    static void reset(){ptr=0;}
    P root=0;

    static long sz(P t){return t?t->sz:0;}
    static void upd(P t){t->sz=sz(t->l)+1+sz(t->r);}
    static P mg(P a, P b){
        if(!a||!b) return a?a:b;
        if(a->pri>b->pri){a=clone(a);a->r=mg(a->r, b);upd(a);return a;}
        b=clone(b);b->l=mg(a, b->l);upd(b);return b;
    }
    static void sp(P t, long k, P& a, P& b){
        if(!t){a=b=0;return;}
        if(k<=0){a=0;b=t;return;}
        if(k>=t->sz){a=t;b=0;return;}
        t=clone(t);
        if(k<=sz(t->l)){b=t;sp(t->l, k, a, t->l);}
        else{a=t;sp(t->r, k-sz(t->l)-1, t->r, b);}
        upd(t);
    }
    static P set_(P t, long k, const S& x){
        t=clone(t);
        long s=sz(t->l);
        if(k==s){t->val=x;return t;}
        if(k<s) t->l=set_(t->l, k, x);
        else t->r=set_(t->r, k-s-1, x);
        return t;
    }

    static Treap join(const Treap& l, const Treap& r){Treap t;t.root=mg(l.root, r.root);return t;}
    pair<Treap, Treap> split(long k)const {Treap a, b;sp(root, k, a.root, b.root);return {a, b};}

    const S& operator[](long k)const {
        P t=root;
        for(;;){
            long s=sz(t->l);
            if(k==s) return t->val;
            if(k<s) t=t->l;
            else k-=s+1, t=t->r;
        }
    }
    void set(long k, S x){root=set_(root, k, x);}
    void insert(long k, S x){P a, b;sp(root, k, a, b);root=mg(mg(a, new_node(x)), b);}
    void erase(long k){P a, b, c;sp(root, k, a, b);sp(b, 1, b, c);root=mg(a, c);}
    void push_front(S x){insert(0, x);}
    void push_back(S x){insert(size(), x);}
    void pop_front(){erase(0);}
    void pop_back(){erase(size()-1);}
    long size()const {return sz(root);}
    bool empty()const {return !root;}
    void clear(){root=nullptr;}

    static P build(const vector<S>& a, int l, int r, int d){
        if(l>=r) return 0;
        int m=(l+r)/2;
        P t=&pool[ptr++];
        *t=Node(a[m]);
        t->pri=((unsigned)max(0, 31-d)<<27)|(Node::rng()>>5);
        t->l=build(a, l, m, d+1);
        t->r=build(a, m+1, r, d+1);
        upd(t);
        return t;
    }
    void build(const vector<S>& a){root=build(a, 0, (int)a.size(), 0);}
    static void dump(P t, vector<S>& out){
        if(!t) return;
        dump(t->l, out);
        out.push_back(t->val);
        dump(t->r, out);
    }
    vector<S> to_vector()const {
        vector<S> out;
        out.reserve(size());
        dump(root, out);
        return out;
    }
};