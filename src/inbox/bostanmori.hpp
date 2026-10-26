#include "../math/convolution.hpp"

template<typename mint>
mint Bostan_Mori(vector<mint> P, vector<mint> Q, long K){
    int d=si(Q)-1;
    while(K>0){
        vector<mint> Q_minus(d+1);
        rep(i, d+1) Q_minus[i]=(i&1?-Q[i]:Q[i]);
        vector<mint> U=convolution(P, Q_minus);
        vector<mint> V=convolution(Q, Q_minus);
        P.clear(), Q.clear();
        for(int i=K%2;i<si(U);i+=2) P.push_back(U[i]);
        for(int i=0;i<si(V);i+=2) Q.push_back(V[i]);
        K/=2;
    }
    return P[0]/Q[0]; //Q[0]==1であることが多い。Q[0]==0は定義できない
}


template <typename mint>
vector<mint> BerlekampMassey(const vector<mint> s){
    const int N=(int)s.size();
    vector<mint> b, c;
    b.reserve(N+1);
    c.reserve(N+1);
    b.push_back(mint(1));
    c.push_back(mint(1));
    mint y=mint(1);
    for(int ed=1;ed<=N;ed++){
        int l=int(c.size()), m=int(b.size());
        mint x=0;
        for(int i=0;i<l;i++) x+=c[i]*s[ed-l+i];
        b.emplace_back(mint(0));
        m++;
        if(x==mint(0)) continue;
        mint freq=x/y;
        if(l<m){
            auto tmp=c;
            c.insert(begin(c), m-l, mint(0));
            for(int i=0;i<m;i++) c[m-1-i]-=freq*b[m-1-i];
            b=tmp;
            y=x;
        }
        else{
            for(int i=0;i<m;i++) c[l-1-i]-=freq*b[m-1-i];
        }
    }
    reverse(begin(c), end(c));
    return c;
}


mint nth_term(long n, vector<mint> s){
    if(n<(long)s.size()) return s[n];
    vector<mint> Q=BerlekampMassey<mint>(s);
    int d=(int)Q.size()-1;
    if(d==0) return mint(0);
    vector<mint> P = convolution(s, Q);
    P.resize(d);
    return Bostan_Mori(P, Q, n);
}