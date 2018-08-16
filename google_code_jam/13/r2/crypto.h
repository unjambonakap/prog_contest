#ifndef CRYPTO_H
#define CRYPTO_H 
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
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <climits>
//#include <ext/hash_map>
#include<ctime>
#include<unistd.h>
#include<endian.h>
#include<sys/time.h>

#include<openssl/aes.h>
#include<openssl/sha.h>
#include<openssl/md4.h>
#include<openssl/hmac.h>

#include<gmp.h>

using namespace std;
using namespace __gnu_cxx;



#define REP(i,n) for(int i = 0; i < int(n); ++i)
#define REPV(i, n) for (int i = (n) - 1; (int)i >= 0; --i)
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)

#define FE(i,t) for (__typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (__typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define two(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()


#define pb push_back
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef unsigned char uchar;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef vector<pair<string,string> > cookie;

extern gmp_randstate_t randstate;
void initcrypto();

struct buffer{
    uchar *a; int n;

    ~buffer(){free(a);}
    buffer(int n=0):n(n){a=(uchar*)malloc(n+1);memset(a,0,n+1);}
    buffer(const uchar *b, int n):n(n){a=(uchar*)malloc(n+1); memcpy(a,b,n); a[n]=0;}
    buffer(const uchar *b){n=strlen((char*)b); a=(uchar*)malloc(n+1); memcpy(a,b,n); a[n]=0;}
    buffer(const char *b){n=strlen(b); a=(uchar*)malloc(n+1); memcpy(a,b,n); a[n]=0;}
    buffer(const buffer &b){n=b.n; a=(uchar*)malloc(n+1); memcpy(a,b.a,n); a[n]=0;}
    buffer operator=(const buffer &b){n=b.n; a=(uchar*)malloc(n+1); memcpy(a,b.a,n); a[n]=0; return *this;}
    bool operator==(const buffer &b)const{
        if (b.n!=n) return 0;
        return !memcmp(b.a,a,n);
    }

    uchar &operator[](int i){return a[i];}
    uchar operator[](int i)const{return a[i];}

    buffer operator+(const buffer &b)const{
        buffer x(n+b.n);
        memcpy(x.a,a,n);
        memcpy(x.a+n,b.a,b.n);
        return x;
    }

    void from(const buffer &b){free(a); n=b.n; a=(uchar*)malloc(n+1); memcpy(a,b.a,n);}
    buffer copy()const{ buffer x; x.from(*this); return x;}


    static buffer Rand(int n){
        buffer x(n);
        REP(i,n) x.a[i]=rand()&0xff;
        return x;
    }

    buffer tob64() const;

    buffer fromb64() const;
    void disphex(int m=-1)const{if (m==-1) m=n; ;REP(i,m) printf("%02x",(unsigned uchar)a[i]); puts("");}
    void disptext(int m=-1)const{if (m==-1) m=n; REP(i,m) printf("%c", isprint(a[i])||isspace(a[i])?a[i]:'?');puts("");}

    void fillrand(int u, int v){
        assert(u>=0 && v<n);
        FOR(i,u,v) a[i]=rand()&0xff;
    }

    buffer hextobyte()const{
        buffer b((n+1)/2);
        int u=0;
        if (n&1) sscanf((char*)a,"%1x",(char*)b.a), ++u;
        REP(i,n/2) sscanf((char*)a+u+2*i,"%2x",b.a+i+u);
        return b;
    }
    buffer bytetohex()const{
        buffer b(2*n);
        REP(i,n) sprintf((char*)b.a+2*i,"%02x",a[i]);
        return b;
    }
    void rpkcs7(int bs=16){
        int x=a[n-1];
        if (!x || x>bs) throw "PADDING ERROR";
        for (int i=n-1; i>=n-x; --i) if (a[i]!=x) throw "PADDING ERROR";
        n-=x;
    }

    buffer pkcs7(int bs=16) const{
        assert(bs<256);
        int u=bs-n%bs;
        buffer b(n+u);
        memcpy(b.a,a,n);
        REP(i,u) b.a[n+i]=u;
        return b;
    }

    double computescore()const;
};




typedef class bignum{
    public:
        mpz_t a;
        ~bignum(){ mpz_clear(a); }
        bignum(const bignum &b){ mpz_init(a); mpz_set(a,b.a); }
        bignum(){mpz_init(a);}
        bignum(const buffer &b, int base=16){ mpz_init(a); mpz_set_str(a,(char*)b.a,base); }
        bignum(int u){ mpz_init(a); mpz_set_si(a,u); }
        buffer getstr(int base=16)const{
            char *x=mpz_get_str(0,base,a);
            buffer b(x);
            free(x);
            return b;
        }

        buffer getstr2()const{ return getstr().hextobyte(); }

        void disp()const{getstr(10).disptext();}

        static bignum frombytestr(const buffer &b){ return bignum(b.bytetohex()); }

        static bignum rand(const bignum &b){
            bignum res;
            mpz_urandomm(res.a,randstate,b.a);
            return res;
        }

        bignum operator-()const{
            bignum res;
            mpz_neg(res.a,a);
            return res;
        }

        bignum &operator=(const bignum &b){ mpz_set(a,b.a); return *this; }
        bignum operator+(const bignum &b)const{
            bignum res;
            mpz_add(res.a,a,b.a);
            return res;
        }
        bignum operator-(const bignum &b)const{
            bignum res;
            mpz_sub(res.a,a,b.a);
            return res;
        }
        bignum operator*(const bignum &b)const{
            bignum res;
            mpz_mul(res.a,a,b.a);
            return res;
        }
        bignum operator/(const bignum &b)const{
            bignum res;
            mpz_fdiv_q(res.a,a,b.a);
            return res;
        }
        bignum ceil(const bignum &b)const{
            bignum res;
            mpz_fdiv_q(res.a,a,b.a);
            return res;
        }
        bignum operator%(const bignum &b)const{
            bignum res;
            mpz_mod(res.a,a,b.a);
            return res;
        }
        bignum powm(const bignum &b, const bignum &mod)const{
            bignum res;
            mpz_powm(res.a,a,b.a,mod.a);
            return res;
        }


        bool operator<(const bignum &b)const{return mpz_cmp(a,b.a)<0;}
        bool operator>(const bignum &b)const{return mpz_cmp(a,b.a)>0;}
        bool operator<=(const bignum &b)const{return mpz_cmp(a,b.a)<=0;}
        bool operator>=(const bignum &b)const{return mpz_cmp(a,b.a)>=0;}
        bool operator==(const bignum &b)const{ return mpz_cmp(a,b.a)==0; }
        bool operator!=(const bignum &b)const{return mpz_cmp(a,b.a)!=0;}


        bignum gcd(const bignum &b)const{bignum res; mpz_gcd(res.a,a,b.a); return res;}

}bg;


#endif


