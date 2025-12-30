#define PROBLEM "https://judge.yosupo.jp/problem/point_add_rectangle_sum"
#include "../structure/fen2d.hpp"

int main(){
    int N,Q;
    cin>>N>>Q;
    vector<array<int,5>> qu(N+Q);
    Fen2D<int,long> f2d;
    rep(i,N){
        int x,y,w;
        cin>>x>>y>>w;
        qu[i]={0,x,y,w};
        f2d.add_point(x,y);
    }
    rep(i,Q){
        int t;
        cin>>t;
        if(t==0){
            int x,y,w;
            cin>>x>>y>>w;
            qu[i+N]={0,x,y,w};
            f2d.add_point(x,y);
        }
        else {
            int l,d,r,u;
            cin>>l>>d>>r>>u;
            qu[i+N]={1,l,d,r,u};
        }
    }
    f2d.build();
    for(auto a: qu){
        if(a[0]==0){
            f2d.add(a[1],a[2],a[3]);
        }
        else {
            cout<<f2d.sum(a[1],a[3],a[2],a[4])<<"\n";
        }
    }
}