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
typedef pair<int64,int64> ipair;
#define MP(A,B) make_pair(A,B)

const int maxn=100+5;
const int64 oo=1000000000LL*1000000000LL;

int n;
ipair a[maxn][maxn];
bool g[maxn][maxn];
int p1[maxn],p2[maxn];
ipair dst[maxn],trace_back[maxn];
int prev[maxn];
bool inque[maxn];
int que[maxn*maxn];
int tp1[maxn],tp2[maxn];

bool biparti_matching()
{
    for (int k=0;k<n;k++) if (p1[k]<0)
    {
        memset(inque,false,sizeof(inque));
        int sizeq=0;
        for (int i=0;i<n;i++) dst[i]=MP(-oo,-oo);
        for (int i=0;i<n;i++) if (p2[i]>=0) trace_back[i]=a[p2[i]][i];
        dst[k]=MP(0,0);
        que[sizeq++]=k;
        inque[k]=true;
        prev[k]=-1;
        int64 bw1=-oo,bw2=-oo;
        int bkey=-1,btarget=-1;
        for (int cl=0;cl<sizeq;cl++)
        {
            int key=que[cl];
            inque[key]=false;
            if (prev[key]>=0 && inque[prev[key]]) continue;
            for (int i=0;i<n;i++) if (g[key][i])
            {
                int64 w1=dst[key].first+a[key][i].first;
                int64 w2=dst[key].second+a[key][i].second;
                if (p2[i]>=0)
                {
                    w1-=trace_back[i].first;
                    w2-=trace_back[i].second;
                    int j=p2[i];
                    if (w1>dst[j].first || w1==dst[j].first && w2>dst[j].second)
                    {
                        dst[j].first=w1;
                        dst[j].second=w2;
                        prev[j]=key;
                        if (!inque[j]) { inque[j]=true; que[sizeq++]=j; }
                    }
                }
                else if (w1>bw1 || w1==bw1 && w2>bw2)
                    bw1=w1,bw2=w2,bkey=key,btarget=i;
            }
        }
        if (btarget<0) return false;
        while (bkey>=0)
        {
            swap(btarget,p1[bkey]);
            p2[p1[bkey]]=bkey;
            bkey=prev[bkey];
        }
    }
    return true;
}
int main()
{
#ifdef _MSC_VER
    freopen("input.txt","r",stdin);
#endif
    scanf("%d",&n);
    for (int i=0;i<n;i++) for (int j=0;j<n;j++)
    {
        char s[1024];
        scanf("%s",s);
        int p=0;
        for (;s[p]!=':';p++);
        int64 a=0,b=0;
        for (int k=0;k<p;k++) a=a*10+(s[k]-'0');
        for (int k=p+1;s[k];k++) b=b*10+(s[k]-'0');
        ::a[i][j]=MP(a-b,a+b);
    }
#ifdef _MSC_VER
    if (1)
    {
        n=100;
        for (int i=0;i<n;i++) for (int j=0;j<n;j++) a[i][j]=MP(rand(),rand());
    }
#endif
    int64 r1=-oo,r2=-oo;
    for (int i=0;i<n;i++) for (int j=0;j<n;j++) g[i][j]=true;
    memset(p1,255,sizeof(p1));
    memset(p2,255,sizeof(p2));
    biparti_matching();
    while (1)
    {
        int64 s1=0,s2=0,bw1=-oo,bw2=-oo;
        for (int i=0;i<n;i++)
        {
            int64 w1=a[i][p1[i]].first;
            int64 w2=a[i][p1[i]].second;
            s1+=w1;
            s2+=w2;
            if (w1>bw1 || w1==bw1 && w2<bw2) bw1=w1,bw2=w2;
        }
#ifdef _MSC_VER
        printf("bw1 = %.0lf\n",(double)bw1);
#endif
        if (s1<r1) break;
        if (bw1>0) s1-=bw1,s2-=bw2;
        if (s1>r1 || s1==r1 && s2>r2) r1=s1,r2=s2;
        if (bw1<=0) break;
        memcpy(tp1,p1,sizeof(p1));
        memcpy(tp2,p2,sizeof(p2));
        for (int x=0;x<n;x++) for (int y=0;y<n;y++)
        {
            int64 k1=a[x][y].first,k2=a[x][y].second;
            if (!(k1==bw1 && k2<bw2)) continue;
            for (int i=0;i<n;i++) for (int j=0;j<n;j++)
                if (a[i][j].first>k1 || a[i][j].first==k1 && a[i][j].second<k2)
                    g[i][j]=false;
                else if (i==x || j==y)
                    g[i][j]=(i==x && j==y);
                else
                    g[i][j]=true;
            if (p1[x]>=0) p2[p1[x]]=-1,p1[x]=-1;
            if (p2[y]>=0) p1[p2[y]]=-1,p2[y]=-1;
            p1[x]=y,p2[y]=x;
            if (biparti_matching())
            {
                int64 s1=-k1,s2=-k2;
                for (int i=0;i<n;i++) s1+=a[i][p1[i]].first,s2+=a[i][p1[i]].second;
                if (s1>r1 || s1==r1 && s2>r2) r1=s1,r2=s2;              
            }
            memcpy(p1,tp1,sizeof(p1));
            memcpy(p2,tp2,sizeof(p2));
        }
        for (int i=0;i<n;i++) if (a[i][p1[i]].first==bw1) p2[p1[i]]=-1,p1[i]=-1;
        for (int i=0;i<n;i++) for (int j=0;j<n;j++) g[i][j]=(a[i][j].first<bw1);
        if (!biparti_matching()) break;
    }
    cout<<(r1+r2)/2<<" "<<(r2-r1)/2<<endl;
    return 0;
} 
