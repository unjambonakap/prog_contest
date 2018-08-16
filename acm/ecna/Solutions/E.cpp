#include <iostream>
#include <string>
#include <climits>
using namespace std;

const int MAXOP=9;

struct retval {
	int val, op;
};

int eval(int a, int b, char op, bool isMaximizing)
{
	int ans;
	switch (op) {
	case '+' : {
		ans = a+b;
		if (a > 0 && b > 0 && ans <= 0)
			cout << "Addition OVERFLOW error: " << a << "+" << b << "=" << ans << endl;
		else if (a < 0 && b < 0 && ans >= 0)
			cout << "Addition OVERFLOW error: " << a << "+" << b << "=" << ans << endl;
		return ans;
	}
	case '-' :  {
		ans = a-b;
		if (a > 0 && b < 0 && ans <= 0)
			cout << "Subtraction OVERFLOW error: " << a << "-" << b << "=" << ans << endl;
		else if (a < 0 && b > 0 && ans >= 0)
			cout << "Subtraction OVERFLOW error: " << a << "-" << b << "=" << ans << endl;
		return ans;
	}
	case '*' : {
		ans = a*b;
		if (a != 0 && b != 0 && ans/a != b) 
			cout << "Multiplication OVERFLOW error: " << a << "*" << b << "=" << ans << endl;
		return ans;
	}
	case '/' : 
		if (b != 0)
			return a/b;
		else if (isMaximizing)
			return INT_MIN;
		else
			return INT_MAX;
	default : cout << "ERROR, operator = " << op << endl;
	}
}

int process(int vals[], char ops[])
{
	string s;
	int n;
	cin >> n;
	for(int i=0; i<n; i++)
		cin >> vals[i] >> ops[i];
	cin >> vals[n];
	return n;
}
	
retval maxiMin(int[], char[], int);
retval miniMax(int vals[], char ops[],  int numOps)
{
/*
cout << "miniMax, numOps = " << numOps << endl;
for(int i=0; i<numOps; i++)
cout << vals[i] << ' ' << ops[i] << ' ';
cout << vals[numOps] << endl;
/**/
	retval ans;
	if (numOps == 0) {
		ans.val = vals[0];
		ans.op = -1;
		return ans;
	}
	int newVals[MAXOP];
	char newOps[MAXOP];
	newVals[0] = eval(vals[0], vals[1], ops[0], true);
	for(int i=1; i<numOps; i++) {
		newVals[i] = vals[i+1];
		newOps[i-1] = ops[i];
	}
	ans = maxiMin(newVals, newOps, numOps-1);
	if (ans.val == INT_MAX)
		ans.val = INT_MIN;
	ans.op = 0;
	for(int i=1; i<numOps; i++) {
		newVals[i-1] = vals[i-1];
		newVals[i] = eval(vals[i], vals[i+1], ops[i], true);
		newOps[i-1] = ops[i-1];
		retval tmp  = maxiMin(newVals, newOps, numOps-1);
		if (tmp.val != INT_MAX && tmp.val > ans.val) {
			ans = tmp;
			ans.op = i;
		}
	}
//cout << "miniMax, numOps = " << numOps << ", returning " << ans.val << endl;
	return ans;
}

retval maxiMin(int vals[], char ops[],  int numOps)
{
/*
cout << "maxiMin, numOps = " << numOps << endl;
for(int i=0; i<numOps; i++)
cout << vals[i] << ' ' << ops[i] << ' ';
cout << vals[numOps] << endl;
/**/
	retval ans;
	if (numOps == 0) {
		ans.val = vals[0];
		ans.op = -1;
		return ans;
	}
	int newVals[MAXOP];
	char newOps[MAXOP];
	newVals[0] = eval(vals[0], vals[1], ops[0], false);
	for(int i=1; i<numOps; i++) {
		newVals[i] = vals[i+1];
		newOps[i-1] = ops[i];
	}
	ans = miniMax(newVals, newOps, numOps-1);
	if (ans.val == INT_MIN)
		ans.val == INT_MAX;
	ans.op = 0;
	for(int i=1; i<numOps; i++) {
		newVals[i-1] = vals[i-1];
		newVals[i] = eval(vals[i], vals[i+1], ops[i], false);
		newOps[i-1] = ops[i-1];
		retval tmp  = miniMax(newVals, newOps, numOps-1);
		if (tmp.val != INT_MIN && tmp.val < ans.val) {
			ans = tmp;
			ans.op = i;
		}
	}
//cout << "maxiMin, numOps = " << numOps << ", returning " << ans.val << endl;
	return ans;
}

int main()
{
	int ncases;
	int vals[MAXOP+1];
	char ops[MAXOP];
	cin >> ncases;
	for(int icase=1; icase<=ncases; icase++) {
		cout << "Case " << icase << ":" << endl;
		int numOps = process(vals, ops);
		retval ans1 = miniMax(vals, ops, numOps);
		cout << "Player 1 (" << vals[ans1.op] << ops[ans1.op] << vals[ans1.op+1] << ") leads to " << ans1.val << endl;
		retval ans2 = maxiMin(vals, ops, numOps);
		cout << "Player 2 (" << vals[ans2.op] << ops[ans2.op] << vals[ans2.op+1] << ") leads to " << ans2.val << endl;
		if (ans1.val > -ans2.val)
			cout << "Player 1 wins" << endl;
		else if (ans1.val < -ans2.val)
			cout << "Player 2 wins" << endl;
		else
			cout << "Tie" << endl;
	}
}
