#include "../../template.hpp"

template<typename T>
vector<int> monotone_minima(int H,int W,const function<T(int,int)>& f){
    vector<int> arm(H);
    auto dfs=[&](auto dfs, int U,int D,int L,int R){
        if(U>D) return;
        int M=(U+D)/2;
        int id=-1;
        for(int i=L;i<=R;i++){
            if(id==-1||f(M,id)>f(M,i)){
                id=i;
            }
        }
        arm[M]=id;
        dfs(dfs,U,M-1,L,id);
        dfs(dfs,M+1,D,id,R);
    };
    dfs(dfs,0,H-1,0,W-1);
    return arm;
}