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
#define ll long long

using namespace std;
typedef pair<int,int> pii;


#include "matching.hpp"


int main(){
	vector<pii> edges, a;
	edges.pb(pii(0, 1));
	edges.pb(pii(1, 2));
	edges.pb(pii(2, 3));
	edges.pb(pii(3, 4));
	edges.pb(pii(4, 1));
	edges.pb(pii(4, 5));
//	edges.pb(pii(4, 5));


	a = get_matching(edges, 6);
	printf("|M| = %d\n", SZ(a));



	return EXIT_SUCCESS;
}

