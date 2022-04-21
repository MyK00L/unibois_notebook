// Reminder: make at least two hashstrings if
// you want to avoid collisions

// values in P need to be larger than |alphabet|
const ll Ps[] = {27509, 83339, 3659, 47521};
const ll Qs[] = {1e9+7, 1e9+9, 1e9+21, 1e9+33};

template<ll P, ll Q>
struct hashstring {
	vector<int> h;
	vector<int> pp;
	hashstring(string &s) : h(s.size()), pp(s.size() + 1){
		h[0] = s[0];
		for(int i = 1; i < s.size(); i++)
			h[i] = (h[i-1] * P + s[i]) % Q;
		pp[0] = 1;
		for(int i = 1; i < pp.size(); i++)
			pp[i] = pp[i-1] * P % Q;
	}
	int get_hash(int l, int r) {
		int total = h[r];
		int pref = l ? h[l-1] * ll(pp[r-l+1]) % Q : 0;
		return (total - pref + Q) % Q;
	}
};

