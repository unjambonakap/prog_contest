// BEGIN CUT HERE

// END CUT HERE
#line 5 "UnknownNames.cpp"

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

inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}


const int maxn=51;
int graph[maxn][maxn];
int deg[maxn];
int visited[maxn];
int n;

string dl[maxn];

int dfs(int p, int d){
	if (visited[p])return 0;
	visited[p]=1;
	if (p==d)return 1;
	REP(i, n)if (graph[p][i] && dfs(i, d))return 1;
	return 0;

}

class UnknownNames {
	public:
	vector <string> sortNames(vector <string> names) {
		int l=names[0].length();
		vs res;
		string prev=string(l, 'A');
		while((n=names.size())>0){
			memset(graph, 0, sizeof(graph));
			REP(i, n) REP(j, n) if (i!=j){
				graph[i][j]=1;
				REP(k, l) if (names[i][k]!='?' && names[j][k]!='?') if (names[i][k]>names[j][k]){graph[i][j]=0; break;}
			}


			vector<pii> temp;
			REP(i, n) {
				dl[i]=prev;
				REP(j, n) if (graph[j][i]&&!graph[i][j]) REP(k, l) if (names[j][k]!='?') dl[i][k]=max(dl[i][k], names[j][k]);
				REP(k, l) if (names[i][k]!='?'){
					if (names[i][k]<dl[i][k])return vs();
				   	dl[i][k]=max(dl[i][k], names[i][k]);
					
				}

				REP(j, i) if (graph[i][j] && graph[j][i])temp.pb(MP(i, j)), graph[j][i]=graph[i][j]=0;
			}
			FE(it, temp){
				memset(visited, 0, sizeof(visited));
				if (dfs(it->ST, it->ND))graph[it->ST][it->ND]=1;
				memset(visited, 0, sizeof(visited));
				if (dfs(it->ND, it->ST))graph[it->ND][it->ST]=1;
			}

			memset(deg, 0, sizeof(deg));
			REP(i, n) REP(j, n) if (graph[i][j])++deg[j];
			vector<int> q;
			REP(i, n) if (deg[i]==0) q.pb(i);
			

			int p=-1;
			REP(i, q.size()) if (p==-1 || dl[q[i]]<dl[p])p=q[i];
			if (p==-1)return vs();
			res.pb(prev=dl[p]);
			swap(names[n-1], names[p]);

			names.pop_back();
		}
		return res;


	}

	// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"?ED?", "TO??", "????"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"AAAA", "AEDA", "TODA" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, sortNames(Arg0)); }
	void test_case_1() { string Arr0[] = {"T???????", "SO??????", "?MP?????", "??OC????", "???BO???", "????MD??", "?????CE?", "??????CR"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"AAAAAACR", "AAAAACER", "AAAAMDER", "AAABODER", "AAOCODER", "AMPCODER", "SOPCODER", "TOPCODER" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, sortNames(Arg0)); }
	void test_case_2() { string Arr0[] = { "?E", "L?", "??", "L?"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"AA", "AE", "LE", "LE" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, sortNames(Arg0)); }
	void test_case_3() { string Arr0[] = {"A???J?", "BC????", "?DE???", "??FG??", "???HI?"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, sortNames(Arg0)); }
	void test_case_4() { string Arr0[] = {"AAH????AB?EE??GCB?HE?G?CACA?A?B??A?JG?AGD????F?EEE",
		"?D?NI??JK?H?N?K???HKM?L?GE?N??G?K?L??M?HM??CP?E?NJ",
		"?KOVL?????K??TKP???L??N?N??O????MI?Y?QK?NR?E?RF???",
		"?M?Z??N?T??R????????TP?OQ??SY??Z?O?Z?YTL?RMG???YV?",
		"W???????Z?TX?Z???XZMYRNX??L??Q?????????L?T?J????Z?",
		"ZYZZ?????S?ZZZ?Z??ZV?Y????LZ?R?ZZVZZ?Z??ZT?M?V?Z??",
		"?Y?Z?Z?X??UZ?ZZ??ZZY?ZV?Z?MZ?W?Z??Z?ZZ?????TZ??Z?Z",
		"Z?????Z??ZV????Z????Z?????S????ZZZZ????Z???TZ?W?ZZ",
		"ZZ??ZZZ???WZZZ????Z?Z?Z?Z???Z?Z?ZZ?Z??Z??Z?W???ZZ?",
		"??????????Z?Z?Z??Z?ZZZ?Z??ZZ?Z?????ZZ??ZZZZZ??ZZ??",
		"?Z?Z???Z????Z?ZZ??Z?ZZZ?Z???Z?ZZ??Z?Z??Z??Z??Z???Z",
		"?Z?ZZ?Z??ZZ?ZZ???????Z???ZZZ?Z?ZZ?Z?ZZ?Z?ZZZ?Z??ZZ",
		"??Z??ZZ?Z?ZZ?ZZ????Z???Z??Z???????Z??Z??Z???Z?ZZ?Z",
		"ZZ??Z?ZZ??ZZZ??Z????ZZ?Z?ZZ??ZZ???Z?ZZ??ZZZZZZZ??Z",
		"?Z????ZZZ???Z??Z?Z?Z?Z????Z??ZZZZ??ZZ?Z?????Z??Z??",
		"Z???ZZZ??Z?ZZ??Z??Z?Z???Z???ZZ??Z???Z?ZZ??ZZ??Z??Z",
		"??????ZZ???Z?Z?ZZ?ZZ????Z??Z??????ZZ?ZZ?Z?Z?Z??Z??",
		"ZZZ?Z??ZZ???Z??Z?Z?ZZ?Z??ZZ?Z????ZZZ??Z??Z?ZZ??ZZZ",
		"Z?Z???ZZZ???ZZ?Z??Z???ZZZZZ??Z??Z??Z?Z?ZZZ?ZZ??Z?Z",
		"Z???Z???ZZ?Z??Z??ZZ??ZZZ??Z??ZZ?Z?????????Z???Z?ZZ",
		"Z?Z????Z?ZZZ?????Z???Z?Z??ZZ??Z??ZZZ??ZZZ?Z?ZZ?Z?Z",
		"???Z?????????ZZZZ??Z?Z??Z????Z??ZZ???Z?ZZ??????Z??",
		"???Z?Z?ZZZ?Z??Z?????Z??????ZZZ?Z?Z?ZZ?ZZZZZ?ZZZZ??",
		"Z??ZZ??Z?????Z????ZZZ?Z?Z??Z?ZZZ?Z?Z???Z?Z??????Z?",
		"ZZ?Z?ZZ?Z???ZZ????Z???Z?Z??Z?ZZZZ??ZZZ???ZZ?Z?ZZZ?",
		"??ZZ????ZZ??Z?Z????ZZZ?Z?Z?Z?ZZZ?Z???ZZ?ZZ???Z???Z",
		"Z??Z???Z?ZZZ???Z?Z?????Z???ZZ???Z?ZZZ?????Z??ZZZ??",
		"?Z????ZZZ??Z???????Z???Z???Z?Z?Z??Z?ZZ?ZZ?ZZZZ???Z",
		"?ZZZ?ZZZZ?ZZ?Z?ZZZZ?ZZ?Z?Z??Z?ZZ??ZZ?Z???Z??????ZZ",
		"ZZ?ZZZ??Z????Z?ZZZZZ?Z???Z??ZZ?Z???ZZ?Z?Z?ZZ??ZZZZ",
		"?ZZ?Z?ZZ?ZZZ?ZZ??ZZZZ?ZZ?Z?Z?????ZZ???ZZZZ?Z?Z?ZZ?",
		"Z??ZZ??ZZ???Z?ZZZ??Z??ZZ?Z?Z??????Z?ZZ?ZZZZ?Z?Z??Z",
		"???ZZ???ZZZZZZ???????ZZZZZ?Z?Z?ZZZZZ??ZZZ??ZZZ????",
		"Z?ZZ?Z?ZZ???ZZZZZ???ZZ?ZZ?Z??ZZ?Z????Z??Z?????ZZ?Z",
		"??Z?ZZZ?Z???Z???Z?ZZ???Z??ZZ???Z??ZZ??Z???Z?????ZZ",
		"?Z?Z?Z?Z?Z?Z?ZZ???Z??ZZ?ZZZ?Z???????Z?ZZ?ZZ???????",
		"Z??Z??Z???ZZZZZZ??ZZ???????ZZZZ?Z?????ZZ?Z??Z??ZZ?",
		"????????Z??ZZ????ZZ??Z?ZZ???Z?ZZ??Z?Z??ZZZ?ZZZ?ZZ?",
		"??Z??ZZ?Z?Z?????Z??Z?ZZZ??Z?Z?ZZ??ZZ?Z?Z?ZZ???ZZ??",
		"??ZZ???ZZ????????ZZZZ????Z??ZZ?Z?Z?ZZZZZZZ????ZZ??",
		"?ZZ?Z????ZZ???ZZZ?Z???Z?ZZZ???Z?ZZZ?????ZZZZZ?Z?ZZ",
		"????Z?Z??Z????Z??ZZZZZ??Z??ZZZ?ZZ??Z???Z?Z?Z???ZZ?",
		"Z???????Z?ZZZZ??Z?ZZZ?ZZZ??Z??Z??Z?Z?ZZZ?Z?Z?ZZ?ZZ",
		"?Z?ZZ??ZZZZ???ZZZZZZZ?ZZ????Z?Z?ZZ???Z?Z?ZZ???Z??Z",
		"??Z?Z??Z?Z??ZZ??Z?ZZ?Z???ZZ??ZZ???Z?????Z?Z?ZZ?Z?Z",
		"Z?Z??ZZ???ZZ?ZZZ?ZZZ??Z????ZZ???ZZ?ZZ????ZZ???ZZZ?",
		"????ZZ?ZZ?ZZ?ZZ??ZZZ???ZZZ??Z???Z??ZZ?Z?????Z????Z",
		"??ZZ?Z??Z?ZZ???ZZ?Z?Z?Z?????Z?Z???Z??ZZ??Z?Z?ZZ??Z", 
		"?ZZZZ??Z?Z?ZZZ?Z?Z?Z?ZZZ???Z??Z?ZZ??Z?Z??Z??Z?Z??Z",
		"ZZ?Z???Z??ZZZ?ZZZ?ZZ?ZZ?ZZ???ZZZZ?Z??Z?Z?Z?Z??Z??Z"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"AAHAAAAABAEEAAGCBAHEAGACACAAAABAAAAJGAAGDAAAAFAEEE", "ADHNIAAJKAHENAKCBAHKMGLCGEANAAGAKALJGMAHMAACPFEENJ", "AKOVLAAJKAKENTKPBAHLMGNCNEAOAAGAMILYGQKHNRAEPRFENJ", "AMOZLANJTAKRNTKPBAHLTPNOQEASYAGZMOLZGYTLNRMGPRFYVJ", "WMOZLANJZATXNZKPBXZMYRNXQELSYQGZMOLZGYTLNTMJPRFYZJ", "ZYZZLANJZSTZZZKZBXZVYYNXQELZYRGZZVZZGZTLZTMMPVFZZJ", "ZYZZLZNXZSUZZZZZBZZYYZVXZEMZYWGZZVZZZZTLZTMTZVFZZZ", "ZYZZLZNXZSUZZZZZZZZZYZVXZEMZYZGZZZZZZZTZZTMTZVFZZZ", "ZYZZLZNXZZUZZZZZZZZZZZVZZZMZYZZZZZZZZZZZZZMTZZFZZZ", "ZYZZLZZXZZVZZZZZZZZZZZVZZZSZYZZZZZZZZZZZZZMTZZWZZZ", "ZYZZLZZZZZVZZZZZZZZZZZVZZZSZYZZZZZZZZZZZZZZTZZWZZZ", "ZYZZLZZZZZVZZZZZZZZZZZVZZZSZZZZZZZZZZZZZZZZTZZZZZZ", "ZYZZLZZZZZVZZZZZZZZZZZVZZZSZZZZZZZZZZZZZZZZTZZZZZZ", "ZYZZLZZZZZVZZZZZZZZZZZVZZZZZZZZZZZZZZZZZZZZTZZZZZZ", "ZYZZZZZZZZVZZZZZZZZZZZVZZZZZZZZZZZZZZZZZZZZTZZZZZZ", "ZYZZZZZZZZVZZZZZZZZZZZVZZZZZZZZZZZZZZZZZZZZTZZZZZZ", "ZYZZZZZZZZVZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZTZZZZZZ", "ZYZZZZZZZZVZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZTZZZZZZ", "ZYZZZZZZZZVZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZTZZZZZZ", "ZZZZZZZZZZVZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZTZZZZZZ", "ZZZZZZZZZZVZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZTZZZZZZ", "ZZZZZZZZZZVZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZTZZZZZZ", "ZZZZZZZZZZVZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZTZZZZZZ", "ZZZZZZZZZZVZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZTZZZZZZ", "ZZZZZZZZZZWZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZWZZZZZZ", "ZZZZZZZZZZWZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZWZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZWZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZWZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZWZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZWZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZWZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ", "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, sortNames(Arg0)); }
	void test_case_5() { string Arr0[] = {"BI", "AQ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(5, Arg1, sortNames(Arg0)); }

	// END CUT HERE

};

// BEGIN CUT HERE
int main(){
	UnknownNames ___test; 
	___test.run_test(-1);
} 
// END CUT HERE
