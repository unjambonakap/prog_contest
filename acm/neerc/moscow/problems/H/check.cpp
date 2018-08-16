#define EJUDGE
#include "testlib.h"
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>

#define pb push_back
#define mp make_pair
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(),(v).end()

using namespace std;

typedef pair<int, int> ii;
typedef long long int64;
typedef vector<int> vi;
typedef long long ll;

template<class T> T abs(T x) { return x > 0 ? x : (-x); }
template<class T> T sqr(T x) { return x * x; }

const int64 BUBEN = (int64)(2E18);

int main(int argc, char* argv[])
{
    setName("checker for H");
    registerTestlibCmd(argc, argv);

    int64 res = ouf.readLong();

    int64 Ans = ans.readLong();

    if (res != Ans) {
    	quitf(_wa, "WA");    
    }

    int n = inf.readInt();
    int64 m = inf.readLong();
    int64 f = inf.readLong();
    int64 money = m, ac = 0;
    for (int i = 0; i < n; ++i) {
    	int64 cost = inf.readLong();
    	int64 val = ouf.readLong();
    	ac += val;
    	if (ac < 0) quitf(_wa, "Incorrect 1");
    	if (val > BUBEN / cost)  quitf(_wa, "Incorrect 1");
    	money -= val * cost;
    	if (val != 0) money -= f;
    	if (money < 0  || ac < 0) quitf(_wa, "Incorrect 1");
    }

    if (money != res || ac != 0) quitf(_wa, "Botva");

	quitf(_ok, "OK");
    return 0;
}
