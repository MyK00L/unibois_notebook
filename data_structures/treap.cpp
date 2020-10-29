#include "../template.cpp"

// always use the same size MN for the same type!
template<typename T, usize MN/*=1000000*/>
class treap {
	private:
		struct node {
			node *l;
			node *r;
			u32 y;
			u32 siz;
			T val;
		};
		inline static node nodes[MN];
		inline static usize nodecnt;
		static node* newnode(T& val){
			nodes[nodecnt]={0,0,(u32)rng(),1,val};
			return nodes+nodecnt++;
		}
		static u32 siz(node * p){
			return p?p->siz:0;
		}
		static void updt(node * p){
			p->siz=siz(p->l)+siz(p->r)+1;
		}
		node* root;
		void split(node* p, node*& l, node*& r, u32 pos){
			if(!p) return void(l=r=0);
			if(pos<=siz(p->l)) split(p->l,l,p->l,pos), r=p;
			else split(p->r,p->r,r,pos-siz(p->l)-1), l=p;
			updt(p);
		}
		void merge(node *& ret, node *l, node *r){
			if(!l||!r) ret=l?l:r;
			else if(l->y<r->y) merge(l->r,l->r,r),ret=l;
			else merge(r->l,l,r->l),ret=r;
			updt(ret);
		}
	public:
		treap split(u32 pos){
			node *r;
			split(root,root,r,pos);
			return treap{r};
		}
		void merge(treap& r){
			merge(root,root,r->root);
			r->root=0;
		}
		void insert(u32 pos, node* nn){
			node *l, *r;
			split(root,l,r,pos);
			merge(l,l,nn);
			merge(l,l,r);
			root=l;
		}
		void insert(u32 pos, T& val){
			insert(pos,newnode(val));
		}
		node* erase(u32 pos){
			node *r, *ret;
			split(root,root,r,pos);
			split(r,ret,r,1);
			merge(root,root,r);
			ret->l=ret->r=0;
			ret->siz=1;
			return ret;
		}
		T& operator[](usize pos){
			node * p=root;
			while(p){
				if(pos==siz(p->l))return p->val;
				else if(pos<siz(p->l))p=p->l;
				else {
					pos-=siz(p->l)+1;
					p=p->r;
				}
			}
		}
		usize size(){
			return siz(root);
		}
		template<class It> treap(It begin, It end){
			stack<node*> s;
			node * nn=0;
			for(;begin!=end;++begin){
				nn = newnode(*begin);
				while(!s.empty() && nn->y<s.top()->y){
					nn->l=s.top();
					updt(s.top());
					s.pop();
				}
				if(!s.empty())s.top()->r=nn;
				s.push(nn);
			}
			while(!s.empty()){
				nn=s.top();
				updt(nn);
				s.pop();
			}
			root=nn;
		}
};

