//MADE BY lordmonsoon A.I.
#include<string>
#include<vector>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<sstream>
#include<iostream>
#include<utility>
#include<bitset>

using namespace std;

#define pi pair<int,int>
#define vi vector<int>
#define vpi vector<pi>
#define fst first
#define snd second
#define pb push_back
#define SIZE(a) (int)(a.size())
#define LENGTH(a) (int)(a.length())
#define REP(i,n) for(int i=0;i<(n);i++)
#define REPD(i,n) for(int i=(n);i>=0;i--)
#define FOR(i,n,m) for(int i=(n);i<=(m);i++)
#define FORD(i,n,m) for(int i=(n);i>=(m);i--)
#define MIN(a,b) ((a)<(b) ? (a) : (b))
#define MAX(a,b) ((a)<(b) ? (b) : (a))
#define ABS(a) ( (a)<0 ? -(a) : (a))
#define STRUMIEN(A,B) istringstream A(B)
#define SORT(A) sort(A.begin(),A.end())


////////////////////////////////////////////////////////////////////////////////

long long f[3001][3001];

long long F(int d,int b)
{
      if(d==0 || b==0) return 0;
//      if(d<=b) return (1LL<<d)-1;
      if(f[d][b]==-1) f[d][b] = F(d-1,b) + 1 + F(d-1,b-1);
      if(f[d][b]>=4294967296LL) f[d][b] = 4294967296LL;
      return f[d][b];
}

int n;
long long FF,DD,BB;

int main()
{
      REP(i,3001) REP(j,3001) f[i][j] = -1;
      FOR(i,1,3000) FOR(j,1,32) F(i,j);
      scanf("%d",&n);
      REP(i,n)
      {
            scanf("%I64d %I64d %I64d",&FF,&DD,&BB);
            printf("Case #%d:",i+1);
//oblicz Fmax
            if(BB==1) printf(" %I64d",DD);
            else if(BB==2)
            {
                  long long xx = (DD*(DD+1))/2;
                  if(xx>=4294967296LL) xx = -1;
                  printf(" %I64d",xx);
            }
            else if(BB>=DD)
            {
                  if(DD>32) printf(" -1");
                  else printf(" %I64d",(1LL<<DD)-1);
            }
            else //BB>=3 i BB<=DD czyli mamy ograniczenie F(BB,DD)>=2^BB 
            {
                  if(BB>32 || DD>=3000) printf(" -1");
                  else 
                  {
                        if(f[DD][BB]==4294967296LL) printf(" -1");
                        else printf(" %I64d",f[DD][BB]);
                  }
            }
//oblicz Dmin
            if(BB==1) printf(" %I64d",FF);
            else if(BB==2)
            {
                  long long s = sqrt(FF) - 1;
                  s>?=1;
                  while(s*(s+1)<FF+FF) s++;
                  printf(" %I64d",s);
            }
            else if(BB>32)
            {
                  long long s = 1,p = 2;
                  while(p-1<FF) {s++;p*=2;}
                  printf(" %I64d",s);
            }
            else
            {
                  long long s = 1;
                  while(f[s][BB]<FF) s++;
                  printf(" %I64d",s);
            }
//oblicz Bmin
            if(DD>=FF) printf(" 1");
            else if(DD*(DD+1)>=2*FF) printf(" 2");
            else if(DD>=3000 || f[DD][3]>=FF) printf(" 3");
            else
            {
                  long long s = 4;
                  while(f[DD][s]<FF) s++;
                  printf(" %I64d",s);
            }            
            printf("\n");
      }
      return 0;
}
