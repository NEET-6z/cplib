#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B"
#include "../dsu/dsu_weighted.hpp"

int main(){
    int N,Q;
    cin>>N>>Q;
    dsu_weighted<int> uf(N);
    while(Q--){
        int o,x,y;
        cin>>o>>x>>y;
        if(o==0){
            int z;
            cin>>z;
            uf.merge(x,y,z);
        }
        else{
            if(!uf.same(x,y)) cout<<"?\n";
            else cout<<uf.weight(y)-uf.weight(x)<<"\n";
        }
    }
}



