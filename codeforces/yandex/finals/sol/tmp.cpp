#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#define MAXN 100050
using namespace std;
struct{
    int v,id,next;
}edge[MAXN*4];
int e,ft[MAXN],sc[MAXN];
int n,m;
int dep[MAXN],last[MAXN],pre[MAXN],fa[MAXN],dp[MAXN];
bool odd[MAXN];
int q,uu[MAXN],vv[MAXN],lca[MAXN];

int find(int *arr,int u)
{
    if(arr[u]^u)
        arr[u]=find(arr,arr[u]);
    return arr[u];
}
void init()
{
    e=0;
    memset(ft,-1,sizeof(ft));
    memset(sc,-1,sizeof(sc));
}
void add_edge(int *arr,int u,int v,int id)
{
    edge[e].v=v;
    edge[e].id=id;
    edge[e].next=arr[u];
    arr[u]=e++;
}
void dfs1(int u)
{
    last[u]=pre[u]=u;
    for(int i=ft[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(dep[v]==0){
            fa[v]=u;
            dep[v]=dep[u]+1;
            dfs1(v);
            pre[v]=u;
            if(find(last,v)==find(last,u))
                odd[u]|=odd[v];
        }
        else if(dep[v]+1<dep[u]){
            int tmp=find(last,u);
            while(dep[tmp]>dep[v]+1){
                last[tmp]=fa[tmp];
                tmp=find(last,tmp);
            }
            if((dep[u]-dep[v])%2==0)
                odd[u]=true;
        }
    }
    for(int i=sc[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(dep[v]!=0)
            lca[edge[i].id]=find(pre,v);
    }
}
void dfs2(int u)
{
    if(odd[find(last,u)])
        dp[u]++;
    for(int i=ft[u];i!=-1;i=edge[i].next){
        int v=edge[i].v;
        if(dep[v]==dep[u]+1){
            if(find(last,v)==find(last,u))
                odd[v]|=odd[u];
            dp[v]=dp[u];
            dfs2(v);
        }
    }
}
bool judge(int u,int v,int root)
{
    if(find(pre,u)!=find(pre,v))
        return false;
    if((dep[u]-dep[v])%2)
        return true;
    return dp[u]+dp[v]-dp[root]*2>0;
}
void solve()
{
    memset(dep,0,sizeof(dep));
    memset(odd,false,sizeof(odd));
    for(int i=1;i<=n;i++){
        if(!dep[i]){
            fa[i]=0;
            dep[i]=1;
            dfs1(i);
            dp[i]=0;
            dfs2(i);
        }
    }
    for(int i=1;i<=q;i++)
        if(judge(uu[i],vv[i],lca[i]))
            puts("Yes");
        else
            puts("No");
}
int main()
{
    //freopen("e.txt","r",stdin);
    int u,v;
    while(scanf("%d%d",&n,&m)!=EOF){
        init();
        for(int i=1;i<=m;i++){
            scanf("%d%d",&u,&v);
            add_edge(ft,u,v,i);
            add_edge(ft,v,u,i);
        }
        scanf("%d",&q);
        for(int i=1;i<=q;i++){
            scanf("%d%d",uu+i,vv+i);
            add_edge(sc,uu[i],vv[i],i);
            add_edge(sc,vv[i],uu[i],i);
        }
        solve();
        for (int i=0; i<n; ++i) printf("%d => %d\n", i, find(last, i));
    }
    //while(1);
    return 0;
}
