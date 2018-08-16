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

#include "BigNum.h"
#include "Rsa.h"
#include "Attack.h"
#include "Factorization.h"
//#include <gmp.h>
//#include <gmpxx.h>

using namespace std;
using namespace __gnu_cxx;

#define PI asin(1)*2.
#define EPS 10e-8


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i <= (b)) && (c); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)
#define FORVC(i, a, b, c) for(i = (a); (i >= (b)) && (c); i--)
#define FE(i,t) for (typeof(t.begin())i=t.begin();i!=t.end();i++)
#define FEV(i,t) for (typeof(t.rbegin())i=t.rbegin();i!=t.rend();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define ST first
#define ND second
#define SZ(a) ((a).size())
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define MP(x,y) make_pair(x,y)
#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define MDIST(x,y,a,b) (abs((a)-(x))+abs((b)-(y)))

#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)

#define ST first
#define ND second

#define ll long long

inline int count_bit(int n){return (n == 0)?0:(n&1)+count_bit(n>>1);}

typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;





using namespace BigNumUtils;
using namespace Factorization;


int main(){

	srand(time(NULL));

	

	BigNum n;
	n="513344440057166482153529478106373725517955044987880453208559";
	n="5730429416421047103624515556624430774351";
//	n="323856535638645605476327282669";
//	n="530873111675224529";
//	n="15770708441";
//	n="84923";
	BigNum a, b;
	//cout<<dixonRandomSquare(n, 2000)<<endl;
	a=quadraticSieve(n, 10000);
	////cout<<quadraticResidue(10, 13)<<endl;
	



	//Rsa ra=Rsa::simpleGen(100);
	//Rsa rb=Rsa::simpleGen(100);
	//vs temp;

	//string plainT="wtf?! hello world", npT;
	//string sgn="my sgn";
	//vs ta;
	//pair<vs,vs> pa;
   	//pair<string, string> pb;

	////cryptage simple
	//ta=ra.getPub().encrypt(plainT);
	//cout<<plainT<<"<<<<<<<===>>>>>>><"<<ra.getPriv().decrypt(ta)<<endl;

	////message+signature 
	//pa=ra.getPriv().cryptWithSign(MP(plainT, sgn), rb.getPub());
	//pb=rb.getPriv().decryptWithSign(pa, ra.getPub());
	//cout<<plainT<<", "<<sgn<<"<<<<<<<<===>>>>>>>>>"<<pb.ST<<", "<<pb.ND<<endl;


	////message signé
	//ta=cryptSignedMessage(plainT, ra.getPub(), rb.getPriv());
	//cout<<plainT<<"<<<<<<<<<<<===============>>>>>>>>>><"<<decryptSignedMessage(ta, rb.getPub(), ra.getPriv())<<endl;
	//return EXIT_SUCCESS;
	/*
OUTPUT:
wtf?! hello world<<<<<<<===>>>>>>><wtf?! hello world
wtf?! hello world, my sgn<<<<<<<<===>>>>>>>>>wtf?! hello world, my sgn
wtf?! hello world<<<<<<<<<<<===============>>>>>>>>>><wtf?! hello world
	   */
}



