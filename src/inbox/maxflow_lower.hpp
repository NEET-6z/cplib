#include "../graph/maxflow.hpp"

template <typename Cap>
struct MaxFlowLowerBound {
  maxflow<Cap> mf;
  vector<Cap> in, up;
  int ts_edge, st_edge;
  int X, Y, V;
  Cap sum;

  MaxFlowLowerBound(int V) : mf(V + 2), in(V), X(V), Y(V + 1), V(V), sum(0) {}

  void add_edge(int from, int to, Cap low, Cap high) {
    assert(from != to);
    mf.add_edge(from, to, high - low);
    in[from] -= low;
    in[to] += low;
    up.emplace_back(high);
  }

  void build() {
    for (int i = 0; i < V; i++) {
      if (in[i] > 0) {
        mf.add_edge(X, i, in[i]);
        sum += in[i];
      } else if (in[i] < 0) {
        mf.add_edge(i, Y, -in[i]);
      }
    }
  }

  bool can_flow(int s, int t) {
    assert(s != t);
    mf.add_edge(t, s, mf.INF);
    ts_edge = (int)mf.g[t].size() - 1;
    st_edge = (int)mf.g[s].size() - 1;
    return can_flow();
  }

  bool can_flow() {
    build();
    auto ret = mf.flow(X, Y);
    return ret >= sum;
  }

  optional<Cap> flow(int s, int t) {
    if (can_flow(s, t)) {
      return mf.flow(s, t);
    } else {
      return nullopt;
    }
  }

  optional<Cap> min_flow(int s, int t) {
    if (can_flow(s, t)) {
      auto ret = mf.INF - mf.g[t][ts_edge].cap;
      mf.graph[t][ts_edge].cap = mf.g[s][st_edge].cap = 0;
      return ret - mf.flow(t, s);
    } else {
      return nullopt;
    }
  }

  void output(int M) {
    vector<Cap> ans(M);
    for (int i = 0; i < mf.g.size(); i++) {
      for (auto& e : mf.g[i]) {
        if (!e.isrev && ~e.idx) ans[e.idx] = up[e.idx] - e.cap;
      }
    }
    for (auto& p : ans) cout << p << endl;
  }
};
