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

const int maxn=10;
const int mod=1e4+7;
const int maxv='z'-'a';
const int npos=2e5;
int r, c;
int mp[maxn][maxn];
int mem[npos][maxn];
int A[2][npos];

map<vi, int> remap;
vi mpa[npos];




vi tmp;
int pos;
void gen(int a){

    if (a==maxn){
        mpa[pos]=tmp;
        remap[tmp]=pos++;
        
    }else{
        FOR(i, 0, (!a?maxn:tmp[a-1])){
            tmp[a]=i;
            gen(a+1);
        }
    }
    


}

int solve(){
    int res=0;

    memset(A, 0, sizeof(A));
    A[0][0]=1;
    int *a, *b;
    REP(v, maxv+1){
        a=A[v&1], b=A[v+1&1];
        memset(b, 0, sizeof(int)*npos);
        REP(j, c) REP(i, pos) if (a[i]){
            vi k=mpa[i];
            if (j==c-1){
                b[i]+=b[i]+a[i];
                if (b[i]>mod) b[i]-=mod;
            }
            if (k[j]<(!j?r:k[j-1]) && (mp[k[j]][j]=='.' || mp[k[j]][j]==v)){
                ++k[j];
                int ni;
                if (mem[i][j]==-1) mem[i][j]=ni=remap[k];
                else ni=mem[i][j];

                a[ni]+=a[i];
                if (a[ni]>mod) a[ni]-=mod;
            }

        }


    }



    vi ans(maxn, 0);
    REP(i, c) ans[i]=r;


    return b[remap[ans]];
}


int main(){
    int tn;
    cin>>tn;


    tmp.resize(maxn); pos=0;

    gen(0);
    memset(mem, -1, sizeof(mem));


    FOR(ti, 1, tn){
        cin>>r>>c;
        REP(i, r){
            string s;
            cin>>s;
            REP(j, c) mp[i][j]=(s[j]=='.'?'.':s[j]-'a');
        }


        printf("Case #%d: %d\n", ti, solve());

    }
    return 0;

}




