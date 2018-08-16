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

const int maxn=27;

char sa[3][maxn];
int n;
int cnt[3];
int type[3][2];
int st;
char s1[maxn], s2[maxn];
char *sx,*sy;

int dp2[3][3][maxn][maxn][maxn];//t1,t2,pos1,pos2,len

const char *str[]={"Pre","In","Post"};


struct data{
    int f,l;
    data(int f, int l):f(f),l(l){}
};

struct node{
    char c;
    int l,r;
    node(){l=r=-1;}
    node(char c, int l, int r):c(c),l(l),r(r){}
}lst[int(1e6)];

int have;

int build(char *s, int a, int f){
    int cnt=0;
    if (a==-1) return cnt;
    char c=lst[a].c+'A';

    if (f==0) *(s+cnt++)=c;
    cnt+=build(s+cnt,lst[a].l,f);

    if (f==1) *(s+cnt++)=c;
    cnt+=build(s+cnt,lst[a].r,f);


    if (f==2) *(s+cnt++)=c;
    *(s+cnt)=0;

    return cnt;
}

int findc(char *s, int l, int n){ int x=0; REP(i,n) x|=1<<s[l+i]; return x; }

int findx(int f, int l, int n, int cl){if (f==0) return l; return f==1?l+cl:l+n-1;}
int getll(int f, int l, int n, int cl){ if (f==0) return l+1; return l; }
int getrl(int f, int l, int n, int cl){ if (f==2) return l+cl; return l+cl+1; }

int cmp2(int a, int b){

    build(s1,a,0);
    build(s2,b,0);
    int x=strcmp(s1,s2);
    if (x!=0) return x<0;
    build(s1,a,1);
    build(s2,b,1);
    return strcmp(s1,s2)<0;

}
int solve2(int f1, int f2, int l1, int l2, int n){
    if (n==0) return -1;
    int &r=dp2[f1][f2][l1][l2][n];
    if (findc(sx,l1,n)!=findc(sy,l2,n)) return 0;


    if (r!=-1){
        if (r==0) return 0;
        return r;
    }
    r=0;


    int mid;
    REP(i,n){
        int mid=sx[findx(f1,l1,n,i)];
        if (mid==sy[findx(f2,l2,n,i)]){
            int r1=solve2(type[f1][0],type[f2][0],getll(f1,l1,n,i),getll(f2,l2,n,i),i);
            if (!r1) continue;
            int r2=solve2(type[f1][1],type[f2][1],getrl(f1,l1,n,i),getrl(f2,l2,n,i),n-1-i);
            if (!r2) continue;

            lst[0]=node(mid,r1,r2);

            int up=0;
            if (!r) r=have++, up=1;
            else up=cmp2(0,r);
            if (up) memcpy(lst+r,lst,sizeof(node));
        }
    }

    return r;
}




int go1(vector<data> tb, int n){
    if (n==0) return -1;

    REP(i,3) REP(j,i) if (tb[i].f==tb[j].f) REP(k,n) if (sa[i][k+tb[i].l]!=sa[j][k+tb[j].l]) return 0;   

    int uu=findc(sa[0],tb[0].l,n);
    REP(j,2) if (uu!=findc(sa[j+1],tb[j+1].l,n)) return 0;



    int hasx[3]={-1,-1,-1};

    REP(i,3) hasx[tb[i].f]=i;
    int cnt=0;
    REP(i,3) if (hasx[i]!=-1) ++cnt;

    if (cnt<=2){
        int wh=tb[0].f==tb[2].f;
        sx=sa[wh];
        sy=sa[2];
        return solve2(tb[wh].f,tb[2].f,tb[wh].l,tb[2].l,n);
    }else{
        char mid=sa[hasx[0]][tb[hasx[0]].l];
        int cl=0;
        int wh=hasx[1];

        REP(i,n){
            if (sa[wh][tb[wh].l+i]==mid) break;
            ++cl;
        }

        vector<data> tl=tb, tr=tb;
        REP(i,3){
            tl[i].f=type[tb[i].f][0];
            tr[i].f=type[tb[i].f][1];

            tl[i].l=getll(tb[i].f,tb[i].l,n,cl);
            tr[i].l=getrl(tb[i].f,tb[i].l,n,cl);
        }
        int r1=go1(tl,cl);
        int r2=go1(tr,n-1-cl);
        if (!r1 || !r2) return 0;

        int pos=have++;
        lst[pos]=node(mid,r1,r2);
        return pos;
    }

}


void go(){
    have=0;
    vector<data> tb;
    REP(i,3) tb.pb(data(i,0));

    have=1;
    memset(dp2,-1,sizeof(dp2));
    int r=go1(tb,n);

    if (!r) return;

    //if (st++) puts("\n");
    REP(i,3) REP(j,2) printf("%s%c",str[type[i][j]]," \n"[i==2&&j==1]);
    REP(i,3) build(s1,r,i), printf("%s\n",s1);

}


void gen(int a){
    if (a==6) go();
    else{
        REP(j,3) if (cnt[j]<2){
            ++cnt[j];
            type[a/2][a%2]=j;
            gen(a+1);
            --cnt[j];
        }
    }
}


int main(){
    int tn=0;
    while(1){

        if (scanf(" %s",sa[0])<=0) break;
        scanf(" %s",sa[1]);
        scanf( "%s",sa[2]);
        n=strlen(sa[0]);
        REP(i,3) REP(j,n) sa[i][j]-='A';

        memset(cnt,0,sizeof(cnt));
        st=0;
        gen(0);
    }
    return 0;

}

