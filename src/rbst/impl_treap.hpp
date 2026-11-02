#include "../template.hpp"
extern "C" const char* __asan_default_options(){
    return "detect_leaks=0";
}
template<class S>
struct Treap {
    struct Node {
        S val;int sz=1;unsigned pri=rng();Node *l=0, *r=0;
        Node(S x):val(x){}
        static unsigned rng(){static mt19937 g(random_device{}());return g();}
    };
    using P=Node*;
    P root=0;

    static int sz(P t){return t?t->sz:0;}
    static void upd(P t){t->sz=sz(t->l)+1+sz(t->r);}
    static P mg(P a, P b){
        if(!a||!b) return a?a:b;
        if(a->pri>b->pri){a->r=mg(a->r, b);upd(a);return a;}
        b->l=mg(a, b->l);upd(b);return b;
    }
    static void sp(P t, int k, P& a, P& b){
        if(!t){a=b=0;return;}
        if(k<=sz(t->l)){b=t;sp(t->l, k, a, t->l);}
        else{a=t;sp(t->r, k-sz(t->l)-1, t->r, b);}
        upd(t);
    }

    static Treap join(Treap l, Treap r){Treap t;t.root=mg(l.root, r.root);return t;}
    pair<Treap, Treap> split(int k){Treap a, b;sp(root, k, a.root, b.root);root=0;return {a, b};}

    S& operator[](int k){
        P t=root;
        for(;;){
            int s=sz(t->l);
            if(k==s) return t->val;
            if(k<s) t=t->l;
            else k-=s+1, t=t->r;
        }
    }
    void insert(int k, S x){P a, b;sp(root, k, a, b);root=mg(mg(a, new Node(x)), b);}
    void erase(int k){P a, b, c;sp(root, k, a, b);sp(b, 1, b, c);root=mg(a, c);}
    void push_front(S x){insert(0, x);}
    void push_back(S x){insert(size(), x);}
    void pop_front(){erase(0);}
    void pop_back(){erase(size()-1);}
    int size(){return sz(root);}
    bool empty(){return !root;}
};