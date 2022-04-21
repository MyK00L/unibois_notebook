// K-dimensional Fenwick Tree.
// Operations are in O(log^k(n)).
// 1d version just wraps fenwick.cpp

int lsb(int n) { return n&-n; }

vi get_next(vi v){
	return vi(v.begin() + 1, v.end());
}

template <int D> 
struct k_fenwick {
	vector<k_fenwick<D - 1>> v;
	// assert: sizes.size() == D
	k_fenwick(vi sizes) : v(sizes[0] + 1, vi(sizes.begin() + 1, sizes.end())){}
	void add(vi is, int k){
		vi next = get_next(is);
		for(int i = is[0] + 1; i < v.size(); i += lsb(i))
			v[i].add(next, k);
	}
	int query(vi is){
		vi next = get_next(is);
		int ans = 0;
		for(int i = is[0] + 1; i > 0; i -= lsb(i))
			ans += v[i].query(next);
		return ans;
	}
	int rsq(vi ls, vi rs){
		vi next_ls = get_next(ls);
		vi next_rs = get_next(rs);
		int ans = 0;
		for(int i = rs[0] + 1; i > 0; i -= lsb(i))
			ans += v[i].rsq(next_ls, next_rs);
		for(int i = ls[0]; i > 0; i -= lsb(i))
			ans -= v[i].rsq(next_ls, next_rs);
		return ans;
	}
};

// Specialized 1D version that wraps standard fenwick tree
template <> struct k_fenwick<1> {
	fenwick ft;
	k_fenwick(vi sizes) : ft(sizes[0]){}
	int query(vi sizes) { return ft.sum(sizes[0]);}
	void add(vi sizes, int k) { ft.add(sizes[0], k);}
	int rsq(vi ls, vi rs) { return ft.rsq(ls[0], rs[0]);}
};