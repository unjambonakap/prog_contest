#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
bool test(float w, int max, int n) {
    vector<float> v(n);
    for (int i=0; i<n; i++) fscanf(stdin, "%f", &v[i]);
    sort(v.begin(), v.end());
    bool ok = (v[0] <= w/2) && ((max - v[n-1]) <= w/2);
    if ( ! ok) fprintf(stderr, "\tnot touching sides 0-%d\n", max);
    for (int i=0; i<n-1 && ok; i++) {
        if (v[i+1] - v[i] > w) { ok = false; fprintf(stderr, "\t%f - %f > %f\n", v[i+1], v[i], w); }
    }
    return ok;
}
int main() {
    int n1, n2;
    float w;
    while(fscanf(stdin, "%d %d %f", &n1, &n2, &w), w > 0) {
        fprintf(stderr, "\t%d %d %f:\n", n1, n2, w);
        bool x = test(w, 75, n1), y = test(w, 100, n2);
        fprintf(stdout, "%s\n", x && y ? "YES" : "NO");
    }
    return 0;
}

