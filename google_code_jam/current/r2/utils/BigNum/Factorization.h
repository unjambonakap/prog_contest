#ifndef FACTORIZATION_H 
#define FACTORIZATION_H

#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
//#include <ext/hash_map>
#include <gmp.h>
#include <pthread.h>


using namespace std;
using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

class BigNum;

typedef vector<vector<BigNum> > MBN;



namespace Factorization{
	const int MAX_QS_RANGE=100000;

	struct DixonRow;
	struct Polynomial;
	struct DummyPThread;
	struct Factor;

	bool getSmoothDecomp(BigNum, const vector<Factor>&, vector<ll>&);
	bool getSmoothDecomp(BigNum, const vector<BigNum>&, vector<ll>&);
	bool getF2SmoothDecomp(BigNum, const vector<Factor>&, vector<char>&);
	bool getF2SmoothDecomp(BigNum, const vector<BigNum>&, vector<char>&);
	vector<char> decompToF2(const vector<ll>&);


	vector<BigNum> primeBaseB(const BigNum&);
	vector<BigNum> primeBaseN(const BigNum&);
	vector<BigNum> primeBaseN(const BigNum&, const BigNum&);
	vector<BigNum> nextPrimes(const BigNum&, int);

	BigNum dixonRandomSquare(const BigNum&, const BigNum&);


	void *_qsWorkRange(void*);
	vector<DixonRow> qsWorkRangeLow(const BigNum&, const BigNum&, const vector<Factor>&, const BigNum&, const Polynomial&);
	vector<DixonRow> qsWorkRange(const BigNum&, const BigNum&, const vector<Factor>&, const BigNum&, const Polynomial&, int*);
	BigNum quadraticSieve(const BigNum&, const BigNum&, int=1);
	
	bool isQuadraticResidue(BigNum, const BigNum&);
	BigNum quadraticResidue(const BigNum&, const BigNum&);
	BigNum solveCongruentSystem(const BigNum&, const vector<BigNum>&, const vector<DixonRow>&);
		
};



#endif

