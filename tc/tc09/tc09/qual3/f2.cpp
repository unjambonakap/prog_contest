#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <cassert>
#include <climits>
#include <cstdio>
#include <iostream>
#include <sstream>

using namespace std;



#define REP(i,n) for(i = 0; i < (n); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)

#define SZ(a) (int((a).size()))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define pb push_back
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;

string intToStr(int a){
	stringstream out;
	out<<a;
	return out.str();
}

int vx[]={1, 0, -1, 0};
int vy[]={0, -1, 0, 1};
const int MAX_N=55;
class PrettyPrintASpiral{
	public:
		int tb[MAX_N][MAX_N];
		int padding[MAX_N];
		vector <string> getWindow(int row1, int col1, int row2, int col2){
			int cn, rn;
			cn=col2-col1, rn=row2-row1;
			int nc=(cn+1)*(rn+1);
			int i, j, k, id;
			int x, y, d, dt, nx, ny;
			x=y=0;
			d=0;
			dt=0;
			id=1;
			memset(padding, 0, sizeof(padding));

			while(nc>0){
				if (x>=col1 && x<=col2 && y>=row1 && y<=row2){
					padding[x-col1]=intToStr(id).length();
					assert(padding[x-col1]>=0);
					tb[x-col1][y-row1]=id, --nc;
				}
				x+=vx[d], y+=vy[d];
				if (d%2==0)k=abs(x);
				else k=abs(y);

				if (d!=0 && k==dt)d=(d+1)%4;
				else if (d==0 && k==dt+1)++d, ++dt;
				++id;
			}


			vector<string> res(rn+3);
			REP(i, rn+1){
				REP(j, cn+1){
					string a=intToStr(tb[j][i]);
					res[i]+=string(1+padding[j]-(int)a.length()-(j==0), ' ')+intToStr(tb[j][i]);
				}
			}

			
			return res;
		}

};

int main(){
	int n, i, j;
	cin>>n;

	REP(i, n){
		int a, b, c, d;
		cin>>a>>b>>c>>d;

		PrettyPrintASpiral().getWindow(a, b, c, d);



	}


	return EXIT_SUCCESS;
}

