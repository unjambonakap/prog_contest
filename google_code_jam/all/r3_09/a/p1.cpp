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
#define MDIST(x,y,a,b) (abs((a)-(x))+abs((b)-(y)))
#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ST first
#define ND second
#define ll long long

using namespace std;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef queue<int> qi;

inline int count_bit(int n){return (n == 0)?0:(n&1)+count_bit(n>>1);}


#define MAX_R 12
#define MAX_B 5
#define MAX_P 100000
#define BOX 'o'
#define EMPTY '.'
#define DEST 'x'
#define SPEC 'w'
#define WALL '#'

int w, h;
int state[MAX_B][twoll(MAX_B*MAX_B)];
ll restate[MAX_B][MAX_P];
char map[MAX_R][MAX_R];
char tmap[MAX_R][MAX_R];
int remap[MAX_R][MAX_R];
int dp[MAX_R][MAX_R][MAX_P];
int found;

int vx[]={0, -1, 0, 1}, rvx[]={0, 1, 0, -1};
int vy[]={1, 0, -1, 0}, rvy[]={-1, 0, 1, 0};

class State{
	public:
		State(){}
		State(pii _p, int _s, int _c){p=_p, s=_s, c=_c;}
		pii p; int s, c;
};


vi box, dest;

pii ep;
int es;

void set_state(int s){
	ll i;
	int c;
	
	c=0;
	REP(i, twoll(s*s))
		if (count_bit(i) == s)state[s-1][i]=c, restate[s-1][c]=i, c++;
	
}

pii get_corner(const vi &a){
	pii p;
	int i;

	
	p.ST=p.ND=MAX_R;
	REP(i, SZ(a))
		p.ST=MIN(p.ST, a[i]%w), p.ND=MIN(p.ND, a[i]/w);
	return p;


}

int get_state(const vi &a){
	int i;
	pii minp;
	ll s;

	minp=get_corner(a);

	s=0;
//	printf("1 %d %d\n", minp.ST, minp.ND);
	REP(i, SZ(a)){
//		printf("%d %d\n", a[i]%w-minp.ST, a[i]/w-minp.ND);
		s|=twoll(a[i]%w-minp.ST+(a[i]/w-minp.ND)*SZ(a));
	}
	
	
//	printf("%Ld\n", s);
	assert(state[SZ(a)-1][s] > -1);
	return state[SZ(a)-1][s];
}
int is_stable(vector<pii> &v){
	int i, j, nx, ny;
	int visited[MAX_B], nv;
	queue<int> q;
	pii p;

	memset(visited, 0, sizeof(visited));
	nv=SZ(v)-1;
	visited[0]=1;
	q.push(0);

	while(!q.empty()){

		p=v[q.front()]; q.pop();
		REP(i, 4){
			nx=p.ST+vx[i], ny=p.ND+vy[i];
			REP(j, SZ(v)){
				if (v[j].ST == nx && v[j].ND == ny)
					if (!visited[j])
						visited[j]=1, nv--, q.push(j);
				
			}


		}
	}


	return (nv==0);


}

int solve(){
	int *u;
	int i, j, k, nx, ny, px, py;
	int iss;

	ll rs;
	pii p;
   	int s, c;

	queue<State> q;
	State st;
	


	
	pii sp;
	int ss;



	ep=get_corner(dest), es=get_state(dest);
	sp=get_corner(box), ss=get_state(box);



	memset(dp, -1, sizeof(dp));
	q.push(State(sp, ss, 0));





	memcpy(tmap, map, sizeof(tmap));

	while(!q.empty()){
		assert(s <= MAX_P);

		st=q.front(); q.pop();
		p=st.p, s=st.s, c=st.c;

		u=&dp[p.ST][p.ND][s];
		if (*u != -1)continue;
		*u=c;

		if (ep == p && s == es)return c;

		rs=restate[SZ(box)-1][s];
		vector<pii> b;

		REP(i, SZ(box)*SZ(box))
			if (rs&twoll(i))
				b.pb(pii(i%SZ(box)+p.ST, i/SZ(box)+p.ND));

		iss=is_stable(b);



		//REP(i, SZ(b))
		//	printf("box at %d %d\n", b[i].ST, b[i].ND);
		//printf("with %Ld\n", rs);
		REP(k, SZ(b))
			tmap[b[k].ST][b[k].ND]=WALL;
		REP(i, SZ(b)){
			vector<pii> temp=b;
			REP(j, 4){



				pii corner=pii(MAX_R, MAX_R);

				nx=b[i].ST+vx[j], ny=b[i].ND+vy[j];
				px=b[i].ST+rvx[j], py=b[i].ND+rvy[j];

				REP(k, SZ(b))
					if (k != i)
						corner.ST=MIN(corner.ST, b[k].ST), corner.ND=MIN(corner.ND, b[k].ND);

				corner.ST=MIN(corner.ST, nx), corner.ND=MIN(corner.ND, ny);

				REP(k, SZ(b))
					if (k != i && (b[k].ST-corner.ST >= SZ(b) || b[k].ND-corner.ND >= SZ(b)))break;

				if (k != SZ(b))continue;


				if (nx-corner.ST >= SZ(b) || ny-corner.ND >= SZ(b))continue;



				if (nx < 0 || nx >= w  || ny < 0 || ny >= h)continue;
				if (px < 0 || px >= w  || py < 0 || py >= h)continue;

				if (tmap[nx][ny] == EMPTY && tmap[px][py] == EMPTY){
					temp[i]=pii(nx, ny);
					if (!is_stable(temp) && !iss)
						continue;

					vi ntemp;
					REP(k, SZ(temp))
						ntemp.pb(temp[k].ST+temp[k].ND*w);
					q.push(State(get_corner(ntemp), get_state(ntemp), c+1));



				}

			}

		}
		REP(k, SZ(b))
			tmap[b[k].ST][b[k].ND]=EMPTY;

	}





	return dp[ep.ST][ep.ND][es];
}



int main(){
	int i, j, k, T;

	cin >> T;
	scanf("\n");

	memset(state, -1, sizeof(state));
	memset(restate, -1, sizeof(restate));

	FOR(i, 1, MAX_B)
		set_state(i);
	REP(i, T){

		cin >> h >> w;
		scanf("\n");
		REP(j, h){
			REP(k, w)
				cin >> map[k][j];
			scanf("\n");
		}

		box.clear(); dest.clear();
		memset(remap, 0, sizeof(remap));

		REP(j, h)
			REP(k, w){
				if (map[k][j] == WALL)
					remap[k][j]=1;
				else{
					if (map[k][j] == BOX || map[k][j] == SPEC)
						box.pb(k+j*w);
					if (map[k][j] == DEST || map[k][j] == SPEC)
						dest.pb(k+j*w);
					map[k][j]=EMPTY;
				}
			}
		printf("Case #%d: %d\n", i+1, solve());

	}



	return EXIT_SUCCESS;
}

