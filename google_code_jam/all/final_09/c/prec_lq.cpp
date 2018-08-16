#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
//#include <ext/hash_map>


using namespace std;
using namespace __gnu_cxx;

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
#define FEV(i,t) for (typeof(t.rbegin())i=t.rbegin();i!=t.rend();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define ST first
#define ND second
#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define MDIST(x,y,a,b) (abs((a)-(x))+abs((b)-(y)))

#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ST first
#define ND second

typedef long long ll;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

inline int count_bit(int n){return (n == 0)?0:(n&1)+count_bit(n>>1);}
inline ll sqr(int x){return ll(x)*ll(x);}
inline double dist(ll x, ll y, ll a, ll b){return sqrt(double(sqr(x-a)+sqr(y-b)));}

const double INF=1e20;


const int MAX_R=10, MAX_P=26;
const int MOD=10007;

int r, c;
int mmap[MAX_R][MAX_R];
map<string, int> dp[MAX_P];
int used[MAX_R][MAX_R];
map<string, vs> prec;

vector<pii> buildList(string s){
	vector<pii> v;
	for (int i=0; i < s.length(); i+=2)
		v.pb(pii(s[i]-'0', s[i+1]-'0'));
	return v;
}
string buildStr(vector<pii>& v){
	string s="";
	FE(it, v)
		s=s+string(1, (char)it->ST+'0')+string(1, (char)it->ND+'0');
	return s;
}


bool checkIt(vector<pii>& v, int c){
	int i, j;
	FE(it, v)
		REP(i, it->ST+1)
			REP(j, it->ND+1)
				if (mmap[i][j] > c)return false;
	
	return true;

}



int solve(string s, int c){
	int i, j, k;

	map<string, int>::iterator r=dp[c].find(s);
	if (r != dp[c].end())
		return r->ND;

	int& ret=dp[c][s];
	ret=0;

				
	if (s == "")return ret=1;

	vector<pii> v, nv;
	v=buildList(s);

	if (!checkIt(v, c))
		return 0;

	if (c > 0)
		ret+=solve(s, c-1);
	ret%=MOD;
	

	FE(it, prec[s]){
		int count=0;
		nv=buildList(*it);
		FOR(i, 0, SZ(v)-1){
			FOR(j, 0, SZ(nv)-1)
				if (v[i] == nv[j])break; 
			if (j == SZ(nv) && mmap[v[i].ST][v[i].ND] >= 0 && mmap[v[i].ST][v[i].ND] != c)break;
			if (j != SZ(nv))count++;
		}
		if (i != SZ(v))continue;
		ret+=MOD+solve(*it, c)*pow(-1, SZ(v)-count+1);
		ret%=MOD;
	}
	return ret;

}


void init(){
	int i, j, k;

	string s, ns;

	queue<string> q;
	vector<pii> v;

	prec.clear();


	s="99";
	q.push(s);
	prec[s]=vs();



	while(!q.empty()){
		s=q.front(), q.pop();
		v=buildList(s);


		FOR(i, 1, two(v.size())-1){
			vector<pii> nv;
			REP(j, v.size()){
				if (!(i&two(j)))
					nv.pb(v[j]);
				else
					nv.pb(pii(v[j].ST, v[j].ND-1)), nv.pb(pii(v[j].ST-1, v[j].ND));
			}


			vector<pii>::iterator it, ita;
			it=nv.begin();
			while(it != nv.end()){
				if (it->ST < 0 || it->ND < 0){
					it=nv.erase(it);
					continue;
				}
				ita=nv.begin();
				while(ita != nv.end()){

					if (ita == it){ita++; continue;}
					if (it->ST <= ita->ST && it->ND <= ita->ND){
						it=nv.erase(it);
						break;
					}

					ita++;
				}
				if (ita == nv.end())
					it++;
			}


			ns=buildStr(nv);
			prec[s].pb(ns);
			if (prec.find(ns) == prec.end())
				prec[ns]=vs(), q.push(ns);
		}
	}
}

int main(){
	int i, j, k, T;
	char ca;
	init();
	scanf("%d", &T);
	REP(i, T){
		scanf("%d %d\n", &r, &c);
		REP(j, MAX_P)
			dp[j].clear();
		REP(j, r){
			REP(k, c){
				scanf("%c", &ca);
				if (ca == '.')
					mmap[k][j]=-1;
				else
					mmap[k][j]=ca-'a';

			}
			scanf("\n");
		}
		//printf("%d \n", solve(string("11"), 4));
		printf("Case #%d: %d\n", i+1, solve(string(1, (char)c-1+'0')+string(1, (char)r-1+'0'), MAX_P-1));
	}


	return EXIT_SUCCESS;
}

