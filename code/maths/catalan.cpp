
// Catalan(n) = Choose(2n,n)/(n+1)
// Number of correct bracket sequence consisting of n opening and n closing brackets.
// The number of rooted full binary trees with n+1 leaves
// The number of triangulations of a convex polygon with n+2 sides
// The number of monotonic lattice paths from (0,0) to (n,n) that don't pass above the main diagonal
const int MOD = 1000000007;
const int MAX = 1000;
int catalan[MAX];
void init() {
	catalan[0] = catalan[1] = 1;
	for (int i=2; i<=n; i++) {
		catalan[i] = 0;
		for (int j=0; j < i; j++)
			catalan[i] = (catalan[j] * catalan[i-j-1] + catalan[i]) % MOD;
	}
}


// The number of ways to put n identical objects into k labeled boxes is Choose(n+k-1,n)

