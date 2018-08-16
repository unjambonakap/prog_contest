#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <climits>
//#include <ext/hash_map>


using namespace std;
using namespace __gnu_cxx;



#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i <= (b)) && (c); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)
#define FORVC(i, a, b, c) for(i = (a); (i >= (b)) && (c); i--)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)

#define SZ(a) (int((a).size()))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()

#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

class BidirectionalQueue{
	public:

		int extractElements(int N, vector <int> indices){
			int pos[N+1];
			int i, j, k;
			int p=0;
			REP(i, N)
				pos[i]=i;
			FE(it, indices)--(*it);
			//FE(it, indices)
			//	printf("%d\n", *it);
			//printf("<<%d\n", N);
			int s=0, l;
			REP(i, SZ(indices)){
				l=N-i;
				//printf("%d == %d >> %d %d %d with %d\n", l, p, pos[indices[i]], (l+p-pos[indices[i]])%l, (l+pos[indices[i]]-p)%l, s);
				assert(min((l+p-pos[indices[i]])%l, (l+pos[indices[i]]-p)%l)>=0);;
				s+=min((l+p-pos[indices[i]])%l, (l+pos[indices[i]]-p)%l);
				p=pos[indices[i]];
				FOR(j, indices[i], N-1)
					--pos[j];
				
				if (p==l-1)p=0;

			}
			return s;


		

		}

};

int main(){
	int i, j;
	int n, na, nb;

	cin>>n;
	REP(i, n){
		cin>>na;
		cin>>nb;
		
		vi s(nb, 0);
		REP(j, nb)
			cin>>s[j];
//		if (i!=3)continue;
		printf("%d\n", BidirectionalQueue().extractElements(na, s));


	}


	return EXIT_SUCCESS;
}

