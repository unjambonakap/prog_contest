#include<iostream>
#include<cstdio>
#include<cassert>
#include<vector>
#include<cstring>

using namespace std;

typedef pair<int,int> pii;
#define pb push_back
#define FOR(i,a,b)		for(int i=(a);i<(b);i++)
#define REP(i,n)		FOR(i,0,n)
#define ST first
#define ND second
#define MP make_pair
#define two(x) (1<<(x))

const int maxn=15;

int indep[two(maxn)];
int n;
int q[two(maxn)];
int idl[two(maxn)];
int d[two(maxn)], par[two(maxn)];
int np;
int g[maxn][maxn];
int order[maxn];



int main(){
	freopen("exclusive.in", "r", stdin);
	freopen("exclusive.out", "w", stdout);
	cin>>n;
	memset(g, 0, sizeof(g));
	vector<pii> query(n);
	REP(i, n){
		char a, b; cin>>a>>b;
		query[i]=MP(a-'L', b-'L');

		g[query[i].ST][query[i].ND]=1;
		g[query[i].ND][query[i].ST]=1;
	}

	REP(i, two(maxn)){
		int ok=1;
		REP(j, maxn) REP(k, maxn) if ((i&two(j)) && (i&two(k)) && g[j][k]) ok=0; 
		indep[i]=ok;
	}

	np=0;
	REP(i, two(maxn)) if (indep[i]){
		//REP(j, maxn) if (!(i&two(j)) && indep[i|two(j)]){indep[i]=0; break;}
		if (indep[i]) idl[np++]=i;
	}

	memset(d, 0x7f, sizeof(d));

	int qa, qe;
	qa=qe=0;
	REP(i, two(maxn)) if (indep[i]) q[qe++]=i, d[i]=0, par[i]=-1;

	while(qa<qe){
		int p=q[qa++];
		int c=d[p]+1;
		REP(j, np){
			int m=idl[j];
			if ((m&p)==0 && d[m|p]>c){d[m|p]=c; par[m|p]=m; q[qe++]=m|p;}
		}
	}
	int cnt=0;
	int x=two(maxn)-1;

		
	printf("%d\n", d[x]-1);
	while(par[x]!=-1){
		int nx=par[x];
		REP(j, n) if ((x&two(j)) && !(nx&two(j))) order[j]=cnt;
		x=x^nx;
		--cnt;
	}


	REP(i, n){
		int a, b;
		a=query[i].ST, b=query[i].ND;
		if (order[a]<order[b]) swap(a, b);

		printf("%c %c\n", a+'L', b+'L');
	}



	return 0;
}




