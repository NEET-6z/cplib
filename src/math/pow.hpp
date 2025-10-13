#pragma once
#include "../template.hpp"

template<class T>
T POW(T x, long n){
    T ret = 1;
    while(n){
        if(n & 1) ret*=x;
        x*=x;
        n>>=1L;
    }
    return ret;
}