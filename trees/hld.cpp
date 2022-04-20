#include "../template.cpp"
const int MN = 100005;
vector<int> g[MN]; // graph with bidirectional adjlist
int siz[MN]; // size of subtree
int ord[MN]; // hld order
int _ord; // temp to fill ord
int f[MN]; // parent in tree
int cf[MN]; // chain father (highest node in the chain)
int ch[MN]; // depth of the chain (how many chains are above this chain)
void df0(int p) {
	siz[p]=1;
	int ma=0;
	for(auto &i:g[p]) if(i!=f[p]) {
		f[i]=p;
		df0(i);
		siz[p]+=siz[i];
		if(siz[i]>ma) {
			ma=siz[i];
			swap(i,g[p][0]);
		}
	}
}
void df1(int p) {
	ord[p]=_ord++;
	for(auto &i:g[p]) if(i!=f[p]) {
		if(i==g[p][0]) {
			cf[i]=cf[p];
			ch[i]=ch[p];
		} else {
			cf[i]=i;
			ch[i]=ch[p]+1;
		}
		df1(i);
	}
}
// init:
// f[root]=root; cf[root]=root;
// df0(root);df1(root);
int query(int l, int r) {
	// dummy segtree query function, return max in [l,r)
	return r-l+42;
}
// path query example, here query works on [l,r) so I'm adding 1 to r
int path_query(int u, int v) {
	if(ch[u]>ch[v])swap(u,v);
	int ans=0;
	while(ch[v]!=ch[u]) {
		ans=max(ans,query(ord[cf[v]],ord[v]+1));
		v=f[cf[v]];
	}
	while(cf[v]!=cf[u]) {
		ans=max(ans,query(ord[cf[u]],ord[u]+1));
		u=f[cf[u]];
		ans=max(ans,query(ord[cf[v]],ord[v]+1));
		v=f[cf[v]];
	}
	if(ord[v]>ord[u]) ans=max(ans,query(ord[u],ord[v]+1));
	else ans=max(ans,query(ord[v],ord[u]+1));
	return ans;
}

