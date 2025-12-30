#include "../template.hpp"

vector<vector<int>> grid_bfs(vector<string>& S,int sy,int sx){
    vector<int> dd={0,1,0,-1,0};
    int H=si(S);
    int W=si(S[0]);
    vector dp(H,vector<int>(W,1e9));
    queue<pair<int,int>> q;
    dp[sy][sx]=0;
    q.push({sy,sx});
    while(si(q)){
        auto [y,x]=q.front();
        q.pop();
        rep(i,4){
            int ny=y+dd[i];
            int nx=x+dd[i+1];
            if(ny<0||H<=ny||nx<0||W<=nx) continue;
            if(dp[ny][nx]!=1e9) continue;
            if(S[ny][nx]=='#') continue;
            dp[ny][nx]=dp[y][x]+1;
            q.push({ny,nx});
        }
    }
    return dp;
};