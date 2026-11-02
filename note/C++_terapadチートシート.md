# 競技プログラミング用メモ（C++ / TeraPad）

## 1. 便利構文・初期化

```cpp
// C++20: メンバ順の比較
auto operator<=>(const C&) const = default;

// 配列の初期化
int a[3] = {0}; // {0,0,0}
int b[3] = {1}; // {1,0,0}
int c[3] = {};  // {0,0,0}
// ローカルの int a[3]; は未初期化。グローバル/static はゼロ初期化。
// std::array も array<int,3> a{}; でゼロ初期化。

// -1 まで入力
for (int N; cin >> N && N != -1; ) {
    // ...
}

// tie
tie(a, b) = pair{x, y};

// デバッグ（標準エラー出力）
cerr << x << '\n';

// ビット反転
~x;

// ASCII互換環境で英字の大小を反転する小技
c ^ 32; // 汎用的な文字変換には tolower / toupper
```

## 2. 便利な型

### optional

```cpp
optional<int> opt;           // 値なし
optional<int> a = 42;
auto b = make_optional(42);
auto p = make_optional(make_pair(10, 10));

if (opt) { }                 // 値あり判定
opt.has_value();
*opt;                        // 値取得（存在確認後）
opt.value();                 // 値なしなら例外
opt.value_or(100);            // 値なし時の代替値
opt = nullopt;               // 値なしにする
```

### variant

```cpp
variant<int, double, string> v = 10;
get<int>(v);                 // 型を指定して取得
if (auto p = get_if<int>(&v)) { /* *p を使う */ }
v.index();                   // 現在の型のインデックス（0始まり）
```

### 大きな数

```cpp
__int128_t x;  // GCC/Clang 拡張
__float128 y;  // 対応環境依存
```

## 3. 数値・文字の注意

```cpp
0b1001; // 9（C++14以降）

// double では 1e18 + 1 == 1e18 になり得る
long long x = 1'000'000'000'000'000'000LL + 1;
long double y = 1e18L + 1; // long double の精度は環境依存

long long scaled = llround(value * 1e4); // 小数の整数化は丸めを検討
islower((unsigned char)c); // 戻り値は0または非ゼロ。必ず1とは限らない
```

## 4. 標準ライブラリ関数

### 検索・判定

- `find`, `find_if`, `find_if_not`

- `count`, `count_if`

- `any_of`, `all_of`, `none_of`

- `binary_search`, `lower_bound`, `upper_bound`, `equal_range`

- `adjacent_find`

- `search`, `search_n`, `find_first_of`

- `equal`, `mismatch`, `lexicographical_compare`

```cpp
auto it = lower_bound(a.begin(), a.end(), x);
auto [lb, ub] = equal_range(a.begin(), a.end(), x);
```

※ 二分探索系はソート済み範囲で使用。

### 最大・最小・比較

- `min`, `max`, `minmax`

- `min_element`, `max_element`, `minmax_element`

- `clamp`（C++17）

- `lexicographical_compare`

### 初期化・生成

- `iota`, `fill`, `fill_n`

- `generate`, `generate_n`

- `copy`, `copy_n`, `copy_if`

- `move`, `swap`, `iter_swap`

```cpp
iota(a.begin(), a.end(), 0);
fill(a.begin(), a.end(), 0);
```

### 並べ替え・順序

- `sort`, `stable_sort`

- `partial_sort`, `partial_sort_copy`

- `nth_element`

- `is_sorted`, `is_sorted_until`

- `next_permutation`, `prev_permutation`

- `partition`, `stable_partition`, `partition_point`

- `shuffle`

```cpp
sort(a.begin(), a.end());
sort(a.rbegin(), a.rend()); // 降順
next_permutation(a.begin(), a.end());
```

### 削除・重複・置換

- `remove`, `remove_if`

- `unique`

- `erase_if`（C++20）

- `replace`, `replace_if`

- `replace_copy`, `replace_copy_if`

- `reverse`, `reverse_copy`

- `rotate`

- `erase`（コンテナのメンバ関数／対応する非メンバ関数）

```cpp
a.erase(remove(a.begin(), a.end(), x), a.end());
sort(a.begin(), a.end());
a.erase(unique(a.begin(), a.end()), a.end());
```

