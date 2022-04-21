// point update range query segtree
const int N = 1e5;  // limit for array size
int n;  // array size
S t[2 * N]; // t[n..] contains original array
void build() {  // build the tree
  for (int i = n - 1; i > 0; --i) t[i] = combine(t[i<<1],t[i<<1|1]);
}
void modify(int p, const S& value) {
  for (t[p += n] = value; p >>= 1; ) t[p] = combine(t[p<<1], t[p<<1|1]);
}
S query(int l, int r) {
  S resl, resr;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) resl = combine(resl, t[l++]);
    if (r&1) resr = combine(t[--r], resr);
  }
  return combine(resl, resr);
}

