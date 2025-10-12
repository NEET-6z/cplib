#include "../template.hpp"

inline vector<array<long, 3>> floor_intervals(long N) {
    vector<array<long, 3>> ret;
    for(long i = 1; i <= N;) {
        long q = N / i;
        long j = N / q;
        ret.push_back({i, j + 1, q});
        i = j + 1;
    }
    return ret;
}