#pragma once
#include "template.hpp"

//省メモリ化はしてません
template<class S, S (*op)(S, S), S (*e)(), typename K = uint64_t> struct dynamic_segtree {
    struct Node {
        Node *p, *left, *right;
        S d;
        Node(Node* _p = nullptr): p(_p), left(nullptr), right(nullptr), d(e()) {}
    };

    K n, log;
    Node* root;
    dynamic_segtree(K _n) {
        n = __bit_ceil(_n);
        log = __countr_zero(n);
        root = new Node();
    }
    void set(K p, S x) {
        Node* now = root;
        for(int i = log; i--;) {
            if(p >> i & 1) {
                if(!now->right) now->right = new Node(now);
                now = now->right;
            }
            else {
                if(!now->left) now->left = new Node(now);
                now = now->left;
            }
        }
        now->d = x;
        while(now->p) {
            now = now->p;
            now->d = op(now->left ? now->left->d : e(), now->right ? now->right->d : e());
        }
    }

    S get(K p) {
        Node* now = root;
        for(int i = log; i--;) {
            if(p >> i & 1) {
                if(!now->right) return e();
                now = now->right;
            }
            else {
                if(!now->left) return e();
                now = now->left;
            }
        }
        return now->d;
    }
    S prod(K l, K r) { return prod(l, r, root, 0, n); }

    S prod(K a, K b, Node*& now, K l, K r) {
        if(!now || r <= a || b <= l) return e();
        if(a <= l && r <= b) return now->d;
        K c = (l + r) >> 1;
        S lv = prod(a, b, now->left, l, c);
        S rv = prod(a, b, now->right, c, r);
        return op(lv, rv);
    }
};

template<class T> using DynamicSegtreeFrom =
    dynamic_segtree<class T::S, T::op, T::e, typename T::K>;