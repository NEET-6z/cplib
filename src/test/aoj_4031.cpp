// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=4031
// competitive-verifier: ERROR 1e-4
#include "../geometry/circle.hpp"


const S inf=1e12;

int main(){
    int N;
    cin>>N;
    vector<Circle> A(N);
    rep(i, N){
        int x, y, r;
        cin>>x>>y>>r;
        A[i]=Circle(P(x, y), r);
    }
    vector<P> B;
    B.push_back(P(0, 0));
    rep(i, N) rep(j, i){
        auto [a, b]=crosspoint_cc(A[i], A[j]);
        B.push_back(a);
        if(a!=b) B.push_back(b);
    }
    int M=B.size();

    vector<pair<S, pair<int, int>>> E;
    vector<pair<S, int>> F;
    vector<vector<pair<S, int>>> G(M);
    rep(i, N){
        vector<pair<S, int>> V;
        rep(j, M){
            if(abs(abs(A[i].o-B[j])-A[i].r)<=EPS){
                S a=arg(B[j]-A[i].o);
                if(a<0) a+=2*PI;
                V.emplace_back(a, j);
            }

        }
        sort(V.begin(), V.end());
        int L=(int)V.size();
        if(L==1) F.emplace_back(A[i].r*PI, V[0].second);
        else{
            rep(k, L){
                S s=V[(k+1)%L].first-V[k].first;
                if(s<0) s+=PI*2;
                if(s<0) s=0;
                s=s*180/PI;
                S c=2*A[i].r*PI*(s/360);
                G[V[k].second].emplace_back(c, V[(k+1)%L].second);
                G[V[(k+1)%L].second].emplace_back(c, V[k].second);
            }
        }
    }

    vector<S> dp(M, inf);
    using T=pair<S, int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    rep(i, M){
        if(abs(B[i])<=EPS){
            dp[i]=0;
            pq.push({(S)0, i});
        }
    }
    while(!pq.empty()){
        auto [k, v]=pq.top();
        pq.pop();
        if(k>dp[v]) continue;
        for(auto [c, e]:G[v]){
            if(dp[e]>dp[v]+c){
                dp[e]=dp[v]+c;
                pq.push({dp[e], e});
            }
        }
    }

    S ans=0;
    rep(i, M) if(dp[i]!=inf) ans=max(ans, dp[i]);
    rep(i, M) for(auto [c, j]:G[i]){
        if(dp[i]==inf||dp[j]==inf) continue;
        S a=dp[i];
        S b=dp[j];
        if(a>b) swap(a, b);
        assert((b-a)-c<=EPS);
        ans=max(ans, b+(c-(b-a))/2);
    }
    for(auto [c, i]:F) if(dp[i]!=inf) ans=max(ans, dp[i]+c);

    cout<<fixed<<setprecision(15);
    cout<<ans<<"\n";

}

