/*
   Overview of the idea (simplified by ignoring the fact that an "n-digit" number can't start with 0):
   An n-digit base-11 stepping number is the same as n-cycle in the path graph P(11).
   If T is this graph's transition matrix, the number of these is the trace of T^n.
   We can exponentiate T by repeated squaring, doing all calculations in the ring of integers mod 4294967143.

   This method is simple but, sadly, too slow.
   OK, let f(n) be the number of n-digit base-11 stepping numbers.
   We can actually only consider f(2n): if n is odd, f(n)=0 because the graph P(11) is bipartite.
   Since T (so also T^2) is symmetric, it's diagonalizable. This leads to an explicit formula:
   f(2n) = 1/12 [22 2^n + 23 3^n + (22-s) (2-s)^n + (22+s) (2+s)^n + 21]  where s = sqrt(3).
   This works equally well in R or F_p(s), where p = 4294967143. (Sadly, 3 is a nonresidue mod p.)
   */

#include <iostream>
#include <stdint.h>
using namespace std;

struct Scalar
{
    static const uint_fast64_t modulus;
    uint_fast32_t value;
    Scalar(): value(0) {}
    Scalar(uint_fast32_t v): value(v) {}
    void operator+=(Scalar r)
    {
        value = (uint_fast64_t(value) + uint_fast64_t(r.value)) % modulus;
    }
    Scalar operator+(Scalar r)
    {
        return Scalar( (uint_fast64_t(value) + uint_fast64_t(r.value)) % modulus );
    }
    Scalar operator*(Scalar r)
    {
        return Scalar( (uint_fast64_t(value) * uint_fast64_t(r.value)) % modulus );
    }
};
Scalar operator*(uint_fast32_t v, Scalar x) { return Scalar(v) * x; }
ostream &operator<<(ostream &out, Scalar s) { return (out << s.value); }
const uint_fast64_t Scalar::modulus = 4294967143;

// Represent tuples of the form (x[0], x[1], x[2] + x[3] sqrt(3))
typedef Scalar Tuple[4];
inline void multiply(Tuple p, Tuple x, Tuple y)
{
    p[0] = x[0] * y[0];
    p[1] = x[1] * y[1];
    Scalar p2 = x[2] * y[2] + 3 * x[3] * y[3];
    Scalar p3 = x[2] * y[3] + x[3] * y[2];
    p[2] = p2;
    p[3] = p3;
}

int main()
{
    Scalar one_twelfth = 1789569643;
    Tuple c = { 22 * one_twelfth, 23 * one_twelfth, 22 * one_twelfth, one_twelfth };
    Scalar a = 21 * one_twelfth;
    Tuple squares[64];
    squares[0][0] = 2;
    squares[0][1] = 3;
    squares[0][2] = 2;
    squares[0][3] = 1;

    for (int p = 1; p < 64; p++)
        multiply(squares[p], squares[p-1], squares[p-1]);

    uint64_t trials, n;
    cin >> trials;
    while (cin >> n)
    {
        if (n % 2 == 0)
            n /= 2;
        else
        {
            cout << 0 << endl;
            continue;
        }
        Tuple x = { c[0], c[1], c[2], c[3] };
        int p = 0;
        while (n)
        {
            if (n & 1) multiply(x, x, squares[p]);
            p++;
            n >>= 1;
        }
        cout << a + x[0] + x[1] + x[2] + x[2] << endl; /* Not a typo: want field trace of x[2]+x[3] sqrt(3) */
    }

    return 0;
}
