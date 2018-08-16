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

#define two(x) (1ULL << (x))
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

const int maxn=155;
const int maxm=4;
const int sz=64;
ull state[2][maxn*maxm];
ull *sa, *sb, *sc;
ull ans[maxn*maxm], mask[maxn*maxm], wall[maxn*maxm];
int n, m, om;
string sk;

int checkit(){ REP(i, n) REP(j, m) if (ans[i*4+j]!=sc[i*4+j]) return 0; return 1; }

int doit(){
    sa=state[0]; sb=state[1];
    memcpy(sb, mask, sizeof(mask));
    sc=sb;
    if (checkit()) return 0;


    int res=0;
    FE(it, sk){
        ++res;
        swap(sa, sb); sc=sb;
        memset(sb, 0, sizeof(ans));

        if (*it=='U'){
            REP(i, n-2) REP(j, m){
                int a=i*4+j+4, b=a-4;
                sb[b]|=sa[a]&mask[b];
                sb[a]|=sa[a]&wall[b];
            }
        }else if (*it=='D'){
            REP(i, n-2) REP(j, m){
                int a=i*4+j+4, b=a+4;
                sb[b]|=sa[a]&mask[b];
                sb[a]|=sa[a]&wall[b];
            }
        }else if (*it=='R'){
            REP(i, n-2) REP(j, m){
                int a=i*4+j+4, b=a+1;
                sb[a]|=(sa[a]<<1)&mask[a];
                sb[a]|=(wall[a]>>1|wall[b]<<63)&sa[a];
                sb[b]|=mask[b]&(sa[a]>>63);
            }
        }else if (*it=='L'){
            REP(i, n-2) REP(j, m){
                int a=i*4+j+4, b=a-1;
                sb[a]|=(sa[a]>>1)&mask[a];
                sb[a]|=(wall[a]<<1|wall[b]>>63)&sa[a];
                sb[b]|=mask[b]&(sa[a]<<63);
            }

        }

        //printf("done %c\n", *it);
        //REP(i, n){ REP(j, om) printf("%Lu", sb[i*4+j/sz]>>j%sz&1); printf("\n"); }
        //printf("\n\n");
        if (checkit()) return res;
    }
    return -1;
}


int main(){
    cin>>n>>m;
    int fuu; cin>>fuu;
    getchar();

    memset(mask, 0, sizeof(mask));
    memset(ans, 0, sizeof(ans));
    memset(wall, 0xff, sizeof(wall));
    REP(i, n){ 
        string s; cin>>s;
        REP(j, m){
            mask[i*4+j/sz]|=two(j%sz)*(s[j]!='#'); 
            wall[i*4+j/sz]^=two(j%sz)*(s[j]!='#'); 
            if (s[j]=='E') ans[i*4+j/sz]=two(j%sz);
        }
    }
    om=m;
    m=(m-1)/sz+1;
    cin>>sk;
    int res=doit();
    printf("%d\n", res);

    return 0;

}


