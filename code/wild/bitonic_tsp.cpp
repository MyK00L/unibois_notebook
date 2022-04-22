/* Bitonic Euclidean TSP - GiackAloZ */

const double EPS = 1e-9;
struct point {
	double x, y;
	point() : x(0), y(0) {}
	point(double _x, double _y) : x(_x), y(_y) {}
	//sort by x-coordinate
	bool operator<(const point &o) const{
		return fabs(x - o.x) > EPS ? x < o.x : y < o.y; } };

double dist(point a, point b){
	return hypot(fabs(a.x - b.x), fabs(a.y - b.y)); }

//memoization
double memo[MAXN][MAXN];
int n;

//p1 and p2 indexes the choices to make
double tsp_dp(int p1, int p2, vector<point> &p){
	//recovering parameter v from p1 and p2
	int v = 1 + max(p1,p2);
	//if we arrived at last point
	if(v == n-1)		//we wrap around
		return dist(p[p1], p[v]) + dist(p[p2], p[v]);
	double &ans = memo[p1][p2];
	if(ans != -1) return ans;
	//extend path from left to right by v from p1
	double LRext = dist(p[p1], p[v]) + tsp_dp(v, p2, p);
	//extend path from right to left by v from p2
	double RLext = dist(p[p2], p[v]) + tsp_dp(p1, v, p);
	return ans = min(LRext, RLext);
}

int main(){
	while(cin.peek() != EOF){
		int cc = scanf("%d", &n);
		if(cc < 1) return 0;
		vector<point> v(n);
		for(point &p : v){
			int x, y; cin >> x >> y;
			p = point(x,y); }
		sort(v.begin(), v.end());

		for(int i = 0; i < MAXN; i++)
			for(int j = 0; j < MAXN; j++)
				memo[i][j] = -1;
		cout << fixed << setprecision(2);
		cout << tsp_dp(0, 0, v) << '\n';
	}
}