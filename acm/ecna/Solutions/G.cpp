#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

const int MAX = 50;
const int MAXAMT = 100000;

string names[MAX];
int nNames;

double rates[MAX][MAX];

int index(string name)
{
	for(int j=0; j<nNames; j++)
		if (names[j] == name)
			return j;
	names[nNames++] = name;
	return nNames-1;
}

bool store(int i, int j, double val)
{
	if (val == 0.0)
		return false;
	if (rates[i][j] == 0.0) {
		rates[i][j] = val;
		return true;
	}
	else if (fabs(rates[i][j] - val) > 0.0001) {
		cout << "ERROR: inconsistancy in data with " << names[i] << " and " << names[j] << endl;
		exit(-1);
	}
	return false;
}

void updateTable()
{
	bool changesMade = true;
	while (changesMade) {
		changesMade = false;
		for(int i=0; i<nNames; i++)
			for(int j=0; j<nNames; j++) {
				if (i==j)
					continue;
				for(int k=0; k<nNames; k++) 
					changesMade |= store(i, j, rates[i][k]*rates[k][j]);
			}
	}
}

int main()
{
	int i, j, k, n, icase=0;
	cin >> n;
	while (n != 0) {
		icase++;
		for(i=0; i<MAX; i++)
			for(j=0; j<MAX; j++)
				rates[i][j] = 0.0;
		nNames = 0;
		string n1, n2;
		double r1, r2;
		int i1, i2;
		for(i=0; i<n; i++) {
			cin >> r1 >> n1 >> n2 >> r2 >> n2;
			i1 = index(n1);
			i2 = index(n2);
			store(i1, i2, r2/r1);
			store(i2, i1, r1/r2);
			updateTable();
		}

		cin >> r1 >> n1;
		i1 = index(n1);
		i=0;
		while(rates[i1][i] == 0.0 || r1*rates[i1][i] > MAXAMT)
			i++;
		int bestNum = (int)(r1*rates[i1][i]);
		if (fabs(bestNum - r1*rates[i1][i]) > 0.0000001)
			bestNum++;
		double bestDiff = bestNum*rates[i][i1] - r1;
		int bestIndex = i;
		double prevBest = -1;
		int prevIndex;
		i++;
		for(;i<nNames; i++) {
			if (rates[i1][i] != 0.0 && r1*rates[i1][i] <= MAXAMT) {
				int num = (int)(r1*rates[i1][i]);
				if (fabs(num - r1*rates[i1][i]) > 0.0000001)
					num++;
				double diff = num*rates[i][i1] - r1;
				if (diff <= bestDiff) {
					prevBest = bestDiff;
					prevIndex = bestIndex;
					bestDiff = diff;
					bestNum = num;
					bestIndex = i;
				}
			}
		}
		if (fabs(prevBest - bestDiff) < 0.000001) {
			cout << "Error case " << icase << ": diffs too close for " << names[bestIndex] << " and " << names[prevIndex] << endl;
			exit(-1);
		}
		cout << "Case " << icase << ": " << bestNum << ' ' << names[bestIndex] << endl;

		cin >> n;
	}
	return 0;
}
