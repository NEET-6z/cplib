#include "../template.hpp"


template <class T, auto op, auto e,
          class E, auto mapping, auto composition, auto id>
class LazyTreap {
public:
    LazyTreap() = default;

    static LazyTreap join(LazyTreap l, LazyTreap r){
        return LazyTreap(join(move(l.root), move(r.root)));
    }

    pair<LazyTreap, LazyTreap> split(int k){
        assert(0<=k&&k<=size());
        auto p=split(move(root), k);
        return {LazyTreap(move(p.first)),
                LazyTreap(move(p.second))};
    }

    void update(int l, int r, const E& x){
        assert(0<=l&&l<r&&r<=size());
        node_ptr a, b, c;
        tie(a, b)=split(move(root), l);
        tie(b, c)=split(move(b), r-l);
        b->lazy=composition(b->lazy, x);
        root=join(join(move(a), move(b)), move(c));
    }

    T fold(int l, int r){
        assert(0<=l&&l<r&&r<=size());
        node_ptr a, b, c;
        tie(a, b)=split(move(root), l);
        tie(b, c)=split(move(b), r-l);
        auto ret=b->sum;
        root=join(join(move(a), move(b)), move(c));
        return ret;
    }

    void reverse(int l, int r){
        assert(0<=l&&l<r&&r<=size());
        node_ptr a, b, c;
        tie(a, b)=split(move(root), l);
        tie(b, c)=split(move(b), r-l);
        b->rev^=true;
        root=join(join(move(a), move(b)), move(c));
    }

    void insert(int k, const T& x){
        assert(0<=k&&k<=size());
        auto s=split(move(root), k);
        root=join(join(move(s.first), new Node(x)),
                  move(s.second));
    }

    void erase(int k){
        assert(0<=k&&k<size());
        auto p=split(move(root), k);
        auto q=split(move(p.second), 1);
        root=join(move(p.first), move(q.second));
    }

    void push_front(const T& x){
        root=join(new Node(x), move(root));
    }

    void push_back(const T& x){
        root=join(move(root), new Node(x));
    }

    void pop_front(){
        assert(!empty());
        root=split(move(root), 1).second;
    }

    void pop_back(){
        assert(!empty());
        root=split(move(root), size()-1).first;
    }

    int size()const {return size(root);}

    bool empty()const {return size()==0;}

private:
    struct Node;
    using node_ptr=Node*;

    static unsigned int rand(){
        static random_device rd;
        static mt19937 rng(rd());
        return rng();
    }

    struct Node {
        node_ptr left, right;
        T val, sum;
        E lazy;
        unsigned int pri;
        int sz;
        bool rev;

        Node()
            :Node(e()){}

        Node(const T& x)
            :left(nullptr),
            right(nullptr),
            val(x),
            sum(val),
            lazy(id()),
            pri(rand()),
            sz(1),
            rev(false){}

    };

    node_ptr root=nullptr;

    explicit LazyTreap(node_ptr root):root(root){}

    static int size(const node_ptr& t){
        return t?t->sz:0;
    }

    static void recalc(const node_ptr& t){
        if(!t) return;
        t->sz=size(t->left)+1+size(t->right);
        t->sum=t->val;
        if(t->left) t->sum=op(t->left->sum, t->sum);
        if(t->right) t->sum=op(t->sum, t->right->sum);
    }

    static void push(const node_ptr& t){
        if(!t) return;

        if(t->rev){
            swap(t->left, t->right);
            if(t->left) t->left->rev^=true;
            if(t->right) t->right->rev^=true;
            t->rev=false;
        }

        if(t->lazy!=id()){
            t->val=mapping(t->val, t->lazy);

            if(t->left){
                t->left->lazy=composition(t->left->lazy, t->lazy);
                t->left->sum=mapping(t->left->sum, t->lazy);
            }

            if(t->right){
                t->right->lazy=composition(t->right->lazy, t->lazy);
                t->right->sum=mapping(t->right->sum, t->lazy);
            }

            t->lazy=id();
        }

        recalc(t);
    }

    static node_ptr join(node_ptr l, node_ptr r){
        if(!l) return r;
        if(!r) return l;

        push(l);
        push(r);

        if(l->pri>r->pri){
            l->right=join(l->right, r);
            recalc(l);
            return l;
        }
        else{
            r->left=join(l, r->left);
            recalc(r);
            return r;
        }
    }

    static pair<node_ptr, node_ptr> split(node_ptr t, int k){
        if(!t) return {nullptr, nullptr};

        push(t);

        if(k<=size(t->left)){
            auto s=split(t->left, k);
            t->left=s.second;
            recalc(t);
            return {s.first, t};
        }
        else{
            auto s=split(t->right, k-size(t->left)-1);
            t->right=s.first;
            recalc(t);
            return {t, s.second};
        }
    }
};