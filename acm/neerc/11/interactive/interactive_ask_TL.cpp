#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>

typedef uint8_t Byte;
typedef Byte* Permutation;

static size_t n;

static void Inc(Permutation p) { for (size_t i = 0; i < n; ++i) p[i] = i + 1; }
static void Dec(Permutation p) { for (size_t i = 0; i < n; ++i) p[i] = n - i; }

static std::ostream& operator <<(std::ostream &os, Permutation p) {
    for (size_t i = 0; i < n; ++i)
        os << int(p[i]) << " ";
    return os;
}

struct LCS {
    size_t *a;
    Permutation prev;

    LCS(): a(new size_t[(n + 1) * (n + 1)]), prev(new Byte[n]) {
        memset(a, 0, (n + 1) * (n + 1) * sizeof(*a));
        init();
    }
    ~LCS()  { delete a; }
    void init() { memset(prev, 255, n); }

    size_t calc(Permutation p, Permutation q) {
        #define A(i, j) a[(i) * (n + 1) + (j)]
        size_t i = 0;
        while (i < n && p[i] == prev[i]) ++i;
        for (; i < n; ++i)
            for (size_t j = 0; j < n; ++j)
                A(i + 1, j + 1) =
                    p[i] == q[j] ? A(i, j) + 1 : std::max(A(i, j + 1), A(i + 1, j));
        memcpy(prev, p, n);
        return A(n, n);
        #undef A
    }

};

static Permutation perms;
static size_t pc;

std::ofstream logg; //("interactive.log");

static void BestPerm(Permutation p) {
    if (pc < 5)
        memcpy(p, perms + (rand() % pc) * n, n);
    else {
        for (size_t i = 0; i < n; ++i) p[i] = i + 1;
        std::random_shuffle(p, p + n);
    }
}

static size_t Ask(Permutation p) {
    std::cout << p << std::endl;
    size_t r;
    std::cin >> r;
    if (r == n) exit(0);
    logg << pc << " : " << p << " ->" << r << std::endl;
    return r;
}

int main() {
    srand(923841);
    std::cin >> n;
    size_t fn = 1;
    for (size_t i = 2; i <= n; ++i) fn *= i;
    perms = new Byte[fn * n / 2];

    Permutation p = new Byte[n]; Inc(p);
    size_t r = Ask(p);
    Permutation p1 = new Byte[n]; Dec(p1);
    size_t r1 = Ask(p1);

    LCS lcs, lcs1;
    Permutation q = new Byte[n]; Inc(q);
    for (size_t i = 0; i < fn; ++i) {
        if (lcs.calc(q, p) == r && lcs1.calc(q, p1) == r1)
            memcpy(perms + pc++ * n, q, n);
        std::next_permutation(q, q + n);
        if (i % 10000 == 0) logg << i << std::endl;
    }
    delete q;

    while (1) {
        BestPerm(p);
        r = Ask(p);
        size_t j = 0;
        lcs.init();
        for (size_t i = 0; i < pc; ++i) {
            if (lcs.calc(perms + i * n, p) == r) {
                memcpy(perms + j * n, perms + i * n, n);
                ++j;
            }
            //if (i % 10000 == 0) logg << i << " " << j << std::endl;
        }
        pc = j;
    }
    delete p;
    return 0;
}
