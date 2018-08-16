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
#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)

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
#define MDIST(x,y,a,b) (abs((a)-(x))+abs((b)-(y)))
inline int count_bit(int n){return (n == 0)?0:(n&1)+count_bit(n>>1);}

#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ST first
#define ND second
#define ll long long

using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef queue<int> qi;

#define MAX_N 100
#define MAX_M 10
#define MAX_V 26
#define MAX_T 5
#define MAX_P 4
#define MOD 10009

string ps[MAX_T];
string str[MAX_N];
int occ[MAX_N][MAX_V];
int n, m, nt;

class Term{
	public:
		Term(){}
		Term(int _id, int _t){id=_id, t=_t;}
		int id, t;


};
vector<vector<Term> > store[MAX_M][4][256];



void set_terms(int a, int b, int c){
	int i, j;
	vector<vector<Term> > *ta, *tb, *tc;
	ta=&store[a-1][b-1][c];

	if (b == 1){
		REP(i, a)
			ta->pb(vector<Term>(1, Term(i, c)));
		return;
	}

	tb=&store[a-1][b-1-1][c/MAX_P], tc=&store[a-1][1-1][c%MAX_P];
	FE(it, *tb)
		FE(ita, *tc){
			ta->pb(*it);
			ta->back().insert(ta->back().end(), ita->begin(), ita->end());
			assert(ta->back().size() <= MAX_P);
		}

}

void set_prod(){
	int i, j, k;
	REP(i, MAX_M)
		REP(j, MAX_P)
			REP(k, pow(MAX_P, j+1))
				set_terms(i+1, j+1, k);
	
}
int solve(int a){
	int i, j, k, l, u;
	int s, t, state, sa, ta;
	int permut[256];
	char repermut[MAX_P];

	s=0;
	REP(i, nt){

		memset(permut, -1, sizeof(permut));
		k=state=0;
		memset(repermut, -1, sizeof(repermut));
		REP(j, ps[i].length()){
			if (permut[ps[i][j]] == -1)permut[ps[i][j]]=k, repermut[k++]=ps[i][j];
			state+=permut[ps[i][j]]*pow(MAX_P, j);
		}

		FE(it, store[a-1][ps[i].length()-1][state]){
			vi ask[MAX_M];

			FE(ita, *it)
				ask[ita->id].pb(ita->t);
			
			

			
			

			t=1;
			REP(k, a){
				if (ask[k].size() == 0){
					t*=n;
					t%=MOD;
					continue;
				}
				sa=0;
				REP(l, n){
					ta=1;


					REP(u, SZ(ask[k])){
						ta*=occ[l][repermut[ask[k][u]]-'a'];
						ta%=MOD;
					}
					sa+=ta;
					sa=sa%MOD;

				}
				t*=sa;
				t%=MOD;
			}
			s+=t;
			s%=MOD;
		}


	}

	return s;
}

int main(){
	int i, j, k, T;
	char c;



	scanf("%d\n", &T);
	set_prod();


	//vector<vector<Term> > *ta;
	//ta=&store[1][1][1];
	//printf("la\n");
	//FE(it, *ta){
	//	printf("new term\n");
	//	FE(ita, *it)
	//		printf("%d %d\n", ita->id, ita->t);
	//}
	//return 0;

	REP(i, T){
		REP(j, MAX_T)
			ps[j]=string();
		nt=0;
		while((c=getchar()) != ' '){
			if (c == '+')nt++;
			else ps[nt]+=c;
		}
		nt++;
		cin >> m;
		cin >> n;
		REP(j, n)
			cin >> str[j];
		scanf("\n");


		memset(occ, 0, sizeof(occ));
		REP(j, n)
			REP(k, str[j].length())
			occ[j][str[j][k]-'a']++;


		printf("Case #%d:", i+1);
		REP(j, m)
			printf(" %d", solve(j+1));


		printf("\n");




	}


	return EXIT_SUCCESS;
}

