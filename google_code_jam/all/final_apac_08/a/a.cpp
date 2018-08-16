#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <assert.h>


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORV(i, b, a) for(i = (b); i > (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define SZ(a) (a).size()
#define pb push_back
#define ll long long

using namespace std;
typedef pair<int,int> pii;

#define MAX_W 1000010
int n, m;

class type{
	public:
		type(int _h, int _w, int _a){h = _h, w = _w, a = _a;}
		int h, w, a;


};
vector<type> bird, nbird;
vector<type> p;



void solve(){
	int minh, minw, maxh, maxw;
	int maxnw, maxnh, minnh, minnw;
	int i, j;
	vector<type> max_ta, min_ta, mixhw, mixwh;
	
	maxh = maxw = -1, minh = minw = MAX_W;
	maxnh = maxnw = MAX_W, minnh = minnw = -1;
	if (SZ(bird) == 0){
		REP(i, SZ(p)){
			REP(j, SZ(nbird)){
				if (p[i].h == nbird[j].h && p[i].w == nbird[j].w){
					p[i].a = -1;
					break;
				}
			}

		}
		return;
	}

	REP(i, SZ(bird)){
		//printf("bird at %d %d\n", bird[i].h, bird[i].h);
		maxh = MAX(maxh, bird[i].h);
		maxw = MAX(maxw, bird[i].w);
		minh = MIN(minh, bird[i].h);
		minw = MIN(minw, bird[i].w);
	}

	REP(i, SZ(nbird))
		//printf("nbird at %d %d\n", nbird[i].h, nbird[i].h);

		REP(j, SZ(nbird)){
			if (nbird[j].h >= minh && nbird[j].h <= maxh){
				if (nbird[j].w > maxw)
					maxnw = MIN(maxnw, nbird[j].w);
				else{
					assert(nbird[j].w < minw);
					minnw = MAX(minnw, nbird[j].w);
				}
			}else if (nbird[j].w >= minw && nbird[j].w <= maxw){
				if (nbird[j].h > maxh)
					maxnh = MIN(maxnh, nbird[j].h);
				else{
					assert(nbird[j].h < minh);
					minnh = MAX(minnh, nbird[j].h);
				}
			}else{

				if (nbird[j].h > maxh && nbird[j].w > maxw)
					max_ta.pb(nbird[j]);
				else if (nbird[j].h < minh && nbird[j].w < minw)
					min_ta.pb(nbird[j]);
				else if (nbird[j].h < minh && nbird[j].w > maxw)
					mixhw.pb(nbird[j]);
				else if (nbird[j].h > maxh && nbird[j].w < minw)
					mixwh.pb(nbird[j]);


			}
		}


	//printf("bird between %d < h < %d and %d < w < %d\n", minh, maxh, minw, maxw);
	//printf("not if h < %d or h > %d  or w < %d or w > %d\n", minnh, maxnh, minnw, maxnw);


	REP(i, SZ(p)){
		//printf("test bird at %d %d\n", p[i].h, p[i].w);
		if (p[i].w >= minw && p[i].w <= maxw && p[i].h >= minh && p[i].h <= maxh){
			p[i].a = 1;
			//printf("bird\n");
		}
		else if (p[i].w >= maxnw || p[i].h >= maxnh || p[i].w <= minnw || p[i].h <= minnh){
			//printf("not bird\n");
			p[i].a = -1;
		}
		else{
			p[i].a = 0;
			REP(j, SZ(max_ta)){
				if (p[i].h >= max_ta[j].h && p[i].w >= max_ta[j].w){
					p[i].a = -1;
					break;
				}
			}
			if (j != SZ(max_ta))
				continue;

			REP(j, SZ(min_ta)){
				if (p[i].h <= min_ta[j].h && p[i].w <= min_ta[j].w){
					p[i].a = -1;
					break;
				}
			}
			if (j != SZ(min_ta))
				continue;
			REP(j, SZ(mixhw)){
				if (p[i].h <= mixhw[j].h && p[i].w >= mixhw[j].w){
					p[i].a = -1;
					break;
				}
			}
			if (j != SZ(mixhw))
				continue;
			REP(j, SZ(mixwh)){
				if (p[i].h >= mixwh[j].h && p[i].w <= mixwh[j].w){
					p[i].a = -1;
					break;
				}
			}
			if (j != SZ(mixwh))
				continue;
		}
	}




}
void disp(){
	int i;
	REP(i, m){
		if (p[i].a == 1)
			printf("BIRD\n");
		else if (p[i].a == 0)
			printf("UNKNOWN\n");
		else
			printf("NOT BIRD\n");
	}

}
int main(){
	int i, j;
	int T;
	string s;
	int h, w;

	cin >> T;

	REP(i, T){
		cin >> n;
		bird.clear(), nbird.clear(), p.clear(); 
		REP(j, n){
			cin >> h >> w >> s;
			if (s == "BIRD")
				bird.pb(type(h, w, 1));
			else{
				nbird.pb(type(h, w, -1));
				cin >> s;
			}
		}



		cin >> m;

		REP(j, m){
			cin >> h >> w;
			p.pb(type(h, w, 0));


		}

		printf("Case #%d:\n", i + 1);
		solve();
		disp();

	}


	return EXIT_SUCCESS;
}

