#pragma once
#include "../template.hpp"

template<class T, integral I>
T pow(T b,I k){
    T r=1;
    for(;k;k>>=1, b*=b) if(k&1) r*=b;
    return r;
}