// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_A
#include "../graph/scc.hpp"

int main(){
    int n, m;
    cin>>n>>m;
    scc_graph scc(n);
    rep(i, m){
        int a, b;
        cin>>a>>b;
        scc.add_edge(a, b);
    }
    cout<<(scc.scc().size()!=n)<<endl;
}