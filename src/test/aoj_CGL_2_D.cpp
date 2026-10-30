// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D
// competitive-verifier: ERROR 1e-8
#include "../geometry/intersect.hpp"


int main(){
    int Q;
    cin>>Q;
    while(Q--){
        vector<P> p(4);
        rep(i, 4){
            int x, y;
            cin>>x>>y;
            p[i]=P(x, y);
        }
        Line s(p[0], p[1]), t(p[2], p[3]);
        cout<<distance_ss(s, t)<<"\n";
    }
}
