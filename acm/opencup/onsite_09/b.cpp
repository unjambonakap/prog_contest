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
#include <sstream>
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



#define REP(i,n) for(int i = 0; i < int(n); ++i)
#define REPV(i, n) for (int i = (n) - 1; (int)i >= 0; --i)
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)

#define FE(i,t) for (__typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (__typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define two(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()


#define pb push_back
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}


const int maxn=111;
const int maxm=33;
const int maxp=55;

int N, mod;

char A[maxp][maxn];
int na[maxp];
char buf[1111];
int rmp[256];
int vis[maxp];

int cnt[maxp];
int tsf[maxp][maxm];
int nfinish[maxp][maxm];
int nnew[maxp][maxm];
int type[maxp];

void go(int a){
	if (vis[a]) return;
	vis[a]=1;

	if (type[a]){
		int d=type[a]-1;
		REP(i,N) tsf[a][i]=(i*10+d)%N;
		if (d) nnew[a][d%N]=1;
		REP(i,N) if ((i*10+d)%N==0) nfinish[a][i]=1;
		cnt[a]=d%N==0;
		return;
	}


	vi tb;
	int n=na[a];
	REP(i,n) tb.pb(rmp[A[a][i]]);

	REP(i,n) go(tb[i]);

	REP(v,N){
		int x=v;
        REP(i,n) x=tsf[tb[i]][x];
		tsf[a][v]=x;
	}
	cnt[a]=0;
	REP(i,n) cnt[a]+=cnt[tb[i]], cnt[a]%=mod;
	REP(v,N){
		int &u=nfinish[a][v];
		int x=v;
		REP(i,n) u+=nfinish[tb[i]][x], u%=mod, x=tsf[tb[i]][x];
	}

	int tmp[maxm];
	memset(tmp,0,sizeof(tmp));
	REP(i,n){
		int B[maxm];
        memset(B,0,sizeof(B));
        REP(j,N) cnt[a]+=1ll*tmp[j]*nfinish[tb[i]][j]%mod, cnt[a]%=mod;
		REP(j,N) B[tsf[tb[i]][j]]+=tmp[j];
		REP(j,N) B[j]+=nnew[tb[i]][j], B[j]%=mod;
		memcpy(tmp,B,sizeof(B));
	}
    cnt[a]%=mod;
	memcpy(nnew[a],tmp,sizeof(tmp));
}


int main(){
	freopen("divisible.in","r",stdin);
	freopen("divisible.out","w",stdout);
	cin>>N>>mod;
	int k; cin>>k;
	int pos=0;
	REP(i,k){
		scanf(" %s", buf);
		strcpy(A[pos], buf+3);
		rmp[buf[0]]=pos;
		na[pos]=strlen(A[pos]);
		++pos;
	}

	REP(i,10) rmp['0'+i]=pos, type[pos]=i+1, ++pos;
	go(0);
	printf("%d\n", cnt[0]);
	return 0;
}



