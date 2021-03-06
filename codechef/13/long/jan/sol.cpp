/**
 * January 2013 Long Challenge at Codechef
 *
 * Problem:     CUCUMBER - Cucumber Boy and Cucumber Girl
 * Author:      Anton Lunyov (Tester and Editorialist)
 * Complexity:  O(B * N^2 + B^2) per test
 * Timing:      0.55 out of 1.301
 *
 * Description:
 * See editorial :)
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long LL;

const int maxN = 60;
const int maxM = 8000;

void read(int n, LL *a) {
    for (int i = 0; i < n; ++i) {
        a[i] = 0;
    }
    char type[11];
    scanf("%s", type);
    if (strcmp(type,"raw") == 0) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int Qij;
                scanf("%d", &Qij);
                if (Qij & 1) {
                    a[i] |= 1LL<<j;
                }
            }
        }
    } else {
        unsigned S, P, A;
        scanf("%u%u%u", &S, &P, &A);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // we get rid of mod 100 since (x mod 100) mod 2 = x mod 2
                // (x + 1) % 2 equals to !(x & 1), so not to be confused :)
                if(!(S>>12 & 1)) {
                    a[i] |= 1LL<<j;
                }
                // overflow = mod 2^32
                S = S * P + A;
            }
        }
    }
}

LL calc(int n, LL *a) {
    int i, j, k;

    // adding of column composed of ones to Q 
    for (i = 0; i < n; ++i) {
        a[i] += 1LL<<n;
    }

    puts("");
    puts("===");
    for (i=0; i<n; ++i){
        for (int j=0; j<=n; ++j) printf("%d",a[i]>>j&1);
        puts("");

    }

    // x is the index of column G from the editorial
    int x = n;

    // i is the current row 
    // k is the current column
    for (i = k = 0; i < n; ++i, ++k) {

        // we seek for non-zero elements among a[i][k], a[i+1][k], ..., a[n-1][k]
        for (j = i; j < n && !(a[j] & 1LL<<k); ++j)
            ;

        if (j == n) {

            // if we did not find then k > i means that rank of _a_ is < n
            // and all determinants Q_{a,c} are zero so we return 0
            if (k == i + 1) {
                return 0;
            }

            // otherwise k is the column that will be G
            x = k;
            // and we should increase our current column in the Guass-Jordan elim
            ++k;
            // we now sek again for non-zero element in column
            for (j = i; j < n && !(a[j] & 1LL<<k); ++j)
                ;
            // if even this time we find only zeros it means that rank < N and we return 0
            if (j == n) {
                return 0;
            }
        }
        // now we know that a[j][k] != 0  so we swap i-th and j-th row if nessecary
        // and move on to the privoting
        if(i!=j) {
            swap(a[i], a[j]);
        }
        // note that we do pivoting for all rows and not only for rows > i
        for (j = 0; j < n; ++j) {
            if (j != i && (a[j] & 1LL<<k)) {
                // the xor do the addition modulo 2
                a[j] ^= a[i];
            }
        }
    }
    // result is simply the content of column G with setting det(Q_{a,x}) to be 1
    LL res = 1LL<<x;
    for (i = 0; i < x; ++i) {
        if (a[i] & 1LL<<x) {
            res += 1LL<<i;
        }
    }
    for (int i=0; i<=n; ++i) printf("%d",res>>i&1); puts("");
    puts("");
    return res;
}

const int maxH = 16;
int BITPARITY[1<<maxH];

void bitparity_precalc()
{
    BITPARITY[0] = 0;
    for (int n = 1; n < (1<<maxH); ++n) {
        BITPARITY[n] = BITPARITY[n>>1] ^ (n & 1);
    }
}

typedef unsigned short US; // it's not United States :D
inline int bit_parity(LL a)
{
    // check it out the funny way of taking 16 first bits of the number
    // we simply cast it to unsigned short type :)
    return BITPARITY[a>>48] ^ BITPARITY[US(a>>32)] ^ BITPARITY[US(a>>16)] ^ BITPARITY[US(a)];
}

int main() {
    bitparity_precalc();
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; ++t) {

        // m is B from the problem statement
        int n, m;
        scanf("%d%d", &n, &m);

        // the number V[i] has sequence determinants Q_{i,c} as its binary form
        LL V[maxM];

        // the number of odd elements among Q_a[1][1] (needed when n=1)
        int cnt = 0;

        for (int i = 0; i < m; ++i) {
            // b[j] is the j-th row of the matrix Q[i] written in binary
            LL b[maxN];
            read(n, b);
            if(n == 1) {
                cnt += b[0]; 
            } else {
                // we calculate determinants Q_{i,c} in O(n^2)
                V[i] = calc(n, b);
            }
        }
        int ans = 0;
        if (n == 1) {
            ans = cnt * (cnt - 1) / 2; 
        } else {
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < i; ++j) {
                    ans += bit_parity(V[i] & V[j]);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
