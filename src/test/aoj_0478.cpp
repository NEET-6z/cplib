// competitive-verifier: PROBLEM https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0478
#include "../tree/hld.hpp"
#include "../segtree/segtree.hpp"

const long mod=(1L<<61)-1;
long rd=7954398468495l;

long add(long a, long b){return (a+=b)>=mod?a-mod:a;}
long mul(long a, long b){
    __int128_t c=(__int128_t)a*b;
    return add(c>>61, c&mod);
}

long pw[1<<20];

using S=pair<long, int>;
S op(S l, S r){
    return S{add(mul(l.first, pw[r.second]), r.first), l.second+r.second};
}
S e(){
    return S{0, 0};
}

int main(){
    pw[0]=1;
    rep(i, (1<<20)-1) pw[i+1]=mul(pw[i], rd);

    int N;
    cin>>N;
    vector<S> A(N);
    rep(i, N){
        char c;
        cin>>c;
        A[i]=S{c-'a'+1, 1};
    }
    vector<vector<int>> G(N);
    rep(i, N-1){
        int u, v;
        cin>>u>>v;
        u--;v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    HLD hld(G);
    segtree<S, op, e> seg(2*N);
    rep(i, N) seg.set(hld.order[i], A[i]), seg.set(2*N-1-hld.order[i], A[i]);
    int Q;
    cin>>Q;
    set<long> st;
    while(Q--){
        int o;
        cin>>o;
        if(o==1){
            int s, t;
            cin>>s>>t;
            s--;t--;
            S cur=e();
            for(auto [l, r]:hld.path_decompose(s, t, false)) cur=op(cur, seg.prod(l, r));
            st.insert(cur.first);
            cout<<st.size()<<"\n";
        }
        else{
            int k;
            char c;
            cin>>k>>c;
            k--;
            A[k].first=c-'a'+1;
            seg.set(hld.order[k], A[k]), seg.set(2*N-1-hld.order[k], A[k]);
        }
    }

}