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

#define MOD 9901
vi s[400];
int n,zero,paths,cycles;
bool b[400];
void dfs(int x){
  b[x]=1;
  FOR(i,s[x].size())if(!b[s[x][i]])dfs(s[x][i]);
}
void calc(){
  zero=paths=cycles=0;
  memset(b,0,sizeof(b));
  for(int i=1;i<=n;i++)if(!b[i]&&s[i].size()==1){
    paths++;
    int cur=i;
    while(1){
      b[cur]=1;
      int j=0;while(j<s[cur].size()&&b[s[cur][j]])j++;
      if(j==s[cur].size())break;
      cur=s[cur][j];
    }
  }
  for(int i=1;i<=n;i++)if(!s[i].size())zero++,b[i]=1;
  for(int i=1;i<=n;i++)if(!b[i]){
    cycles++;
    dfs(i);
  }
}
int main() {
  int C;cin>>C;
  int fact[3000]={1},fact2[3000]={1,1,1};
  FOR(i,2999)fact[i+1]=fact[i]*(i+1)%MOD;
  for(int i=3;i<3000;i++)fact2[i]=fact2[i-1]*i%MOD;
  for(int c=1;c<=C;c++){
    int k,t[20][2],ans=0;
    cin>>n>>k;
    FOR(z,k)cin>>t[z][0]>>t[z][1];
    FOR(take,1<<k){
      int mult=1;FOR(i,k)if(take&1<<i)mult*=-1;
      for(int i=1;i<=n;i++)s[i].clear();
      FOR(i,k)if(take&1<<i)FOR(j,2)s[t[i][j]].push_back(t[i][j^1]);
      for(int i=1;i<=n;i++)if(s[i].size()>2)goto hell;
      calc();
      mult=(mult%MOD+MOD)%MOD;
      if(cycles>1)goto hell;
      if(cycles){
        if(zero+paths)goto hell;
        ans=(ans+mult)%MOD;
        goto hell;
      }
      if(!paths){//cout<<fact2[n-1]<<" "<<mult<<endl;
        ans=(ans+fact2[n-1]*mult)%MOD;
        goto hell;
      }
      FOR(z,paths-1)mult=mult*2%MOD;
      ans=(ans+mult*fact[zero+paths-1])%MOD;
hell:;      
    }
    cout<<"Case #"<<c<<": "<<ans<<endl;
  }
  return 0;
}
