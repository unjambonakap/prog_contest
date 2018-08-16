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
double toDouble(string s){double a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

vector<string> pt;
set<string> des;
struct node{
    double w;
    string p;
    node *a, *b;
    node(int &k){
        assert(pt[k]=="(");
        w=toDouble(pt[k+1]);
        k+=2;

        if (pt[k]==")") {++k; a=b=0; return;}


        p=pt[k];

        ++k;
        a=new node(k);
        b=new node(k);
        assert(pt[k]==")");
        ++k;
    }
    ~node(){
        if (a) delete a;
        if (b) delete b;

    }
    double query(){
        double ans=w;
        if (!a) return ans;
        if (des.count(p)) return ans*a->query();
        return ans*b->query();
        

    }
};


int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){
        int n;
        cin>>n;
        string s;
        s="";

        getchar();
        REP(i, n){
            string sa;
            getline(cin, sa);
            s+=sa;
        }
        string ns;
        FE(it, s) if (*it=='(' || *it==')') ns+=" "+string(1, *it)+" "; else ns+=*it;
        istringstream ss(ns);

        pt.clear();
        while(ss>>s) pt.pb(s);
        int k=0;
        //REP(i, pt.size()) cout<<"xx"<<pt[i]<<"xx"<<endl;
        node r(k);

        int m;
        cin>>m;
        printf("Case #%d:\n", ti);
        REP(i, m){
            cin>>s;
            cin>>k;
            des.clear();
            REP(j, k){
                cin>>s;
                des.insert(s);
            }
            printf("%lf\n", r.query());

        }

    }



    return 0;
}
