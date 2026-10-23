#include "../../template.hpp"

//f(i,j,k) min:A[i][j]<=A[i][k], max:A[i][j]>=A[i][k]
vector<int> monotone_minima(int H, int W, const function<bool(int, int, int)>& f){
    vector<int> arm(H);
    auto dfs=[&](auto dfs, int U, int D, int L, int R){
        if(U>D) return;
        int M=(U+D)/2;
        int id=-1;
        for(int i=L;i<=R;i++){
            if(id==-1||!f(M, id, i)){
                id=i;
            }
        }
        arm[M]=id;
        dfs(dfs, U, M-1, L, id);
        dfs(dfs, M+1, D, id, R);
    };
    dfs(dfs, 0, H-1, 0, W-1);
    return arm;
}

template <typename T>
vector<int> monotone_minima(int N, int M, const function<T(int, int)>& A){
    function<bool(int, int, int)> f=[&](int i, int j, int k)->bool {
        return A(i, j)<=A(i, k);
    };
    return monotone_minima(N, M, f);
}