#include "../template.hpp"

// 各位置での回文半径を求める
// aaabaaa -> 1214121
// 偶数長の回文を含めて直径を知るには，N+1 個の $ を挿入して 1 を引く
// $a$a$a$b$a$a$a$ -> 123432181234321
auto manacher(string s){
    long n=si(s), i=0, j=0;
    vector<long> r(n);
    while(i<n){
        while(i>=j&&i+j<n&&s[i-j]==s[i+j]) j++;
        r[i]=j;
        long k=1;
        while(i>=k&&i+k<n&&k+r[i-k]<j){
            r[i+k]=r[i-k];
            k++;
        }
        i+=k, j-=k;
    }
    return r;
}