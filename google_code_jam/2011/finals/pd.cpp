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

#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
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
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=300;
int n;
int order[maxn];




int main(){
    int tn;
    cin>>tn;
    FOR(ti, 1, tn){

        cin>>n;
        REP(i, n) cin>>order[i];
        set<int> v, p;
        REP(i, n) v.insert(i+1), p.insert(i+1);
        printf("Case #%d:", ti);
        int res[n+1];
        REP(i, n-1){
            int va=*(--v.end()), vb=*(----v.end());
            if (i==n-2) res[order[i]]=va;
            else{
                if (*(--p.end())==order[i]){
                    int fd=0;
                    REP(j, order[i]) if (!p.count(j+1) && res[j+1]>vb && res[j+1]<va){fd=1; break;}
                    if (fd) res[order[i]]=va;
                    else res[order[i]]=vb;
                } else{
                    set<int>::iterator it=v.begin(), itx=p.find(order[i]);
                    while(itx!=p.begin()) --itx, ++it;
                    ++it;

                    res[order[i]]=*it;


                }
                p.erase(order[i]);
                v.erase(res[order[i]]);

            }

        }
        res[order[n-1]]=1;
        REP(i, n) printf(" %d", res[i+1]);
        printf("\n");
    }

    return 0;


}



