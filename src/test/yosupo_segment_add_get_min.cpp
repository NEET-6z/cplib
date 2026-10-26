// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/segment_add_get_min
#include "../structure/li_chao_tree.hpp"

const long INF=2e18;
int main(){
    int N, Q;
    cin>>N>>Q;
    vector<array<long, 4>> ql;
    vector<long> z;
    rep(i, N){
        long l, r, a, b;
        cin>>l>>r>>a>>b;
        ql.push_back({l, r, a, b});
    }

    rep(i, Q){
        long t;
        cin>>t;
        if(t){
            long p;
            cin>>p;
            z.push_back(p);
            ql.push_back({p, INF, INF, INF});
        }
        else{
            long l, r, a, b;
            cin>>l>>r>>a>>b;
            ql.push_back({l, r, a, b});
        }
    }
    li_chao_tree<long> lct(z, INF);
    for(auto [l, r, a, b]:ql){
        if(b==INF){
            long y=lct.get(l);
            if(y==INF) cout<<"INFINITY\n";
            else cout<<y<<"\n";
        }
        else lct.add_segment({a, b}, l, r);
    }
}