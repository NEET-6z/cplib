#pragma once
#include "template.hpp"

template<typename T, int MAX_N> struct Combination {
    array<T, MAX_N + 1> fa{}, ifa{};
    constexpr Combination() {
        fa[0] = 1;
        for(int i = 1; i <= MAX_N; i++) fa[i] = fa[i - 1] * i;
        ifa[MAX_N] = fa[MAX_N].inv();
        for(int i = MAX_N; i >= 1; i--) ifa[i - 1] = ifa[i] * i;
    }

    T fact(int n){
        return fa[n];
    }

    T inv_fact(int n){
        return ifa[n];
    }

    T C(int n, int k) {
        if(k < 0 || k > n) return 0;
        return fa[n] * ifa[k] * ifa[n - k];
    }

    T P(int n, int k) {
        if(k < 0 || k > n) return 0;
        return fa[n] * ifa[n - k];
    }

    T H(int n, int k) {
        if(n == 0 && k == 0) return 1;
        if(n <= 0 || k < 0) return 0;
        return C(n + k - 1, k);
    }
    // n<=m+K
    T Kata(int n, int m, int k) {
        if(n > m + k) return 0;
        return C(n + m, n) - C(n + m, n - k - 1);
    };    
};


