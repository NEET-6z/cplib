#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_5_A"
#define ERROR 1e-6
#include "../geometry/closest_pair.hpp"

int main(){
    int N;
    cin>>N;
    vector<pld> A(N);
    rep(i, N) cin>>A[i].first>>A[i].second;
    cout<<closest_pair(A)<<"\n";
}