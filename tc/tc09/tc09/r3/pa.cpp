#include <vector>
#include <iostream>
#include <cstring>
#include <queue>


#include <algorithm>

using namespace std;
int n;

struct tree{
	int x, y, h;
};
struct state{
	vector<tree> list;
	int v;
	bool operator<(const state &s){return v>s.v;}
};
void swap(tree &a, tree &b){
	tree c=a;
	a=b, b=c;
}
void rmin(int &r, int a){if (a<r)r=a;}
void rmax(int &r, int a){if (a>r)r=a;}


int perim(const vector<tree> &tx, int n){

	int xmin, xmax, ymin, ymax;
	int i;
	xmin=ymin=0, xmax=ymax=1000010;
	for (i=0; i<n; ++i){
		rmin(xmin, tx[i].x);
		rmax(xmax, tx[i].x);
		rmin(ymin, tx[i].y);
		rmax(ymax, tx[i].h);
	}

	return 2*(ymax-ymin+xmax-xmin);
}


class SaveTheThrees{
	public:

		int minimumCut(vector<int> x, vector<int> y, vector<int> h){
			int i, j, k, tot, op;

			vector<tree> tx;
			n=x.size();

			tx=vector<tree>(n);
			for (i=0; i<n; ++i)
				tx[i].x=x[i], tx[i].y=y[i], tx[i].h=h[i]; 


			state s;
			s.list=tx;
			s.v=perim(tx, n);
			priority_queue<state> q;
			q.push(s);

			while(1){


			}
			return tot;
		}

};
int main(){

	int tn, ti;
	int i, j;
	cin>>tn;
	for (ti=0; ti<tn; ++ti){
		cin>>n;
		vector<int> x(n), y(n), h(n);
		for (i=0; i<n; ++i)
			cin>>x[i]>>y[i]>>h[i];

		printf("Case #%d: %d\n", ti+1, SaveTheTrees().minimumCut());
	}

}









