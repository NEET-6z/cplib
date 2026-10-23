#include "../template.hpp"


const long mod=(1L<<61)-1;
long add(long a, long b){return (a+=b)>=mod?a-mod:a;}
long mul(long a, long b){
    __int128_t c=(__int128_t)a*b;
    return add(c>>61, c&mod);
}

template<long rd=7954398468495>
struct RH {
    long n;
    vector<long> hs, pw;
    RH(vector<int> s):n(si(s)), hs(n+1), pw(n+1, 1){
        rep(i, n){
            pw[i+1]=mul(pw[i], rd);
            hs[i+1]=add(mul(hs[i], rd), s[i]);
        }
    }
    long get(long l, long r)const {return add(hs[r], mod-mul(hs[l], pw[r-l]));}
    int lcp(int i, int j){
        int ok=0, ng=min(n-i, n-j)+1;
        while(ok<ng-1){
            int mid=ok+ng>>1;
            (get(i, i+mid)==get(j, j+mid)?ok:ng)=mid;
        }
        return ok;
    }
};