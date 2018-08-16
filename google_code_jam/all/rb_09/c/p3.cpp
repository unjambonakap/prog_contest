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


#define PI asin(1)*2.
#define EPS 10e-8


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i <= (b)) && (c); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)
#define FORVC(i, a, b, c) for(i = (a); (i >= (b)) && (c); i--)
#define FE(i,t) for (typeof(t.begin())i=t.begin();i!=t.end();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define SZ(a) ((a).size())
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ll long long

using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef queue<int> qi;

#define MAX_W 20
#define MAX_Q 50
#define MAX_QU 1000
#define MAX_N 1000
#define MID 500

#define P '+'
#define M '-'

string tb[MAX_W][MAX_W][MAX_N];
char map[MAX_W][MAX_W];
string nb[MAX_N];
int ask[MAX_Q];
int found[MAX_Q];
int remain;

int w, n;
int vx[]={-1, 0, 1, 0};
int vy[]={0, 1, 0, -1};

void solve(){
	int i, j, k;
	int x, y, nx, ny, v, nv;
	string ns, *ss;

	queue<pii> q;
	pii p;

	REP(k, MAX_N)
		nb[k]=string();

	REP(i, w)
		REP(j, w){
			REP(k, MAX_N)
				tb[i][j][k]=string();
					
			if (map[i][j] != P && map[i][j] != M)
				q.push(pii(i+j*w, map[i][j]-'0')), nb[MID+map[i][j]-'0']=tb[i][j][MID+map[i][j]-'0']=map[i][j];
			
		}
			


	memset(found, 0, sizeof(found));

	REP(i, n)
		if (!found[i] && nb[ask[i]+MID].length() != 0)
			found[i]=1, remain--;
		
	

	int count=0, step=1;

	while(!q.empty()){
		p=q.front(); q.pop();

		x=p.first%w, y=p.first/w;
		v=p.second;
		if (tb[x][y][MID+v].length() != step){

			REP(i, n)
				if (!found[i] && nb[ask[i]+MID].length() != 0)
					found[i]=1, remain--;
				

			
			if (remain == 0)return;
			step++;
		}
		

		REP(i, 4){
			nx=x+vx[i], ny=y+vy[i];
			if (nx < 0 || ny < 0 || nx >= w || ny >= w) continue;

			if (map[x][y] == P)
				nv=v+map[nx][ny]-'0';
			else if (map[x][y] == M)
				nv=v-map[nx][ny]+'0';
			else
				nv=v;
			if (MID+nv < 0 || MID+nv >= MAX_N)continue;

			ns=tb[x][y][MID+v]+map[nx][ny];
			ss=&tb[nx][ny][MID+nv];

			//cout << ns << endl;
		//	cout << map[nx][ny] <<  "new v: " << nv << endl;

			if (ss->length() == 0 || (ss->length() == ns.length() && ss->compare(ns) > 0)){
				*ss=ns;
				q.push(pii(nx+ny*w, nv));

				if (map[nx][ny] != P && map[nx][ny] != M)
					if (nb[MID+nv].length() == 0 || (ns.length() == nb[MID+nv].length() && ns.compare(nb[MID+nv]) < 0))
						nb[MID+nv]=ns;
					
			}
		}


	}


}



int main(){
	int i, j, k, T, d;
	cin >> T;
	REP(i, T){
		cin >> w >> n;
		scanf("\n");
		REP(j, w){
			REP(k, w)
				scanf("%c", &map[k][j]);
			scanf("\n");
		}

		REP(j, n)
			cin >> ask[j];


		remain=n;
		solve();

		printf("Case #%d:\n", i+1);
		REP(j, n)
			cout << nb[MID+ask[j]] << endl;
		

	}


	return EXIT_SUCCESS;
}

