---
data:
  attributes:
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
  dependencies:
  - files:
    - filename: segtree.hpp
      icon: LIBRARY_ALL_AC
      path: src/segtree.hpp
    type: Depends on
  - files: []
    type: Required by
  - files: []
    type: Verified with
  dependsOn:
  - src/segtree.hpp
  embedded:
  - code: "// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A\n\
      #include \"../segtree.hpp\"\n\nint op(int l, int r){return min(l,r);}\nint e(){return\
      \ INT_MAX;}\n\nint main(){\n    ios::sync_with_stdio(false);\n    cin.tie(nullptr);\n\
      \n    int n,q;\n    cin>>n>>q;\n    segtree<int,op,e> seg(n);\n    while(q--){\n\
      \        int com,x,y;\n        cin>>com>>x>>y;\n        if(com==0){\n      \
      \      seg.set(x,y);\n        }\n        else{\n            y++;\n         \
      \   cout<<seg.prod(x,y)<<\"\\n\";\n        }\n    }\n}"
    name: default
  - code: "#line 1 \"src/test/a.cpp\"\n// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A\n\
      #line 1 \"src/segtree.hpp\"\n#include<bits/stdc++.h>\nusing namespace std;\n\
      \ntemplate<class S,S(*op)(S,S),S(*e)()>struct segtree{\n  int n;vector<S> t;\n\
      \  segtree(int n_): n(__bit_ceil(n_)), t(n*2, e()) {}\n  void set(int i,S x){for(t[i+=n]=x;i>>=1;)t[i]=op(t[i*2],t[i*2+1]);}\n\
      \  S operator[](int k){return t[k+n];}\n  S prod(int l,int r){\n    S L=e(),R=e();\n\
      \    for(l+=n,r+=n;l<r;l>>=1,r>>=1){\n      if(l&1)L=op(L,t[l++]);\n      if(r&1)R=op(t[--r],R);\n\
      \    }\n    return op(L,R);\n  }\n};\n#line 3 \"src/test/a.cpp\"\n\nint op(int\
      \ l, int r){return min(l,r);}\nint e(){return INT_MAX;}\n\nint main(){\n   \
      \ ios::sync_with_stdio(false);\n    cin.tie(nullptr);\n\n    int n,q;\n    cin>>n>>q;\n\
      \    segtree<int,op,e> seg(n);\n    while(q--){\n        int com,x,y;\n    \
      \    cin>>com>>x>>y;\n        if(com==0){\n            seg.set(x,y);\n     \
      \   }\n        else{\n            y++;\n            cout<<seg.prod(x,y)<<\"\\\
      n\";\n        }\n    }\n}\n"
    name: bundled
  isFailed: false
  isVerificationFile: true
  path: src/test/a.cpp
  pathExtension: cpp
  requiredBy: []
  testcases:
  - elapsed: 0.005057140000644722
    environment: g++
    memory: 3.712
    name: 00_small_00.in
    status: AC
  - elapsed: 0.003718283000125666
    environment: g++
    memory: 3.584
    name: 00_small_01.in
    status: AC
  - elapsed: 0.004193989998384495
    environment: g++
    memory: 3.584
    name: 00_small_02.in
    status: AC
  - elapsed: 0.005103503001009813
    environment: g++
    memory: 3.584
    name: 00_small_03.in
    status: AC
  - elapsed: 0.004595813999912934
    environment: g++
    memory: 3.712
    name: 01_rand_00.in
    status: AC
  - elapsed: 0.005187913999179727
    environment: g++
    memory: 3.712
    name: 01_rand_01.in
    status: AC
  - elapsed: 0.00934761200005596
    environment: g++
    memory: 3.584
    name: 01_rand_02.in
    status: AC
  - elapsed: 0.007543457999418024
    environment: g++
    memory: 3.712
    name: 01_rand_03.in
    status: AC
  - elapsed: 0.008482844999889494
    environment: g++
    memory: 3.712
    name: 02_biased_00.in
    status: AC
  - elapsed: 0.007284413999514072
    environment: g++
    memory: 3.584
    name: 02_biased_01.in
    status: AC
  - elapsed: 0.007224744000268402
    environment: g++
    memory: 3.712
    name: 02_biased_02.in
    status: AC
  - elapsed: 0.03070271300020977
    environment: g++
    memory: 3.84
    name: 02_biased_03.in
    status: AC
  - elapsed: 0.007014814000285696
    environment: g++
    memory: 3.584
    name: 03_rand_00.in
    status: AC
  - elapsed: 0.00984120199973404
    environment: g++
    memory: 3.584
    name: 03_rand_01.in
    status: AC
  - elapsed: 0.006179612999403616
    environment: g++
    memory: 3.712
    name: 03_rand_02.in
    status: AC
  - elapsed: 0.010134362000826513
    environment: g++
    memory: 3.712
    name: 03_rand_03.in
    status: AC
  - elapsed: 0.02139657400039141
    environment: g++
    memory: 4.352
    name: 03_rand_04.in
    status: AC
  - elapsed: 0.021885920999920927
    environment: g++
    memory: 4.352
    name: 03_rand_05.in
    status: AC
  - elapsed: 0.020827092999752495
    environment: g++
    memory: 4.352
    name: 04_maximum_00.in
    status: AC
  - elapsed: 0.021357757999794558
    environment: g++
    memory: 4.352
    name: 04_maximum_01.in
    status: AC
  timestamp: '2025-10-05 10:54:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: src/test/a.cpp
layout: document
---
