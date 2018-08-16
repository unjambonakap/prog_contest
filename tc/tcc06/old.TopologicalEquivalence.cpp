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

const int maxn=500*8;


int n;
map<pii, int> pl;
pii rpl[maxn*5];
vi e[maxn];
vi ne[1000][8];

int done[maxn];
int visited[maxn];

void dfs(int a, vi &b){
    if (visited[a]) return;
    visited[a]=1;
    b.pb(a);
    FE(it, e[a]) dfs(*it, b);
}



class TopologicalEquivalence {
	public:
	int countDistinct(vector <string> lineSegs) {
        pl.clear();
        n=0;
        REP(i, maxn) e[i].clear();
        FE(it, lineSegs){
            FE(ita, *it) if (*ita==',' || *ita=='-') *ita=' ';
            istringstream ss(*it);
            int xa, ya, xb, yb;
            while(ss>>xa){
                ss>>ya>>xb>>yb;
                if (!pl.count(MP(xa, ya))) rpl[n]=MP(xa, ya), pl[MP(xa, ya)]=n++;
                if (!pl.count(MP(xb, yb))) rpl[n]=MP(xb, yb), pl[MP(xb, yb)]=n++;
                int a=pl[MP(xa, ya)], b=pl[MP(xb, yb)];
                e[a].pb(b);
                e[b].pb(a);
            }
        }
        memset(visited, 0, sizeof(visited));

        REP(i, n) if (e[i].size()==2 && e[i][0]!=i){
            FE(it, e[e[i][0]]) if (*it==i) *it=e[i][1];
            FE(it, e[e[i][1]]) if (*it==i) *it=e[i][0];
            e[i].clear();
        }
        

        
        vector<vi> fig;
        REP(i, n) if (!visited[i] && e[i].size()){
            fig.pb(vi());
            dfs(i, fig.back());
        }
        int na=fig.size();
        map<int, int> rmp;
        REP(i, na){
            REP(j, fig[i].size()) rmp[fig[i][j]]=j;
            REP(j, fig[i].size()){
                ne[i][j]=vi(fig[i].size(), 0);
                FE(it, e[fig[i][j]]) ++ne[i][j][rmp[*it]];
            }

        }

        memset(done, 0, sizeof(done));
        int ans=na;
        REP(i, na) REP(j, i) if (!done[j] && fig[i].size()==fig[j].size()){
            int nb=fig[i].size();
            int perm[nb];
            REP(k, nb) perm[k]=k;
            do{
                int fd=1;

                REP(x, nb) REP(y, nb) if (ne[i][x][y]!=ne[j][perm[x]][perm[y]]){fd=0; goto out;}
out:
                if (fd){ --ans; done[i]=1; break; }
            }while(next_permutation(perm, perm+nb));

        }
        return ans;

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
void test_case_2() { string Arr0[] = {"0,0-1,0 2,0-3,0 4,0-5,0 6,0-7,0 8,0-9,0 10,0-11,0", "0,1-1,1 2,1-3,1 4,1-5,1 6,1-7,1 8,1-9,1 10,1-11,1", "0,2-1,2 2,2-3,2 4,2-5,2 6,2-7,2 8,2-9,2 10,2-11,2", "0,3-1,3 2,3-3,3 4,3-5,3 6,3-7,3 8,3-9,3 10,3-11,3", "0,4-1,4 2,4-3,4 4,4-5,4 6,4-7,4 8,4-9,4 10,4-11,4", "0,5-1,5 2,5-3,5 4,5-5,5 6,5-7,5 8,5-9,5 10,5-11,5", "0,6-1,6 2,6-3,6 4,6-5,6 6,6-7,6 8,6-9,6 10,6-11,6", "0,7-1,7 2,7-3,7 4,7-5,7 6,7-7,7 8,7-9,7 10,7-11,7", "0,8-1,8 2,8-3,8 4,8-5,8 6,8-7,8 8,8-9,8 10,8-11,8", "0,9-1,9 2,9-3,9 4,9-5,9 6,9-7,9 8,9-9,9 10,9-11,9", "0,10-1,10 2,10-3,10 4,10-5,10 6,10-7,10 8,10-9,10", "0,11-1,11 2,11-3,11 4,11-5,11 6,11-7,11 8,11-9,11", "0,12-1,12 2,12-3,12 4,12-5,12 6,12-7,12 8,12-9,12", "0,13-1,13 2,13-3,13 4,13-5,13 6,13-7,13 8,13-9,13", "0,14-1,14 2,14-3,14 4,14-5,14 6,14-7,14 8,14-9,14", "0,15-1,15 2,15-3,15 4,15-5,15 6,15-7,15 8,15-9,15", "0,16-1,16 2,16-3,16 4,16-5,16 6,16-7,16 8,16-9,16", "0,17-1,17 2,17-3,17 4,17-5,17 6,17-7,17 8,17-9,17", "0,18-1,18 2,18-3,18 4,18-5,18 6,18-7,18 8,18-9,18", "0,19-1,19 2,19-3,19 4,19-5,19 6,19-7,19 8,19-9,19", "0,20-1,20 2,20-3,20 4,20-5,20 6,20-7,20 8,20-9,20", "0,21-1,21 2,21-3,21 4,21-5,21 6,21-7,21 8,21-9,21", "0,22-1,22 2,22-3,22 4,22-5,22 6,22-7,22 8,22-9,22", "0,23-1,23 2,23-3,23 4,23-5,23 6,23-7,23 8,23-9,23", "0,24-1,24 2,24-3,24 4,24-5,24 6,24-7,24 8,24-9,24", "0,25-1,25 2,25-3,25 4,25-5,25 6,25-7,25 8,25-9,25", "0,26-1,26 2,26-3,26 4,26-5,26 6,26-7,26 8,26-9,26", "0,27-1,27 2,27-3,27 4,27-5,27 6,27-7,27 8,27-9,27", "0,28-1,28 2,28-3,28 4,28-5,28 6,28-7,28 8,28-9,28", "0,29-1,29 2,29-3,29 4,29-5,29 6,29-7,29 8,29-9,29", "0,30-1,30 2,30-3,30 4,30-5,30 6,30-7,30 8,30-9,30", "0,31-1,31 2,31-3,31 4,31-5,31 6,31-7,31 8,31-9,31", "0,32-1,32 2,32-3,32 4,32-5,32 6,32-7,32 8,32-9,32", "0,33-1,33 2,33-3,33 4,33-5,33 6,33-7,33 8,33-9,33", "0,34-1,34 2,34-3,34 4,34-5,34 6,34-7,34 8,34-9,34", "0,35-1,35 2,35-3,35 4,35-5,35 6,35-7,35 8,35-9,35", "0,36-1,36 2,36-3,36 4,36-5,36 6,36-7,36 8,36-9,36", "0,37-1,37 2,37-3,37 4,37-5,37 6,37-7,37 8,37-9,37", "0,38-1,38 2,38-3,38 4,38-5,38 6,38-7,38 8,38-9,38", "0,39-1,39 2,39-3,39 4,39-5,39 6,39-7,39 8,39-9,39", "0,40-1,40 2,40-3,40 4,40-5,40 6,40-7,40 8,40-9,40", "0,41-1,41 2,41-3,41 4,41-5,41 6,41-7,41 8,41-9,41", "0,42-1,42 2,42-3,42 4,42-5,42 6,42-7,42 8,42-9,42", "0,43-1,43 2,43-3,43 4,43-5,43 6,43-7,43 8,43-9,43", "0,44-1,44 2,44-3,44 4,44-5,44 6,44-7,44 8,44-9,44", "0,45-1,45 2,45-3,45 4,45-5,45 6,45-7,45 8,45-9,45", "0,46-1,46 2,46-3,46 4,46-5,46 6,46-7,46 8,46-9,46", "0,47-1,47 2,47-3,47 4,47-5,47 6,47-7,47 8,47-9,47", "0,48-1,48 2,48-3,48 4,48-5,48 6,48-7,48 8,48-9,48", "0,49-1,49 2,49-3,49 4,49-5,49 6,49-7,49 8,49-9,49"}

                ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, countDistinct(Arg0)); }

//²            void test_case_2() { string Arr0[] = {"0,2-2,2 10,2-12,0 2,2-4,0 12,0-14,2",
//²                "4,0-4,4 14,2-10,2 4,4-2,2 10,2-12,4",
//²                "4,4-6,2 12,4-14,2 6,2-8,2 12,4-12,6",
//²                "14,8-12,6 6,2-4,0 12,6-10,8"}
//²
//²                ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, countDistinct(Arg0)); }

                // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    TopologicalEquivalence ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE
