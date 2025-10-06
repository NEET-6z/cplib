#pragma once
#include "template.hpp"

//省メモリ化はしてません
template<class S, S (*op)(S, S), S (*e)(), class T=uint64_t>
struct dynamic_segtree {
    struct Node{
        Node *p, *left, *right;
        S d;
        Node(Node* _p=nullptr): p(_p), left(nullptr), right(nullptr), d(e()) {}
    };

    T n,log;
    Node* root;
    dynamic_segtree(T _n): {
        n=__bit_ceil(_n);
        log=__countr_zero(n);
        root=new Node();
    }
    void set(T p, S x) {
        Node* now=root;
        for(int i=log;i--;){
            if(p>>i&1){
                if(!now->right) now->right=new Node(now);
                now=now->right;
            }
            else{
                if(!now->left) now->left=new Node(now);
                now=now->left;
            }
        }
        now->d=x;
        while(now->p){
            now=now->p;
            now->d=op(now->left?now->left->d:e(), now->right?now->right->d:e());
        }
    }
    
    S get(T p){
        Node* now=root;
        for(int i=log;i--;){
            if(p>>i&1){
                if(!now->right) return e();
                now=now->right;
            }
            else{
                if(!now->left) return e();
                now=now->left;
            }
        }
        return now->d;
    }
    S prod(T l, T r) {
        return prod(l, r, root, 0, n);
    }

    S prod(T a, T b, Node *&now, T l, T r) {
        if(!now||r<=a||b<=l) return e();
        if(a<=l&&r<=b) return now->d;
        T c=(l+r)>>1;
        S lv=prod(a, b, now->left, l, c);
        S rv=prod(a, b, now->right, c, r);
        return op(lv, rv);
    }
};

template<class T> using DynamicSegtreeFrom =
    dynamic_segtree<typename T::S, T::op, T::e, T::T>;