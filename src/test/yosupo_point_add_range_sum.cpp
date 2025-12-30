#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "../segtree/dynamic_segtree.hpp"

long op(long l,long r){return l+r;}
long e(){return 0;}

int main(){
    int n,q;
    cin>>n>>q;
    dynamic_segtree<long,op,e> seg(n);
    rep(i,n){
        int a;
        cin>>a;
        seg.set(i,a);
    }
    rep(i,q){
        int c,x,y;
        cin>>c>>x>>y;
        if(c==0){
            seg.set(x,seg.get(x)+y);
        }
        else {
            cout<<seg.prod(x,y)<<"\n";
        }
    }
}