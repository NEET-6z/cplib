#include "../template.hpp"

template<class K, int MAX_N=1000000>
struct Treap {
    struct Node {
        K key;
        int sz=1;
        unsigned pri;
        Node *l=0, *r=0;
        Node() = default;
        Node(K k):key(k), pri(rng()){}
        static unsigned rng(){static mt19937 g(random_device{}());return g();}
    };
    using P=Node*;
    inline static Node pool[MAX_N];
    inline static int ptr=0;
    static P new_node(K k){
        assert(ptr<MAX_N);
        P t=&pool[ptr++];
        *t=Node(k);
        return t;
    }
    P root=0;

    static int sz(P t){return t?t->sz:0;}
    static void upd(P t){t->sz=sz(t->l)+1+sz(t->r);}
    static P mg(P a, P b){
        if(!a||!b) return a?a:b;
        if(a->pri>b->pri){a->r=mg(a->r, b);upd(a);return a;}
        b->l=mg(a, b->l);upd(b);return b;
    }
    static void sp(P t, K k, P& a, P& b){
        if(!t){a=b=0;return;}
        if(t->key<k){a=t;sp(t->r, k, t->r, b);}
        else{b=t;sp(t->l, k, a, t->l);}
        upd(t);
    }
    static P er(P t, K k){
        if(!t) return 0;
        if(t->key==k) return mg(t->l, t->r);
        if(k<t->key) t->l=er(t->l, k);
        else t->r=er(t->r, k);
        upd(t);return t;
    }

    static Treap join(Treap& l, Treap& r){
        Treap t;t.root=mg(l.root, r.root);
        l.root=r.root=nullptr;
        return t;
    }
    pair<Treap, Treap> split(K k){
        Treap a, b;sp(root, k, a.root, b.root);root=0;
        return {a, b};
    }

    void insert(K k){
        P a, b;
        root=er(root, k);
        sp(root, k, a, b);
        root=mg(mg(a, new_node(k)), b);
    }
    void erase(K k){root=er(root, k);}
    bool contains(K k){
        P t=root;
        while(t&&!(t->key==k)) t=k<t->key?t->l:t->r;
        return t;
    }
    P find(K k){
        P t=root;
        while(t&&!(t->key==k)) t=k<t->key?t->l:t->r;
        return t;
    }
    P at(int k){
        P t=root;
        for(;;){
            int s=sz(t->l);
            if(k==s) return t;
            if(k<s) t=t->l;
            else k-=s+1, t=t->r;
        }
    }
    int lower_bound(K k){
        int r=0;
        for(P t=root;t;){
            if(t->key<k) r+=sz(t->l)+1, t=t->r;
            else t=t->l;
        }
        return r;
    }
    int size(){return sz(root);}
    bool empty(){return !root;}
};