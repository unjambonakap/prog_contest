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

const int maxn=111;
const int mod=1e9+7;

char buf[maxn];
int dp[2][100];
int n;

void add(int &a, int b){
    a+=b;
    if (a>mod) a-=mod;
}

void sub(int &a, int b){
    a-=b;
    if (a<0) a+=mod;
}

int checkit(){
    string s=buf;
    set<string> seen;
    seen.insert(s);
    queue<string> q;
    q.push(s);
    while(!q.empty()){
        string s=q.front(); q.pop();
        cout<<s<<endl;
        REP(i,s.length()-1){
            if (s[i]>'a' && s[i+1]<'z'){
                --s[i]; ++s[i+1];
                if (!seen.count(s)) seen.insert(s), q.push(s);
                ++s[i]; --s[i+1];
            }if (s[i]<'z' && s[i+1]>'a'){
                ++s[i]; --s[i+1];
                if (!seen.count(s)) seen.insert(s), q.push(s);
                --s[i]; ++s[i+1];
            }
        }
    }
    return (seen.size()-1)%mod;

}

int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        scanf(" %s", buf);
        n=strlen(buf);
        REP(i,n) buf[i]-='a';
        memset(dp,0,sizeof(dp));
        dp[0][buf[0]]=1;
        int p=0, np=1;
        REP(i,n-1){
            memset(dp[np],0,sizeof(dp[np]));
            out(dp[p],3);
            int s=0;
            REP(j,26) add(s,dp[p][j]);
            int ns=s;
            REP(j,buf[i+1]+1) add(dp[np][buf[i+1]-j], ns), sub(ns,dp[p][25-j]);
            ns=s;
            sub(ns,dp[p][0]);
            for (int j=1; buf[i+1]+j<26; ++j) add(dp[np][buf[i+1]+j], ns), sub(ns,dp[p][j]);
            p=np; np^=1;
        }
            out(dp[p],5);
        int res=mod-1;
        REP(i,26) res=(res+dp[p][i])%mod;
        REP(i,n) buf[i]+='a';
        int ans=checkit();
        printf("%d %d\n", res, ans);
        printf("%d\n",res);


    }
    return 0;
}




