// BEGIN CUT HERE

// END CUT HERE
#line 5 "FamilyTree.cpp"

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


const int maxn=110;
int seen[maxn], seenp[maxn];
int n;
int color[maxn];
int graph[maxn][maxn];



struct state{
    int g, id;
    set<state*> children;
    set<state*> parent;
    void init(){
        g=-1;
        children.clear();
        parent.clear();


    }
    void addp(state *a){
        parent.insert(a); 
        FE(it, parent) (*it)->addc(this);
    }
    void addc(state *s){ children.insert(s); }
    void setg(int _g){
        if (g==-1) g=_g;
        if (g!=_g) g=-2;
        else g=_g;
    }
    void setC(){
        if (seen[id]) return;
        seen[id]=1;
        FE(it, children) (*it)->setC();
        
    }

    int checkP(){
        if (seen[id]) return 0;
        if (seenp[id]) return 1;
        seenp[id]=1;
        
        FE(it, parent) if (!(*it)->checkP())return 0;
        
        return 1;

    }
};

map<string, int> mp_name;
state tb[maxn];


int twocol(){
    queue<int> q;
    REP(i, n) if (color[i]!=-1) q.push(i);
    while(!q.empty()){
        int p=q.front(); q.pop();
        assert(color[p]!=-1);
        REP(j, n) if (graph[p][j]){
            if (color[j]==-1) color[j]=1^color[p], q.push(j);
            else if (color[j]==color[p]) return 0;
        }
    }
    while(1){
        int fd=-1;
        REP(i, n) if (color[i]==-1){fd=i; break;}
        if (fd==-1) break;
        q.push(fd);
        color[fd]=0;
        while(!q.empty()){
            int p=q.front(); q.pop();
            assert(color[p]!=-1);
            REP(j, n) if (graph[p][j]){
                if (color[j]==-1) color[j]=1^color[p], q.push(j);
                else if (color[j]==color[p]) return 0;
            }
        }
    }
    return 1;

}

int checkit(){
    memset(graph, 0, sizeof(graph));
    memset(color, -1, sizeof(color));

    REP(i, n){
        state *s=tb+i;
        color[s->id]=s->g;
        if (s->g==-2) return 0;

        if (s->parent.size()>2) return 0;
        if (s->parent.size()==2){
            state *va, *vb;
            va=*s->parent.begin();
            vb=*(++s->parent.begin());
            graph[va->id][vb->id]=graph[vb->id][va->id]=1;
            if (va->g!=-1 && vb->g!=-1 && va->g==vb->g) return 0;
        }
        memset(seen, 0, sizeof(seen));
        memset(seenp, 0, sizeof(seenp));

        s->setC();
        seen[s->id]=0;
        if (!s->checkP()) return 0;
    }

    return twocol();

}

class FamilyTree {
    public:
        int firstBad(vector <string> data) {
            mp_name.clear();
            n=0;

            REP(i, maxn) tb[i].init();
            REP(i, data.size()){
                istringstream ss(data[i]);
                string a, b;
                ss>>a>>b;
                int id;
                if (mp_name.find(a)==mp_name.end()) mp_name.insert(MP(a, id=n++));
                else id=mp_name[a];

                state *s=tb+id;
                s->id=id;
                if (b[0]>='a') s->setg(b[0]=='m');
                else{
                    state *p;
                    int pid;
                    if (mp_name.find(b)==mp_name.end()) mp_name[b]=pid=n++;
                    else pid=mp_name[b];
                    if (pid==id) return i;
                    p=tb+pid;
                    p->id=pid;
                    s->addp(p);
                }
                if (!checkit()) return i;
            }
            return -1;

        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        //void test_case_0() { string Arr0[] = {"BOB JOHN","BOB JOHN","BOB MARY","BOB m","AL f"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(0, Arg1, firstBad(Arg0)); }
        void test_case_0() { string Arr0[] = {"BO LESLIE", "SUE CASEY", "SUE ROBIN", "DEE ROBIN", "DEE LESLIE", "BO CASEY"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(0, Arg1, firstBad(Arg0)); }
        void test_case_1() { string Arr0[] = {"BOB JOHN","BOB MARY","MARY JOHN","JOHN f","MARY f","AL f"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(1, Arg1, firstBad(Arg0)); }
        void test_case_2() { string Arr0[] = {"BOB JOHN", "CARLA BOB", "JOHN CARLA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, firstBad(Arg0)); }
        void test_case_3() { string Arr0[] = {"BOB RICK", "AL RICK", "AL PAULA", "PAULA LINUS", "LINUS BOB","BOB PAULA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(3, Arg1, firstBad(Arg0)); }
        void test_case_4() { string Arr0[] = {"JOHN f", "JOHN m"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(4, Arg1, firstBad(Arg0)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    FamilyTree ___test; 
    ___test.run_test(-1);
} 
// END CUT HERE
