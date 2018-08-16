//  Author: Javier Gomez-Serrano
//  Solution for 'sums'
//  Complexity: O(N)
//  Algorithm: Extensive use of cumulative sums and cumulative min from both sides
#include <iostream>
#define MAXN 1000007
using namespace std;
int A[MAXN];
int R[MAXN], S[MAXN], T[MAXN], U[MAXN];

int main(){
    int N;
    while (cin >> N, N){
          for (int i=0;i<N;i++) cin >> A[i];
          T[0] = A[0]; for (int i=1;i<N;i++) T[i] = T[i-1]+A[i];
          U[N-1] = A[N-1]; for (int i=N-2;i>=0;i--) U[i] = U[i+1]+A[i];
          S[0] = A[0]; for (int i=1;i<N;i++) S[i] = min(S[i-1],T[i]);
          R[N-1] = A[N-1]; for (int i=N-2;i>=0;i--) R[i] = A[i] + min(R[i+1], 0);
          int res = 0; if (S[N-1] >= 0) res++;
          for (int i=1;i<N;i++){
              if (R[i] >= 0 && U[i] + S[i-1] >= 0) res++;
          }
          cout << res << endl;
    }
    return 0;
}
