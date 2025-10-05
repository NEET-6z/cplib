---
data:
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  dependencies:
  - files: []
    type: Depends on
  - files: []
    type: Required by
  - files:
    - filename: a.cpp
      icon: TEST_ACCEPTED
      path: src/test/a.cpp
    type: Verified with
  dependsOn: []
  embedded:
  - code: "#include<bits/stdc++.h>\nusing namespace std;\n\ntemplate<class S,S(*op)(S,S),S(*e)()>struct\
      \ segtree{\n  int n;vector<S> t;\n  segtree(int n_): n(__bit_ceil(n_)), t(n*2,\
      \ e()) {}\n  void set(int i,S x){for(t[i+=n]=x;i>>=1;)t[i]=op(t[i*2],t[i*2+1]);}\n\
      \  S operator[](int k){return t[k+n];}\n  S prod(int l,int r){\n    S L=e(),R=e();\n\
      \    for(l+=n,r+=n;l<r;l>>=1,r>>=1){\n      if(l&1)L=op(L,t[l++]);\n      if(r&1)R=op(t[--r],R);\n\
      \    }\n    return op(L,R);\n  }\n};\n"
    name: default
  - code: "#line 1 \"src/segtree.hpp\"\n#include<bits/stdc++.h>\nusing namespace std;\n\
      \ntemplate<class S,S(*op)(S,S),S(*e)()>struct segtree{\n  int n;vector<S> t;\n\
      \  segtree(int n_): n(__bit_ceil(n_)), t(n*2, e()) {}\n  void set(int i,S x){for(t[i+=n]=x;i>>=1;)t[i]=op(t[i*2],t[i*2+1]);}\n\
      \  S operator[](int k){return t[k+n];}\n  S prod(int l,int r){\n    S L=e(),R=e();\n\
      \    for(l+=n,r+=n;l<r;l>>=1,r>>=1){\n      if(l&1)L=op(L,t[l++]);\n      if(r&1)R=op(t[--r],R);\n\
      \    }\n    return op(L,R);\n  }\n};\n"
    name: bundled
  isFailed: false
  isVerificationFile: false
  path: src/segtree.hpp
  pathExtension: hpp
  requiredBy: []
  timestamp: '2025-10-05 10:49:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - src/test/a.cpp
documentation_of: src/segtree.hpp
layout: document
---
