/*
 * CERC 2011: Regulate
 * "Slow" solution - should not be accepted by the time limit.
 *
 * Author: Martin Kacer
 *
 * All components are held in double-linked lists.
 * The list 'prev' and 'next' directions are mixed as necessary.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 8000
#define MAXC 100

int ncnt, ccnt;
int next[2][MAXN][MAXC]; /* 0=next, 1=prev */
char links[MAXN][MAXN];

void error(const char* msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

#define RET_NOTEX "No such cable"
#define RET_THREE "Forbidden: monopoly"
#define RET_CIRCLE "Forbidden: redundant"
#define RET_OWNED "Already owned"
#define RET_OK "Sold"

int getnext(int n, int c, int prv) {
    return (next[0][n][c] == prv) ? next[1][n][c] : next[0][n][c];
}

void putnext(int n, int c, int nxt) {
    if (next[0][n][c] == -1) next[0][n][c] = nxt;
    else if (next[1][n][c] == -1) next[1][n][c] = nxt;
    else error("putting into non-free node");
}

void disconn(int a, int c, int b) {
    if (next[0][a][c] == b) next[0][a][c] = -1;
    else if (next[1][a][c] == b) next[1][a][c] = -1;
    else error("disconnecting not connected");
}

const char* one_connect(int a, int b, int c) {
    int aa, ap;
    if (links[a][b] == c) return RET_OWNED;
    if (links[a][b] == -1) return RET_NOTEX;
    if (next[0][a][c] >= 0 && next[1][a][c] >= 0) return RET_THREE;
    if (next[0][b][c] >= 0 && next[1][b][c] >= 0) return RET_THREE;
    ap = -1; aa = a;
    for (;;) {
        int nx = getnext(aa, c, ap);
        if (nx == -1) break;
        ap = aa; aa = nx;
    }
    if (aa == b) return RET_CIRCLE;
    disconn(a, links[a][b], b); disconn(b, links[a][b], a);
    links[a][b] = links[b][a] = c;
    putnext(a, c, b); putnext(b, c, a);
    return RET_OK;
}

int main() {
    for (;;) {
        int i, j, m, t;
        if (scanf("%d%d%d%d", &ncnt, &m, &ccnt, &t) < 4) break;
        if (!ncnt) break;
        for (i = 0; i < ncnt; ++i) for (j = 0; j < ncnt; ++j)
            links[i][j] = -1;
        for (i = 0; i < ncnt; ++i) for (j = 0; j < ccnt; ++j)
            next[0][i][j] = next[1][i][j] = -1;
        for (i = 0; i < m; ++i) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c); --a; --b; --c;
            if (links[a][b] >= 0) error("duplicate link");
            links[a][b] = links[b][a] = c;
            putnext(a, c, b); putnext(b, c, a);
        }
        for (i = 0; i < t; ++i) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c); --a; --b; --c;
            printf("%s.\n", one_connect(a, b, c));
        }
        printf("\n");
    }
    return 0;
}
