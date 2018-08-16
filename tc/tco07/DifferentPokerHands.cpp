// BEGIN CUT HERE

// END CUT HERE
#line 5 "DifferentPokerHands.cpp"

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

int cnt[13];
struct cset{
	vector<pii> c;
	int type;
	vi diff;
	cset(vector<pii> a):c(a){
		sort(ALL(c));

//		REP(i, 5) printf("%d|%d ", c[i].ST, c[i].ND); printf("\n");
		bool st=true;
		REP(i, 4) if (c[i].ST!=c[i+1].ST-1 && (i!=3 || c[0].ST!=0 || c[4].ST!=12)){st=false; break;}
		if (st && c[0].ST==0 && c[4].ST==12) c[4].ST=-1;
		sort(ALL(c));

		bool col=true;
		REP(i, 4)  if (c[i].ND!=c[4].ND) {col=false; break;}
		memset(cnt, 0, sizeof(cnt));
		REP(i, 5) cnt[c[i].ST]++;
		int paa=-1, pab=-1, tv=-1, sq=-1;
		REP(i, 13){
		   	if (cnt[i]==2 && paa==-1) paa=i;
			else if (cnt[i]==2) pab=i;
			else if (cnt[i]==3) tv=i;
			else if (cnt[i]==4) sq=i;
		}
		diff.clear();

		if (st && col) type=0, diff.pb(c[0].ST);
		else if (sq!=-1) type=2, diff.pb(sq);
		else if (tv!=-1 && paa!=-1) type=3, diff.pb(tv), diff.pb(paa-15);
		else if (col){ type=4; REP(i, 5) diff.pb(c[i].ST);}
		else if (st) type=5, diff.pb(c[0].ST);
		else if (tv!=-1){ type=6, diff.pb(tv); REP(i, 5) if (c[i].ST!=tv) diff.pb(c[i].ST-15); }
		else if (paa!=-1 && pab!=-1){type=7, diff.pb(paa), diff.pb(pab); REP(i, 5) if (c[i].ST!=paa && c[i].ST!=pab) diff.pb(c[i].ST-15);assert(diff.size()==3);}
		else if (paa!=-1){type=8, diff.pb(paa); REP(i, 5) if (c[i].ST!=paa) diff.pb(c[i].ST-15);}
		else{type=9; REP(i, 5) diff.pb(c[i].ST);}
		//sort(ALL(diff), greater<int>());
	}
	bool operator<=(const cset &a)const{
		if (a.type!=type)return a.type<type;
		assert(a.diff.size()==diff.size());
		REP(i, diff.size()) if (a.diff[i]!=diff[i]) return diff[i]<a.diff[i];
		//REP(i, 5) if (c[i].ST!=a.c[i].ST) return (c[i].ST<a.c[i].ST);
		return 1;
	}

	bool operator<(const cset &a)const{
		if (a.type!=type)return a.type<type;
		assert(a.diff.size()==diff.size());
		REP(i, diff.size()) if (a.diff[i]!=diff[i]) return diff[i]<a.diff[i];
		//REP(i, 5) if (c[i].ST!=a.c[i].ST) return (c[i].ST<a.c[i].ST);
		return 0;
	}

};

vector<pii> cards;
set<cset> lst;

class DifferentPokerHands {
	public:
		int noDifferentHands(vector <string> cc) {
			cards.clear();
			REP(i, 5){
				int v, c;
				v=cc[i][0]; c=cc[i][1];
				if (v=='T') v=8;
				else if (v=='J') v=9;
				else if (v=='Q') v=10;
				else if (v=='K') v=11;
				else if (v=='A') v=12;
				else v-='2';

				if (c=='S') c=0;
				else if (c=='C') c=1;
				else if (c=='D') c=2;
				else if (c=='H') c=3;
				else assert(0);
				cards.pb(MP(v, c));
			}
			cset org(cards);
			CLR(lst);

			REP(va, 13) REP(ca, 4) REP(vb, 13) REP(cb, 4)if (vb!=va || cb!=ca){// if (vb<va || (vb==va && cb<ca)){
				pii a, b;
				a=MP(va, ca); b=MP(vb, cb);
				//if (va!=2 || vb!=12)continue;
				bool fd=false;
				REP(i, 5) if (cards[i]==a || cards[i]==b){fd=true; break;}
				if (fd)continue;
				vector<pii> npa=cards;
				npa.pb(a); npa.pb(b);

				//REP(i, 5) printf("%d ", cards[i].ST); printf("\n");
				cset best=org;
				REP(i, 7) REP(j, i){

					vector<pii> np;
					REP(k, 7) if (k!=i && k!=j) np.pb(npa[k]);
					cset na(np);
					if (best<na) best=na;
				}
				if (org<=best) lst.insert(best);

			}

			//FE(it, lst){
			//   	cset best=*it;
			//	REP(i, 5) printf("%d %d||", best.c[i].ST, best.c[i].ND);printf("\n");
			//}

			return lst.size();

			}

			// BEGIN CUT HERE
			public:
			void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
			private:
			template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
			void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
			//void test_case_0() { string Arr0[] = {"5S", "6S", "7S", "8S", "9S"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, noDifferentHands(Arg0)); }
			void test_case_0() { string Arr0[] = {"5H", "3D", "QS", "2S", "5S"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, noDifferentHands(Arg0)); }
			void test_case_1() { string Arr0[] = {"AS", "AD", "KH", "KC", "QS"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(1, Arg1, noDifferentHands(Arg0)); }
			void test_case_2() { string Arr0[] = {"AH", "8S", "6S", "4S", "AS"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 96; verify_case(2, Arg1, noDifferentHands(Arg0)); }

			// END CUT HERE

		};

		// BEGIN CUT HERE
		int main(){
			DifferentPokerHands ___test; 
			___test.run_test(0);
		} 
		// END CUT HERE
