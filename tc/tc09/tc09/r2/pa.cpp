#include <vector>
#include <string>
#include <cstdio>
#include <cmath>
#include <iostream>


using namespace std;
int n, k;

int getCol(int s, int r, int c){
	if (s==0)return 1;
	int ra, ca;
	ra=r-r%n, ca=c-c%n;

	int white;
	white=getCol(s-1, ra/n, ca/n);
	int border=(n-k)/2;
	if (white && (r%n<border || n-1-r%n<border || c%n<border || n-1-c%n<border))white=1;
	else white=0;

	return white;
}


class PlaneFractal{
	public:

		vector<string> getPattern(int s, int N, int K, int ra, int rb, int ca, int cb){
			int i, j;
			vector<string> vs;
			n=N, k=K;
			//ra-=(pow((double)N, s)-1)/2, rb-=(pow((double)N, s)-1)/2;
			//ca-=(pow((double)N, s)-1)/2, cb-=(pow((double)N, s)-1)/2;
			for (i=ra; i<=rb; ++i){	
				string sa;

				for (j=ca; j<=cb; ++j)
					sa+=getCol(s, i, j)?"0":"1";
				
				vs.push_back(sa);
			}
			return vs;

		}
};


int main(){
	int ti, tn;
	cin>>tn;
	int s, N, K, ra, rb, ca, cb;
	int i;
	for (ti=1; ti<=tn; ++ti){
		cin>>s>>N>>K>>ra>>rb>>ca>>cb;
		vector<string> res=PlaneFractal().getPattern(s, N, K, ra, rb, ca, cb);
		for (i=0; i<res.size(); ++i)
			cout<<res[i]<<endl;;
		printf("\n");


	}



}

