#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <utility>
#include <numeric>
#include <algorithm>
#include <bitset>
#include <complex>

using namespace std;

typedef unsigned uint;
typedef long long Int;
typedef vector<int> vint;
typedef pair<int,int> pint;
#define mp make_pair

template<class T> void pv(T a, T b) { for (T i = a; i != b; ++i) cout << *i << " "; cout << endl; }
template<class T> void chmin(T &t, T f) { if (t > f) t = f; }
template<class T> void chmax(T &t, T f) { if (t < f) t = f; }
int in() { int x; scanf("%d", &x); return x; }

#define MAX 1010
const int INF = 1001001001;

int N, M;
int F;
int AX[MAX], AY[MAX], BX[MAX], BY[MAX], C[MAX];

int fsLen[MAX];
int fs[MAX][MAX];
int V;
int is[MAX][MAX];

int D[MAX][MAX];
void ae(int u, int v, int c) {
    chmin(D[u][v], c);
    chmin(D[v][u], c);
}

int dist[MAX];

Int sumOf(Int a, Int b) {
    //cout<<"sumOf "<<a<<" "<<b<<" : "<<((a + b) * (b - a + 1) / 2)<<endl;
    return (a + b) * (b - a + 1) / 2;
}
Int calc(Int y, Int dA, Int dB) {
    //cout<<"calc "<<y<<" "<<dA<<" "<<dB<<endl;
    Int ret = 0;
    Int z = (y + dB - dA) / 2;
    assert(0 <= z && z <= y);
    //cout<<"z = "<<z<<endl;
    ret += sumOf(dA, dA + z);
    if (z < y) {
        ret += sumOf(dB, dB + (y - z - 1));
    }
    return ret;
}

int main() {
    int i;
    int x, e;
    int u, v, w;
    int sx, sy;

    for (; ~scanf("%d%d%d", &N, &F, &M); ) {
        for (i = 0; i < M; ++i) {
            AX[i] = in() - 1;
            AY[i] = in() - 1;
            C[i] = in();
            BX[i] = in() - 1;
            BY[i] = in() - 1;
        }
        for (x = 0; x < N; ++x) {
            fsLen[x] = 0;
            fs[x][fsLen[x]++] = 0;
            fs[x][fsLen[x]++] = F - 1;
        }
        for (i = 0; i < M; ++i) {
            x = AX[i];
            fs[x][fsLen[x]++] = AY[i];
            x = BX[i];
            fs[x][fsLen[x]++] = BY[i];
        }
        V = 0;
        for (x = 0; x < N; ++x) {
            sort(fs[x], fs[x] + fsLen[x]);
            fsLen[x] = unique(fs[x], fs[x] + fsLen[x]) - fs[x];
            for (e = 0; e < fsLen[x]; ++e) {
                is[x][e] = V++;
            }
        }
        //for(x=0;x<N;++x){cout<<"fs[x] : ";pv(fs[x],fs[x]+fsLen[x]);}
        for (u = 0; u < V; ++u) for (v = 0; v < V; ++v) {
            D[u][v] = (u != v) ? INF : 0;
        }
        for (x = 0; x < N - 1; ++x) {
            ae(is[x][0], is[x + 1][0], 1);
        }
        for (x = 0; x < N; ++x) {
            for (e = 0; e < fsLen[x] - 1; ++e) {
                ae(is[x][e], is[x][e + 1], fs[x][e + 1] - fs[x][e]);
            }
        }
        for (i = 0; i < M; ++i) {
            x = AX[i];
            e = lower_bound(fs[x], fs[x] + fsLen[x], AY[i]) - fs[x];
            u = is[x][e];
            x = BX[i];
            e = lower_bound(fs[x], fs[x] + fsLen[x], BY[i]) - fs[x];
            v = is[x][e];
            ae(u, v, C[i]);
        }
        for (w = 0; w < V; ++w) for (u = 0; u < V; ++u) for (v = 0; v < V; ++v) {
            chmin(D[u][v], D[u][w] + D[w][v]);
        }
        for (int qry = in(); qry--; ) {
            sx = in() - 1;
            sy = in() - 1;
            for (u = 0; u < V; ++u) {
                dist[u] = INF;
            }
            for (int phase = 0; phase < 2; ++phase) {
                if (phase == 0) {
                    e = upper_bound(fs[sx], fs[sx] + fsLen[sx], sy) - fs[sx] - 1;
                } else {
                    e = lower_bound(fs[sx], fs[sx] + fsLen[sx], sy) - fs[sx];
                }
                w = is[sx][e];
                for (u = 0; u < V; ++u) {
                    chmin(dist[u], abs(sy - fs[sx][e]) + D[w][u]);
                }
            }
            //cout<<"dist : ";pv(dist,dist+V);
            Int ans = 0;
            for (x = 0; x < N; ++x) if (x != sx) {
                if (fsLen[x] == 1) {
                    ans += dist[is[x][0]];
                } else {
                    for (e = 0; e < fsLen[x] - 1; ++e) {
                        ans += calc(fs[x][e + 1] - fs[x][e], dist[is[x][e]], dist[is[x][e + 1]]);
                    }
                    for (e = 1; e < fsLen[x] - 1; ++e) {
                        ans -= dist[is[x][e]];
                    }
                }
            }
            printf("%lld\n", ans);
        }
    }

    return 0;
}

