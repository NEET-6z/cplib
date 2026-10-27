// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/line_add_get_min
#include "../structure/li_chao_tree.hpp"

int main(){
    int N, Q;
    cin>>N>>Q;
    vector<pair<long, long>> ql;
    vector<long> z;
    rep(i, N){
        long a, b;
        cin>>a>>b;
        ql.emplace_back(a, b);
    }
    rep(i, Q){
        long t, a;
        cin>>t>>a;
        if(t) z.push_back(a), ql.emplace_back(-2e18, a);
        else{
            long b;
            cin>>b;
            ql.emplace_back(a, b);
        }
    }
    li_chao_tree<long> lct(z, (long)2e18);
    for(auto [a, b]:ql){
        if(a==-2e18) cout<<lct.get(b)<<"\n";
        else lct.add_line({a, b});
    }
}