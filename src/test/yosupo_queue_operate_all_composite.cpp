#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"
#include "../structure/swag.hpp"
#include "../math/modint.hpp"

using mint=modint<>;
using S=pair<mint,mint>;
S op(S l, S r){return {l.fi*r.fi, l.se*r.fi+r.se};}
S e(){return {1,0};}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int Q;
    cin>>Q;

    vector<pair<mint,mint>> R,LD,RD;
    SWAG<S,op,e> swag;
    while(Q--){
        int o;
        cin>>o;
        if(o==0){
            int a,b;
            cin>>a>>b;
            swag.push({a,b});
        }
        else if(o==1){
            swag.pop();
        } 
        else{
            long x;
            cin>>x;
            S s=swag.get();
            mint ans=s.fi*x+s.se;
            cout<<ans<<"\n";  
        }

    }
}
