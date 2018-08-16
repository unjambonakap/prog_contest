/******************************************************************/
/* ACM ICPC 2012-2013                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tashkent - Tbilisi, December 2, 2012 */
/******************************************************************/
/* Problem G. Great Deceiver                                      */
/*                                                                */
/* Original idea         Elana Kryuchkova                         */
/* Problem statement     Dmitry Gozman                            */
/* Test set              Dmitry Gozman                            */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Mikhail Mirzayanov                       */
/******************************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <climits>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <bitset>
#include <utility>
#include <algorithm>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

const int N = 100;

long long z[N][2];
long long a[N];
long long b[N];

int main(int argc, char* argv[])
{
    freopen("great.in", "r", stdin);
    freopen("great.out", "w", stdout);

    long long n;
    int k;
    cin >> n >> k;

    forn(i, N)
    {
        b[i] = (i % 2 == 0 ? k : 1);
        a[i] = n % k;
        n /= k;
    }

    z[N - 1][1] = 1;

    for (int i = N - 2; i >= 0; i--)
    {
        forn(d, b[i])
        {
            z[i][0] += z[i + 1][0];
            if (d < a[i])
                z[i][0] += z[i + 1][1];
            if (d == a[i])
                z[i][1] += z[i + 1][1];
        }        
    }

    cout << z[0][0] + z[0][1] << endl;

    return 0;
}

