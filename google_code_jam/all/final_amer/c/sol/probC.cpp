// Prewritten header. See lib.el

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<ii, ii> iiii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef unsigned long long ull;
#define sz(a) int((a).size())
#define pb push_back
#define mp make_pair
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)
#define present(c,x) ((c).find(x) != (c).end())
#define cpresent(c,x) (find(all(c),x) != (c).end())

class Solver {
public:
  Solver(ifstream& i);
  string solve();
private:
  int Q;
  int M;
  vector<vector<double> > probs;
};

void solve(string type){
  string infile="c:/codejam/semis/ProblemC/C-" + type + ".in";
  string outfile="c:/codejam/semis/ProblemC/C-" + type + ".out";
  cout << infile << " to " << outfile << endl;
  ifstream input(infile.c_str());
  ofstream output(outfile.c_str());
  int N;
  input >> N;
  cout << N << " cases" << endl;
  for (int i = 1; i <= N; ++i){
    cout << "Case #" << i << endl;
    Solver ps(input);
    string soln=ps.solve();
    output << "Case #" << i << ": " << soln << endl;
    cout << soln << endl;
  }
  input.close();
  output.close();
}

int main(int argc, char* argv[])
{string type = "test";
  if (argc > 1){
    int loc = 0;
    char param = argv[1][loc];
    while (param == '-'){
      ++loc;
      param = argv[1][loc];
    }
    switch (param){
    case '2':
    case 'l':
    case 'L':
      type = "large"; break;
    case '1':
    case 's':
    case 'S':
      type = "small"; break;
    default:
      type = "test"; break;}
  }
  solve(type);
}

Solver::Solver(ifstream& i){
  // Read in data to local variables.
  // Remember to define local variables in class description at top
  i >> M >> Q;
  probs.assign(Q, vector<double>(4,0) );
  for (int j = 0; j < Q; ++j){
    for (int k = 0; k < 4; ++k){
      i >> probs[j][k];
    }
    sort(all(probs[j]));
  }
}

string Solver::solve() {
  // Solve problem, using local variables, and return string.
  // If you need to parse a float with exactly 6 decimal
  // places, do:
  //  char floatBuffer[20];
  //  sprintf(floatBuffer, ".6f", f);
  vector<double> ans(M, 0.0);
  ans[0] = 1.0;
  for (int j = 0; j < Q; ++j){
    vector<double> p = probs[j];
    vector<int> next(4,0);
    vector<double> nextprob;
    for (int t = 0; t < 4; ++t){
      nextprob.pb(p[t]*ans[0]);
    }
    vector<double> nextans(M,0.0);
    int h = 0;
    while (h < M){
      double recd = 0; int holder = -1;
      for (int i = 0; i < 4; ++i){
	if (nextprob[i] > recd){
	  recd = nextprob[i]; holder = i;
	}
      }
      if (recd == 0)
	break;
      nextans[h] = recd;
      ++next[holder];
      if (next[holder] == M)
	nextprob[holder] = -1;
      else
	nextprob[holder]=p[holder]*ans[next[holder]];
      ++h;
    }
    ans = nextans;
  }
  double total = 0;
  for (int i = 0; i < M; ++i){
    total += ans[i];
  }
  char* z = new char[300];
  sprintf(z,"%.8f",total);
  string s = z;
  delete[] z;
  return s;
}

