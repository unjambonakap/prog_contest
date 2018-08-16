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
#include <climits>
//#include <ext/hash_map>


using namespace std;
using namespace __gnu_cxx;



#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i <= (b)) && (c); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)
#define FORVC(i, a, b, c) for(i = (a); (i >= (b)) && (c); i--)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
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

#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline ll sqr(int x){return ll(x)*ll(x);}
inline double dist(ll x, ll y, ll a, ll b){return sqrt(double(sqr(x-a)+sqr(y-b)));}
inline bool bit_set(int a, int b){return (a&two(b));}

const double INF=1e20;
class PrimePairs{
	public:
		static const int MAX_N=52;


		int graph[MAX_N][MAX_N];
		int with[MAX_N];
		int seen[MAX_N];
		int n;
		bool isPrime(int a){
			int i;
			if (a%2==0)return a==2;
			for(i=3; i*i<=a; i+=2)
				if (a%i==0)return 0;
			return 1;
		}

		bool dfs(int a){
			int i, j, k;
			if (seen[a])return 0;
			seen[a]=1;

			REP(i, n){
				if (graph[i][a]){
					if (with[i]==-1 || dfs(with[i])){
						with[i]=a, with[a]=i;
						return true;
					}
				}
			}
			return false;
		}

		vector<int> matches(vector<int> sa){
			int i, j, k;
			vector<int> res;
			n=SZ(sa);
			memset(graph, 0, sizeof(graph));

			REP(i, n)
				FOR(j, i+1, n-1){
					graph[i][j]=graph[j][i]=isPrime(sa[j]+sa[i]);
					//printf("<<< %d %d\n", i, j);
				}


			FOR(i, 1, n-1){
				if (!graph[0][i])continue;
				memset(with, -1, sizeof(with));

				with[0]=i, with[i]=0;
				FOR(j, 1, n-1){
					if (j==i || with[j]!=-1)continue;
					memset(seen, 0, sizeof(seen));
					seen[0]=seen[i]=1;
					if (!dfs(j))
						goto fail;
					


				}

				//printf("la\n");
				res.pb(sa[i]);

fail:;
			}

			//exit(0);
			sort(ALL(res));
			return res;
		}
};

int main(){
	int t, tn;
	cin>>tn;
	int n, i, s;
	long a, b;
	vector<int> sa;
	FOR(t, 1, tn){
		cin>>n;
		CLR(sa);
		REP(i, n){
			cin>>s;
			sa.pb(s);
		}


		printf("Case #%d:", t); 
		vector<int> res=PrimePairs().matches(sa);
		FE(it, res)
			printf(" %d", *it);
		printf("\n");
		//break;
	}


	return EXIT_SUCCESS;
}

