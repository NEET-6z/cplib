#include "../template.hpp"

template <typename T>
vector<tuple<T, int, int>> manhattan_mst(vector<T> xs, vector<T> ys){
    const int n=xs.size();
    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    vector<tuple<T, int, int>> ret;
    for(int s=0;s<2;s++){
        for(int t=0;t<2;t++){
            auto cmp=[&](int i, int j) {return xs[i]+ys[i]<xs[j]+ys[j];};
            sort(idx.begin(), idx.end(), cmp);
            map<T, int> sweep;
            for(int i : idx){
                for(auto it=sweep.lower_bound(-ys[i]);it!=sweep.end();it=sweep.erase(it)){
                    int j=it->second;
                    if(xs[i]-xs[j]<ys[i]-ys[j]) break;
                    ret.emplace_back(abs(xs[i]-xs[j])+abs(ys[i]-ys[j]), i, j);
                }
                sweep[-ys[i]]=i;
            }
            swap(xs, ys);
        }
        for(auto& x : xs) x=-x;
    }
    sort(ret.begin(), ret.end());
    return ret;
}