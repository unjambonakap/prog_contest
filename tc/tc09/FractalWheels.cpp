// BEGIN CUT HERE

// END CUT HERE
#line 5 "FractalWheels.cpp"

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

const int MAX_N=1001;
int graph[MAX_N][MAX_N];
int ng[MAX_N][MAX_N];
int visited[MAX_N];
int degree[MAX_N];
int leaf[MAX_N];
int center;
int n;




void addEdge(const string &s){
	istringstream ss(s);
	int a, b;
	ss>>a>>b;
	graph[a][b]=graph[b][a]=1;
}

bool checkit(int pos, int depth, int d){
	int i, j, k, c;
	c=0;


	if (depth==0){
		REP(i, n)
			if (ng[pos][i])return 0;
		return 1;
	}
	vi adjL;
	REP(i, n)
		if (ng[pos][i]){
			ng[pos][i]=ng[i][pos]=0;
			adjL.pb(i);
		}
	if (adjL.size()!=d)return 0;

	vi cycle;
	int pa=adjL[0];
	while(1){
		cycle.pb(pa);
		REP(i, adjL.size()){
			if (ng[pa][adjL[i]]){
				ng[pa][adjL[i]]=ng[adjL[i]][pa]=0;
				pa=adjL[i];
				break;
			}
		}
		if (i==adjL.size())break;
	}
	if (cycle.size()!=adjL.size()+1 || cycle[0]!=cycle.back())return 0;
	

	FE(it, adjL){
		if (!checkit(*it, depth-1, d))return 0;
	}
	
	return 1;


}

class FractalWheels {
	public:
	vector <int> describeWheel(int N, vector <string> edges) {
		string s, sa;
		int i, j, k;


		n=N;
		memset(graph, 0, sizeof(graph));


		FE(it, edges)s+=*it;

		for (i=0; i<s.length(); ++i){
			if (s[i]==','){
				addEdge(sa);
				sa="";
			}
			else
				sa+=s[i];
		}
		addEdge(sa);

		memset(degree, 0, sizeof(degree));
		REP(i, n)
			for (j=i+1; j<n; ++j)
				if (graph[i][j])
					++degree[i], ++degree[j];

		memset(leaf, 0, sizeof(leaf));
		set<int> dg;

		REP(i, n){
			if (degree[i]==3)leaf[i]=1;
			dg.insert(degree[i]);
		}
		vi sol;

		if (dg.size()>3)return sol;
		if (dg.find(3)==dg.end())return sol;

		set<int>::iterator ita=dg.end();
		--ita;
		int d=*ita;

		if (d==3){
			if (n==4 && dg.size()==1){
				sol.pb(0);
				sol.pb(3);
			}
			return sol;
		}

		//{7, {"0 1,0 2,0 3,0 4,0 5,0 6,", "1 2,2 3,1 3,4 5,5 6,4 6"}}
		if (d+1==n){
			printf("la\n");
			if (dg.size()==2){
				int c;
				c=0;
				REP(i, n){
					if (degree[i]>3)++c;
					if (degree[i]==d)center=i;
				}
				memcpy(ng, graph, sizeof(graph));

				if (c==1 && checkit(center, 1, d)){

					sol.pb(0);
					sol.pb(d);
				}
			}
			return sol;
		}

		
		d-=3;
		if (d<3)
			return sol;
		

		if (dg.find(d)==dg.end())//no center
			return sol;
		int c=0;
		center=-1;

		REP(i, n){
			if (degree[i]==d){
				if (d==3){
					int ca=0;
					REP(j, n)
						if (graph[i][j] && degree[j]==3)
							break;

					if (j!=n){++c; continue;}//sure it's a leaf
				}
				if (center!=-1)return sol;
				center=i;




			}
			if (degree[i]==3)++c;
		}
		if (degree[center]==3)--c;

		if (center==-1)return sol;

		int depth=0;

		while(c!=1){
			if (c==0 || c%d!=0)return sol;
			c/=d;
			++depth;
		}


		memcpy(ng, graph, sizeof(graph));
		if (!checkit(center, depth, d))return sol;
		sol.pb(depth-1);
		sol.pb(d);
		return sol;
	}
//	void test_case_0() { int Arg0 = 5; string Arr1[] = {
//"","0 1,0 2,0 3,0 4,",
//"1 2,2 3,3 4,1 4"
//}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 4 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, describeWheel(Arg0, Arg1)); }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 13; string Arr1[] = {
	"0 1,0 2,0 3,1 2,1 3,1 4,1 5,1 6,2 3,2 7,2 8,2 9,3 ", "10,3 11,3 12,4 5,4 6,5 6,7 8,7 9,8 9,10 11,10 12,1", "1 12"
}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 4 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, describeWheel(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 21; string Arr1[] = {
"0 1,0 2,0 3,0 4,1 2,1 4,1 5,1 6,1 7,1 8,2 3,2 9,2 ",
"10,2 11,2 12,3 4,3 13,3 14,3 15,3 16,4 17,4 18,4 1","",
"9,4 20,5 6,5 8,6 7,7 8,9 10,9 12,10 11,11 12,13 14",
",13 16,14 15,15 16,17 18,17 20,18 19,19 20",""
}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 4 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, describeWheel(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 13; string Arr1[] = {
"0 1,0 2,0 3,1 2,1 3,1 4,1 5,1 6,2 3,2 7,2 8,2 9,3 ",
"10,3 11,3 12,4 5,4 6,5 6,7 8,7 9,8 9,10 11,10 12,1",
"1 12,0 7"
}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, describeWheel(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 11; string Arr1[] = {
"0 2,0 3,0 4,0 5,0 6,0 7,0 8,0 9,0 10,1 2,1 10,",
"2 3,3 4,4 5,5 6,6 7,7 8,8 9,9 10"
}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, describeWheel(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 3; string Arr1[] = {
"0 1,1 2"
}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, describeWheel(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  FractalWheels ___test; 
        ___test.run_test(0); 
        } 
// END CUT HERE
