// BEGIN CUT HERE

// END CUT HERE
#line 5 "SymmetricalTree.cpp"

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

struct node;

const int maxn=22;
int cid;
int pos, n;
string s;

char **seen[maxn][maxn];
string **dp[maxn][maxn];
string *dpz[maxn];
char *seenz[maxn];
int same[maxn][maxn];
vector<node*> dlist[maxn+1];
int graph[maxn][maxn];
int match[maxn];
int visited[maxn];


int dfs(int a, int n){
    if (visited[a]) return 0;
    visited[a]=1;
    REP(i, n) if (graph[a][i] && (match[i]==-1 || dfs(match[i], n))){
        match[i]=a;
        return 1;
    }
    return 0;
}




struct node{
    int id;
    node *parent;
    int nc;
    int d;
    string res;
    vector<node*> children;

    void build(node*, int);
    void builda(node*, int);
    string inv();

   
};
node tb[maxn], tba[maxn];
int posa; string sa; int cida;

void node::build(node *p, int _d){
    d=_d;
    parent=p;
    id=cid++;
    dlist[d].pb(this);
    children.clear();
    nc=0; 


    if (s[pos]=='0') return;

    while(pos<s.length() && s[pos]!='0'){

        ++pos;
        children.pb(tb+cid);
        tb[cid].build(this, _d+1);
        ++pos;
    }
    nc=children.size();
}

void node::builda(node *p, int _d){
    d=_d;
    parent=p;
    id=cida++;
    children.clear();
    nc=0;
    if (sa[posa]=='0') return;

    while(posa<sa.length() && sa[posa]!='0'){
        ++posa;
        children.pb(tba+cida);
        tba[cida].builda(this, _d+1);
        ++posa;
    }
    nc=children.size();
}

string node::inv(){
    string tmp;
    REPV(i, nc) tmp+="1"+children[i]->inv()+"0";
    return tmp;
}


string inv(string s){
    cida=0; posa=0; sa=s;
    tba[0].builda(0, 0);
    return tba[0].inv();

}
string rec(int p, int m);
string solve(int p){
    node *a=tb+p;
    if (a->nc==0) return "";;
    if (a->nc==1){
        string s=solve(a->children[0]->id);
        return "1"+s+"0";
    }
    return rec(p, two(a->nc)-1);

}

string solvea(int a, int ma, int b, int mb){
    assert(a!=b);
    assert(tb[a].d==tb[b].d);
    string &s=dp[a][b][ma][mb];
    if (!ma || !mb) return "";
    if (seen[a][b][ma][mb]) return s;
    seen[a][b][ma][mb]=1;

    s="";
    int na, nb;
    na=tb[a].nc; nb=tb[b].nc;
    REP(i, na) if (ma&two(i)) REP(j, nb) if (mb&two(j)){
        int aa, bb;
        aa=tb[a].children[i]->id; bb=tb[b].children[j]->id;
        assert(aa!=bb);
        assert(tb[aa].d==tb[bb].d);

        string ns="1"+solvea(aa, two(tb[aa].nc)-1, bb, two(tb[bb].nc)-1)+"0"+solvea(a, ma^two(i), b, mb^two(j));
        if (s.length()<ns.length() || (s.length()==ns.length() && ns<s)) s=ns;
    }
    return s;


}


string rec(int p, int m){

    if (!m) return "";
    string &s=dpz[p][m];
    if (seenz[p][m]) return s;
    seenz[p][m]=1;
    node *e=tb+p;
    if (count_bit(m)==1){
        REP(j, e->nc) if (m&two(j)){
            s=solve(e->children[j]->id);
            return s="1"+s+"0";
        }
    }

    

    s="";
    REP(j, e->nc) if (m&two(j) && match[e->children[j]->id]==-1){
        int ok=1;
        string ns=rec(p, m^two(j));
        if (s.length()<ns.length() || (s.length()==ns.length() && ns<s)) s=ns;
    }

    REP(j, e->nc) if (m&two(j)) REP(k, j) if (m&two(k)){
        int va, vb;
        va=e->children[j]->id; vb=e->children[k]->id;
        if (match[va]!=-1 && match[va]!=vb) continue;
        assert(tb[va].d==tb[vb].d);
        string ns=min(solvea(va, two(tb[va].nc)-1, vb, two(tb[vb].nc)-1), solvea(vb, two(tb[vb].nc)-1, va, two(tb[va].nc)-1));
        ns="1"+ns+"0"+rec(p, m^two(j)^two(k))+"1"+inv(ns)+"0";
        if (s.length()<ns.length() || (s.length()==ns.length() && ns<s)) s=ns;
    }
    return s;


}


