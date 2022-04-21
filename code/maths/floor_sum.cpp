// sum x in [0,n] of (floor((ax+b)/c))
// O(log(a))
long long FloorSumAP(long long a, long long b, long long c, long long n){
	if(!a) return (b / c) * (n + 1);
	if(a >= c or b >= c) return ( ( n * (n + 1) ) / 2) * (a / c) + (n + 1) * (b / c) + FloorSumAP(a % c, b % c, c, n);
	long long m = (a * n + b) / c;
	return m * n - FloorSumAP(c, c - b - 1, a, m - 1);
}

