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
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)

#define FE(i,t) for (__typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (__typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define two(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()


#define pb push_back
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}



string doit(int a, int b, int c, int d){

    if (abs(b-c)>1) return "-1";
    if (b==c){
        if (a<b || d<c) return "-1";
        if (a==b && d==c) return "-1";
        if (a==b){
            string s="7";
            REP(i,b) s+="47";
            REP(i,d-b-1)s+="7";
            return s;
        }
        string s;
        REP(i,a-b) s+="4";
        REP(i, b-1) s+="74";
        REP(i, d-b+1) s+="7";
        
        s+="4";
        return s;
    }else if (b<c){
        string s;
        if (a<c || d<c) return "-1";
        s="74";
        REP(i, a-c) s+="4";
        REP(i, c-2) s+="74";
        REP(i, d-c+1) s+="7";
        s+="4";
        return s;
    }else{
        string s;
        if (a<b || d<b) return "-1";
        REP(i, a-b) s+="4";
        REP(i, b) s+="47";
        REP(i, d-b) s+="7";
        return s;
    }
}

int main(){

    int a, b, c, d;
    cin>>a>>d>>b>>c;
    
    string res=doit(a,b,c,d);
    cout<<res<<endl;
    

    return 0;
}


