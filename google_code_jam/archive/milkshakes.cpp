#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
//#include "foreach.h"
using namespace std;


bool custok(int m, vector<int> const& u, vector<bool> const& malted)
{
	if (m >= 0 && malted[m]) return true;
	for (int i = 0; i < u.size(); ++i)
		if (!malted[u[i]]) return true;
	return false;
}


int testall(vector<int> const& cmalt, vector< vector<int> > const& cunmalt, vector<bool> const& malted)
{
	for (int i = 0; i < cmalt.size(); ++i)
		if (!custok(cmalt[i], cunmalt[i], malted)) return i;
	return -1;
}


void Case()
{
	int N, M;
	cin >> N >> M;
	vector<bool> malted(N,false);
	vector<int> cmalt(M,-1);
	vector< vector<int> > cunmalt(M);
	for (int i=0; i<M; ++i) {
		int T;
		cin >> T;
		for (int j=0; j<T; ++j) {
			int X,Y;
			cin >> X >> Y;
			if (Y)
				cmalt[i] = X-1;
			else
				cunmalt[i].push_back(X-1);
		}
	}
	for (;;) {
		int unhappy = testall(cmalt, cunmalt, malted);
		if (unhappy < 0) {
			for (int i = 0; i < N; ++i)
				cout << int(malted[i]) << ' ';
			cout << '\n';
			return;
		}
		if (cmalt[unhappy] < 0) {
			cout << "IMPOSSIBLE\n";
			return;
		}
		malted[cmalt[unhappy]] = true;
	}
}


int main()
{
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cout << "Case #" << i << ": ";
		Case();
	}
}
