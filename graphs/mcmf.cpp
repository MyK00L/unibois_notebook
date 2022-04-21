// Min-Cost Max-Flow using successive
// shortest paths - O(kVE) worst case,
// should be O(kElogE) average, with K
// being the amount of paths you find.

// change to another type if needed!
const int MAXCOST = 2e9 + 5;
const int MAXFLOW = 2e9 + 5;

// MAXN: number of maximum nodes
// T: type used to store flow
// X: type used to store costs
template <int MAXN, class T = int, class X = int>
struct MCMF {
  struct edge {
    int to, rev;
    T flow;
    X cost;
  };
  int s = MAXN - 2; // source
  int t = MAXN - 1; // sink
  vector<edge> g[MAXN];
  // f is flow/capacity, c is cost
  void add_edge(int a, int b, T f, X c, bool dir = 1) {
    g[a].push_back({b, int(g[b].size()), f, c});
    g[b].push_back({a, int(g[a].size()) - 1, dir ? 0 : f, -c});
  }
  X dist[MAXN];
  T flow[MAXN];
  queue<int> q;
  bool in_q[MAXN];
  int prev[MAXN]; // to retrace SPs
  edge* last[MAXN]; // link to edge
  bool spfa() {
    fill_n(dist, MAXN, MAXCOST);
    fill_n(flow, MAXN, MAXFLOW);
    fill_n(in_q, MAXN, 0);
    q.push(s); dist[s] = 0; in_q[s] = 1;
    prev[t] = -1;
    while(q.size()) {
      int curr = q.front();
      q.pop(); in_q[curr] = 0;
      for(auto &e : g[curr]) {
        if(e.flow > 0 && dist[curr] + e.cost < dist[e.to]) {
          dist[e.to] = dist[curr] + e.cost;
          prev[e.to] = curr;
          last[e.to] = &e;
          flow[e.to] = min(flow[curr], e.flow);
          if(!in_q[e.to]) {
            in_q[e.to] = 1, q.push(e.to);
          }
        }
      }
    }
    return prev[t] != -1;
  }
  // returns {flow, cost}
  pair<T, X> send_flow() {
    pair<T, X> ans;
    while(spfa()) {
      T pushed = flow[t];
      ans.first += pushed;
      ans.second += pushed * dist[t];
      int curr = t;
      while(curr != s) {
        edge &e = *last[curr];
        e.flow -= pushed;
        g[e.to][e.rev].flow += pushed;
        curr = prev[curr];
      }
    }
    return ans;
  }
};