// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
#include "../segtree.hpp"

int op(int l, int r){return min(l,r);}
int e(){return INT_MAX;}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,q;
    cin>>n>>q;
    segtree<int,op,e> seg(n);
    while(q--){
        int com,x,y;
        cin>>com>>x>>y;
        if(com==0){
            seg.set(x,y);
        }
        else{
            cout<<seg.prod(x,y+1)<<"\n";
        }
    }
}