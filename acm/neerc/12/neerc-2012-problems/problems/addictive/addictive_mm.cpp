/******************************************************************/
/* ACM ICPC 2012-2013                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tashkent - Tbilisi, December 2, 2012 */
/******************************************************************/
/* Problem A. Addictive Bubbles                                   */
/*                                                                */
/* Original idea         Georgiy Korneev                          */
/* Problem statement     Georgiy Korneev                          */
/* Test set              Georgiy Korneev                          */
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

int main(int argc, char* argv[])
{
    freopen("addictive.in", "r", stdin);
    freopen("addictive.out", "w", stdout);

    int n, m, c;
    cin >> n >> m >> c;

    vector<int> counts(c);
    forn(i, c)  
        cin >> counts[i];

    vector<string> f(n, string(m, ' '));

    int x = 0, y = 0;
    int d = 1;
    int cc = 0;

    forn(i, n * m)
    {
        while (counts[cc] == 0)
            cc++;
        f[x][y] = '1' + cc;
        counts[cc]--;

        y += d;
        if (y < 0 || y >= m)
        {
            y -= d;
            x++;
            d = -d;
        }
    }

    forn(i, n)
        cout << f[i] << endl;

    return 0;
}

