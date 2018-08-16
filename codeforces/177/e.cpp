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
typedef unsigned int uint;
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

const int maxn=111111;
const int mod=1e9+7;

char sa[maxn], sb[maxn];
int pw[maxn];
int pw2[maxn];
int H[maxn], L[maxn];
int sl[maxn], sh[maxn];
int n;

int dp[maxn];
int sum[maxn];

int get(int a, int v){
    if (a<0) return 0;
    ll res=dp[a];
    res+=1ll*(pw2[a+1]-1)*v%mod*v;
    res+=2ll*sum[a]*v;
    res-=1ll*v*(sl[a+1]+sh[a+1]);
    res%=mod;
    if (res<0) res+=mod;
    return res;
}

void dumb(int a, int b){

    int prev=a;
    int res=0;
    FOR(i,a+1,b+1){
        int ok=1;
        int x=i;
        while(x) if (x%10!=4 && x%10!=7){ok=0; break;} else x/=10;
        if (!ok) continue;
        res+=prev*i;
        prev=i;
        printf("ON %d >>> %d\n",i,res);
    }
    printf("FUUU %d\n",res);


}


int main(){
    scanf(" %s",sa);
    scanf(" %s",sb);

    n=strlen(sa);
    REP(i,n) sa[i]-='0', sb[i]-='0';

    int m=0;
    pw[0]=1;
    REP(i,n) pw[i+1]=10ll*pw[i]%mod;
    pw2[0]=1;
    REP(i,n) pw2[i+1]=2ll*pw2[i]%mod;

    REP(i,n/2) swap(sa[i],sa[n-i-1]);
    REP(i,n/2) swap(sb[i],sb[n-i-1]);

    for (m=n-1; sa[m]==sb[m]; --m);

    L[0]=4; H[0]=7;
    sl[0]=sh[0]=0;

    REP(i,n) L[i+1]=10ll*L[i]%mod;
    REP(i,n) H[i+1]=10ll*H[i]%mod;

    REP(i,n) sl[i+1]=(sl[i]+L[i])%mod;
    REP(i,n) sh[i+1]=(sh[i]+H[i])%mod;




    dp[0]=28;
    sum[0]=11;
    REP(i,m){
        ll tmp=get(i,L[i+1])+get(i,H[i+1]);
        tmp+=1ll*(L[i+1]+sh[i+1])*(H[i+1]+sl[i+1]);
        dp[i+1]=tmp%mod;
        sum[i+1]=(2*sum[i]+1ll*(H[i+1]+L[i+1])*pw2[i+1])%mod;
    }

    //int a=0, b=0;
    //REP(i,n) a+=pw[i]*sa[i], b+=pw[i]*sb[i];
    //dumb(a,b);

    int res=0, cur=0;
    REP(i,n) cur=(1ll*pw[i]*sa[i]+cur)%mod;
    
    REP(i,m){
        cur=(cur-1ll*pw[i]*sa[i]%mod+mod)%mod;
        if (sa[i]==7) continue;
        ll tmp=get(i-1,cur+H[i]);
        tmp+=(1ll*cur+sh[i]+L[i])*(1ll*cur+sl[i]+H[i]);
        res=(res+tmp)%mod;
        sa[i]=7;
    }
    int last=(sh[m]+cur)%mod;


    cur=(cur-L[m]+mod)%mod;
    cur=(cur+H[m])%mod;

    for (--m; m>=0; --m){
        if (sb[m]==7){
            ll tmp=get(m-1,cur+L[m]);
            tmp+=(1ll*cur+L[m]+sl[m])*last;
            res=(res+tmp)%mod;
            
            last=(1ll*cur+sh[m]+L[m])%mod;
        }
        cur=(cur+1ll*pw[m]*sb[m])%mod;
    }
    res=(res+1ll*last*cur)%mod;

    printf("%d\n",res);

    return 0;
}

