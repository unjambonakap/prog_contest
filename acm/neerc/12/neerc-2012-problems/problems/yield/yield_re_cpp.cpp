/******************************************************************/
/* ACM ICPC 2012-2013                                             */
/* Northeastern European Regional Contest                         */
/* St Petersburg - Barnaul - Tashkent - Tbilisi, December 2, 2012 */
/******************************************************************/
/* Problem Y. Yield                                               */
/*                                                                */
/* Original idea         Standard                                 */
/* Problem statement     Standard                                 */
/* Test set              Standard                                 */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author                Roman Elizarov                           */
/******************************************************************/

#include <fstream>
#include <utility>

using namespace std;

int main() {
	ifstream in("yield.in");
	ofstream out("yield.out");
	pair<int,int> p;
	in >> p.first >> p.second;
	out << (p.first + p.second) << endl;
	return 0;
}

