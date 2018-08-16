#include <vector>
#include <cstdio>
#include <string>
#include <cmath>
#include <set>

using namespace std;
#define pb push_back

int r, c, n;
int extrem_row[3][51][2];
int extrem_col[3][51][2];

int tr_area(int xa, int ya, int xb, int yb, int xc, int yc){return abs((xb-xa)*(yc-ya)-(yb-ya)*(xc-xa));}


void rmax(int &r, int a){if (r<a)r=a;}
void rmin(int &r, int a){if (a<r)r=a;}
set<vector<int> > deleted;

int fproc(int ra, int ca, int rb, int cb, int rc, int cc){
	int i;
	int ara=tr_area(ra, ca, rb, cb, rc, cc), arb;

	for (i=0; i<r; ++i){
		if (extrem_row[0][i][0]==-1)continue;	
		arb=tr_area(i, extrem_row[0][i][0], rb, cb, rc, cc);
		if (arb>ara)return 0;
		arb=tr_area(i, extrem_row[0][i][1], rb, cb, rc, cc);
		if (arb>ara)return 0;
	}
	for (i=0; i<r; ++i){
		if (extrem_row[1][i][0]==-1)continue;	
		arb=tr_area(ra, ca, i, extrem_row[1][i][0], rc, cc);
		if (arb>ara)return 0;
		arb=tr_area(ra, ca, i, extrem_row[1][i][1], rc, cc);
		if (arb>ara)return 0;
	}
	for (i=0; i<r; ++i){
		if (extrem_row[2][i][0]==-1)continue;	
		arb=tr_area(ra, ca, rb, cb, i, extrem_row[2][i][0]);
		if (arb>ara)return 0;
		arb=tr_area(ra, ca, rb, cb, i, extrem_row[2][i][1]);
		if (arb>ara)return 0;
	}

	for (i=0; i<c; ++i){
		if (extrem_col[0][i][0]==-1)continue;	
		arb=tr_area(extrem_col[0][i][0], i, rb, cb, rc, cc);
		if (arb>ara)return 0;
		arb=tr_area(extrem_col[0][i][1], i, rb, cb, rc, cc);
		if (arb>ara)return 0;
	}
	for (i=0; i<r; ++i){
		if (extrem_col[1][i][0]==-1)continue;	
		arb=tr_area(ra, ca, extrem_col[1][i][0], i, rc, cc);
		if (arb>ara)return 0;
		arb=tr_area(ra, ca, extrem_col[1][i][1], i, rc, cc);
		if (arb>ara)return 0;
	}
	for (i=0; i<r; ++i){
		if (extrem_col[2][i][0]==-1)continue;	
		arb=tr_area(ra, ca, rb, cb, extrem_col[2][i][0], i);
		if (arb>ara)return 0;
		arb=tr_area(ra, ca, rb, cb, extrem_col[2][i][1], i);
		if (arb>ara)return 0;
	}
	vector<int> sgn;
	sgn.pb(ra), sgn.pb(ca), sgn.pb(rb), sgn.pb(cb), sgn.pb(rc), sgn.pb(cc);
	if (deleted.find(sgn)!=deleted.end())return 0;

	deleted.insert(sgn);
	return 1;



}

int procb(int ra, int ca, int rb, int cb){
	int res=0;
	for (int i=0; i<r; ++i){
		if (extrem_row[2][i][0]==-1)continue;
		res+=fproc(ra, ca, rb, cb, i, extrem_row[2][i][0]);
		if (extrem_row[2][i][0]!=extrem_row[2][i][1])
			res+=fproc(ra, ca, rb, cb, i, extrem_row[2][i][1]);
	}	for (int i=0; i<r; ++i){
		if (extrem_col[2][i][0]==-1)continue;
		res+=fproc(ra, ca, rb, cb, extrem_col[2][i][0], i);
		if (extrem_col[2][i][0]!=extrem_col[2][i][1])
			res+=fproc(ra, ca, rb, cb, extrem_col[2][i][1], i);
	}
	return res;
}
int proca(int ra, int ca){
	int res=0;
	for (int i=0; i<r; ++i){
		if (extrem_row[1][i][0]==-1)continue;
		res+=procb(ra, ca, i, extrem_row[1][i][0]);
		if (extrem_row[1][i][0]!=extrem_row[1][i][1])
			res+=procb(ra, ca, i, extrem_row[1][i][1]);
	}for (int i=0; i<c; ++i){
		if (extrem_col[1][i][0]==-1)continue;
		res+=procb(ra, ca, extrem_col[1][i][0], i);
		if (extrem_col[1][i][0]!=extrem_col[1][i][1])
			res+=procb(ra, ca, extrem_col[1][i][1], i);
	}
	return res;
}

class ExtendableTriangles{
	public:

		int getCount(vector<string> grid){
			int i, j, k;
			int res;
			int cnt[3];
			char *mp="RGB";

			r=grid.size();
			c=grid[0].length();
			n=r*c;

			memset(cnt, 0, sizeof(cnt));

			for (i=0; i<r; ++i)
				for (j=0; j<c; ++j)
					for (k=0; k<3; ++k)
						if (grid[i][j]==mp[k])++cnt[k];

			for (i=0; i<3; ++i){
				for (j=0; j<r; ++j){
					extrem_row[i][j][0]=-1, extrem_row[i][j][1]=51;
					for (k=0; k<c; ++k)
						if (grid[j][k]==mp[i])
							rmax(extrem_row[i][j][0], k), rmin(extrem_row[i][j][1], k);


				}

				for (j=0; j<c; ++j){
					extrem_col[i][j][0]=-1, extrem_col[i][j][1]=51;
					for (k=0; k<r; ++k)
						if (grid[k][j]==mp[i])
							rmax(extrem_col[i][j][0], k), rmin(extrem_col[i][j][1], k);

				}
			}
			res=cnt[0]*cnt[1]*cnt[2];
			deleted.clear();
			for (i=0; i<n; ++i)
				if (grid[i/c][i%c]==mp[0])
					res-=proca(i/c, i%c);


			return res;

		}

};
