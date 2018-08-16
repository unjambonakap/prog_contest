// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheBoredJohn.cpp"

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



#define REP(i,n) for(i = 0; i < (n); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


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
inline bool bit_set(int a, int b){return (a&two(b));}


int gcd(int a, int b){
	if (b==0)return a;
	return gcd(b, a%b);
}

vi decomp;

class TheBoredJohn {
	public:
	long long killMonsters(int n, long long k, vector <string> missing) {
		string s;
		FE(it, missing)s+=*it;
		FE(it, s)
			if (*it==',')*it=' ';
		int a, b, d;
		vector<pii> list;

		istringstream ss(s);

		while(ss>>a>>b){
			if (a==0)b=1;
			if (b==0)a=1;
			d=gcd(max(a, b), min(a, b));
			assert(d!=0);
			list.pb(MP(a/d, b/d));
		}
		int i, j, t, ta;

		decomp=vi(n, -1);
		decomp[2]=-1;
		for (i=2; i<n; ++i){
			if (decomp[i]==-1){
				for (j=i+i; j<n; j+=i)
					decomp[j]=i;
			}

		}

		decomp[1]=1;
		for (i=2; i<n; ++i){
			if (decomp[i]==-1)decomp[i]=i-1;
			else{
				//printf("on %d\n", i);
				a=decomp[i], b=i/a, d=gcd(max(a, b), min(a, b));
				decomp[i]=(ll(decomp[a])*decomp[b]*d)/decomp[d];
			}

		//	b=0;
		//	for (j=1; j<i; ++j)
		//		if (gcd(i, j)==1)++b;
		//	
		//	printf("%d => %d %d\n", i, decomp[i], b);
		//	assert(b==decomp[i]);
		}
		//printf("ici\n");


		ll tot=ll(n)*n;
		sort(ALL(list));
		map<ll, int> dat;
		int c;
		list.pb(MP(-1, -1));
		for (i=1, c=0; i<list.size(); ++i){
			if (list[i]!=list[i-1]){
				int sc=0;
				a=list[i-1].ST, b=list[i-1].ND;
				if (a<b){ sc=1; swap(a, b); }

				//printf("push %d  for %d %d\n", sc+b*2+a*2*n, list[i-1].ST, list[i-1].ND);
				dat[sc+ll(b*2)+a*2LL*n]=c+1, c=0;
			}
			else ++c;
		}

		ll res=0;
		priority_queue<int> delay;
		if (k==0)return 0;

		map<ll, int>::iterator ita;
		if ((ita=dat.find(2*n))!=dat.end())
			delay.push(n-1-ita->ND);
		else
			--k, res+=n-1;
		if (k==0)return res;
		if ((ita=dat.find(2*n+2))!=dat.end())
			delay.push(n-1-ita->ND);
		else
			--k, res+=n-1;		
		if (k==0)return res;
		if ((ita=dat.find(2*n+1))!=dat.end())
			delay.push(n-1-ita->ND);
		else
			--k, res+=n-1;
		for (i=2; i<n && k; ++i){

			while(delay.size()>0 && delay.top()>=(n-1)/i && k>0){
				res+=delay.top(); delay.pop();
				--k;
			}
			if (k==0)break;

			ita=dat.lower_bound(2LL*n*i);
			b=0;
			t=(n-1)/i;

			while(ita!=dat.end() && ita->ST<2LL*n*(i+1))
				++b, delay.push(t-ita->ND), ++ita;
			

			a=min(2LL*decomp[i]-b, k);
			k-=a;
			res+=a*t;


		}
		while(delay.size()>0 && k>0){
			res+=delay.top(); delay.pop();
			--k;
		}	
		return res;

		

		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	
	//void test_case_0() { int Arg0 = 3; long long Arg1 = 4LL; string Arr2[] = {"1 1,0 1,1 0"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 4LL; verify_case(0, Arg3, killMonsters(Arg0, Arg1, Arg2)); }//must find 700
	//end in 60
	void test_case_0() { int Arg0 = 2504716; long long Arg1 = 11035833522496LL; string Arr2[] = {"755324 2267244,783368 801298,1941752 2306416,48543", "8 576604,56293 1788258,261502 799917,291283 581727", ",2265570 1768386,582566 1163454,515240 2086182,293", "755 222052,1552951 1996934,523004 1599834,871444 2", "053474,1443944 156616,1566736 1602596,2429984 5985", "64,1942271 558694,1214992 299282,1197296 473976,21", "41360 2359692,124798 640236,2268662 2340702,185673", "7 479384,166009 2101568,410025 1201616,1175020 888", "208,221372 1550308,598648 236988,1402296 1138828,2", "499157 1332435,1070680 1179846,249596 1280472,2576", "20 1043091,739980 1880754,2264072 1558830,1491384 ", "456483,820050 2403232,721972 78308,970876 1153208,", "1917412 593427,1600724 935762,587510 444104,235004", "0 1776416,1036540 1096984,299324 118494,1506453 14", "66040,1633408 1775792,2415030 268500,816704 887896", ",166553 1865092,2073080 2193968,360986 39154,23945", "92 947952,1165132 2326908,2126338 638512,926904 21", "65560,1988229 752634,1552687 233615,945016 1393826", ",2399089 1545659"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 4LL; verify_case(0, Arg3, killMonsters(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 2; long long Arg1 = 1000000000LL; string Arr2[] = {"1 1,0 1,1 0"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 0LL; verify_case(1, Arg3, killMonsters(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 9; long long Arg1 = 1LL; string Arr2[] = {"8 2,0 1,7 6,6 8,3 3,0 5,3 4"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 8LL; verify_case(2, Arg3, killMonsters(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 6; long long Arg1 = 9LL; string Arr2[] = {"0 3,2"," 4,3 3",",4 2,2 0"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 18LL; verify_case(3, Arg3, killMonsters(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  TheBoredJohn ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE
