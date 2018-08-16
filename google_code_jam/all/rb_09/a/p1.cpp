#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <cassert>


#define PI asin(1)*2.
#define EPS 10e-8


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i <= (b)) && (c); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)
#define FORVC(i, a, b, c) for(i = (a); (i >= (b)) && (c); i--)
#define FE(i,t) for (typeof(t.begin())i=t.begin();i!=t.end();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define SZ(a) ((a).size())
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ll long long

using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef queue<int> qi;

#define MAX_L 20
#define MAX_A 100

int nl, na;
char buf[MAX_L];

vector<string> slist;

struct tree;
int an[MAX_A][1000];

typedef struct tree{
	double w;
	int fid;
	tree *f, *nf;
}tree;


void set_tree(tree *a){
	
	int i;
	char c;
	string s;
	a->f=a->nf=NULL;
	a->fid=-1;

	assert(scanf("%lf", &a->w) == 1);




	i=0;
	while(1){
		c=getchar();
		if (c == ' ' || c == '\n')continue;
		if (c == ')') return;
		if (c == '(')break;

		if (c >= 'a' && c <= 'z') buf[i++]=c;
	}
	buf[i]='\0';

	s=string(buf);

	REP(i, slist.size())
		if (s == slist[i])
			break;
	if (i == slist.size())
		slist.pb(s);

	a->fid=i;


	a->f=new tree; a->nf=new tree;
	set_tree(a->f);
	while(getchar() != '(');
	set_tree(a->nf);
	while(getchar() != ')');


}

void del_tree(tree *a){
	if (a == NULL)return;
	del_tree(a->f);
	del_tree(a->nf);
	delete a;
}


double solve(int a, tree *root){
	double r=root->w;
	if (root->fid != -1){
		if (an[a][root->fid]){
			r*=solve(a, root->f);
		}
		else{
			r*=solve(a, root->nf);
		}
	}
	return r;

}

int main(){
	int i, j, k, u, T, naf;

	scanf("%d\n", &T);
	string s;

	REP(i, T){

		scanf("%d\n", &nl);
		tree *root=new tree;
		slist.clear();

		while(getchar() != '(');
		set_tree(root);

		assert(scanf("%d\n", &na) == 1);

		memset(an, 0, sizeof(an));
		REP(u, na){
			cin >> s >> naf;
			REP(j, naf){
				cin >> s;
				REP(k, slist.size()){
					if (s == slist[k]){
						an[u][k]=1;
						break;
					}
				}
			}
		}

		

		printf("Case #%d:\n", i+1);
		REP(j, na)
			printf("%lf\n", solve(j, root));

		del_tree(root);
		

	}


	return EXIT_SUCCESS;
}

