#pragma once
#include "template.hpp"

template<class Block> struct BucketDecomposition {
    using S = Block::S;
    using F = Block::F;

    int N, B;
    vector<Block> blocks;
    BucketDecomposition(vector<S> A, int B_=-1): B(B_) {
        N = A.size();
        if(B==-1) B = sqrt(N) + 1;
        blocks.reserve((N + B - 1) / B);
        rep(i, (N + B - 1) / B) {
            vector<S> a;
            for(int j = i * B; j < min(N, (i + 1) * B); j++) a.push_back(A[j]);
            blocks.push_back(Block(si(a), i, a));
        }
    }
    Block::S prod(int l, int r) {
        int lb = l / B;
        int rb = (r - 1) / B;
        S ret{};
        if(lb == rb)
            ret = blocks[lb].op(ret, blocks[lb].prod(l - B * lb, r - B * lb));
        else {
            for(int i = lb; i <= rb; i++) {
                if(i == lb)
                    ret = blocks[lb].op(ret, blocks[i].prod(l - B * i, B));
                else if(i == rb)
                    ret = blocks[lb].op(ret, blocks[i].prod(0, r - B * i));
                else ret = blocks[lb].op(ret, blocks[i].all_prod());
            }
        }
        return ret;
    }
    void apply(int l, int r, Block::F f) {
        int lb = l / B;
        int rb = (r - 1) / B;
        if(lb == rb) blocks[lb].apply(l - B * lb, r - B * lb, f);
        else {
            for(int i = lb; i <= rb; i++) {
                if(i == lb) blocks[i].apply(l - B * i, B, f);
                else if(i == rb) blocks[i].apply(0, r - B * i, f);
                else blocks[i].all_apply(f);
            }
        }
    }
};