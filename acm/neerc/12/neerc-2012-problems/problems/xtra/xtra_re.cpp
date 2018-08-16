/******************************************************************/
/* ACM ICPC 2012-2013                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tashkent - Tbilisi, December 2, 2012 */
/******************************************************************/
/* Problem X. Xtrapolation                                        */
/*                                                                */
/* Original idea         Andrey Stankevich                        */
/* Problem statement     Andrey Stankevich                        */
/* Test set              Andrey Stankevich                        */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Roman Elizarov                           */
/******************************************************************/

/*
    Solution for NEERC'2010 Problem X: Xtrapolation
    (C) Roman Elizarov
*/

#include <iostream>

using namespace std;

int main() {
	long long sum = 0;
	while (true) {
		int num;
		cin >> num;
		if (num == 0)
			break;
		sum += num;
		cout << sum << endl;
	}
	return 0;
}

