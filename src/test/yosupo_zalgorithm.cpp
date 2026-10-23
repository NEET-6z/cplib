#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"
#include "../string/z.hpp"

int main(){
    string S;
    cin>>S;
    vector<int> z=z_algorithm(S);
    rep(i,S.size())cout<<z[i]<<" \n"[i+1==S.size()];
}