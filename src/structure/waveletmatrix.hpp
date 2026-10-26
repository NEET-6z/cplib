#include "../template.hpp"


template<typename S=int, int H=30>
struct WaveletMatrix {
    int N;
    vector<vector<int>> d;
    WaveletMatrix(vector<S> A):N(si(A)), d(H){
        for(int h=H;h--;){
            vector<int> dir(N);
            vector<int> left, right;
            rep(i, N){
                dir[i]=A[i]>>h&1;
                (dir[i]?right:left).emplace_back(A[i]);
            }
            rep(i, si(left)) A[i]=left[i];
            rep(i, si(right)) A[si(left)+i]=right[i];
            d[h].resize(N+1);
            rep(i, N) d[h][i+1]=d[h][i]+dir[i];
        }
    }
    tuple<int, int, int, int> get_subtree_range(int h, int l, int r){
        int a0=l-d[h][l], a1=d[h][l];
        int b0=r-d[h][r], b1=d[h][r];
        int c0=N-d[h][N];
        return {a0, b0, c0+a1, c0+b1};
    }
    S kth_smallest_rec(int h, int l, int r, int k){
        if(h==0) return 0;
        auto [l0, r0, l1, r1]=get_subtree_range(h-1, l, r);
        int lsz=r0-l0;
        if(k<lsz){
            return kth_smallest_rec(h-1, l0, r0, k);
        }
        else{
            return (1l<<(h-1))+kth_smallest_rec(h-1, l1, r1, k-lsz);
        }
    }
    S kth_smallest(int L, int R, int k){
        return kth_smallest_rec(H, L, R, k);
    }

    int range_freq(int l, int r, S upper){
        if(l>=r||upper<=0) return 0;
        if(upper>=(1LL<<H)) return r-l;

        int ret=0;
        for(int h=H;h--;){
            auto [l0, r0, l1, r1]=get_subtree_range(h, l, r);
            if((upper>>h)&1LL){
                ret+=r0-l0;
                l=l1;
                r=r1;
            }
            else{
                l=l0;
                r=r0;
            }
        }
        return ret;
    }

    S prev_value(int l, int r, S lower){
        int k=range_freq(l, r, lower);
        if(k==0) return -1;
        return kth_smallest(l, r, k-1);
    }

    S next_value(int l, int r, S lower){
        int k=range_freq(l, r, lower);
        if(k==r-l) return -1;
        return kth_smallest(l, r, k);
    }
};

