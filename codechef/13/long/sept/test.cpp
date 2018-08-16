
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


const int N=1e6+10;

struct suffixarray{
int n,f[N],p[N],q[N],L[N+N];
bool b[N];
int lcp(int i,int j){
    if(i>j)swap(i,j);
    int res=n;
    for(i+=n,j+=n-1;i<=j;i=i+1>>1,j=j-1>>1)
        res=min(res,min(L[i],L[j]));
    return res;
}
void setlcp(int i,int v){ for(i+=n;L[i]>v;i/=2)L[i]=v; }
bool scmp(int x,int y){ return f[x]<f[y]; }
void suff_sort(){
    REP(i,n)b[i]=0,p[i]=i; b[n]=true;
    for(int i,j,x,h=0;h<n;){
        for(i=j=0;j<=n;++j)if(b[j])sort(p+i,p+j,scmp),i=j;
        for(i=0,j=1;j<n;++i,++j)b[j]|=f[p[i]]!=f[p[j]];
        for(h=h?h*2:1,i=x=0;i<n;f[j]=x+=b[i++])if((j=p[i]-h)<0)j+=n;
    }
}
void suff_sort_withlcp(){
    REP(i,n)b[i]=0,p[i]=i,L[i+1]=L[i+n]=n; b[n]=true;
    for(int i,j,x,y,h=0;h<n;){
        for(i=j=0;j<=n;++j)if(b[j])sort(p+i,p+j,scmp),i=j;
        REP(i,n)q[p[i]]=i;
        for(i=0,j=1;j<n;++i,++j)
            if(!b[j] && f[p[i]]!=f[p[j]])
                b[j]=true,x=p[i]+h,y=p[j]+h,
                    setlcp(i,h?h+lcp(q[x<n?x:x-n],q[y<n?y:y-n]):0);
        for(h=h?h*2:1,i=x=0;i<n;f[j]=x+=b[i++])if((j=p[i]-h)<0)j+=n;
    }
}

};


int main(){
    int n=1e6;
    REP(i,n) f[i]=i%15;
    suff_sort_withlcp();

    return 0;

}
