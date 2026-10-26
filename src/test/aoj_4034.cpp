// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=4034
#include "../string/sa.hpp"
#include "../util/random.hpp"

using P=complex<long>;
using R=pair<long, long>;

bool arglt(P a, P b){
    auto half=[](P& p){
        return p.imag()<0||(p.imag()==0&&p.real()<0);
    };
    if(half(a)!=half(b)) return half(a)<half(b);
    long c=1L*a.real()*b.imag()-1L*a.imag()*b.real();
    if(c!=0) return c>0;
    return norm(a)<norm(b);
}

using ul=unsigned long;

Random rd;
int main(){
    cin.tie(0)->ios::sync_with_stdio(0);

    map<array<long, 4>, ul> mp;

    int N, M;
    cin>>N>>M;
    vector<pair<vector<ul>, int>> A(N);
    rep(i, N) A[i].second=i;
    rep(I, N){
        vector<P> a(M);
        P md(0, 0);
        rep(i, M){
            long x, y;
            cin>>x>>y;
            P p=P(x, y);
            md+=p;
            p*=M;
            a[i]=p;
        }
        {
            vector<P> tmp;
            rep(i, M){
                a[i]-=md;
                if(abs(a[i])>0) tmp.push_back(a[i]);
            }
            swap(tmp, a);
        }
        int n=a.size();
        if(n==0) continue;
        sort(a.begin(), a.end(), arglt);
        a.push_back(a[0]);
        vector<ul> b(n);
        rep(i, n){
            P z=a[i+1]*conj(a[i]);
            long u=z.real();
            long v=z.imag();
            {
                long g=gcd(v, u);
                v/=g;
                u/=g;
            }
            long x=norm(a[i]-a[i+1]);
            long w=norm(a[i]);
            {
                long g=gcd(x, w);
                x/=g;
                w/=g;
            }
            array<long, 4> X={u, v, w, x};
            if(!mp.count(X)) mp[X]=rd();
            b[i]=mp[X];
        }
        rep(i, n) b.push_back(b[i]);
        vector<int> sa=suffix_array(b);
        int id=-1;
        rep(i, 2*n) if(sa[i]<n){
            id=sa[i];
            break;
        }
        vector<ul> B(n);
        rep(i, n) B[i]=b[i+id];
        A[I].first=B;
    }
    vector<vector<int>> ans(N);
    sort(A.begin(), A.end());
    rep(l, N){
        int r=l+1;
        vector<int> z={A[l].second};
        while(r<N&&A[l].first==A[r].first) z.push_back(A[r].second), r++;
        for(int i:z) for(int j:z) if(i!=j) ans[i].push_back(j);
        l=r-1;
    }
    rep(i, N){
        cout<<ans[i].size();
        for(int j: ans[i]) cout<<" "<<j+1;
        cout<<"\n";
    }

}
