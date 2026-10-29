#include "../template.hpp"
template<class T>
struct Treap {
    struct Node {
        T v;
        int sz;
        unsigned pri;
        Node *l = 0, *r = 0;
        Node(T v) : v(v), sz(1), pri(rand()) {}
    };
    using P = Node*;
    P root = 0;

    int sz(P t) { return t ? t->sz : 0; }
    void upd(P t) {
        if (t) t->sz = 1 + sz(t->l) + sz(t->r);
    }
    P merge(P a, P b) {
        if (!a || !b) return a ? a : b;
        if (a->pri > b->pri) {
            a->r = merge(a->r, b);
            upd(a);
            return a;
        }
        b->l = merge(a, b->l);
        upd(b);
        return b;
    }
    void split(P t, int k, P &a, P &b) {
        if (!t) { a = b = 0; return; }
        if (sz(t->l) < k) {
            split(t->r, k - sz(t->l) - 1, t->r, b);
            a = t;
        } else {
            split(t->l, k, a, t->l);
            b = t;
        }
        upd(t);
    }
    void insert(int k, T x) {
        P a, b;
        split(root, k, a, b);
        root = merge(merge(a, new Node(x)), b);
    }
    void erase(int k) {
        P a, b, c;
        split(root, k, a, b);
        split(b, 1, b, c);
        delete b;
        root = merge(a, c);
    }
    T& get(int k) {
        P t = root;
        while (t) {
            int s = sz(t->l);
            if (k == s) return t->v;
            if (k < s) t = t->l;
            else k -= s + 1, t = t->r;
        }
        throw out_of_range("Treap index");
    }
    int size() { return sz(root); }
};