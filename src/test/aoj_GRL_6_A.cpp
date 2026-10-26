// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A
#include "../graph/maxflow.hpp"

int main(){
    int N, M;
    cin>>N>>M;
    maxflow<long> g(N);
    rep(i, M){
        int u, v, c;
        cin>>u>>v>>c;
        g.add_edge(u, v, c);
    }
    cout<<g.flow(0, N-1)<<"\n";
}
