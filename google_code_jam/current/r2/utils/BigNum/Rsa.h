#ifndef RSA_H
#define RSA_H


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
#include <sstream>
//#include <ext/hash_map>
#include <gmp.h>
#include "BigNum.h"


using namespace std;
//using namespace __gnu_cxx;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;


using namespace BigNumUtils;
class Rsa;

ostream& operator<<(ostream&, const Rsa&);

namespace Useless{
	string intStr(int, int=-1);
	int stringInt(string);

};

struct RsaPub{
	RsaPub(const BigNum&, const BigNum&);
	vs encrypt(const string&, int=-1)const;
	vs encrypt(vs)const;
	string design(const vs&)const;
	vs designR(vs)const;
	BigNum e, n;
};
struct RsaPriv{
	RsaPriv(const BigNum&, const BigNum&);
	vs sign(const string&, int=-1)const;
	vs sign(vs)const;
	string decrypt(const vs&)const;
	vs decryptR(vs)const;
	pair<vs,vs> cryptWithSign(const pair<string,string>&, const RsaPub &)const;
	pair<string,string> decryptWithSign(const pair<vs,vs>&, const RsaPub &)const;
	BigNum d, n;
};
class Rsa{
	public:
		static Rsa simpleGen(int);
		static Rsa lowFactRes(int);

		void disp(ostream&)const;

		RsaPriv getPriv()const;
		RsaPub getPub()const;


	private:
		Rsa(const BigNum&, const BigNum&, const BigNum&, const BigNum&);
		BigNum e, d, p, q, n, phin;
};

vs cryptSignedMessage(const string&, const RsaPub&, const RsaPriv&);
string decryptSignedMessage(vs, const RsaPub&, const RsaPriv&);



#endif


