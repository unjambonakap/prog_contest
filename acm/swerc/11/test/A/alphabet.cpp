// Solution for problem 'Alphabet Soup'

// The solution is O(P log P) and is the one sketched in the outline.
// For the pattern matching we used Knuth-Morris-Pratt algorithm.

// Author: Javier Gomez-Serrano
#include <algorithm>
#include <iostream>
using namespace std;

#define BIGPRIME 100000007
#define NUM_DEGS 360000

long long S;
long long P;

// Knuth-Morris-Pratt
void preKmp(const int *pat, int lp, int *f) {
  int i, t;
  
  // Compute f[i] = length of the longest proper suffix of pat[0..i]
  // which is also a prefix of pat.
  f[0] = t = 0;
  for (i = 1; i < lp; i++) {    // here t = f[i - 1]
    while (t && pat[i] != pat[t]) t = f[t - 1];
    if (pat[i] == pat[t]) ++t;
    f[i] = t;
  }
}

// Return the first occurrence of pat[0..lp) in str[0..ls]
int KMP(const int *pat, int lp, const int *str, int ls) {
  int f[lp], i, t = 0;
  preKmp(pat, lp, f);
  for (i = 0; i < ls; i++) {
    while (t && pat[t] != str[i]) t = f[t - 1];
    if (pat[t] == str[i]) ++t;
    if (t == lp) {
      if (i >= lp)
        return i - lp + 1;
      t = f[t - 1];
    }
  }
  return -1;
}

int gcd(int a,int b){
    return (b==0)?a:gcd(b,a%b);
}

long long power(long long a, long long b){
     // Returns a^b mod BIGPRIME
     if (b == 0) return 1;
     long long p1 = power(a,b/2);
     long long res = (p1*p1)%BIGPRIME;
     if (b%2){ res*=a; res%=BIGPRIME; }
     return res;
}

int main(){
    while (cin >> S >> P && (S != -1 || P != -1)){
        int positions[P];
        for (int i=0;i<P;i++) cin >> positions[i];
        sort(&positions[0], &positions[P]);
        int differences[P];
        int dd[2*P];
        for (int i=0;i<P;i++){
            differences[i] = (positions[i] - positions[(i+P-1)%P] + NUM_DEGS)%NUM_DEGS;
            dd[i] = differences[i];
            dd[i+P] = dd[i];
        }
        int k = KMP(differences,P,dd,2*P);
        long long res = 0;
        for (long long i = 0; i < P/k; i++){
            res+=power(S,k*gcd(i,P/k));
            res%=BIGPRIME;
        }
        res*=k;
        res%=BIGPRIME;
        res*=power(P,BIGPRIME-2);
        res%=BIGPRIME;
        cout << res << endl;
    }
    return 0;
}
