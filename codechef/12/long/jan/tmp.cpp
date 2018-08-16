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

#define MOD (1000000007)
#define MAX_INT (2147483647)

const int PSIZE=1<<20;
const int GSIZE=1<<10;
const int OSIZE=16<<20;
const int MSIZE=50000+5;
const int POWERSIZE=35;

bool is_prime[PSIZE];
int n_primes,primes[PSIZE/2],one_factor[PSIZE];
int gcd_buffer[GSIZE][GSIZE];
int n_factors[MSIZE],factors[MSIZE][50];

int length,exponents[40],length2;
int64 base[40],base2[40];

int64 s,t;
int64 p26[POWERSIZE];

int order_buffer[OSIZE];
map<int64,int64> order_buffer_map;

void preprocess()
{
    n_primes=0;
    memset(is_prime,true,sizeof(is_prime));
    is_prime[0]=is_prime[1]=false;
    for (int i=4;i<PSIZE;i+=2) is_prime[i]=false;
    for (int i=0;i<PSIZE;i++) one_factor[i]=i;
    for (int i=2;i<PSIZE;i+=2) one_factor[i]=2;
    for (int i=3;i*i<PSIZE;i+=2) if (is_prime[i]) for (int j=i*i;j<PSIZE;j+=(i+i)) { is_prime[j]=false; one_factor[j]=i; }
    n_primes=0;
    for (int i=0;i<PSIZE;i++) if (is_prime[i]) primes[n_primes++]=i;
    for (int a=0;a<GSIZE;a++) for (int b=0;b<GSIZE;b++)
        if (a==0 || b==0)
            gcd_buffer[a][b]=a+b;
        else if (a>=b)
            gcd_buffer[a][b]=gcd_buffer[b][a%b];
    for (int a=0;a<GSIZE;a++) for (int b=a+1;b<GSIZE;b++) gcd_buffer[a][b]=gcd_buffer[b][a];
    memset(order_buffer,255,sizeof(order_buffer));
    p26[0]=26;
    for (int i=1;i<POWERSIZE;i++) p26[i]=p26[i-1]*p26[i-1]%MOD;
}

int gcd_int(int a,int b)
{
    if (a<b) swap(a,b);
    while (a>=GSIZE && b>0)
    {
        int t=a%b;
        a=b;
        b=t;
    }
    if (b==0) return a;
    return gcd_buffer[a][b];
}

int64 gcd(int64 a,int64 b)
{
    if (a<b) swap(a,b);
    if (b==0) return a;
    if (a<=MAX_INT) return gcd_int((int)a,(int)b);
    return gcd_int((int)b,(int)(a%b));
}

int64 lcm(int64 a,int64 b)
{
    return a/gcd(a,b)*b;
}

void get_all_factors_small(int n)
{
    while (n>1)
    {
        int p=one_factor[n];
        base2[length2++]=p;
        n/=p;
        for (;n%p==0;n/=p);
    }
}

void get_all_factors_int(int n)
{
    if (n<PSIZE) { get_all_factors_small(n); return; }
    for (int i=0;i<n_primes;i++)
    {
        int p=primes[i];
        if (p*p>n) break;
        if (n%p==0)
        {
            base2[length2++]=p;
            for (n/=p;n%p==0;n/=p);
            if (n<PSIZE) { get_all_factors_small(n); return; }
        }
    }
    if (n>1) base2[length2++]=n;    
}

void get_all_factors(int64 n)
{
    length2=0;
    if (n<=MAX_INT) { get_all_factors_int((int)n); return; }
    for (int i=0;i<n_primes;i++)
    {
        int p=primes[i];
        if ((int64)p*p>n) break;
        if (n%p==0)
        {
            base2[length2++]=p;
            for (n/=p;n%p==0;n/=p);
            if (n<=MAX_INT) { get_all_factors_int((int)n); return; }
        }
    }
    if (n>1) base2[length2++]=n;
}

