# 公開関数一覧

## impl_treap.hpp

| 関数              | 処理          |
| --------------- | ----------- |
| `insert(k, x)`  | k番目にxを挿入    |
| `erase(k)`      | k番目の要素を削除   |
| `push_front(x)` | 先頭にxを追加     |
| `push_back(x)`  | 末尾にxを追加     |
| `pop_front()`   | 先頭の要素を削除    |
| `pop_back()`    | 末尾の要素を削除    |
| `size()`        | 要素数を取得      |
| `empty()`       | 空かどうかを判定    |
| `split(k)`      | k番目で分割      |
| `join(l, r)`    | 2つのTreapを結合 |

## treap_seg.hpp

| 関数                | 処理                  |
| ----------------- | ------------------- |
| `insert(k, x)`    | キーkにxを挿入（既存キーは上書き）  |
| `erase(k)`        | キーkの要素を削除           |
| `find(k)`         | キーkの値を取得            |
| `at(k)`           | k番目のノードを取得          |
| `lower_bound(k)`  | k以上のキーを持つ最初の要素の添字   |
| `upper_bound(k)`  | kより大きいキーを持つ最初の要素の添字 |
| `fold(l, r)`      | キー区間 [l, r) の総積を取得  |
| `all()`           | 全要素の総積を取得           |
| `size()`          | 要素数を取得              |
| `empty()`         | 空かどうかを判定            |
| `split(k)`        | キーk未満とk以上に分割        |
| `join(l, r)`      | 2つのTreapを結合         |
| `max_right(l, f)` | 条件fを満たす右端を探索        |
| `min_left(r, f)`  | 条件fを満たす左端を探索        |

## impl_treap_seg.hpp

| 関数                | 処理               |
| ----------------- | ---------------- |
| `set(k, x)`       | k番目の値をxに変更       |
| `get(k)`          | k番目の値を取得         |
| `fold(l, r)`      | 区間 [l, r) の総積を取得 |
| `reverse(l, r)`   | 区間 [l, r) を反転    |
| `insert(k, x)`    | k番目にxを挿入         |
| `erase(k)`        | k番目の要素を削除        |
| `push_front(x)`   | 先頭にxを追加          |
| `push_back(x)`    | 末尾にxを追加          |
| `pop_front()`     | 先頭の要素を削除         |
| `pop_back()`      | 末尾の要素を削除         |
| `size()`          | 要素数を取得           |
| `empty()`         | 空かどうかを判定         |
| `split(k)`        | k番目で分割           |
| `join(l, r)`      | 2つのTreapを結合      |
| `max_right(l, f)` | 条件fを満たす右端を探索     |
| `min_left(r, f)`  | 条件fを満たす左端を探索     |

## treap_lazyseg.hpp

| 関数                | 処理                  |
| ----------------- | ------------------- |
| `insert(k, x)`    | キーkにxを挿入（既存キーは上書き）  |
| `erase(k)`        | キーkの要素を削除           |
| `find(k)`         | キーkの値を取得            |
| `at(k)`           | k番目のノードを取得          |
| `lower_bound(k)`  | k以上のキーを持つ最初の要素の添字   |
| `upper_bound(k)`  | kより大きいキーを持つ最初の要素の添字 |
| `fold(l, r)`      | キー区間 [l, r) の総積を取得  |
| `update(l, r, f)` | キー区間 [l, r) に作用fを適用 |
| `all()`           | 全要素の総積を取得           |
| `size()`          | 要素数を取得              |
| `empty()`         | 空かどうかを判定            |
| `split(k)`        | キーk未満とk以上に分割        |
| `join(l, r)`      | 2つのTreapを結合         |
| `max_right(l, f)` | 条件fを満たす右端を探索        |
| `min_left(r, f)`  | 条件fを満たす左端を探索        |

## impl_treap_lazyseg.hpp

| 関数                | 処理                |
| ----------------- | ----------------- |
| `update(l, r, x)` | 区間 [l, r) に作用xを適用 |
| `fold(l, r)`      | 区間 [l, r) の総積を取得  |
| `reverse(l, r)`   | 区間 [l, r) を反転     |
| `insert(k, x)`    | k番目にxを挿入          |
| `erase(k)`        | k番目の要素を削除         |
| `push_front(x)`   | 先頭にxを追加           |
| `push_back(x)`    | 末尾にxを追加           |
| `pop_front()`     | 先頭の要素を削除          |
| `pop_back()`      | 末尾の要素を削除          |
| `size()`          | 要素数を取得            |
| `empty()`         | 空かどうかを判定          |
| `split(k)`        | k番目で分割            |
| `join(l, r)`      | 2つのTreapを結合       |
| `max_right(l, f)` | 条件fを満たす右端を探索      |
| `min_left(r, f)`  | 条件fを満たす左端を探索      |

## 共通事項

- 区間指定は半開区間 [l, r)。
- `fold` はモノイド演算による区間集約を行う。
- `update` は遅延伝播による区間更新を行う。
- `split` は元のTreapを2つに分割する。
- `join` は2つのTreapを結合する。
- 各操作の基本計算量は期待 \\(O(\log N)\\)。