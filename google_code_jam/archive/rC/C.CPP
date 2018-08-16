#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

#define MOD 1000000007
#define maxn 1024000
#define llong long long

struct node{
     llong v,id;       
};

int n,m;
llong X,Y,Z;

llong A[maxn];
node B[maxn];
llong tree[maxn];

bool cmp(node a,node b){
     return a.v<b.v;
}

void init(){
     for(int i=0;i<m;i++)scanf("%d",&A[i]);
     for(int i=0;i<n;i++){
         B[i].id=i;
         B[i].v=A[i%m];
         A[i%m]=(X*A[i%m]+Y*(i+1))%Z;  
     }
     sort(B,B+n,cmp);
     int k=2;
     A[B[0].id]=2;
     for(int i=1;i<n;i++){
         if(B[i].v>B[i-1].v)k++;
         A[B[i].id]=k; 
     }
}

int lowbit(int x){
    return x&-x;
}
void insert(int p,llong v){
     while(p<(n+3)){
		 printf("insert %d %d %d\n",p,v,tree[p]);
        tree[p]=(tree[p]+v)%MOD;
        p=p+lowbit(p);
     }
}

llong sum(int p){
      llong s=0;
      while(p>0){
         s=(s+tree[p])%MOD;
		 printf("sum %d %d (value: %d, s => %d)\n", p,p-lowbit(p),tree[p],s);
         p=p-lowbit(p);          
      }
      return s;
}
void work(){
	printf("real start\n");
     memset(tree,0,sizeof(tree));
     insert(1,1);
	printf( "start\n");
     llong res=0,t;
     for(int i=0;i<n;i++){
         t=sum(A[i]-1)%MOD;
		 printf("for  %d ,%d => %d\n", i,A[i],t);
		 for (int j=  0;j < n+3;j++){
			 printf("disp tree : %d => %d\n", j,tree[j]);

		 }
         res=(res+t)%MOD;
         insert(A[i],t);
     }     
     printf("%lld\n",res);
	 exit(0);
}
int main(){
        int cases;
    int k=1;
    scanf("%d",&cases);
    int x,y,z;
    while(cases-->0){
        scanf("%d%d%d%d%d",&n,&m,&x,&y,&z);
        X=x;Y=y;Z=z;
        init();
        printf("Case #%d: ",k++);
        work();             
    }   
    return 0;
}
