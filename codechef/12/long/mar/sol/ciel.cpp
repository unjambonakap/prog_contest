#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <ctime>
#include <string.h>

using namespace std;

typedef long long int64;
typedef unsigned long long uint64;
#define two(X) (1<<(X))
#define twoL(X) (((int64)(1))<<(X))
#define contain(S,X) (((S)&two(X))!=0)
#define containL(S,X) (((S)&twoL(X))!=0)
const double pi=acos(-1.0);
const double eps=1e-11;
template<class T> inline void checkmin(T &a,T b){if(b<a) a=b;}
template<class T> inline void checkmax(T &a,T b){if(b>a) a=b;}
template<class T> inline T sqr(T x){return x*x;}
typedef pair<int,int> ipair;
#define SIZE(A) ((int)A.size())
#define LENGTH(A) ((int)A.length())
#define MP(A,B) make_pair(A,B)
#define PB(X) push_back(X)

typedef vector<int> VI;
struct State;

map<int,int> hash_states[9];
vector<State> list_states[9];

struct State
{
    int n;
    int c[9];
    int source;

    void load(int n,VI s)
    {
        this->n=n;
        for (int i=0;i<n;i++) c[i]=s[i];
        source=s[n];
    }
    void refine()
    {
        int d[9];
        for (int i=0;i<n;i++) d[i]=-1;
        int counter=0,new_source=-1;
        for (int i=0;i<n;i++) if (d[i]<0)
        {
            if (source==c[i]) new_source=counter;
            for (int j=0;j<n;j++) if (c[i]==c[j]) d[j]=counter;
            counter++;
        }
        for (int i=0;i<n;i++) c[i]=d[i];
        source=new_source;
    }
    int get_state()
    {
        refine();
        int s=source;
        for (int i=0;i<n;i++) s=s*n+c[i];
        return s;
    }
    void merge(int a,int b)
    {
        if (c[a]==c[b]) return;
        int dest=c[a],src=c[b];
        for (int i=0;i<=n;i++) if (c[i]==src) c[i]=dest;
        if (source==src) source=dest;
    }
    bool expand(int t1,int t2)
    {
        c[n]=-1;
        if (t1>=0) merge(t1,n);
        if (t2>=0) merge(t2,n);
        bool exists=false;
        for (int i=1;i<=n;i++) if (c[i]==source) { exists=true; break; }
        if (!exists) return false;      
        for (int i=0;i<n;i++) c[i]=c[i+1];
        refine();
        return true;
    }
};

int e[9][40000];
bool w[9][10000];
double f[10000],tmpf[10000];
bool ready[9];

void preprocess(int n)
{
    if (ready[n]) return;
    ready[n]=true;
    State state;
    state.n=n;
    for (int i=0;i<n;i++) state.c[i]=i;
    state.source=n-1;
    list_states[n].push_back(state);
    hash_states[n][state.get_state()]=0;
    for (int idx=0;idx<SIZE(list_states[n]);idx++)
    {
        State state=list_states[n][idx];
        w[n][idx]=(state.source==state.c[n-1]);
        for (int set=0;set<4;set++)
        {
            State new_state(state);
            if (!new_state.expand((set&1)?0:-1,(set&2)?(state.n-1):-1))
            {
                e[n][(idx<<2)|set]=-1;
                continue;
            }
            int s=new_state.get_state();
            if (hash_states[n].find(s)!=hash_states[state.n].end()) 
            {
                e[n][(idx<<2)|set]=hash_states[n][s];
                continue;
            }
            int sz=SIZE(hash_states[n]);
            e[n][(idx<<2)|set]=sz;
            list_states[n].push_back(new_state);
            hash_states[n][s]=sz;
        }
    }
}

void expand(int n,double p,double f[],bool to_upper,bool to_left)
{
    int n_states=SIZE(hash_states[n]);
    for (int i=0;i<n_states;i++) tmpf[i]=0;
    int *next=e[n];
    if (!to_left)
    {
        for (int i=0;i<n_states;i++,next+=4) if (f[i]>0)
        {
            if (next[0]>=0) tmpf[next[0]]+=f[i]*p;
            if (next[1]>=0) tmpf[next[1]]+=f[i]*(1-p);
        }
    }
    else if (!to_upper)
    {
        for (int i=0;i<n_states;i++,next+=4) if (f[i]>0)
        {
            if (next[0]>=0) tmpf[next[0]]+=f[i]*p;
            if (next[2]>=0) tmpf[next[2]]+=f[i]*(1-p);
        }
    }
    else
    {
        double p0=p*p;
        double p1=(1-p)*p;
        double p2=(1-p)*(1-p);
        for (int i=0;i<n_states;i++,next+=4) if (f[i]>0)
        {
            if (next[0]>=0) tmpf[next[0]]+=f[i]*p0;
            if (next[1]>=0) tmpf[next[1]]+=f[i]*p1;
            if (next[2]>=0) tmpf[next[2]]+=f[i]*p1;
            if (next[3]>=0) tmpf[next[3]]+=f[i]*p2;
        }
    }
    for (int i=0;i<n_states;i++) f[i]=tmpf[i];
}

double solve(int n,int64 m,double p)
{
    if (n==1 && m==1) return 1;
    if (p>0.99999999) return 0;
    if (n==1 || m==1) return pow(1.0-p,(double)n+(double)m-2.0);
    if (pow(1.0-pow(p,(double)n),(double)m)<1e-6) return 0;
    preprocess(n);
    int n_states=SIZE(hash_states[n]);
    cout<<n_states<<endl;
    memset(f,0,sizeof(f));
    f[0]=1;
    double last_sum=0;
    for (int x=0;x<m;x++) 
    {
        for (int y=0;y<n;y++) if (x>0 || y>0) expand(n,p,f,x>0,y>0);
        double sum=0;
        for (int i=0;i<n_states;i++) if (w[n][i]) sum+=f[i];
        if (x+1==m || x+1>=20 && sum<1e-6) return sum;
        if (x+1>=30) return sum*pow(sum/last_sum,(double)(m-x-1));
        last_sum=sum;
    }
    return 0;
}

int main()
{
#ifdef _MSC_VER
    freopen("input.txt","r",stdin);
#endif
    memset(ready,false,sizeof(ready));
    int n;
    int64 m;
    double p;
    int testcase;
    for (cin>>testcase;testcase>0;testcase--)
    {
        cin>>n>>m>>p;
        double ret=solve(n,m,p);
        printf("%.18lf\n",ret);
    }
    return 0;
}



