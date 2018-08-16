#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 305, MAXK = 16, MOD = 9901;

int T, N, K, edge1 [MAXK], edge2 [MAXK], deg [MAXN], fact [MAXN], path [MAXK];
bool vis [MAXN], adj [MAXN][MAXN];

int fastpow (int a, int b)
{
    int p = 1;

    while (b > 0)
    {
        if (b & 1) p = p * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }

    return p;
}

int inv (int a)
{
    return fastpow (a, MOD - 2);
}

bool cycle (int num, int from)
{
    vis [num] = true;

    for (int i = 0; i < N; i++)
        if (adj [num][i] && i != from)
            if (vis [i] || cycle (i, num))
                return true;

    return false;
}

int plen (int num)
{
    vis [num] = true;

    int count = 1;

    for (int i = 0; i < N; i++)
        if (adj [num][i] && !vis [i])
            count += plen (i);

    return count;
}

int solve (int mask)
{
    memset (adj, false, sizeof (adj));
    memset (deg, 0, sizeof (deg));

    for (int i = 0; i < K; i++)
        if (mask & 1 << i)
        {
            adj [edge1 [i]][edge2 [i]] = adj [edge2 [i]][edge1 [i]] = true;
            deg [edge1 [i]]++; deg [edge2 [i]]++;
        }

    for (int i = 0; i < N; i++)
        if (deg [i] > 2)
            return 0;

    memset (vis, false, sizeof (vis));

    int ccount = 0;

    for (int i = 0; i < N; i++)
        if (!vis [i] && cycle (i, -1))
            ccount++;

    if (__builtin_popcount (mask) == N)
    {
        if (ccount > 1)
            return 0;
    }
    else if (ccount > 0)
        return 0;

    memset (vis, false, sizeof (vis));

    int P = 0, sum = 0;

    for (int i = 0; i < N; i++)
        if (!vis [i])
        {
            int p = plen (i);

            if (p > 1)
            {
                path [P++] = p;
                sum += p;
            }
        }

    int total = fact [N - sum + P] * fastpow (2, P) % MOD;

    for (int i = 0; i < P; i++)
        total = (total + fact [N - sum + P - 1] * fastpow (2, P) % MOD * (path [i] - 1)) % MOD;

    return total;
}

int main ()
{
    scanf ("%d", &T);

    for (int t = 1; t <= T; t++)
    {
        scanf ("%d %d", &N, &K);

        for (int i = fact [0] = 1; i <= N; i++)
            fact [i] = fact [i - 1] * i % MOD;

        for (int i = 0; i < K; i++)
        {
            scanf ("%d %d", edge1 + i, edge2 + i);
            edge1 [i]--; edge2 [i]--;
        }

        int total = 0;

        for (int m = 0; m < 1 << K; m++)
            total = (total + (__builtin_popcount (m) & 1 ? -1 : 1) * solve (m)) % MOD;

        total = (total + MOD) * inv (2 * N) % MOD;
        printf ("Case #%d: %d\n", t, total);
    }

    return 0;
}
