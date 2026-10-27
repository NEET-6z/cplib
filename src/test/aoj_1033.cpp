// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1033
// competitive-verifier: ERROR 1e-5
#include "../geometry/arrangement.hpp"


int main(){
    for(int N;cin>>N,N!=0;){

        vector<Line> A(N);
        rep(i,N)cin>>A[i].a>>A[i].b;
        vector<P> ps;
        P sp,gp;
        cin>>sp>>gp;
        vector<vector<pair<int,S>>> G=segment_arrangement(A,ps);
        N=0;
        vector<pair<int,int>> es;
        rep(i,G.size())for(auto &e:G[i])e.second=N++,es.emplace_back(i, e.first);
        
        vector<vector<pair<int,S>>> H(N);
        rep(i,N){
            int f=es[i].first;
            int j=es[i].second;
            for(auto &[k,e]:G[j]){
                H[i].emplace_back(e,radtodeg(angle_diff(ps[j]-ps[f], ps[k]-ps[j])));
            }
        }
        vector<S> dp(N,1e9);
        priority_queue<pair<S,int>,vector<pair<S,int>>,greater<>> pq;
        rep(i,N)if(ps[es[i].first]==sp)dp[i]=0,pq.push({0,i});
        while(!pq.empty()){
            auto [k,v]=pq.top();
            pq.pop();
            if(dp[v]<k) continue;
            for(auto [e,c]:H[v]){
                if(dp[e]<=k+c) continue;
                dp[e]=k+c;
                pq.push({dp[e],e});
            }
        }
        S ans=1e9;
        rep(i,N)if(ps[es[i].second]==gp)ans=min(ans, dp[i]);
        if(ans==1e9)ans=-1;
        cout<<ans<<"\n";
    }
}