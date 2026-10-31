// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B
#include "../graph/mincostflow.hpp"

int main(){
    int N, M, F;
    cin>>N>>M>>F;
    PrimalDual<long, long> g(N);
    rep(i, M){
        int u, v, c, d;
        cin>>u>>v>>c>>d;
        g.add_edge(u, v, c, d);
    }
    auto [flow, cost]=g.flow(0, N-1, F);
    if(flow<F) cost=-1;
    cout<<cost<<"\n";
}
