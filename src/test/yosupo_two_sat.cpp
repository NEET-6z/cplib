// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/two_sat
#include "../graph/twosat.hpp"

int main(){
    string p,cnf;
    cin>>p>>cnf;
    int N,M;
    cin>>N>>M;
    two_sat sat(N);
    rep(i,M){
        int a,b,c;
        cin>>a>>b>>c;
        int A=abs(a)-1,B=abs(b)-1;
        if(a<0) A=~A;
        if(b<0) B=~B;
        sat.add_clause(A,B);
    }
    cout<<"s ";
    if(sat.satisfiable()){
        cout<<"SATISFIABLE\n";
        cout<<"v ";
        vector<bool> ans=sat.answer();
        rep(i,N) cout<<(ans[i]?(i+1):-(i+1))<<" ";
        cout<<"0\n";
    }
    else{
        cout<<"UNSATISFIABLE\n";
    }
}