int64 get_order(int64 n)
{
    if (n<OSIZE)
    {
        if (order_buffer[n]>=0) return order_buffer[n];
    }
    else 
    {
        map<int64,int64>::iterator it=order_buffer_map.find(n);
        if (it!=order_buffer_map.end()) return it->second;
    }
    get_all_factors(n-1);
    int64 r=n-1;
    int64 p2[POWERSIZE];
    p2[0]=2;
    if (n<=MAX_INT)
    {
        for (int i=1;i<POWERSIZE;i++) p2[i]=p2[i-1]*p2[i-1]%n;
        for (int k=0;k<length2;k++)
            for (;r%base2[k]==0;r/=base2[k])
            {
                int64 e=r/base2[k],f=1;
                for (int i=0;e;i++,e>>=1) if (e&1) f=f*p2[i]%n;
                if (f!=1) break;            
            }
    }
    else
    {
        for (int i=1;i<POWERSIZE;i++) 
        {
            int64 c=p2[i-1];
            p2[i]=(((c*(c>>16)%n)<<16)+c*(c&65535))%n;
        }
        int64 a[POWERSIZE],b[POWERSIZE];
        for (int i=0;i<POWERSIZE;i++) a[i]=p2[i]>>16,b[i]=p2[i]&65535;
        for (int k=0;k<length2;k++)
            for (;r%base2[k]==0;r/=base2[k])
            {
                int64 e=r/base2[k],f=1;
                for (int i=0;e;i++,e>>=1) if (e&1) f=(((f*a[i]%n)<<16)+f*b[i])%n;
                if (f!=1) break;            
            }
    }
    if (n<OSIZE) 
        order_buffer[n]=(int)r;
    else
        order_buffer_map.insert(MP(n,r));
    return r;
}

int64 DFS(int d,int64 phi,int64 order)
{
    if (d==length) return phi/order;
    int64 r=DFS(d+1,phi,order);
    int64 p=base[d];
    phi*=p-1;
    int64 g=get_order(p);
    for (int i=exponents[d];i>0;i--)
    {
        r+=DFS(d+1,phi,lcm(order,g));
        if (i>0) phi*=p,g*=p;
    }
    return r;
}

int64 solve(int64 n)
{
    length=0;
    int pos=(int)(n-s);
    for (int i=0;i<n_factors[pos];i++)
    {
        int p=factors[pos][i];
        int e=0;
        for (;n%p==0;n/=p) e++;
        base[length]=p;
        exponents[length++]=e;
    }
    if (n>1) base[length]=n,exponents[length++]=1;
    int64 e=DFS(0,1,1)-1,r=1;
    for (int i=0;e;i++,e>>=1) if (e&1) r=r*p26[i]%MOD;
    return r;
}

int main()
{
#ifdef _MSC_VER
    freopen("input.txt","r",stdin);
    double start_time=(double)clock();
#endif
    preprocess();
    int testcase;
    for (cin>>testcase;testcase>0;testcase--)
    {
        cin>>s>>t;
        int64 m=t+1;
        int n=(int)(m-s+1);
        for (int i=0;i<n;i++) n_factors[i]=0;
        for (int i=0;;i++)
        {
            int p=primes[i];
            if ((int64)p*p>m) break;
            int64 e=s/p*p;
            if (e<s) e+=p;
            if (!(e&1)) e+=p;
            for (int d=(int)(e-s);d<n;d+=p+p) factors[d][n_factors[d]++]=p;
        }
        int64 ret=0,last_sum=0;
        for (int64 key=s;key<=t;key++)
            if (key&1)
                if (key==s) ret+=solve(key)*26;
                else ret+=last_sum*26;
            else
            {
                last_sum=solve(key+1);
                ret+=last_sum;
            }
        cout<<ret%MOD<<endl;
    }
#ifdef _MSC_VER
    double end_time=(double)clock();
    printf("RunTime = %.3lf\n",(end_time-start_time)/CLOCKS_PER_SEC);
#endif
    return 0;
}
