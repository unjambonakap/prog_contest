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
#define two(x) (1u << (x))
#define twoll(x) (1Lu << (x))
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
inline int ctz(int n){return (n==0?-1:(n&1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=42;
const unsigned int mask=-1;
int ta[maxn], tb[maxn];
int na, nb;

struct bignum{
    ull b[4];

    bignum(){REP(i, 4) b[i]=0;}
    bignum operator=(const bignum &a){
        REP(i, 4) b[i]=a.b[i];
        return *this;

    }
    bignum square()const{
        bignum res;
        assert(!b[3] && !b[2]);
        REP(i, 2) REP(j, 2){
            res.b[i+j]+=b[i]*b[j];
            res.b[i+j+1]+=res.b[i+j]>>32;
            res.b[i+j]&=mask;
        }
        return res;
    }
    bignum operator+(int a)const{
        bignum res=*this;
        REP(i, 4) res.b[i]+=a, a=res.b[i]>>32, res.b[i]&=mask;
        return res;
    }
    bignum operator+(bignum &a)const{
        bignum res;
        REP(i, 4) res.b[i]+=b[i]+a.b[i], res.b[min(3, i+1)]+=res.b[i]>>32, res.b[i]&=mask;
        return res;
    }

    bool operator<(const bignum &a)const{REPV(i, 4) if (b[i]!=a.b[i]) return b[i]<a.b[i]; return 0;}
    bool operator==(const bignum &a)const{REPV(i, 4) if (b[i]!=a.b[i]) return 0; return 1;}
    bool operator!=(const bignum &a)const{return !(*this==a);}
    bignum sqrt();
    string getstr()const{
        string res;
        REP(i, 128) res+=(b[i/32]&two(i%32)?"1":"0");
        while(res[res.length()-1]=='0') res.erase(res.length()-1);

        return res;
    }
    ull getn()const{ return b[0]+(b[1]<<32); }
};


bignum divtwo(bignum a){

    REP(i, 4){
        if (i && a.b[i]&1) a.b[i-1]|=two(31);
        a.b[i]>>=1;
    }
    return a;
}
bignum bignum::sqrt(){
    bignum res;
    bignum H, T;
    H.b[0]=H.b[1]=UINT_MAX;
    while(T+1<H){
        bignum M=divtwo(T+H);
        if (*this<M.square()) H=M;
        else T=M;
    }
    return T;
}


string solve(string s){
    int n=s.length();
    bignum k;
    REP(i, n) k.b[i/32]|=two(i%32)*(s[i]=='1');
    int m=n/2;

    na=nb=0;
    REP(i, m+2) if (s[i]=='?') ta[na++]=i;
    FOR(i, m, n-1) if (s[i]=='?') tb[nb++]=i;

    string res="";

    if (na+nb==0){
        if (k==k.sqrt().square()) res=s;
    }else if (nb<=na){
        REP(ma, two(nb)){
            bignum a=k;
            REP(i, m) a.b[i/32]|=two(i%32);
            REP(i, nb) if (ma&two(i)) a.b[tb[i]/32]|=two(tb[i]%32);
            bignum b=a.sqrt().square();
            REP(i, m) if (s[i]!='?' && (k.b[i/32]&two(i%32))!=(b.b[i/32]&two(i%32))) goto outa;
            FOR(i, m, n-1) if ((a.b[i/32]&two(i%32))!=(b.b[i/32]&two(i%32))) goto outa;

            res=b.getstr();
            break;
outa:;
        }

    }else{
        m+=2;
        REP(ma, two(na)){
            REP(j, 2){
                bignum x, a=k, xq;
                REP(i, na) if (ma&two(i)) a.b[ta[i]/32]|=two(ta[i]%32);

                bignum c, b;

                x.b[0]=1|(j?2:0);
                xq=x.square();
                FOR(i, 2, m-2){
                    if ((xq.b[(i+1)/32]&two((i+1)%32))!=(a.b[(i+1)/32]&two((i+1)%32))){
                        x.b[i/32]|=two(i%32);
                        xq=x.square();
                    }
                }


                b=xq;
                FOR(i, m, n-1) if (s[i]=='?') a.b[i/32]|=b.b[i/32]&two(i%32);

                if (a==b){
                    res=b.getstr();
                    goto fd;
                }
            }
        }
fd:;
    }

    reverse(ALL(res));
    return res;


}


int main(){
    int tn;
    cin>>tn;
    getchar();
    FOR(ti, 1, tn){
        string s;
        cin>>s;
        reverse(ALL(s));

        string oo="";
        string res;
        while(1){
            if (s.size()<2 || (s[0]!='0')){

                s[0]='1';
                res=solve(s);
                if (res!="") break;
            }
            assert(s[1]!='1');
            s.erase(0, 2);
            oo+="00";

        }

        printf("Case #%d: ", ti);
        cout<<res<<oo<<endl;

    }
        return 0;
}



