#include "../template.hpp"

vector<int> eratosthenes(int N){
    vector<int> is(N+2,1);
    is[0]=is[1]=0;
    for(long i=2;i*i<=N;++i){
        if(is[i]){
            for(int j=i*i;j<=N;j+=i) is[j]=0;
        }
    }
    return is;
}

struct SegmentSieve {
    long L,R;
    vector<int> P;
    SegmentSieve (long _L,long _R):L(_L),R(_R){
        int sq=sqrtl(R)+1;
        vector<int> sm(sq,1);
        P.assign(R-L+1,1);
        for(long i=2;i * i<=R;i++){
            if(!sm[i]) continue;
            for(long j=i*i;j<R;j+=i) sm[j]=0;
            long start=max((L+i-1)/i,i*2);
            for(long j=start;j<R;j+=i) P[j-L]=0;
        }
    }
    bool operator[](long k) const {return P[k-L];}
};