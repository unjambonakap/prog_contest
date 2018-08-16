// BEGIN CUT HERE

// END CUT HERE
#line 5 "TopologicalEquivalence.cpp"

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


const int maxn=8, maxp=50*50/3;
int n;
map<pii, int> mp;
multiset<int> e[maxp];
int visited[maxp];
int parent[maxp];
int seen[maxp];
vi tmp;


int root(int a){return parent[a]==-1?a:parent[a]=root(parent[a]);}

int add(int a, int b){ e[a].insert(b); if (a!=b) e[b].insert(a); }

void dfs(int a){
    if (visited[a]) return;
    visited[a]=1;
    int del=0;
    if (e[a].size()==2){
        int x=*e[a].begin(), y=*(++e[a].begin());
        if (x!=a && y!=a){
            del=1;
            e[x].erase(e[x].find(a));
            e[y].erase(e[y].find(a));
            add(x, y);
        }
    }
    if (!del) tmp.pb(a);
    int fd=1;
    while(fd){
        fd=0;
        FE(it, e[a]) if (!visited[*it]){fd=1; dfs(*it); break;}
    }

}


class TopologicalEquivalence {
	public:
	int countDistinct(vector <string> ls) {
        n=0;
        mp.clear();
        REP(i, maxp) e[i].clear();

        FE(it, ls){
            FE(ita, *it) if (*ita==','||*ita=='-') *ita=' ';
            istringstream ss(*it);
            int a, b, c, d;
            while(ss>>a>>b>>c>>d){
                int x, y;
                if (mp.count(MP(a, b))) x=mp[MP(a, b)]; else x=mp[MP(a, b)]=n++;
                if (mp.count(MP(c, d))) y=mp[MP(c, d)]; else y=mp[MP(c, d)]=n++;
                add(x, y);
            }
        }
        memset(parent, -1, sizeof(parent));
        memset(visited, 0, sizeof(visited));
        vector<vi> tb;
        REP(i, n){
            tmp.clear();
            dfs(i);
            if (tmp.size()) tb.pb(tmp);
        }


        int m=tb.size();
        vector<vector<vi> > ntb(m);
        REP(i, m){
            sort(ALL(tb[i]));
            ntb[i]=vector<vi>(tb[i].size());
            REP(j, tb[i].size()) FE(it, e[tb[i][j]]) ntb[i][j].pb(lower_bound(ALL(tb[i]), *it)-tb[i].begin());
        }

        int res=0;
        memset(seen, 0, sizeof(seen));
        REP(i, m){
            int fd=0;
            int nm=ntb[i].size();
            REP(j, i) if (!seen[j] && nm==ntb[j].size()){
                vi x(nm);
                REP(k, nm) x[k]=k;
                vector<vi> &a=ntb[j], &b=ntb[i];
                do{
                    fd=1;
                    REP(l, nm){
                        if (a[l].size()!=b[x[l]].size()){fd=0; goto fail;}
                        vi tmpx;
                        REP(ka, a[l].size()) tmpx.pb(x[a[l][ka]]);
                        sort(ALL(tmpx));
                        if (tmpx!=b[x[l]]){fd=0; goto fail;}
                    }
fail:;
                    if (fd) goto out;
                    
                }while(next_permutation(ALL(x)));
            }
out:;
            seen[i]=fd;
            res+=1-fd;
        }
        return res;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0,7-5,7 5,7-5,2 5,2-0,2 0,2-0,7 5,2-7,0",
 "8,7-15,7 15,7-10,2 10,2-8,7 10,2-10,5 10,5-12,5",
 "16,6-19,2 16,6-22,4 22,4-21,2 21,2-19,4",
 "24,7-24,2",
 "25,5-27,3 27,7-29,5 25,2-27,3 29,2-27,3 25,5-27,7","27,3-29,5"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, countDistinct(Arg0)); }
	void test_case_1() { string Arr0[] = {"16,0-17,1 17,1-17,3 17,3-16,4 16,4-14,4 14,4-14,0",
 "9,1-9,3 9,3-10,4 10,4-12,4 12,4-13,3 14,0-16,0",
 "0,4-1,2 1,2-2,0 2,0-3,2 1,2-3,2 3,2-4,4 5,0-7,0",
 "25,0-27,0 24,1-24,3 24,3-25,4 25,4-27,4 27,4-27,2",
 "7,0-8,1 8,1-7,2 7,2-8,3 8,3-7,4 7,4-5,4 5,4-5,2",
 "18,0-20,0 18,0-18,2 18,2-18,3 18,2-18,4 18,4-20,4",
 "21,0-23,0 21,0-21,2 21,2-22,2 21,2-21,4 24,1-25,0",
 "5,2-5,0 5,2-7,2 9,1-10,0 10,0-12,0 12,0-13,1",
 "27,2-25,2 28,0-28,2 28,2-28,4 30,0-30,2 30,2-30,4",
 "28,2-30,2 31,0-31,4"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(1, Arg1, countDistinct(Arg0)); }
	void test_case_2() { string Arr0[] = {
    "8,29-2,21 6,40-4,49 56,9-55,5 0,46-4,49 74,6-73,3", "20,5-22,1 8,78-3,77 76,2-78,9 17,9-10,6 26,3-23,9", "5,24-2,21 36,1-35,5 42,2-46,9 7,63-9,64 76,0-77,1", "52,3-51,7 42,2-48,6 39,1-38,0 85,6-82,8 38,0-33,0", "82,8-85,8 67,3-68,7 23,9-27,5 86,0-89,3 35,9-32,9", "9,14-7,11 7,37-8,32 9,65-7,63 2,65-1,63 73,3-74,9", "2,31-0,37 27,5-26,3 52,2-56,9 63,9-68,7 2,31-8,32", "0,37-7,37 5,76-3,77 7,11-7,19 4,46-6,40 22,1-21,6", "0,12-7,19 44,5-46,9 2,18-7,19 5,1-0,1 78,4-77,1", "63,9-67,3 16,0-18,7 9,54-7,54 5,53-2,55 5,82-9,84", "21,6-23,9 5,73-4,72 6,81-5,82 3,59-5,53 5,3-6,9", "82,0-81,4 18,7-17,9 4,7-1,9 6,40-7,48 7,67-0,60", "81,4-85,6 59,6-58,6 0,23-8,29 42,2-42,3 89,3-85,8", "6,33-5,34 36,8-35,5 9,75-5,76 65,5-67,2 7,54-6,52", "96,8-90,3 49,6-42,2 91,1-94,3 67,3-67,2 7,20-3,21", "94,3-90,0 7,63-7,67 36,8-35,9 61,6-67,2 2,75-9,75", "17,4-17,9 9,84-1,88 63,9-61,6 2,75-5,73 16,0-10,6", "46,9-42,3 56,9-52,3 7,19-2,16 0,46-3,41 97,1-94,3", "1,81-6,81 78,9-74,9 9,75-8,78 20,5-23,9 46,9-48,6", "8,29-5,24 3,21-5,24 48,6-45,5 4,18-2,18 7,44-7,48", "97,1-90,0 8,29-1,28 6,9-1,9 78,9-74,6 8,44-7,44", "39,1-33,0 6,33-7,37 3,77-7,77 94,3-90,3 35,5-33,0", "18,7-17,4 52,2-52,3 2,65-7,67 63,9-65,5 76,0-78,4", "4,7-4,2 1,81-1,88 2,55-6,52 67,2-68,7 3,41-6,40", "2,55-0,56 17,9-15,6 61,6-60,6 5,73-9,75 60,6-67,2", "7,20-8,29 58,6-52,2 7,48-8,44 96,8-97,8 76,0-76,2", "64,5-61,6 5,84-9,84 15,2-15,6 6,40-0,46 39,1-36,1", "73,3-76,0 1,28-0,23 39,1-35,5 97,1-97,8 42,3-41,7", "2,31-7,37 7,20-2,21 52,2-51,7 7,48-4,49 89,3-82,0", "5,1-6,9 4,7-0,1 56,9-58,6 2,31-5,34 94,6-97,8", "9,54-6,52 55,5-58,6 9,84-9,89 4,72-2,75 9,14-8,12", "9,65-9,64 97,8-94,3 23,9-22,1 20,5-21,6 90,3-94,6", "44,5-42,2 5,84-1,88 54,5-55,5 85,6-86,4 63,9-64,5", "2,16-4,18 17,9-16,0 65,5-64,5 82,8-81,4 1,9-0,1", "74,6-74,9 7,11-0,12 3,59-2,55 90,0-90,3 15,2-16,0", "63,9-60,6 7,11-8,12 9,84-1,81 48,6-49,6 86,0-82,0", "42,2-41,7 2,16-2,18 51,7-56,9 52,2-54,5 81,4-86,4", "81,4-89,3 45,5-44,5 5,53-6,52 20,3-20,5 9,84-6,81", "90,3-97,8 9,75-3,77 23,9-24,1 76,0-78,9 9,14-7,19", "4,7-5,3 3,21-2,21 4,7-6,9 33,0-36,8 94,6-96,8", "41,7-46,9 7,67-1,63 1,81-5,82 49,6-46,9 33,0-36,1", "78,9-78,4 17,9-15,2 59,6-52,2 18,7-18,1 26,3-24,1", "54,5-56,9 85,8-85,6 45,5-46,9 59,6-56,9 35,9-33,0", "78,9-73,3 22,1-24,1 89,3-86,4 89,3-85,6 10,6-15,6", "6,33-8,32 5,34-7,37 7,67-9,65 3,59-6,52 91,1-90,3", "5,1-4,7 1,88-9,89 0,60-7,63 73,3-76,2 67,2-63,9", "5,3-5,1 4,67-2,65"
    }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, countDistinct(Arg0)); }

//	void test_case_2() { string Arr0[] = {"0,2-2,2 10,2-12,0 2,2-4,0 12,0-14,2",
// "4,0-4,4 14,2-10,2 4,4-2,2 10,2-12,4",
// "4,4-6,2 12,4-14,2 6,2-8,2 12,4-12,6",
// "14,8-12,6 6,2-4,0 12,6-10,8"}
//
//; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, countDistinct(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  TopologicalEquivalence ___test; 
        ___test.run_test(-1);
        } 
// END CUT HERE
