#include<cassert>
#include <iostream>
#include<cstring>
#include <set>
#include <cstdio>
#include <stack>
#include <map>
#include<set>
#include<vector>
#include<algorithm>
using namespace std;

typedef pair<int,int> pii;
typedef vector<int> vi ;
#define pb push_back
#define ST first 
#define ND second
#define FOR(i,a,b) for(int i=(a);i<(b);i++)
#define FE(it,set) for(typeof(set.begin()) it = set.begin();it!=set.end();it++)
#define REP(i,a) FOR(i,0,a)

void checkmax(int &a, int b){a=max(a,b);}

const int maxn=55555;
vi e[maxn];
int parent[maxn];
vector<vi> cycle[maxn];
int vis[maxn];
int n;
int order[maxn];
int pos;


int best;
int A[maxn];

int foo(int a, int b){ return min(a, b-a); }

void proc(int &va, int &vb, int v){
	if (v>va) vb=va, va=v;
	else if (v>vb) vb=v;
}

int doit(int p, int Z=-1){
	int &r=A[p];
	if (r!=-1) return r;
	int va, vb;
	va=vb=0;
    set<int> seen;

	REP(i, cycle[p].size()){
		vi &x=cycle[p][i];
		vi tmp;
		int besta=0;
		REP(k, x.size()) if (k){
			int a=x[k];
            seen.insert(a);
			assert(a!=0);
			int v=doit(a, x[k-1]);
			tmp.pb(v);
			checkmax(besta, v+foo(k, x.size()));
		}

		proc(va, vb, besta);
		multiset<int> lst;
		int d=x.size()/2;
		REP(k, d) lst.insert(doit(x[k+1])+k+1);
		
		
		FOR(k, 1, x.size()){
			lst.erase(lst.find(doit(x[k])+k));
			if ((k+d)%x.size()) lst.insert(doit(x[(k+d)%x.size()])+k+d);
			
			if (!lst.empty()) checkmax(best, (*--lst.end())-k+doit(x[k]));
		}


	}

	REP(i, e[p].size()) if (order[e[p][i]]>order[p] && e[p][i]!=Z && !seen.count(e[p][i])){
        proc(va, vb, doit(e[p][i])+1);
	}

	checkmax(best, va+vb);
	return r=va;
}

void dfs(int p){
	vis[p]=1;
	order[p]=pos++;
	REP(i, e[p].size()){
		int a=e[p][i];
		if (a!=parent[p]){
			if (vis[a] && order[a]<order[p]){//just found a cycle
				
				vi tmp;
				int x=p;
				tmp.pb(a);
				while(x!=a){
					int nx=parent[x];
					assert(nx!=-1);
					tmp.pb(x);
					x=nx;
				}
				cycle[a].pb(tmp);
				
			}else if (vis[a]);
			else{
				parent[a]=p;
				dfs(a);
			}
		}
	}
}

int main(){
	freopen("cactus.in", "r", stdin);
	freopen("cactus.out", "w", stdout);
	cin>>n;
	int m; cin>>m;
	REP(i, m){
		int k; cin>>k;
		int a; cin>>a; --a;
		REP(i, k-1){
			int b; scanf(" %d", &b); --b;
			e[a].pb(b); e[b].pb(a);
			a=b;
		}
	}
	pos=0;

	memset(parent, -1, sizeof(parent));
	memset(vis, 0, sizeof(vis));
	dfs(0);
	memset(A, -1, sizeof(A));
	best=-1;
	//REP(i, n){
	//	printf("PRINTING %d\n" ,i);
	//	REP(j, cycle[i].size()){
	//		REP(k, cycle[i][j].size()) printf("%d ", cycle[i][j][k]); printf("\n");

	//	}

	//}

	doit(0);
	printf("%d\n", best);



	return 0;
}



