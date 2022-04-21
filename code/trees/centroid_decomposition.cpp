#include "../template.cpp"
const int MN = 200005;
vector<int> g[MN]; // normal bidirectional adjlist
int cf[MN]; // parent in centroid tree
int ch[MN]; // depth in centroid tree (starts at 1)
int siz[MN]; // temp array for sizes of subtrees
void df0(int p, int f) {
	siz[p]=1;
	for(auto &i:g[p]) if(i!=f && !ch[i]) {
		df0(i,p);
		siz[p]+=siz[i];
	}
}
void cd(int p, int cch, int lc) {
	df0(p,p);
	int nn = siz[p];
myloop:
	for(auto &i:g[p]) if(!ch[i] && siz[i]<siz[p] && siz[i]>nn/2) {
		p=i;
		goto myloop;
	}
	ch[p]=cch;
	cf[p]=lc;
	for(auto &i:g[p]) if(!ch[i]) cd(i,ch[p]+1,p);
}
// cd(0,1,-1)
// doing a dfs starting from every p0 and only visiting nodes with ch[i]>ch[p0] is nlogn
// you can do stuff like count number of paths of lenght k on a tree or avoid rerooting a dp
// lca(u,v) in centroid tree is on path(u,v) in original tree,
// you can use this to count stuff by considering O(logn) ancestors on centroid tree for both queries/updates

