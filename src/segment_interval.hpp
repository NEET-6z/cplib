#include "template.hpp"

inline vector<pair<long, long>> segment_interval(long L, long R) {
    vector<pair<long, long>> lv, rv;
    for(long i = 0; L < R; i++) {
        if((L >> i) & 1) {
            lv.push_back({L, L + (1l << i)});
            L += 1l << i;
        }
        if((R >> i) & 1) {
            rv.push_back({R - (1l << i), R});
            R -= 1l << i;
        }
    }
    lv.insert(lv.end(), rv.rbegin(), rv.rend());
    return lv;
}