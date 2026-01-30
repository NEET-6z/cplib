#include "../template.hpp"

struct Random {
    mt19937 mt;
    Random(){
        random_device rd;
        auto seed=rd()^std::chrono::steady_clock::now().time_since_epoch().count();
        mt.seed(seed);
    }
    int randint(int l,int r){  //[a,b]
        uniform_int_distribution<int> dist(l,r);
        return dist(mt);
    }
    float randfloat(int l=0,int r=1){
        uniform_real_distribution<float> dist(l,r);
        return dist(mt);
    }
    int operator()(){
        return mt();
    }
}