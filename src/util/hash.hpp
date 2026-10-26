#include "../template.hpp"

template<class T>
struct Hash {
    size_t operator()(const T& x)const {
        return hash<T>{}(x);
    }
};

template<class T, class U>
struct Hash<pair<T, U>> {
    size_t operator()(const pair<T, U>& p)const {
        size_t h=Hash<T>{}(p.first);
        h^=Hash<U>{}(p.second)+0x9e3779b9+(h<<6)+(h>>2);
        return h;
    }
};

template<class T>
struct Hash<vector<T>> {
    size_t operator()(const vector<T>& v)const {
        size_t h=0;
        for(auto& x : v)
            h^=Hash<T>{}(x)+0x9e3779b9+(h<<6)+(h>>2);
        return h;
    }
};

template<class T, size_t N>
struct Hash<array<T, N>> {
    size_t operator()(const array<T, N>& a)const {
        size_t h=0;
        for(auto& x : a)
            h^=Hash<T>{}(x)+0x9e3779b9+(h<<6)+(h>>2);
        return h;
    }
};

template<class K, class V>
using HashMap=unordered_map<K, V, Hash<K>>;
// vector/array/pairをkeyに使える
