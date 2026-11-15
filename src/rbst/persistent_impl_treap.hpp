#include "../template.hpp"

template<class S, auto op, auto e, class F, auto mpp, auto cmpo, auto id, int MAX_N=1000000>
struct Treap {
    struct Node {
        S val, sum, rsum;F lz=id();int sz=1;bool rev=0;unsigned pri;Node *l=0, *r=0;
        Node() = default;
        Node(S x):val(x), sum(x), rsum(x), pri(rng()){}
        static unsigned rng(){static mt19937 g(random_device{}());return g();}
    };
    using P=Node*;
    inline static Node pool[MAX_N];
    inline static int ptr=0;
    static P new_node(S x){assert(ptr<MAX_N);P t=&pool[ptr++];*t=Node(x);return t;}
    static P clone(P t){assert(ptr<MAX_N);P n=&pool[ptr++];*n=*t;return n;}
    static void reset(){ptr=0;}
    P root=0;

    static int sz(P t){return t?t->sz:0;}
    static S sm(P t){return t?t->sum:e();}
    static S rs(P t){return t?t->rsum:e();}
    static void upd(P t){
        t->sz=sz(t->l)+1+sz(t->r);
        t->sum=op(op(sm(t->l), t->val), sm(t->r));
        t->rsum=op(op(rs(t->r), t->val), rs(t->l));
    }
    static P apply(P t, const F& f){
        if(!t) return t;
        t=clone(t);
        t->val=mpp(f, t->val);t->sum=mpp(f, t->sum);t->rsum=mpp(f, t->rsum);
        t->lz=cmpo(f, t->lz);
        return t;
    }
    static P toggle(P t){
        if(!t) return t;
        t=clone(t);
        swap(t->l, t->r);swap(t->sum, t->rsum);t->rev^=1;
        return t;
    }
    static void push(P t){
        if(t->rev){t->l=toggle(t->l);t->r=toggle(t->r);t->rev=0;}
        if(t->lz!=id()){t->l=apply(t->l, t->lz);t->r=apply(t->r, t->lz);t->lz=id();}
    }
    static P mg(P a, P b){
        if(!a||!b) return a?a:b;
        if(a->pri>b->pri){a=clone(a);push(a);a->r=mg(a->r, b);upd(a);return a;}
        b=clone(b);push(b);b->l=mg(a, b->l);upd(b);return b;
    }
    static void sp(P t, int k, P& a, P& b){
        if(!t){a=b=0;return;}
        if(k<=0){a=0;b=t;return;}
        if(k>=t->sz){a=t;b=0;return;}
        t=clone(t);push(t);
        if(k<=sz(t->l)){b=t;sp(t->l, k, a, t->l);}
        else{a=t;sp(t->r, k-sz(t->l)-1, t->r, b);}
        upd(t);
    }
    template<class G> S range(int l, int r, G f){
        if(l==r) return e();
        P a, b, c;
        sp(root, l, a, b);sp(b, r-l, b, c);
        b=f(b);
        S ret=sm(b);
        root=mg(mg(a, b), c);
        return ret;
    }

    static Treap join(const Treap& l, const Treap& r){Treap t;t.root=mg(l.root, r.root);return t;}
    pair<Treap, Treap> split(int k)const {Treap a, b;sp(root, k, a.root, b.root);return {a, b};}

    void update(int l, int r, F x){range(l, r, [&](P b){return apply(b, x);});}
    static S query(P t, int l, int r, F f, bool rev){
        if(!t||l>=r) return e();
        if(l==0&&r==t->sz){
            S res=t->sum;
            return mpp(f, res);
        }
        P L=rev?t->r:t->l;
        P R=rev?t->l:t->r;
        bool nr=rev^t->rev;
        F nf=cmpo(f, t->lz);
        int n=sz(L);
        S res=e();
        if(l<n) res=op(res, query(L, l, min(r, n), nf, nr));
        if(l<=n&&n<r) res=op(res, mpp(f, t->val));
        if(r>n+1) res=op(res, query(R, max(0, l-n-1), r-n-1, nf, nr));
        return res;
    }
    S fold(int l, int r)const {
        return query(root, l, r, id(), false);
    }
    void reverse(int l, int r){range(l, r, [](P b){return toggle(b);});}
    void insert(int k, S x){P a, b;sp(root, k, a, b);root=mg(mg(a, new_node(x)), b);}
    void erase(int k){P a, b, c;sp(root, k, a, b);sp(b, 1, b, c);root=mg(a, c);}
    void push_front(S x){insert(0, x);}
    void push_back(S x){insert(size(), x);}
    void pop_front(){erase(0);}
    void pop_back(){erase(size()-1);}
    int size()const {return sz(root);}
    bool empty()const {return !root;}
    void clear(){root=nullptr;}

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
        return l;
    }
    static P build(const vector<S>& a, int l, int r, const vector<unsigned>& p, int& idx){
        if(l>=r) return 0;
        int m=(l+r)/2;
        assert(ptr<MAX_N);
        P t=&pool[ptr++];
        *t=Node(a[m]);
        t->pri=p[idx++];
        t->l=build(a, l, m, p, idx);
        t->r=build(a, m+1, r, p, idx);
        upd(t);
        return t;
    }
    void build(const vector<S>& a){
        int n=a.size();
        vector<unsigned> p(n);
        for(auto& x:p) x=Node::rng();
        sort(p.begin(), p.end(), greater<unsigned>());
        int idx=0;
        root=build(a, 0, n, p, idx);
    }
    static void dump(P t, F f, bool rev, vector<S>& out){
        if(!t) return;
        P L=rev?t->r:t->l;
        P R=rev?t->l:t->r;
        F nf=cmpo(f, t->lz);
        bool nr=rev^t->rev;
        dump(L, nf, nr, out);
        out.push_back(mpp(f, t->val));
        dump(R, nf, nr, out);
    }
    vector<S> to_vector()const {
        vector<S> out;
        out.reserve(size());
        dump(root, id(), false, out);
        return out;
    }
};