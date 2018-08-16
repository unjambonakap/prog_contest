#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <cassert>


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define SZ(a) ((a).size())
#define two(x) (1 << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)
#define ll long long
using namespace std;
typedef pair<int,int> pii;

#define MAX_N 1000
#define MAX_K 12
#define MOD 10007

int n;
int tb[MAX_N];
int ck[MAX_K];
int np[MAX_N];

int set_ck(int k, int v){
	if (ck[k] != -1 && ck[k] != v)
		return -1;
	ck[k]=v;
	return 0;
}

void solve(){
	int count, i, j, k, l, v;
	int mk, last, temp;

	mk=ceil(log(n)/log(2));
	last=-1;
	
	REP(i, two(mk)+1){
		memset(ck, -1, sizeof(ck));
		v=i+n, temp=0;
		//printf("v => %d\n", v);

		REP(j, n){
			//printf("%d\n", i+j);
			bool ok=true;
			REP(l, mk+1)
				if (i+j == two(l)){
					if (set_ck(l, tb[j])){ok=false; break;}
				}
			if (!ok)break;
			
			REP(k, j){
					
				REP(l, mk){
					if (i+j == ((i+k)|two(l))){
					//	printf(" %d  %d=> %d, %d >>>>< %d\n", i+j, i+k, tb[j]-tb[k], ck[l], l);
						if (set_ck(l, (tb[j]-tb[k]+MOD)%MOD)){ok=false; break;}
					}
				}
				if (!ok)break;
			}
			if (!ok)break;
		}

		if (j == n){

		//	printf("act for %d: %d %d => %d\n", i, v, temp, ck[2]);
			//REP(k, n){
			//	REP(l, mk+1){
			//		if ((i+n) & two(l)){
			//			if (ck[l] == -1)
			//				break;
			//			temp+=ck[l];
			//		}
			//	}
			//	if (l != mk+1)continue;

			//	if (ta != tb[k])break;
			//}
			//if (k != n)
		//		continue;

			REP(l, mk+1){
				if (v & two(l)){
				//	printf("%d\n", ck[l]);
					if (ck[l] == -1)
						break;
					temp+=ck[l];
				}
			}

			if (l != mk+1){
				last=-1;
				//printf("theere for %d\n", i);
				break;
			}


			temp%=MOD;
			if (last == -1)
				last=temp;
			else if (last != temp){last=-1; break;}
		}


	}

	if (last == -1)
		printf("UNKNOWN\n");
	else
		printf("%d\n", last);


}

int main(){
	int i, j, T;
	scanf("%d", &T);

	REP(i, T){
		scanf("%d", &n);
		REP(j, n)
			scanf("%d", tb+j);

		//if (i!=1)continue;
		printf("Case #%d: ", i+1);
		solve();



	}


	return EXIT_SUCCESS;
}


