#include<cstdio>
#include<algorithm>
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<set>
#include<map>
#include<numeric>
#include<cmath>
using namespace std;

#define ALL(t) t.begin(),t.end()
#define FOR(i,n) for (int i=0; i<(int)(n); i++)
#define FOREACH(i,t) for (typeof(t.begin()) i=t.begin(); i!=t.end(); i++)
typedef vector<int> vi;
typedef long long int64;

int t[17][1<<17];
int main() {
  int N;cin>>N;
  for(int c=1;c<=N;c++){
    int n,k,x[30],y[30];
    cin>>n>>k;
    FOR(i,n)cin>>x[i]>>y[i];
    FOR(take,1<<n)if(take){
      int minx=1000000,maxx=-1,miny=1000000,maxy=-1;
      FOR(i,n)if(take&1<<i)minx<?=x[i],maxx>?=x[i],miny<?=y[i],maxy>?=y[i];
      t[1][take]=(maxx-minx)>?(maxy-miny);
//      cout<<take<<" "<<t[1][take]<<endl;
    }
    for(int kk=2;kk<=k;kk++)FOR(take,1<<n){
      t[kk][take]=t[kk-1][take];
      for(int take2=take;take2;take2=(take2-1)&take)
        t[kk][take]<?=t[kk-1][take-take2]>?t[1][take2];
    }
    cout<<"Case #"<<c<<": "<<t[k][(1<<n)-1]<<endl;
  }
  return 0;
}
