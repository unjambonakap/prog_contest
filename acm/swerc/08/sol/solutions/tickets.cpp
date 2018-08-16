// problem: Randomly-priced Tickets
// author : Arne Alex
// date   : Oct 2008
// method : all-pairs shortest path (Floyd-Warshall), dynamic programming, probability
// runtime: O(N^3 + N^2 * R^2)

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAX = 100, MAXR = 30;

// dist[i][j] = distance between nodes i and j
// prob[k][m] = probability that total price for a route of length k is <= m
int N, R, dist[MAX][MAX];
double prob[MAX][MAX * MAXR];

// fill in the 
void doprob() {
    memset(prob, 0, sizeof prob);
    // total price of a route of length 0 is always == 0
    fill(prob[0], prob[0] + MAX * MAXR, 1.0);
    // iterate over all lengths
    for (int i = 1; i < MAX; ++i) {
        // iterate over all maximum prices
        for (int j = 0; j < MAX * MAXR; ++j) {
            // iterate over price of last leg of journey
            for (int k = j - 1; k >= 0 && j - k <= R; --k) {
                // add probability that last ticket costs j-k * probability that the rest costs <= k
                prob[i][j] += prob[i - 1][k] / R;
            }
        }
    }
}

// plain vanilla Floyd-Warshall
void fw() {
    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                int d = dist[i][k] + dist[k][j];
                if (dist[i][j] > d) dist[i][j] = d;
            }
        }
    }
}

int main() {
    int kases, Q;
    char line[1024];

    cout.setf(ios::fixed);
    cout.precision(8);
    cin >> kases;
    for (int kase = 1; kase <= kases; ++kase) {
        cin >> N >> R;
        for (int i = 0; i < N; ++i) {
            cin >> line;
            for (int j = 0; j < N; ++j) dist[i][j] = line[j] == 'Y' ? 1 : MAX + 1;
            dist[i][i] = 0;
        }

        // compute all-pairs shortest path once
        fw();
        // do dynamic programming once
        doprob();

        // answer all queries in O(1)
        cout << "Case " << kase << endl;
        for (cin >> Q; Q > 0; --Q) {
            int a, b, c;
            cin >> a >> b >> c;
            // we can have more money than the highest possible price
            c = min(c, (N - 1) * R);
            // result depends only on length of shortest path between a and b
            cout << prob[dist[--a][--b]][c] << endl;
        }
	cout << endl;
    }
    return 0;
}
