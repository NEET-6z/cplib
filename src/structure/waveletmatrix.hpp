#include"../template.hpp"

template<typename S=int,int H=30>
struct WaveletMatrix {
    int N;
    vector<vector<S>> d;
    WaveletMatrix(vector<S> A):N(si(A)),d(H){
        for(int h=H;h--;){
            vector<int> dir(N);
            vector<int> left,right;
            rep(i,N){
                dir[i]=A[i]>>h&1;
                (dir[i]?right:left).emplace_back(A[i]);
            }
            rep(i,si(left)) A[i]=left[i];
            rep(i,si(right)) A[si(left)+i]=right[i];
            d[h].resize(N+1);
            rep(i,N) d[h][i+1]=d[h][i]+dir[i];
        }
    }
    tuple<int,int,int,int> get_subtree_range(int h,int l,int r){
        int a0=l-d[h][l],a1=d[h][l];
        int b0=r-d[h][r],b1=d[h][r];
        int c0=N-d[h][N];
        return {a0,b0,c0+a1,c0+b1};
    }
    long kth_smallest_rec(int h,int l,int r,int k){
        if(h==0) return 0;
        auto [l0,r0,l1,r1]=get_subtree_range(h-1,l,r);
        int lsz=r0-l0;
        if(k<lsz){
            return kth_smallest_rec(h-1,l0,r0,k);
        }
        else{
            return (1l<<(h-1))+kth_smallest_rec(h-1,l1,r1,k-lsz);
        }
    }
    long kth_smallest(int L,int R,int k){
        return kth_smallest_rec(H,L,R,k);
    }
};