#include <vector>
#include <list>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <climits>
#include <iostream>
//#include <ext/hash_map>


using namespace std;
using namespace __gnu_cxx;



#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;



int tb[]={6, 2, 5, 5, 4, 5, 6, 3, 7, 5};
class DigitalCounter{
	public:
		ll dp[120][20][2];
		ll tenpow[16];
		vector<int> cur;
		int l;


		ll solve(int s, int p, int res){
			if (s<0)return -2;

			if (p==l)return (s==0)?0:-2;

			ll &a=dp[s][p][res];
			if (a!=-1)return a;
		//	printf("<<<%d\n", cur[p]);

			a=-2;
			int i, j, k;
			if (res){
				ll t=(10-cur[p]-1)*tenpow[l-p-1];
				if (p==l-1)++t;
				REP(i, 10){
					a=solve(s-tb[i], p+1, 1);
					//printf("ssstry %d on %d => %Ld %Ld %Ld\n", i, p, a, t, i*tenpow[l-p-1]);
					if (a!=-2) return a+=t+i*tenpow[l-p-1];
				}

			}else{
				a=solve(s-tb[cur[p]], p+1, 0);
				if (a!=-2 || cur[p]==9)return a;

				FOR(i, cur[p]+1, 9){
					a=solve(s-tb[i], p+1, 1);
			//		printf("try %d on %d %d\n", i, p, a);
					if (a!=-2) return a+=tenpow[l-p-1]*(i-cur[p]-(p!=l-1));
				}
			}
			return a;

		}
		

		long long nextEvent(string current){
		
			int i, j, k;
			int c, s;
			int minp, maxp;
			l=current.length();
			cur=vector<int>(l, 0);

			s=0;
			REP(i, l)
				cur[i]=current[i]-'0';
			REP(i, l)
				s+=tb[cur[i]];

			tenpow[0]=1;
			REP(i, 15)
				tenpow[i+1]=10*tenpow[i];

			assert(s<120);

			c=1;
			REPV(i, l){
				if (c)++cur[i];
				c=0;
				if (cur[i]>9)cur[i]=0, c=1;
			}
			
			memset(dp, -1, sizeof(dp));
			ll a=solve(s, 0, 0);
			assert(a!=-1);
			return 1+((a==-2)?solve(s, 0, 1):a);

		}

};



int main(){
	int i, n;
	cin>>n;
	string s;

	REP(i, n){
		cin>>s;
		if (i!=0)continue;

		printf("%Ld\n", DigitalCounter().nextEvent(s));
	}



	return 0;

}



