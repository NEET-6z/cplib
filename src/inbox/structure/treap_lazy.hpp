#include "../template.hpp"

template <class K, class T, auto op, auto e,
          class E, auto mapping, auto composition, auto id,
          class Compare = less<K>>
class LazyTreap {
public:
    LazyTreap() = default;

    // l の全キー < r の全キー であること
    static LazyTreap join(LazyTreap l, LazyTreap r){
        return LazyTreap(join(move(l.root), move(r.root)));
    }

    // ---------- 添字による操作 ----------
    pair<LazyTreap, LazyTreap> split(int k){
        assert(0<=k&&k<=size());
        auto p=split(move(root), k);
        return {LazyTreap(move(p.first)), LazyTreap(move(p.second))};
    }

    // 添字範囲 [l, r) に作用
    void update(int l, int r, const E& x){
        assert(0<=l&&l<r&&r<=size());
        node_ptr a, b, c;
        tie(a, b)=split(move(root), l);
        tie(b, c)=split(move(b), r-l);
        b->lazy=composition(b->lazy, x);
        root=join(join(move(a), move(b)), move(c));
    }

    // 添字範囲 [l, r) の総積
    T fold(int l, int r){
        assert(0<=l&&l<r&&r<=size());
        node_ptr a, b, c;
        tie(a, b)=split(move(root), l);
        tie(b, c)=split(move(b), r-l);
        auto ret=b->sum;
        root=join(join(move(a), move(b)), move(c));
        return ret;
    }

    // k 番目(0-indexed, キー昇順)の要素
    pair<K, T> kth(int k){
        node_ptr t=at(k);
        return {t->key, t->val};
    }
    const K& key_at(int k){return at(k)->key;}
    T value_at(int k){return at(k)->val;}

    void erase_at(int k){
        assert(0<=k&&k<size());
        auto p=split(move(root), k);
        auto q=split(move(p.second), 1);
        delete q.first;
        root=join(move(p.first), move(q.second));
    }

    // キー順序を壊さない場合のみ可
    void push_front(const K& key, const T& x){
        assert(empty()||cmp(key, key_at(0)));
        root=join(new Node(key, x), move(root));
    }

    void push_back(const K& key, const T& x){
        assert(empty()||cmp(key_at(size()-1), key));
        root=join(move(root), new Node(key, x));
    }

    void pop_front(){
        assert(!empty());
        auto p=split(move(root), 1);
        delete p.first;
        root=p.second;
    }

    void pop_back(){
        assert(!empty());
        auto p=split(move(root), size()-1);
        delete p.second;
        root=p.first;
    }

    // ---------- キーによる操作 ----------
    // キーが既にあれば値を上書き
    void insert(const K& key, const T& x){
        auto [a, b]=split_key(move(root), key);
        auto [c, d]=split(move(b), 1);
        if(c&&cmp(key, c->key)) d=join(c, move(d)); // c のキー > key なので残す
        else delete c;                              // 同一キー → 置換
        root=join(join(move(a), new Node(key, x)), move(d));
    }

    // 削除できたら true
    bool erase(const K& key){
        auto [a, b]=split_key(move(root), key);
        auto [c, d]=split(move(b), 1);
        bool found=c&&!cmp(key, c->key);
        if(c&&!found) d=join(c, move(d));
        else delete c;
        root=join(move(a), move(d));
        return found;
    }

    // key 以上の最初の添字 / key より大きい最初の添字
    int lower_bound(const K& key)const{
        int idx=0;
        node_ptr t=root;
        while(t){
            if(cmp(t->key, key)){idx+=size(t->left)+1; t=t->right;}
            else t=t->left;
        }
        return idx;
    }

    int upper_bound(const K& key)const{
        int idx=0;
        node_ptr t=root;
        while(t){
            if(!cmp(key, t->key)){idx+=size(t->left)+1; t=t->right;}
            else t=t->left;
        }
        return idx;
    }

    bool contains(const K& key){
        int i=lower_bound(key);
        return i<size()&&!cmp(key, at(i)->key);
    }

    optional<T> find(const K& key){
        int i=lower_bound(key);
        if(i<size()){
            node_ptr t=at(i);
            if(!cmp(key, t->key)) return t->val;
        }
        return nullopt;
    }

    // キー範囲 [lk, rk) に作用(空範囲なら何もしない)
    void update_key(const K& lk, const K& rk, const E& x){
        int l=lower_bound(lk), r=lower_bound(rk);
        if(l<r) update(l, r, x);
    }

    // キー範囲 [lk, rk) の総積(空範囲なら e())
    T fold_key(const K& lk, const K& rk){
        int l=lower_bound(lk), r=lower_bound(rk);
        return l<r?fold(l, r):e();
    }

    // key 未満 / key 以上 に分割
    pair<LazyTreap, LazyTreap> split_key(const K& key){
        auto p=split_key(move(root), key);
        return {LazyTreap(move(p.first)), LazyTreap(move(p.second))};
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
        K key;
        T val, sum;
        E lazy;
        unsigned int pri;
        int sz;

        Node(const K& k, const T& x)
            :left(nullptr),
            right(nullptr),
            key(k),
            val(x),
            sum(x),
            lazy(id()),
            pri(rand()),
            sz(1){}
    };

    node_ptr root=nullptr;
    static inline const Compare cmp=Compare();

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

    // k 番目のノード(途中の遅延を伝播しながら降りる)
    node_ptr at(int k){
        assert(0<=k&&k<size());
        node_ptr t=root;
        while(true){
            push(t);
            int ls=size(t->left);
            if(k<ls) t=t->left;
            else if(k==ls) return t;
            else{k-=ls+1; t=t->right;}
        }
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

    // 先頭 k 個 / 残り
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

    // key 未満 / key 以上
    static pair<node_ptr, node_ptr> split_key(node_ptr t, const K& key){
        if(!t) return {nullptr, nullptr};

        push(t);

        if(cmp(t->key, key)){
            auto s=split_key(t->right, key);
            t->right=s.first;
            recalc(t);
            return {t, s.second};
        }
        else{
            auto s=split_key(t->left, key);
            t->left=s.second;
            recalc(t);
            return {s.first, t};
        }
    }
};