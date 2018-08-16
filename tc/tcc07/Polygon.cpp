// BEGIN CUT HERE

// END CUT HERE
#line 5 "Polygon.cpp"

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
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORV(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

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

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
ll toLL(string s){ll a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=59;

int n;
vi xl, yl, crossy[maxn];
ll mp[maxn][maxn];
ll cnt[maxn][2];


class Polygon {
	public:
	vector <string> getKthPoint(vector <int> x, vector <int> y, vector <string> k) {
		

		n=x.size();
		xl=x; sort(ALL(xl)); xl.resize(unique(ALL(xl))-xl.begin());
		yl=y; sort(ALL(yl)); yl.resize(unique(ALL(yl))-yl.begin());
		assert(xl.size()<maxn);
		assert(yl.size()<maxn);
		REP(i, maxn) CLR(crossy[i]);
		REP(i, n){
			int xa, xb, ya, yb;
			xa=x[i], xb=x[(i+1)%n], ya=y[i], yb=y[(i+1)%n];
			if (xa==xb)continue;
			int la=lower_bound(ALL(xl), min(xa, xb))-xl.begin(), lb=lower_bound(ALL(xl), max(xa, xb))-xl.begin();
			FOR(j, la, lb-1) crossy[j].pb(lower_bound(ALL(yl), ya)-yl.begin());
		}
		int w=xl.size()-1, h=yl.size()-1;
		REP(i, w) sort(ALL(crossy[i]));
		memset(mp, 0, sizeof(mp));
		REP(i, w) REP(j, crossy[i].size()-1) FOR(k, crossy[i][j], crossy[i][j+1]-1) mp[i][k]=j%2^1;

//j		out(xl);
//j		out(yl);
		memset(cnt, 0, sizeof(cnt));
		//REP(i, w) REP(j, h) if (mp[i][j]) printf("%d %d => %d %d x %d %d\n", i, j, xl[i], xl[i+1], yl[j], yl[j+1]);
		REP(i, w){
			REP(j, h) if (mp[i][j]) cnt[i][0]+=yl[j+1]-yl[j]+1-(j==0 || !mp[i][j-1]?0:1);
			cnt[i][0]*=xl[i+1]-xl[i]-(i>0)+(i+1==w);
			if (i+1<w) REP(j, h) if (mp[i][j] || mp[i+1][j]) cnt[i][1]+=yl[j+1]-yl[j]+1-(j==0 || (!mp[i][j-1] && !mp[i+1][j-1])?0:1);
		}
		//REP(i, w) REP(j, 2) printf("nh: %d %d /  %d => %Ld\n", xl[i], xl[i+1], j, cnt[i][j]);
		// REP(i, w) REP(j, h) if (mp[i][j]){
		// 	mp[i][j]=(xl[i+1]-xl[i]+1)*(yl[i+1]-yl[i]+1);
		// 	if (i>0 && mp[i-1][j]>0) mp[i][j]-=(yl[i+1]-yl[i]+1);
		// 	if (j>0 && mp[i][j-1]>0) mp[i][j]-=(xl[i+1]-xl[i]+1);
		// }
		vs res(k.size());
		REP(i, k.size()){
			ll a=toLL(k[i])-1;

			cout<<a<<" "<<k[i]<<endl;
			//printf("on %Ld\n", a);
			REP(j, w) REP(k, 2){
				if (a<cnt[j][k]){
					assert(j+1<w || k==0);
					//printf("fd %d %d rem %Ld over %Ld\n", j, k, a, cnt[j][k]);
					int x, y;
					x=y=-1;
					if (k==0) x=(j==0?0:1)+xl[j]+a/(cnt[j][k]/(xl[j+1]-xl[j]-(j>0)+(j+1==w))), a%=cnt[j][k]/(xl[j+1]-xl[j]-(j>0)+(j+1==w));
					else x=xl[j+1];
					REP(t, h) if (mp[j][t] || (k==1 && mp[j+1][t])){
						int skf=(t==0 || (!mp[j][t-1] && (k==0 || !mp[j+1][t-1]))?0:1);
						int nh=yl[t+1]-yl[t]+1-skf;
						//printf("%d %d %Ld %d\n", j, t, a, nh);
						if (a<nh){y=yl[t]+a+skf; break;}
						else a-=nh;
					}
					res[i]=toStr(x)+" "+toStr(y);
					goto fd;
				}
				a-=cnt[j][k];
			}
fd:;
		}


		return res;


	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	//{, , }
	void test_case_0() { int Arr0[] = {941764403, 942618392, 942618392, 943705832, 943705832, 943472294, 943472294, 943736333, 943736333, 944343682, 944343682, 944162256, 944162256, 943472294, 943472294, 943705832, 943705832, 943322337, 943322337, 943055814, 943055814, 942618392, 942618392, 942220869, 942220869, 941764403, 941764403, 941350521, 941350521, 940830374, 940830374, 940733437, 940733437, 940557670, 940557670, 940598753, 940598753, 938960120, 938960120, 939809944, 939809944, 940138924, 940138924, 940557670, 940557670, 940830374, 940830374, 941350521, 941350521, 941764403}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {906405370, 906405370, 906115326, 906115326, 906578149, 906578149, 906769374, 906769374, 906578149, 906578149, 906769374, 906769374, 907034013, 907034013, 907251555, 907251555, 907385711, 907385711, 906769374, 906769374, 907385711, 907385711, 906769374, 906769374, 907034013, 907034013, 907720865, 907720865, 907034013, 907034013, 907385711, 907385711, 907720865, 907720865, 907385711, 907385711, 907251555, 907251555, 907034013, 907034013, 906769374, 906769374, 907034013, 907034013, 906769374, 906769374, 906405370, 906405370, 906769374, 906769374}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1634761280723", "136073789385", "915006657050", "2898092692499", "1109747829327", "2021236412627", "829655402677", "104071868357", "638506069923", "1013766091545", "1984668676360", "108858941821", "2268306649915", "1226157018864", "1328558184975", "2383736009455", "2920029301676", "1724438279276", "2653802662147", "617214237287", "2958299175160", "133224477477", "1111964503153", "1351450669537", "374958354982", "3165008042369", "3082578997002", "2154341561708", "29187922173", "1483026222465", "1622977226747", "1436504197363", "2079644444333", "3080247445513", "2676024080090", "2562937796545", "1615842081988", "1880093312082", "2268427197516", "101174401621", "2852161543155", "3110660944959", "386530522899", "2813581739233", "2731255352136", "411652739234", "106074269843", "1350935949869", "3167191084670", "3167191084671"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"0 0", "0 1", "0 2", "1 0", "1 1", "1 2", "2 0", "2 1", "2 2" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, getKthPoint(Arg0, Arg1, Arg2)); }
	//void test_case_0() { int Arr0[] = {0, 2, 2, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 2, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"0 0", "0 1", "0 2", "1 0", "1 1", "1 2", "2 0", "2 1", "2 2" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, getKthPoint(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0,1,2,2,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,0,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1","6","2","3","5","4","7"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"0 0", "2 1", "0 1", "1 0", "2 0", "1 1", "" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(1, Arg3, getKthPoint(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {0, 5, 5, 3, 3, 4, 4, 3, 3, 0, 0, 1, 1, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 1, 1, 2, 2, 5, 5, 4, 4, 3, 3, 1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1","4","6","7","12","15","20","25","28","29"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"0 0", "0 4", "1 1", "1 2", "2 2", "3 0", "3 5", "4 4", "5 1", "" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(2, Arg3, getKthPoint(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {0,0,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,0,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"1","2","3","4"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"0 0", "0 1", "1 0", "1 1" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(3, Arg3, getKthPoint(Arg0, Arg1, Arg2)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	Polygon ___test; 
	___test.run_test(0);
} 
// END CUT HERE
