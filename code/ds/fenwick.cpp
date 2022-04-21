// Fenwick tree with lower bound.
// All operations are fast and O(logN).
// Build is O(N). 
// Trick: use map/umap to make it sparse,
// for an extra log.

int lsb(int n) { return n&-n; }

struct fenwick{
	vi v;
	fenwick(int sz) : v(sz+1){}
  fenwick(vi x) : v(x.size() + 1) {
    for(int i = 0; i < x.size(); i++) {
      v[i+1] += x[i];
      if((i+1) + lsb())
    }
  }
	void add(int i, int k){
		for(++i; i < v.size(); i += lsb(i))
			v[i] += k;
	}
	int sum(int i){
		int ans = 0;
		for(++i; i > 0; i -= lsb(i))
			ans += v[i];
		return ans;
	}
	int rsq(int l, int r){
		return sum(r) - sum(l-1);
	}
  // returns the idx i of the first position
  // such that sum[0, i] > k
  int lb(int k) {
    // "kth element has sum = k+1"
    k++;
    int sum = 0, pos = 0;
    for(int i = 1<<bits; i; i >>= 1) {
      if(pos + i < v.size() && sum + v[pos + i] < k) {
        pos += i;
        sum += v[pos];
      }
    }
    return pos; 
  }
};