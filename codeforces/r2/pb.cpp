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


const int maxn=1000;
const int inf=1e5;
int A[maxn][maxn], B[maxn][maxn];
int F[maxn][maxn], G[maxn][maxn];



int main(){
    int n;
    cin>>n;
    int fx=-1, fy=-1;
    REP(i, n) REP(j, n){
        int a; cin>>a;
        int x, y;
        x=y=0;
        if (a==0) x=y=1, fx=i, fy=j;
        else{
            while(!(a&1)) ++x, a>>=1;
            while(a%5==0) ++y, a/=5;
        }
        A[i][j]=x; B[i][j]=y;

        F[i][j]=G[i][j]=inf;
    }
    F[0][0]=A[0][0];
    G[0][0]=B[0][0];
    REP(i, n) REP(j, n){
        if (j<n-1){
            int a=F[i][j]+A[i][j+1];
            int b=G[i][j]+B[i][j+1];
            if (F[i][j+1]>a) F[i][j+1]=a;
            if (G[i][j+1]>b) G[i][j+1]=b;
        }
        if (i<n-1){
            int a=F[i][j]+A[i+1][j];
            int b=G[i][j]+B[i+1][j];
            if (F[i+1][j]>a) F[i+1][j]=a;
            if (G[i+1][j]>b) G[i+1][j]=b;
        }
    }

    pii ans;
    int px=n-1, py=n-1;
    if (min(F[px][py], G[px][py])>1 && fx!=-1){
        printf("1\n");

        REP(i, fx) printf("D");
        REP(i, fy) printf("R");
        REP(i, n-fx-1) printf("D");
        REP(i, n-fy-1) printf("R");
        printf("\n");


    }else if (F[px][py]<G[px][py]){
            string s;
            printf("%d\n", F[px][py]);
            while(px|py){
                if (!py) --px, s+="D";
                else if (!px) --py, s+="R";
                else{
                    if (F[px-1][py]+A[px][py]==F[px][py]) --px, s+="D";
                    else --py, s+="R";

                }
            }
            reverse(ALL(s));
            cout<<s<<endl;
    }else{
        printf("%d\n", G[px][py]);
        string s;
        while(px|py){
            if (!py) --px, s+="D";
            else if (!px) --py, s+="R";
            else{
                if (G[px-1][py]+B[px][py]==G[px][py]) --px, s+="D";
                else --py, s+="R";
            }
        }
        reverse(ALL(s));
        cout<<s<<endl;
    }


    return 0;
}
