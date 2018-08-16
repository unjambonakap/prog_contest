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
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define SZ(a) ((a).size())
#define two(x) (1 << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define ll long long

using namespace std;
typedef pair<int,int> pii;
vector<string> list;

#define MAX_N 1000

vector<vector<int> > edge;
int nb[MAX_N];


int get_id(string s){
	int i;
	REP(i, list.size())
		if (list[i] == s)
			return i;
	list.pb(s);
	return list.size()-1;
}

int get_nb(int a){
	int i, j;
	vector<int> tb;
	REP(i, edge[a].size())
		tb.pb(get_nb(edge[a][i]));
	

	sort(ALL(tb));
	reverse(ALL(tb));

	int max = 0;
	REP(i, SZ(tb))
		max = MAX(max, tb[i]+i);

	return MAX(max, SZ(tb)+1);
	

	
	
}

int solve(){
	memset(nb, 0, sizeof(nb));
	return get_nb(0);
}



int main(){
	string buf;
	int i, j, k;
	int n, m, T;
	int a, b;
	string s;

	cin >> T;
	REP(i, T){
		scanf("%d", &n);

		CLR(edge);
		CLR(list);

		REP(k, n){
			cin >> s;
			b = get_id(s);
			if (b >= edge.size())
				edge.pb(vector<int>());

			scanf("%d", &m);
			REP(j, m){
				cin >> s;
				if (s.c_str()[0] <= 'Z'){
					a = get_id(s);
				   	edge[b].pb(a);
					if (a >= edge.size())
						edge.pb(vector<int>());
				}
				
					
			}
		}
		printf("Case #%d: %d\n", i+1, solve());




	}


	return EXIT_SUCCESS;
}

