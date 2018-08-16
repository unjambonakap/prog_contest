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


const int maxn=(3e8+20)/2;
const int st=5, N=1e6;
int isnp[maxn/32];

int res[333]={39175,35241,33867,33219,32691,32139,31928,31499,31341,31080,30899,30913,30576,30405,30301,30139,30087,30002,29854,29814,29600,29720,29405,29423,29435,29274,29336,29150,29172,29095,29090,28875,28874,28901,28653,28729,28749,28687,28755,28594,28584,28417,28392,28489,28355,28315,28386,28313,28256,28258,28169,28080,28070,28052,28033,28035,27971,28017,27892,27899,27977,27712,27847,27868,27831,27821,27783,27794,27716,27699,27611,27660,27723,27534,27588,27680,27510,27459,27447,27443,27499,27577,27454,27448,27327,27347,27304,27472,27326,27266,27219,27227,27345,27189,27308,27228,27199,27167,27086,27143,27101,27097,27178,27021,27108,27013,26974,27086,27143,27133,26917,27074,26976,26793,26904,26928,26827,26892,26881,26925,26796,26823,26879,26935,26830,26788,26788,26857,26912,26782,26705,26816,26715,26708,26784,26590,26671,26606,26624,26836,26539,26668,26606,26718,26638,26632,26642,26559,26499,26564,26416,26555,26338,26618,26476,26456,26642,26415,26339,26483,26470,26400,26467,26593,26352,26354,26345,26398,26378,26469,26347,26372,26389,26434,26306,26359,26331,26390,26348,26469,26168,26342,26128,26258,26390,26251,26268,26241,26223,26395,25941,26110,26293,26226,26247,26184,26098,26035,26138,26190,26168,26268,26107,26223,26138,26000,26145,26052,25999,26168,26038,26225,26169,26056,26095,26173,26095,25947,25966,25999,25994,26045,26114,25971,26158,25913,26090,25813,25930,25903,25956,26020,26001,25825,25940,25949,26045,25925,26008,25808,26013,25938,25712,25883,25989,25900,25795,25759,25943,25783,25953,25667,25756,25915,25964,25824,25857,25833,25905,25729,25951,25770,25971,25768,25858,25928,25627,25768,25862,25623,25773,25705,25657,25806,25819,25724,25712,25735,25587,25726,25606,25780,25597,25743,25704,25615,25592,25771,25735,25587,25755,25680,25519,25692,25737,25552,25616,25639,25521,25530};

void gen(){
    for (int i=1; i<9000; ++i) if (!(isnp[i>>5]>>(i&31)&1)){
        int p=2*i+1;
        for (int j=p*p/2; j<maxn; j+=p) isnp[j>>5]|=1<<(j&31);
    }
    vi tb;
    for (int i=st; i+N<=maxn*2; i+=N){
        int s=0;
        REP(j,N) if ((i+j)%4==1 && !(isnp[(i+j)>>6]>>(i+j>>1&31)&1)) ++s;
        tb.pb(s);
    }
    FE(it,tb) printf("%d,",*it);
}



const int maxm=2e4;
int isp[maxm], pl[maxm];
int np;
int checkit(int a){
    if (a==1) return 0;
    if (a==2) return 1;
    if (a%4!=1) return 0;
    int x=sqrt(a)+1;
    for (int i=0; pl[i]<=x; ++i) if (a%pl[i]==0) return 0;
    return 1;
}




int main(){
    //gen();
    np=0;
    memset(isp,1,sizeof(isp));
    FOR(i,2,maxm) if (isp[i]){
        for (int j=i*i; j<maxm; j+=i) isp[j]=0;
        pl[np++]=i;
    }

    int l, r; cin>>l>>r;
    int ans=0;
    for (; l%N!=st && l<=r; ++l) ans+=checkit(l);
    for (; r%N!=st-1 && l<=r; --r) ans+=checkit(r);
    FOR(i,l/N,r/N) ans+=res[i];

    cout<<ans<<endl;
    return 0;

}


