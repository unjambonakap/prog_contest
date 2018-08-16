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
#define MOD 10009

string ps[MAX_T];
string s[MAX_N];
int occ[MAX_N][MAX_V];
int n, m, nt;

int get_val(int s, int a, int oc[MAX_V]){
	
	int i, j, t, m;
	if (s >= a){
		t=0;
		REP(i, nt){
			m=1;
			REP(j, ps[i].length())
				m=(m*oc[ps[i][j]-'a'])%MOD;
			
			t=(t+m)%MOD;
		}
		return t;
	}

	int noc[MAX_V];
	t=0;
	REP(i, n){
		memcpy(noc, oc, sizeof(noc));
		REP(j, MAX_V)
			noc[j]+=occ[i][j];
		
		
		t=(t+get_val(s+1, a, noc))%MOD;
	}

	return t;


}


int solve(int a){
	int i, j;
	int t;
	int oc[MAX_V];
	memset(oc, 0, sizeof(oc));

	return get_val(0, a, oc);




}

int main(){
	int i, j, k, T;
	char c;



	scanf("%d\n", &T);

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
			cin >> s[j];
		scanf("\n");
		

		memset(occ, 0, sizeof(occ));
		REP(j, n)
			REP(k, s[j].length())
				occ[j][s[j][k]-'a']++;
			

		printf("Case #%d:", i+1);
		REP(j, m)
			printf(" %d", solve(j+1));
		

		printf("\n");

		


	}


	return EXIT_SUCCESS;
}

