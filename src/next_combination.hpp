#include "template.hpp"

inline bool next_combination(vector<int>& a, int n) {
    int r = si(a);
    int i = r - 1;
    while(~i && a[i] == i + n - r) i--;
    if(i == -1) return false;
    a[i]++;
    for(int j = i + 1; j < r; j++) a[j] = a[j - 1] + 1;
    return true;
}
inline bool next_combination_with_replacement(vector<int>& a, int n) {
    int r = si(a);
    for(int i = r; i--;) {
        if(a[i] < n - 1) {
            ++a[i];
            for(int j = i + 1; j < r; j++) a[j] = a[i];
            return true;
        }
    }
    return false;
}
