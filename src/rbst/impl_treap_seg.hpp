#include "../../template.hpp"
extern "C" const char* __asan_default_options(){
    return "detect_leaks=0";
}

template<class S, auto op, auto e>
struct Treap {
    struct Node {
        S val, sum, rsum;int sz=1;bool rev=0;unsigned pri=rng();Node *l=0, *r=0;
        Node(S x):val(x), sum(x), rsum(x){}
        static unsigned rng(){static mt19937 g(random_device{}());return g();}
    };
    using P=Node*;
    P root=0;

    static int sz(P t){return t?t->sz:0;}
    static S sm(P t){return t?t->sum:e();}
    static S rs(P t){return t?t->rsum:e();}
    static void upd(P t){
        t->sz=sz(t->l)+1+sz(t->r);
        t->sum=op(op(sm(t->l), t->val), sm(t->r));
        t->rsum=op(op(rs(t->r), t->val), rs(t->l));
    }
    static void toggle(P t){if(t){swap(t->l, t->r);swap(t->sum, t->rsum);t->rev^=1;}}
    static void push(P t){if(t->rev){toggle(t->l);toggle(t->r);t->rev=0;}}
    static P mg(P a, P b){
        if(!a||!b) return a?a:b;
        if(a->pri>b->pri){push(a);a->r=mg(a->r, b);upd(a);return a;}
        push(b);b->l=mg(a, b->l);upd(b);return b;
    }
    static void sp(P t, int k, P& a, P& b){
        if(!t){a=b=0;return;}
        push(t);
        if(k<=sz(t->l)){b=t;sp(t->l, k, a, t->l);}
        else{a=t;sp(t->r, k-sz(t->l)-1, t->r, b);}
        upd(t);
    }
    template<class G> S range(int l, int r, G f){
        P a, b, c;
        sp(root, l, a, b);sp(b, r-l, b, c);
        f(b);
        S ret=b->sum;
        root=mg(mg(a, b), c);
        return ret;
    }

    static Treap join(Treap l, Treap r){Treap t;t.root=mg(l.root, r.root);return t;}
    pair<Treap, Treap> split(int k){Treap a, b;sp(root, k, a.root, b.root);root=0;return {a, b};}

    void set(int k, S x){range(k, k+1, [&](P b){b->val=b->sum=b->rsum=x;});}
    S get(int k){return range(k, k+1, [](P){});}
    S fold(int l, int r){return range(l, r, [](P){});}
    void reverse(int l, int r){range(l, r, [](P b){toggle(b);});}
    void insert(int k, S x){P a, b;sp(root, k, a, b);root=mg(mg(a, new Node(x)), b);}
    void erase(int k){P a, b, c;sp(root, k, a, b);sp(b, 1, b, c);root=mg(a, c);}
    void push_front(S x){insert(0, x);}
    void push_back(S x){insert(size(), x);}
    void pop_front(){erase(0);}
    void pop_back(){erase(size()-1);}
    int size(){return sz(root);}
    bool empty(){return !root;}

    template<class G> int max_right(int l, G f){
        P a, b;
        sp(root, l, a, b);
        int r=l;
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
    template<class G> int min_left(int r, G f){
        P a, b;
        sp(root, r, a, b);
        int l=r;
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