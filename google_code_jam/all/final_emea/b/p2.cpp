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

#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ll long long

using namespace std;
typedef pair<int,int> pii;

#define MAX_N 300
#define MAX_C 3
#define END 10000

class offer;
class State;
vector<string> sl;
vector<offer> t;
int n;

class offer{
	public:
		offer(int _s, int _e, int _c){s=_s, e=_e, c=_c;}
		int s, e, c;

};
class State{
	public:
		State(){memset(used, 0, sizeof(used));n_used=count=on=0;}
		State(State &prev, int nc, int end){
			memcpy(used, prev.used, sizeof(used));


			n_used=prev.n_used, count=prev.count+1;
			on=end;

			if (!used[nc])n_used++, used[nc]=1;
		}

		bool operator<(const State &a) const{return (count > a.count) ? true : (count == a.count && on > a.on)? true : false;}
		

		int used[MAX_N];
		int n_used, on, count;
};

int solve(){
	int i, j, k;
	priority_queue<State> q;
	State s;

	q.push(s);
	while(!q.empty()){
		s=q.top();
		q.pop();

		if (s.on >= END)
			return s.count;
		REP(i, n){
			if (s.n_used < MAX_C || s.used[t[i].c]){
				if (t[i].s <= s.on+1 && t[i].e > s.on)
					q.push(State(s, t[i].c, t[i].e));
				
			}
		}


	}


	return -1;
}

int main(){
	int i, j, k, T, id;
	string s;
	scanf("%d", &T);
	pii p;

	REP(i, T){
		scanf("%d", &n);
		t.clear();
		sl.clear();
		REP(k, n){
			cin >> s;


			id=-1;
			REP(j, SZ(sl))
				if (sl[j] == s){id=j; break;}
			
			if (id == -1)
				id=SZ(sl), sl.pb(s);
			scanf("%d %d", &p.first, &p.second);
			t.pb(offer(p.first, p.second, id));
		}


		printf("Case #%d: ", i+1);
		j=solve();
		if (j == -1)
			printf("IMPOSSIBLE\n");
		else
			printf("%d\n", j);





	}


	return EXIT_SUCCESS;
}