### 集計・変換

- `accumulate`（`<numeric>`）

- `reduce`, `transform_reduce`（C++17、`<numeric>`）

- `partial_sum`, `inclusive_scan`, `exclusive_scan`

- `adjacent_difference`

- `transform`

- `inner_product`

- `iota`

```cpp
long long sum = accumulate(a.begin(), a.end(), 0LL);
partial_sum(a.begin(), a.end(), b.begin());
adjacent_difference(a.begin(), a.end(), b.begin());

transform(A.begin() + 1, A.end(), A.begin(), B.begin(),
          [](int x, int y) { return x + y; });
```

### その他

- `for_each`, `for_each_n`

- `distance`, `advance`, `next`, `prev`

- `begin`, `end`, `size`, `ssize`（C++20）

- `tie`, `make_pair`, `make_tuple`, `apply`, `exchange`

- `starts_with`, `ends_with`（`basic_string`、C++20）

- `to_array`（C++20）

## 5. ビット演算

### C++20 `<bit>`

- `has_single_bit(x)`：2の冪乗か

- `bit_floor(x)`：x以下の最大の2の冪乗

- `bit_ceil(x)`：x以上の最小の2の冪乗

- `bit_width(x)`：必要ビット数

- `rotl(x, n)`, `rotr(x, n)`：左右ローテート

- `countr_zero(x)`, `countr_one(x)`

- `countl_zero(x)`, `countl_one(x)`

- `popcount(x)`：1のビット数

```cpp
has_single_bit(16u);
bit_floor(19u); // 16
bit_ceil(19u);  // 32
rotl(10u, 2);
```

### GCC 組み込み関数

- `__builtin_popcount(x)`：unsigned int の1の個数

- `__builtin_popcountll(x)`：unsigned long long の1の個数

- `__builtin_clz(x)`：上位の連続する0の個数

- `__builtin_ctz(x)`：下位の連続する0の個数

- `__builtin_ffs(x)`：最下位の1の位置（1始まり、0なら0）

- `__builtin_parity(x)`：1の個数の偶奇

※ \_\_builtin_clz(0)、\_\_builtin_ctz(0) は未定義動作。

## 6. 演算子の優先順位（高い順）

| **優先順位** | **演算子**                                                 | **結合規則** | **説明**                                                                |
|--------------|------------------------------------------------------------|--------------|-------------------------------------------------------------------------|
| **1**        | ::                                                         | 左から右     | スコープ解決                                                            |
| **2**        | () \[\] . -\> x++ x--                                      | 左から右     | 関数呼び出し、配列添字、メンバアクセス、後置インクリメント/デクリメント |
| **3**        | ++x --x +x -x ! ~ \*x &x sizeof new delete typeid キャスト | 右から左     | 単項演算子、キャスト、前置インクリメント/デクリメント                   |
| **4**        | .\* -\>\*                                                  | 左から右     | メンバポインタアクセス                                                  |
| **5**        | \* / %                                                     | 左から右     | 乗除算、剰余                                                            |
| **6**        | \+ -                                                       | 左から右     | 加算・減算                                                              |
| **7**        | \<\< \>\>                                                  | 左から右     | ビットシフト                                                            |
| **8**        | \< \<= \> \>= \<=\>                                        | 左から右     | 比較（大小）、三方比較                                                  |
| **9**        | == !=                                                      | 左から右     | 等値比較                                                                |
| **10**       | &                                                          | 左から右     | ビットAND                                                               |
| **11**       | ^                                                          | 左から右     | ビットXOR                                                               |
| **12**       | \|                                                         | 左から右     | ビットOR                                                                |
| **13**       | &&                                                         | 左から右     | 論理AND                                                                 |
| **14**       | \|\|                                                       | 左から右     | 論理OR                                                                  |
| **15**       | ?:                                                         | 右から左     | 条件（三項）演算子                                                      |
| **16**       | = += -= \*= /= %= \<\<= \>\>= &= ^= \|=                    | 右から左     | 代入・複合代入                                                          |
| **17**       | ,                                                          | 左から右     | コンマ演算子                                                            |

比較演算子を連鎖させず、必要なら括弧を付ける。

