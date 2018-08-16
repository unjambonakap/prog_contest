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


const int MAX_N=51;
class MismatchedStrings{
	public:
		ll dp[MAX_N][MAX_N*2][1];

		ll solve(int p, int b, int ok){
			if (p==0)return b!=MAX_N || ok;
			ok|=b<MAX_N;
			ll &c=dp[p][b][ok];
			if (c!=-1)return c;
			return c=solve(p-1, b-1, ok)+solve(p-1, b+1, ok);
		}

		string dfs(int p, int b, ll k, int ok){
			if (p==0)return "";
			ok|=b<MAX_N;
			ll d=solve(p-1, b+1, ok);
			if (d==0 || d<=k)
				return ")"+dfs(p-1, b-1, k-d, ok);
			return "("+dfs(p-1, b+1, k, ok);
		}

		string getString(int n, long long k){
			int i, j, p, s;
			memset(dp, -1, sizeof(dp));
			s=MAX_N;
			if (solve(n, MAX_N, 0)<=k)return "";
			return dfs(n, MAX_N, k, 0);
		}


};

int main(){
	int n, i, N;
	ll K;
	cin>>n;
	REP(i, n){
		cin>>N>>K;
		cout<<MismatchedStrings().getString(N, K)<<endl;;

	}


	return EXIT_SUCCESS;
}

