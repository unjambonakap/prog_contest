
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

template<class T> inline void checkmin(T &a,T b){if(b<a) a=b;}
template<class T> inline void checkmax(T &a,T b){if(b>a) a=b;}

inline bool leq(int a1,int a2,int b1,int b2)
{
    return (a1<b1 || a1==b1 && a2<=b2);
}
inline bool leq(int a1,int a2,int a3,int b1,int b2,int b3)
{
    return (a1<b1 || a1==b1 && leq(a2,a3,b2,b3)); 
}
void RadixPass(int *a,int *b,int *r,int n,int K) 
{
    int *cnt=new int[K+1];
    memset(cnt,0,(K+1)*sizeof(int));
    for (int i=0;i<n;i++) cnt[r[a[i]]]++;
    for (int i=1;i<=K;i++) cnt[i]+=cnt[i-1];
    for (int i=n-1;i>=0;i--) b[--cnt[r[a[i]]]]=a[i];
    delete[] cnt;
}
void GetSuffixArray(int *s,int *sa,int n,int K)
{
    if (n<=8)
    {
        bool c[8][8];
        for (int i=n-1;i>=0;i--) for (int j=i+1;j<n;j++)
        {
            if (s[i]==s[j]) c[i][j]=(j+1<n && c[i+1][j+1]);
            else c[i][j]=(s[i]<s[j]);
            c[j][i]=!c[i][j];
        }
        for (int i=0;i<n;i++) sa[i]=i;
        for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) if (c[sa[j]][sa[i]]) swap(sa[i],sa[j]);
        return;
    }
    int n0=(n+2)/3,n1=(n+1)/3,n2=n/3,n02=n0+n2;
    int *s12=new int[n02+3];
    s12[n02]=s12[n02+1]=s12[n02+2]=0; 
    int *SA12=new int[n02+3];
    SA12[n02]=SA12[n02+1]=SA12[n02+2]=0;
    int *s0=new int[n0];
    int *SA0=new int[n0];
    for (int i=0,j=0;i<n+(n0-n1);i++) if (i%3!=0) s12[j++]=i;
    RadixPass(s12,SA12,s+2,n02,K);
    RadixPass(SA12,s12,s+1,n02,K);  
    RadixPass(s12,SA12,s,n02,K);
    int name=0,c0=-1,c1=-1,c2=-1;
    for (int i=0;i<n02;i++)
    {
        if (s[SA12[i]]!=c0 || s[SA12[i]+1]!=c1 || s[SA12[i]+2]!=c2)
            name++,c0=s[SA12[i]],c1=s[SA12[i]+1],c2=s[SA12[i]+2];
        if (SA12[i]%3==1)
            s12[SA12[i]/3]=name;
        else 
            s12[SA12[i]/3+n0]=name;
    }
    if (name<n02)
    {
        GetSuffixArray(s12,SA12,n02,name);
        for (int i=0;i<n02;i++) s12[SA12[i]]=i+1;
    }
    else
    {
        for (int i=0;i<n02;i++) SA12[s12[i]-1]=i; 
    }
    for (int i=0,j=0;i<n02;i++) if (SA12[i]<n0) s0[j++]=3*SA12[i];
    RadixPass(s0,SA0,s,n0,K);
    for (int p=0,t=n0-n1,k=0;k<n;k++)
    {
        int i=(SA12[t]<n0?SA12[t]*3+1:(SA12[t]-n0)*3+2);
        int j=SA0[p];
        if (SA12[t]<n0?leq(s[i],s12[SA12[t]+n0],s[j],s12[j/3]):
                leq(s[i],s[i+1],s12[SA12[t]-n0+1],s[j],s[j+1],s12[j/3+n0]))
        {
            sa[k]=i;
            if ((++t)==n02) for (k++;p<n0;p++,k++) sa[k]=SA0[p];
        }
        else
        { 
            sa[k]=j;
            if ((++p)==n0) for (k++;t<n02;t++,k++) sa[k]=(SA12[t]<n0?SA12[t]*3+1:(SA12[t]-n0)*3+2); 
        }
    }
    delete[] s12;
    delete[] SA12;
    delete[] s0;
    delete[] SA0;
}
void SuffixArray(int n,char *s,int *sa,int *rank)
{
    int *a=new int[n+3];
    for (int i=0;i<n;i++) a[i]=(int)((unsigned char)s[i]);
    a[n]=a[n+1]=a[n+2]=0;
    GetSuffixArray(a,sa,n,256);
    for (int i=0;i<n;i++) rank[sa[i]]=i;
}
void SuffixArray(int n,int *s,int *sa,int *rank)
{
    int maxs=0;
    for (int i=0;i<n;i++) if (s[i]>maxs) maxs=s[i];
    maxs++;
    int *a=new int[n+3];
    a[n]=a[n+1]=a[n+2]=0;
    if (maxs<(1<<16))
    {
        for (int i=0;i<n;i++) a[i]=s[i];
        GetSuffixArray(a,sa,n,maxs);
    }
    else
    {
        int *C=new int[1<<16];
        int *t=new int[n];
        memset(C,0,(1<<16)*sizeof(int));
        for (int i=0;i<n;i++) C[s[i]&65535]++;
        for (int i=1;i<(1<<16);i++) C[i]+=C[i-1];
        for (int i=n-1;i>=0;i--) a[--C[s[i]&65535]]=i;
        memset(C,0,(1<<16)*sizeof(int));
        for (int i=0;i<n;i++) C[s[i]>>16]++;
        for (int i=1;i<(1<<16);i++) C[i]+=C[i-1];
        for (int i=n-1;i>=0;i--) t[--C[s[a[i]]>>16]]=a[i];
        for (int d=0,i=0;i<n;i++) a[t[i]]=(i>0 && s[t[i]]!=s[t[i-1]])?(++d):d;
        GetSuffixArray(a,sa,n,n);
        delete[] C;
        delete[] t;
    }
    for (int i=0;i<n;i++) rank[sa[i]]=i;
}
void PrepareD(int *s,int *sa,int *rank,int *d,int n)
{
    for (int k=0,i=0;i<n;i++)
        if (rank[i]==n-1)
            d[n-1]=k=0;
        else
        {
            if (k>0) k--;
            int t=sa[rank[i]+1];
            for (;i+k<n && i+k<n && s[i+k]==s[t+k];k++);
            d[rank[i]]=k;
        }
}
void PrepareD(char *s,int *sa,int *rank,int *d,int n)
{
    for (int k=0,i=0;i<n;i++)
        if (rank[i]==n-1)
            d[n-1]=k=0;
        else
        {
            if (k>0) k--;
            int t=sa[rank[i]+1];
            for (;i+k<n && i+k<n && s[i+k]==s[t+k];k++);
            d[rank[i]]=k;
        }
}
int _log[65536];
inline int MyLog(int n)
{
    return (n<65536)?_log[n]:(16+_log[n>>16]);
}
void PrepareRMQ(int n,int *a,int *&buffer)
{
    for (int k=0,i=1;i<65536;i++) _log[i]=(i>=(1<<(k+1)))?(++k):k;
    int m=((n-1)>>5)+1;
    buffer=new int[n+n+m*(1+MyLog(m))];
    int *E=buffer+n+n;
    for (int i=0;i<m;i++) E[i]=a[i<<5];
    for (int i=0;i<n;i++) checkmin(E[i>>5],a[i]);
    int *toLeft=buffer;
    int *toRight=buffer+n;
    for (int i=0;i<n;i++) toLeft[i]=(i&31)?min(a[i],toLeft[i-1]):a[i];
    for (int i=n-1;i>=0;i--) toRight[i]=(i+1<n && ((i+1)&31))?min(a[i],toRight[i+1]):a[i];
    for (int p=1;p<=MyLog(m);p++)
    {
        int *current=buffer+n+n+p*m;
        int *prev=current-m;
        int length=(1<<(p-1));
        for (int i=0;i<m;i++)
        {
            current[i]=prev[i];
            if (i+length<m) checkmin(current[i],prev[i+length]);
        }
    }
}
int RMQ(int n,int *a,int *buffer,int s,int t)
{
    if (s>t) swap(s,t);
    if ((s>>5)==(t>>5))
    {
        int R=a[s];
        for (int i=s;i<=t;i++) checkmin(R,a[i]);
        return R;
    }
    int E=a[s];
    for (int i=s;i<=t;i++) checkmin(E,a[i]);
    int R=a[s];
    int m=((n-1)>>5)+1;
    if ((s&31)!=0)
    {
        int *toRight=buffer+n;
        checkmin(R,toRight[s]);
        s=((s>>5)+1)<<5;
    }
    if ((t&31)!=31)
    {
        int *toLeft=buffer;
        checkmin(R,toLeft[t]);
        t=((t>>5)<<5)-1;
    }
    if (s<=t)
    {
        s>>=5;
        t>>=5;
        int L=t-s+1;
        int d=MyLog(L);
        int *f=buffer+n+n+d*m;
        checkmin(R,f[s]);
        checkmin(R,f[t-(1<<d)+1]);
    }
    return R;
}