## 7. 辞書順（ASCII）

```cpp
!"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~
```

## 8. Boost 多倍長

```cpp
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
namespace mp = boost::multiprecision;
using Bint = mp::cpp_int;
using Real = mp::number<mp::cpp_dec_float<10>>;

Bint a = 123456;
Bint b("123456789012345678901234567890");
cin >> a;
string s = a.str();
int i = a.convert_to<int>();
set<Bint> st;
map<Bint, Bint> ma;
```

## 9. PBDS 順序統計木（GCC拡張）

```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<class T>
using ordered_set = tree<T, null_type, less<T>,
    rb_tree_tag, tree_order_statistics_node_update>;

ordered_set<int> s;
// s.find_by_order(k): 小さい順でk番目（0始まり）
// s.order_of_key(x): x未満の要素数
```

## 10. priority_queue の比較関数

```cpp
using P = pair<int, int>;
auto cmp = [](const P& a, const P& b) { return a > b; };
priority_queue<P, vector<P>, decltype(cmp)> pq(cmp); // pairの小さい順
```

## 11. GCC 最適化・デバッグ

```cpp
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
// #pragma GCC optimize("Ofast") // 浮動小数点の厳密性に注意

cerr << x << '\n';
```

avx2 は実行環境が対応していることを確認。Ofast は浮動小数点演算の規則を緩和する。

## 12. ターミナル標準コマンド

### 実行時間・比較

```cpp
time ./a
time ./a > /dev/null
time ./a < in > /dev/null
diff <(./a < in) out
diff -s <(./a < in) out
diff a.cpp b.cpp
```

### wc

```cpp
wc a.cpp -c  # バイト数
wc a.cpp -m  # 文字数
```

### コマンド演算子

```cpp
cmd1 ; cmd2    # 常に次を実行
cmd1 && cmd2   # 成功したら次を実行
cmd1 || cmd2   # 失敗したら次を実行
echo "10" | ./a
```

- `|`：標準出力を次へ

- `|&`：標準出力と標準エラー出力を次へ（Bash等）

- `&`：バックグラウンド実行

### ファイル操作

```cpp
> a.cpp          # 空にする
cat b > a.cpp    # 上書き
cat b >> a.cpp   # 末尾に追加
```

### 計算

```cpp
factor 360
bc
bc -l
```

bc の ^ は累乗。通常の除算は整数部。小数計算は bc -l。

## 13. TeraPad 設定メモ

### 基本

- タブ文字数：4

- オートインデント：ON

- カーソル行に下線：ON

- タイトルバーのファイル名：フルパス表示

- TAB／半角空白／全角空白を表示

- フォント：BIZ UDゴシック

- 文字コード：UTF-8N（BOMなし）

- 改行コード：LF

### ショートカット（設定環境により異なる場合あり）

| **操作**                         | **キー**                            |
|----------------------------------|-------------------------------------|
| **新規作成**                     | Ctrl + N                            |
| **開く**                         | Ctrl + O                            |
| **上書き保存**                   | Ctrl + S                            |
| **名前を付けて保存**             | Ctrl + Shift + S                    |
| **元に戻す**                     | Ctrl + Z                            |
| **やり直す**                     | Ctrl + Y                            |
| **すべて選択**                   | Ctrl + A                            |
| **コピー／切り取り／貼り付け**   | Ctrl + C / Ctrl + X / Ctrl + V      |
| **検索／置換**                   | Ctrl + F / Ctrl + R                 |
| **次／前を検索**                 | F3 / Shift + F3                     |
| **指定行へ移動**                 | Ctrl + J                            |
| **対応する括弧へ移動・選択**     | Ctrl + \[                           |
| **矩形貼り付け**                 | Ctrl + K                            |
| **行削除**                       | Ctrl + Enter                        |
| **矩形選択**                     | Ctrl + B                            |
| **矩形選択（最初は横）**         | Shift + Alt + 矢印                  |
| **小文字／大文字に変換**         | Ctrl + L / Shift + Ctrl + L         |
| **空白インデント／逆インデント** | Shift + Ctrl + I / Shift + Ctrl + U |
| **ショートカットキー表示**       | Shift + F1                          |
