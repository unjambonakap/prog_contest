#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iostream>
#define MAXN 5050
#define mod 1000000007
using namespace std;
struct Tower{
    int x,y;
}tow[MAXN];
int n,d[MAXN],pre[MAXN];
int cnt,len,m;

struct Node{
    int u,v,next;
}node[MAXN*MAXN/2];
int e,first[10050];



int ppow(int num)
{
    long long k=2,ans=1;
    while(num){
        if(num&1)
            ans=ans*k%mod;
        k=k*k%mod;
        num/=2;
    }
    return (int)ans;
}

int find(int u)
{
    if(pre[u]==u)
        return u;
    else{
        int ru=find(pre[u]);
        d[u]^=d[pre[u]];
        return pre[u]=ru;
    }
}

int dist(int u,int v)
{
    return abs(tow[u].x-tow[v].x)+abs(tow[u].y-tow[v].y);
}

void init()
{
    e=0;
    memset(first,-1,sizeof(first));
    memset(d,0,sizeof(d));
    for(int i=1;i<=n;i++)
        pre[i]=i;
}
void add(int u,int v)
{
    node[e].u=u;
    node[e].v=v;
    node[e].next=first[dist(u,v)];
    first[dist(u,v)]=e++;
}

void cal()
{
    int u,v,ru,rv;
    bool flag;
    len=10000;
    m=cnt=n;
    while(len>0){
        flag=true;
        while(first[len]!=-1){
            u=node[first[len]].u;
            v=node[first[len]].v;
            first[len]=node[first[len]].next;
            ru=find(u);
            rv=find(v);
            if(ru==rv){
                if(!(d[u]^d[v])){
                    flag=false;
                    break;
                }
            }
            else{
                pre[ru]=rv;
                d[ru]=d[u]^d[v]^1;
                cnt--;
            }
        }
        if(flag){
            len--;
            m=cnt;
        }
        else
            break;
    }
    cnt=ppow(m);
}
int main()
{
    //freopen("85e.in","r",stdin);
    while(scanf("%d",&n)==1){
        init();
        for(int i=1;i<=n;i++){
            scanf("%d%d",&tow[i].x,&tow[i].y);
            for(int j=1;j<i;j++)
                add(j,i);
        }
        cal();
        printf("%d\n%d\n",len,cnt);
    }
    //while(1);
    return 0;
}