class SymmetricalTree {
    public:
        string makeSymmetrical(string tree) {
            cid=0; pos=0;
            string res;
            n=tree.length()/2+1;
            s=tree;
            REP(i, n+1) dlist[i].clear();
            tb[0].build(0, 0);

            memset(same, 0, sizeof(same));
            REPV(i, n+1){
                REP(j, dlist[i].size()) REP(k, j){
                    node *a=dlist[i][j], *b=dlist[i][k];
                    if (a->children.size()==b->children.size()){
                        memset(graph, 0, sizeof(graph));
                        int na=a->children.size();
                        REP(x, na) REP(y, na) graph[x][y]=same[a->children[x]->id][b->children[y]->id];
                        int ok=1;
                        REP(x, na){
                            memset(visited, 0, sizeof(visited));
                            memset(match, -1, sizeof(match));
                            if (!dfs(x, na)){ok=0; break;}
                        }
                        if (ok) same[a->id][b->id]=same[b->id][a->id]=1;
                    }
                }
            }
            memset(match, -1, sizeof(match));
            REP(i, n){
                REP(j, tb[i].nc) REP(k, j){
                        int ida=tb[i].children[j]->id, idb=tb[i].children[k]->id;
                        if (match[idb]==-1 && same[ida][idb]) match[ida]=idb, match[idb]=ida;
                }

            }
            

            REP(i, n) if (tb[i].nc){
                dpz[i]=new string[two(tb[i].nc)];
                seenz[i]=new char[two(tb[i].nc)];
                memset(seenz[i], 0, sizeof(char)*two(tb[i].nc));
            }

            REPV(i, n+1)
            REP(i, n) REP(j, n) if (i!=j && tb[i].d==tb[j].d){
                int na, nb;
                na=two(tb[i].nc);
                nb=two(tb[j].nc);
                dp[i][j]=new string*[na];
                seen[i][j]=new char*[na];
                REP(k, na){
                    dp[i][j][k]=new string[nb];
                    seen[i][j][k]=new char[nb];
                    memset(seen[i][j][k], 0, sizeof(char)*nb);
                }
            }


            string ans=solve(0);
            REP(i, n) if (tb[i].nc){
                delete[] dpz[i];
                delete[] seenz[i];
            }
            REP(i, n) REP(j, n) if (i!=j && tb[i].d==tb[j].d){
                REP(k, two(tb[i].nc)){
                    delete[] dp[i][j][k];
                    delete[] seen[i][j][k];
                }
                delete[] dp[i][j];
                delete[] seen[i][j];

            }

            return ans;



        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { string Arg0 = "11101001011010100101010011010100"; string Arg1 = "1101011010011010010100"; verify_case(0, Arg1, makeSymmetrical(Arg0)); }
        //void test_case_0() { string Arg0 = "1101100110011000"; string Arg1 = "11011001100100"; verify_case(0, Arg1, makeSymmetrical(Arg0)); }
        //void test_case_0() { string Arg0 = "1010101010101010101010101010101010101010"; string Arg1 = "11011001100100"; verify_case(0, Arg1, makeSymmetrical(Arg0)); }
        void test_case_1() { string Arg0 = "10101100"; string Arg1 = "10110010"; verify_case(1, Arg1, makeSymmetrical(Arg0)); }
        void test_case_2() { string Arg0 = "1011100100"; string Arg1 = "110100"; verify_case(2, Arg1, makeSymmetrical(Arg0)); }
        void test_case_3() { string Arg0 = "101101100110101000"; string Arg1 = "11011010100100"; verify_case(3, Arg1, makeSymmetrical(Arg0)); }
        void test_case_4() { string Arg0 = "11010010110110010101100010110100"; string Arg1 = "10110100110110010110010011010010"; verify_case(4, Arg1, makeSymmetrical(Arg0)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    SymmetricalTree ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE
