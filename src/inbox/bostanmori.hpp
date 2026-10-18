#include "../math/convolution.hpp"

template<typename mint>
mint Bostan_Mori(vector<mint> P,vector<mint> Q,long K){
    int d=si(Q)-1;
    while(K>0){
        vector<mint> Q_minus(d+1);
        rep(i,d+1) Q_minus[i]=(i&1?-Q[i]:Q[i]);
        vector<mint> U=convolution(P,Q_minus);
        vector<mint> V=convolution(Q,Q_minus);
        P.clear(),Q.clear();
        for(int i=K%2;i<si(U);i+=2) P.push_back(U[i]);
        for(int i=0;i<si(V);i+=2) Q.push_back(V[i]);
        K/=2;
    }
    return P[0]/Q[0]; //Q[0]==1であることが多い。Q[0]==0は定義できない
}