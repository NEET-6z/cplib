#include "../template.hpp"

template<class T,class F>
T threeway_search(T low,T high,F f,int itr){
    while(itr--){
        T l=(low*2+high)/3;
        T r=(low+high*2)/3;
        if(f(l)>f(r)) low=l;
        else high=r;
    }
    return low;
}