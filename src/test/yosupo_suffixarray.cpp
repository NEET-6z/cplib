// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/suffixarray
#include "../string/sa.hpp"

int main(){
    string S;
    cin>>S;
    vector<int> sa=suffix_array(S);
    rep(i,S.size())cout<<sa[i]<<" \n"[i+1==S.size()];
}