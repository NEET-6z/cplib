
maxflowの計算量
一般: O(N^2M)
単位容量: O(M√N)

mincostflowの計算量
O(NM+FMlogN) Fは最大流量




牛ゲー
`d[j]<=d[i]+c(i,j)`のとき、i→jの有効辺
最短経路問題を解くと各d[i]を最大化できる


