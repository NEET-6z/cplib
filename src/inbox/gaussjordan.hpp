#include "../template.hpp"

long modinv(long a,long mod){
    long b=mod,u=1,v=0;
    while(b){
        long t=a/b;
        a-=t*b;swap(a,b);
        u-=t*v;swap(u,v);
    }
    u%=mod;
    if(u<0) u+=mod;
    return u;
}

// matrix
template<int MOD> struct Matrix {
    vector<vector<long>> val;
    Matrix(int n,int m,long x=0):val(n,vector<long>(m,x)){}
    void init(int n,int m,long x=0){val.assign(n,vector<long>(m,x));}
    size_t size() const {return val.size();}
    inline vector<long>& operator [] (int i){return val[i];}
};

//falseの場合独立な行数が得られる。trueの場合、最終列を値としてみなし連立一次方程式を解く。左辺が0なのに右辺が非ゼロの行があれば違反
template<int MOD> int GaussJordan(Matrix<MOD> &A,bool is_extended=false){ 
    int m=A.size(),n=A[0].size();
    for(int row=0;row<m;++row)
        for(int col=0;col<n;++col)
            A[row][col]=(A[row][col]%MOD+MOD)%MOD;

    int rank=0;
    for(int col=0;col<n;++col){
        if(is_extended&&col==n-1) break;
        int pivot=-1;
        for(int row=rank;row<m;++row){
            if(A[row][col]!=0){
                pivot=row;
                break;
            }
        }
        if(pivot==-1) continue;
        swap(A[pivot],A[rank]);
        auto inv=modinv(A[rank][col],MOD);
        for(int col2=0;col2<n;++col2)
            A[rank][col2]=A[rank][col2]*inv%MOD;
        for(int row=0;row<m;++row){
            if(row!=rank&&A[row][col]){
                auto fac=A[row][col];
                for(int col2=0;col2<n;++col2){
                    A[row][col2]-=A[rank][col2]*fac%MOD;
                    if(A[row][col2]<0) A[row][col2]+=MOD;
                }
            }
        }
        ++rank;
    }
    return rank;
}