int LCP(int a,int b,int rank[],int d[],int buffer[],int n)
{
    int pa=rank[a];
    int pb=rank[b];
    if (pa==pb) return -1;
    if (pa>pb) swap(pa,pb);
    return RMQ(n,d,buffer,pa,pb-1);
}

const int maxn=1<<20;
const int MOD=1000000007;

int n;
char a[maxn];
int m;
char q[maxn];
int sa[maxn],rank[maxn],d[maxn];
int *rmq_buffer;
int next[maxn],prev[maxn];
int sum[maxn];

void ADDTO(int &a,int b) { a+=b; if (a>=MOD) a-=MOD; }
void SUBTO(int &a,int b) { a-=b; if (a<0) a+=MOD; }

int LCP(int a,int b)
{
    return LCP(a,b,rank,d,rmq_buffer,n);
}

int main()
{
    scanf("%d",&m);
    n=0;
    for (int i=0;i<m;i++)
    {
        char s[16];
        scanf("%s",s);
        q[i]=s[0];
        if (q[i]=='+')
        {
            scanf("%s",s);
            a[n++]=(int)s[0];
        }
    }
    SuffixArray(n,a,sa,rank);
    PrepareD(a,sa,rank,d,n);
    PrepareRMQ(n,d,rmq_buffer);
    next[n]=n+1;
    prev[n+1]=n;
    sa[n]=rank[n]=n;
    sa[n+1]=rank[n+1]=n+1;
    int ret=0;
    memset(sum,0,(n+2)*sizeof(int));
    int overlapped=0;
    for (int s=0,g=0,t=-1,step=0;step<m;step++)
    {
        if (q[step]=='+')
            t++;
        else
        {
            for (int k=rank[s]+1;k<=n;k=(k|(k-1))+1) sum[k]--;
            if (prev[s]<n) SUBTO(overlapped,LCP(prev[s],s));
            if (next[s]<n) SUBTO(overlapped,LCP(next[s],s));
            if (prev[s]<n && next[s]<n) ADDTO(overlapped,LCP(prev[s],next[s]));
            next[prev[s]]=next[s];
            prev[next[s]]=prev[s];
            s++;
        }
        for (;g<=t;g++)
        {
            int c=0,p=n;
            for (int k=rank[g];k>0;k&=(k-1)) c+=sum[k];
            if (c>0) for (int e=0,L=(1<<20);L>0;L>>=1)  if (e+L<=n && c>sum[e+L]) c-=sum[e+=L]; else p=e+L-1;
            prev[g]=sa[p];
            next[g]=next[prev[g]];
            int L1=0,L2=0;
            if (prev[g]<n && (L1=LCP(prev[g],g))>t-g) break;
            if (next[g]<n && (L2=LCP(next[g],g))>t-g) break;
            ADDTO(overlapped,L1+L2);
            if (prev[g]<n && next[g]<n) SUBTO(overlapped,LCP(prev[g],next[g]));
            prev[next[g]]=next[prev[g]]=g;
            for (int k=rank[g]+1;k<=n;k=(k|(k-1))+1) sum[k]++;
        }
        int current=(int)((long long)(t*2-g-s+3)*(g-s)/2%MOD);
        SUBTO(current,overlapped);
        ADDTO(ret,current);
    }
    printf("%d\n",ret);
    return 0;
}
