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

int main(){
    int tn; cin>>tn;
    REP(ti, tn){
        int n;
        int xe, ye, de;
        string s;

        cin>>xe>>ye>>s;
        cin>>n;
        if (s=="R") de=0;
        if (s=="L") de=1;
        if (s=="U") de=2;
        if (s=="D") de=3;

        int res=INT_MAX;
        REP(i,n){
            int xa, ya, da;
            string s;
            cin>>xa>>ya>>s;
            if (s=="R") da=0;
            if (s=="L") da=1;
            if (s=="U") da=2;
            if (s=="D") da=3;

            if (de==da);
            else if (de==(da^1)){
                if (de<=1){
                    if (ya==ye){
                        if (de==1){
                            if (xe>xa) checkmin(res, xe-xa);
                        }else{
                            if (xe<xa) checkmin(res, xa-xe);
                        }
                    }
                }else{
                    if (xa==xe){
                        if (de==3){
                            if (ye>ya) checkmin(res, ye-ya);
                        }else{
                            if (ye<ya) checkmin(res, ya-ye);
                        }
                    }
                }
            }else{
                int ta, tb;
                if (de==0) ta=xa-xe;
                else if (de==1) ta=xe-xa;
                else if (de==2) ta=ya-ye;
                else if (de==3) ta=ye-ya;

                if (da==0) tb=xe-xa;
                else if (da==1) tb=xa-xe;
                else if (da==2) tb=ye-ya;
                else if (da==3) tb=ya-ye;
                if (ta==tb && ta>0) checkmin(res, 2*ta);
            }

        }
        if (res==INT_MAX) printf("SAFE\n");
        else printf("%.1lf\n", res/2.);

    }

    return 0;
}




