#include "template.hpp"


inline bool next_combination(vector<int>& ids, int n){
    int r=si(ids);
    int i=r-1;
    while(~i&&ids[i]==i+n-r) i--;
    if(i==-1) return false;
    ids[i]++;
    for(int j=i+1;j<r;j++) ids[j]=ids[j-1]+1;
    return true;
}
inline bool next_combination_with_replacement(vector<int>& ids, int n) {
    int r = si(ids);
    for(int i=r;i--;){
        if (ids[i]<n-1) {
            ++ids[i];
            for(int j=i+1;j<r;j++) ids[j]=ids[i];
            return true;
        }
    }
    return false;
}
