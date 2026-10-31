// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum
#include "../graph/offline_dc_com.hpp"

long op(long l, long r){return l+r;}

int main(){
    int N, Q;
    cin>>N>>Q;
    vector<long> A(N);
    rep(i, N) cin>>A[i];
    OfflineDynamicConnectivity<long, op> dc(A);
    vector<int> ql;
    rep(i, Q){
        int t, u, v, x;
        cin>>t;
        if(t==0){
            cin>>u>>v;
            dc.insert(ql.size(), u, v);
        }
        if(t==1){
            cin>>u>>v;
            dc.erase(ql.size(), u, v);
        }
        if(t==2){
            cin>>v>>x;
            A[v]+=x;
            dc.set(ql.size(), v, A[v]);
        }
        if(t==3){
            cin>>v;
            ql.push_back(v);
        }
    }
    dc.build(ql.size());
    dc.run([&](int i){
        cout<<dc.get(ql[i])<<"\n";
    });

}