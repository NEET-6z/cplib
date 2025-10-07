#pragma once
#include "template.hpp"
#include "modint.hpp"

template<int MAX_N> struct Binomial {
    array<mint, N + 1> fact{}, ifact{};

    constexpr Binomial(int n) {
        fa[0] = 1;
        for(int i = 1; i <= n; i++) fa[i] = fa[i - 1] * i;
        ifa[n] = fa[n].inv();
        for(int i = n; i >= 1; i--) ifa[i - 1] = ifa[i] * i;
    }

    mint C(int n, int k) const {
        if(k < 0 || k > n) return 0;
        return fa[n] * ifa[k] * ifa[n - k];
    }

    mint P(int n, int k) const {
        if(k < 0 || k > n) return 0;
        return fa[n] * ifa[n - k];
    }

    mint H(int n, int k) const {
        if(n == 0 && k == 0) return 1;
        if(n <= 0 || k < 0) return 0;
        return C(n + k - 1, k);
    }
    // n<=m+K
    mint Kata(int n, int m, int k) -> mint {
        if(n > m + k) return 0;
        return nCk(n + m, n) - nCk(n + m, n - k - 1);
    };
};