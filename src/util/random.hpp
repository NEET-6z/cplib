#include "../template.hpp"

struct Random {
    mt19937 mt;
    Random(){
        random_device rd;
        auto seed=rd()^chrono::steady_clock::now().time_since_epoch().count();
        mt.seed(seed);
    }
    int randint(int l, int r){  //[a,b]
        uniform_int_distribution<int> dist(l, r);
        return dist(mt);
    }
    float randfloat(int l=0, int r=1){
        uniform_real_distribution<float> dist(l, r);
        return dist(mt);
    }
    int operator()(){
        return mt();
    }
};


struct SplitMix64 {
    uint64_t state;
    uint64_t splitmix64(uint64_t x){
        x=(x^(x>>30))*0xbf58476d1ce4e5b9ULL;
        x=(x^(x>>27))*0x94d049bb133111ebULL;
        return x^(x>>31);
    }
    SplitMix64(uint64_t seed=0):state(seed){}
    uint64_t operator()(){return splitmix64(state+=0x9e3779b97f4a7c15ULL);}
};
