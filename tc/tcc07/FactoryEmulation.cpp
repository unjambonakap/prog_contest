// BEGIN CUT HERE

// END CUT HERE
#line 5 "FactoryEmulation.cpp"

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
string toStr(int a){ostringstream os; os<<a; return os.str();}

struct data{
	int t;
   	ll c, inc;
	data(){}
	data(string s){ istringstream(s)>>t>>c>>inc; }
	bool operator<(const data &d)const{return t<d.t;}
	void add(const data &d){c+=d.c, inc+=d.inc;}
};

const int maxn=16;
data tb[maxn], v[maxn];
int n, nv, nstk;
int stk[maxn];
int prods[maxn];
ll gds[maxn];
ll ask[maxn];



class FactoryEmulation {
	public:
	long long maxIncome(vector <string> orders) {
		n=orders.size();
		REP(i, n) tb[i]=data(orders[i]);
		sort(tb, tb+n);

		ll res=0;
		REP(i, two(n)){
			nv=0;
			REP(j, n) if (i&two(j)){
				if (nv==0 || v[nv-1].t<tb[j].t) v[nv++]=tb[j];
				else v[nv-1].add(tb[j]);
			}
			REP(j, nv) ask[j]=(j==0?0:ask[j-1])+v[j].c;

			bool ok=true;
			nstk=0;
			memset(stk, -1, sizeof(stk)); memset(prods, 0, sizeof(prods)); memset(gds, 0, sizeof(gds));
			int pos=0;
			//REP(j, nv) printf("have to %d %d %d\n", v[j].t, v[j].c, v[j].inc);
			//printf("ON >>>>>>>>>< %d => %d\n", i, nv);
			gds[0]=0; prods[0]=1;
			while(pos<nv){
				int prod=prods[pos];
				ll ng=gds[pos];
				
			//	printf("%d %d %Ld\n", pos, prod, ng);

				int nt=v[pos].t-(pos==0?0:v[pos-1].t);
				ll tmp=v[pos].c-ng;
				int a=max(0, (nt-prod)/2), b=a+1;
				if (ll(nt-a)*(prod+a)<ll(nt-b)*(prod+b))a=b;

				int H, T, M;
				if (ll(nt-a)*(prod+a)<tmp){
			//		printf("can't supply for %d\n", pos);
					bool fd=false;
					REPV(prev, pos) if (stk[prev]){
						H=stk[prev]; T=-1; prod=prods[prev];
						int st=(prev==0?0:v[prev-1].t);
						ll have=(prev==0?0:ask[prev-1])+gds[prev];
						nt=v[pos].t-st;
						int a=max(0, min(H, (nt-prod)/2)), b=a+1;
						if (ll(nt-a)*(prod+a)<ll(nt-b)*(prod+b))a=b;
						//printf("having %d\n", prod);
						//printf("CAN PROD: at %d, %d %d %d\n", a, (nt-a)*(prod+a), ask[pos], have);
						if (ll(nt-a)*(prod+a)<ask[pos]-have)continue;
						else T=a;
						//printf("try back for %d, start time %d have %d with prod %d\n", prev, st, have, prod);
						//printf("bounds: %d %d\n", T, H);
						while(T+1<H){
							M=(H+T)/2;
							//FOR(k, prev, pos) printf("try new stop at %d => %d %d\n", M, (v[k].t-st-M)*(prod+M), ask[k]-have);
							bool fail=false;
							FOR(k, prev, pos) if (ll(v[k].t-st-M)*(prod+M)<ask[k]-have){fail=true; break;}
							if (fail) H=M;
							else T=M;
						}
						bool fail=false;
						FOR(k, prev, pos) if (ll(v[k].t-st-T)*(prod+T)<ask[k]-have){fail=true; break;}
						if (!fail && T>=0){
							//printf("pick %d\n", T);
							prods[prev+1]=prod+T; stk[prev]=T; gds[prev+1]=have-ask[prev]+ll(v[prev].t-st-T)*(prod+T);
							FOR(k, prev+1, pos) prods[k+1]=prod+T, stk[k]=0, gds[k+1]=gds[k]+ll(v[k].t-v[k-1].t)*prods[k+1]-v[k].c;
							fd=true; break;
						}else stk[prev]=0;
						
					}
					if (!fd){ok=false; break;}
				}else{
					H=nt+1, T=a;
					while(T+1<H){
						M=(H+T)/2;
						if (ll(nt-M)*(prod+M)>=tmp)T=M;
						else H=M;
					}
					prod+=stk[pos]=T;
					gds[pos+1]=ll(nt-T)*prod-tmp;
					prods[pos+1]=prod;
					//printf("best at %d/%d, prod  %d, remain %Ld\n", T, nt, (nt-T)*prod, ng);
				}
				++pos;

			}
			//printf("RES>>>>>><< %d %d\n", ok, nv);


			if (ok){ ll ns=0; REP(j, nv) ns+=v[j].inc; checkmax(res, ns); }
		}
		return res;
	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] ={"75027 1000000000 1000000000", "64283 273413194 473297270", "58069 423823282 505995226", "77854 90247643 148557165", "19832 32347078 23261358", "52724 521774398 954613766", "10864 18845262 2348313", "9591 4927730 1027466", "25966 136724694 124376682", "73352 1000000000 1000000000", "21206 81461176 117877210", "13991 15021802 137817", "17490 25895800 19428503", "62219 123986542 186075174", "24007 72179080 90978822"} ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 2LL; verify_case(0, Arg1, maxIncome(Arg0)); }
	void test_case_1() { string Arr0[] = {"5 1 8", "7 15 3"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 11LL; verify_case(1, Arg1, maxIncome(Arg0)); }
	void test_case_2() { string Arr0[] = {"5 1 8", "7 16 3"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 8LL; verify_case(2, Arg1, maxIncome(Arg0)); }
	void test_case_3() { string Arr0[] = {"12 39 19", "18 50 13"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 19LL; verify_case(3, Arg1, maxIncome(Arg0)); }
	void test_case_4() { string Arr0[] = {"40 264 318", "88 1660 1120", "54 28 39", "64 348 134", "90 286 3000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 4159LL; verify_case(4, Arg1, maxIncome(Arg0)); }
	void test_case_5() { string Arr0[] = {"30 926 11"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(5, Arg1, maxIncome(Arg0)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	FactoryEmulation ___test; 
	___test.run_test(0);
} 
// END CUT HERE
