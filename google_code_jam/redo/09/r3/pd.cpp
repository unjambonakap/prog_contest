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
ll toll(string s){ll a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int mod=1e9+7;
const int i2=mod/2+1;
const int maxn=110;
ll pt[maxn];
ll mem[maxn][maxn];
ll memb[maxn];

set<ll> pal;
int tb[10];

void rec(int ia, int ib){
    if (ia==ib){
        ll va, vb;
        va=vb=0;
        REP(i, ib) va=va*10+tb[i];
        vb=va;
        vb=(vb*10+tb[ib-1])%mod;
        REPV(i, ib-1) va=va*10+tb[i];
        REPV(i, ib-1) vb=vb*10+tb[i];
        pal.insert(va);
        pal.insert(vb);
        return;
    }
    REP(i, 10) if (ia || i){
        tb[ia]=i;
        rec(ia+1, ib);
    }
}

ll solvez(ll a, ll b){
        set<ll>::iterator ita=pal.lower_bound(a);
        ll cnta, cntb;
        ll p, np;
        int step=0;
        p=a;
        cnta=0;
        while(1){
            np=min(*ita, b+1);
            ++ita;
            if (!step){
            //    printf("%Ld %Ld\n", p, np);
                cnta=(cnta+np-p)%mod;
            }
            if (np==b+1) break;
            p=np;
            step^=1;
        }

        cntb=(b-a+1-cnta)%mod;

        printf("<< finding %Ld %Ld\n", cnta, cntb);
        return (cnta*(cnta+1)+cntb*(cntb-1))%mod*i2%mod;

}




ll eval(string a){
    ll res=0;
    REP(i, a.length()) res=(res+(a[i]-'0')*pt[a.length()-1-i])%mod;
    return res;
}


ll proca(int a, int b){
    ll &r=mem[a][b];
    if (r!=-1) return r;
    r=0;

    int mid=(b-1)/2;
    if (a==mid){
        r=pt[mid];
        if (b%2==0) r+=pt[b/2];
    }else r=(a==mid-1?5:10)*proca(a+1, b);
    //printf("<< %d %d => %Ld\n", a, b, r%mod);
    return r=r%mod;
}

ll procb(int a){
    ll &r=memb[a];
    if (r!=-1) return r;
    r=0;
    if (a==3){
        return r=50;
    }

    r=procb(a-1);
    //printf("la %Ld, %d (start at %Ld\n", proca(0, a-1), a, r);
    r+=9*proca(0, a-1);

    //printf("<< ans: %Ld\n", r);



    return r=r%mod;

}

string prev_pal(string a){
    string b=a;
    int na=(a.length()+1)/2;
    REP(i, na) b[a.length()-i-1]=a[i];
    int ok=1;
    REP(i, a.length()) if (b[i]!=a[i]){ok=b[i]<a[i]; break;}
    if (ok) return b;

    REPV(i, na) if (--b[i]>='0') break; else b[i]='9';
    if (b[0]=='0') b.resize(a.length()-1), b[0]='9';;
    na=(b.length()+1)/2;
    REP(i, na) b[b.length()-i-1]=b[i];
    return b;
}


ll solve(string a){
    string b=prev_pal(a);
    //cout<<a<<endl;
    //cout<<b<<endl;
    ll cnta=0;
    ll eb=eval(b);
    if ((b[b.length()/2]-'0')%2==(b.length()==1?1:0)) cnta=(mod+eval(a)-eb+1)%mod;
    //printf("ixxxx %Ld\n", cnta);

    if (b.length()==2){
        cnta+=6+(eb<22?0:((eb-22)/11+1)/2*11);
    }else if (b.length()==1){
        cnta+=(b[0]-'0')/2;
    }else{
        cnta+=procb(b.length());
     //   printf("start at %Ld\n", cnta);
        int na=(b.length()+1)/2;
        REP(i, na){
            int mul=b[i]-'0';
            if (i==0) --mul;
            else if (i==na-1) mul=(mul+1)/2;
            //printf("%d => %d, %Ld\n", i, mul, proca(i, b.length()));
            //printf("%Ld x %d\n", proca(i, b.length()), mul);
            cnta+=proca(i, b.length())*mul%mod;
        }
        //printf("<< %Ld\n", cnta);
    }

    
    //printf("RES:::::: %Ld\n", cnta);


    return cnta;

}
int dec(string &a){
    reverse(ALL(a));
    if (a=="0") return 1;
    FE(it, a) if (--(*it)<'0') (*it)+=10; else break;
    if (a.length()>1 && a[a.length()-1]=='0') a.resize(a.length()-1);

    reverse(ALL(a));
    return 0;
    

}
ll solvea(string A, string B){
    string oa=A;
    dec(A);
    int off=dec(A);

    //cout<<A<<endl;
    ll cnta=(mod+solve(B)-solve(A))%mod;
    ll cntb=(eval(B)-eval(A)-cnta+2*mod+off)%mod;
    //printf("<< dist: %Ld\n", eval(B)-eval(A));
    string ap=prev_pal(oa);
    //printf("xaxa %Ld\n", cnta);
    //cout<<ap<<endl;
    //printf("<<< %Ld %Ld\n", cnta, cntb);
    //if (ap[ap.length()/2]%2==(ap.length()==1?0:1)) swap(cnta, cntb);
    //if (ap==oa) swap(cnta, cntb);
    return ((cnta*(cnta-1)+cntb*(cntb-1))%mod)*i2%mod;
}

int main(){
    int tn;

    memset(mem, -1, sizeof(mem));
    memset(memb, -1, sizeof(memb));
    pt[0]=1;
    REP(i, maxn-1) pt[i+1]=pt[i]*10%mod;
    //REP(i, 6) rec(0, i+1);
    //pal.insert(1e13+1);
    //printf("<< %Ld %Ld\n", solvez(1, 1001241028LL), solvea("1", "1001241028"));
    //return 0;

    cin>>tn;
    getchar();
    FOR(ti, 1, tn){
        string A, B;
        cin>>A>>B;
     //   if (ti!=114)continue;

     //   cout<<A<<endl<<B<<endl;

        printf("Case #%d: %Ld\n", ti, solvea(A, B));
    }
    return 0;

}




