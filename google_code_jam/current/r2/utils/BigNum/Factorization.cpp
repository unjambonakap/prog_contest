#include "Factorization.h"


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPC(i,n,c) for(i = 0; (i < (n)) && (c); i++)

#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define REPVC(i, n, c) for (i = (n) - 1; (i >= 0) && (c); i--)
#define FOR(i, a, b) for(i = (a); i <= (b); i++)
#define FORC(i, a, b, c) for(i = (a); (i <= (b)) && (c); i++)
#define FORV(i, a, b) for(i = (a); i >= (b); i--)
#define FORVC(i, a, b, c) for(i = (a); (i >= (b)) && (c); i--)
#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();i++)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();i++)

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define ST first
#define ND second
#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define MP(x, y) make_pair(x, y)
#define SQR(x) (pow((x),2))
#define DIST(x,y) (SQR(x)+SQR(y))
#define MDIST(x,y,a,b) (abs((a)-(x))+abs((b)-(y)))

#define CMP(x,y) ((fabs((x)-(y)) < EPS) ? 0 : ((x) < (y)) ? -1 : 1)


//inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
//inline ll sqr(int x){return ll(x)*ll(x);}
//inline double dist(ll x, ll y, ll a, ll b){return sqrt(double(sqr(x-a)+sqr(y-b)));}
inline bool bit_set(int a, int b){return (a&two(b));}

const double INF=1e20;


#include "BigNum.h"

using namespace BigNumUtils;

namespace Factorization{

	struct DixonRow{
		vector<char> vb;
		vector<ll> decomp;
		BigNum a;
		bool operator<(const DixonRow& r)const{return vb>r.vb;}
	};

	struct Polynomial{
		BigNum a, b;//a and b >= 0
		vector<vector<BigNum> > invL;
		BigNum eval(const BigNum& x)const{return sqr(a*x+b);}
		BigNum eval2(const BigNum& x)const{return a*x+b;}
	};

	struct DummyPThread{
		BigNum a, b;
		const vector<Factor>& qr;
		const BigNum& n;
		Polynomial p;
		int logRes[MAX_QS_RANGE+1];
	};

	struct Factor{// by jacobi symbol : (a/p)=1 => (a/p^b)=1
		//y²=a(p), x²=a(p^e) =>>> x=y^(p^(e-1))*a^((p^e-2p^(e-1)+1)/2) ...proof? -_-
		BigNum p;
		vector<BigNum> qr;
		int log;
	};


	vector<BigNum> primeBaseN(const BigNum &n){
		int c;
		BigNum sq, nsq, i, j;
		vector<BigNum> list;
		nsq=4, sq=1, i=3, c=1;

		list.pb(2);
		while(n>c){
			if (nsq<=i)sq++, nsq=(sq+1)*(sq+1);
			for(j=3;sq>=j;j+=2)
				if (i%j==0)
					break;
			if (sq<j)list.pb(i), c++; 

			i+=2;
		}
		return list;
	}

	vector<BigNum> primeBaseNQS(const BigNum &na, const BigNum &n){
		int c;
		BigNum sq, nsq, i, j;
		vector<BigNum> list;
		nsq=4, sq=1, i=3, c=0;

		list.pb(2);
		while(na>c){
			if (nsq<=i)sq++, nsq=(sq+1)*(sq+1);
			for(j=3;sq>=j;j+=2)
				if (i%j==0)
					break;
			if (sq<j && isQuadraticResidue(n, i)){list.pb(i), c++;} 
			i+=2;
		}
		return list;
	}
	vector<BigNum> nextPrimes(const BigNum& na, int n){
		int c;
		BigNum sq, nsq, i, j;
		vector<BigNum> list;
		sq=sqrt(na), nsq=(sq+1)*(sq+1), i=na, c=0;

		list.pb(2);
		while(n>c){
			if (nsq<=i)sq++, nsq=(sq+1)*(sq+1);
			for(j=3;sq>=j;j+=2)
				if (i%j==0)
					break;
			if (sq<j)list.pb(i), c++; 
			i+=2;
		}
		return list;

	}

	bool getF2SmoothDecomp(BigNum n, const vector<Factor>& list, vector<char>& b){
		CLR(b);
		if (n==0)return false;
		int i;
		FE(it, list)
			for(b.pb(0);n%it->p==0;b.back()^=1)
				n/=it->p;
		return n==1;
	}
	bool getF2SmoothDecomp(BigNum n, const vector<BigNum>& list, vector<char>& b){
		CLR(b);
		if (n==0)return false;
		int i;
		FE(it, list)
			for(b.pb(0);n%(*it)==0;b.back()^=1)
				n/=*it;
		return n==1;
	}
	bool getSmoothDecomp(BigNum n, const vector<Factor>& list, vector<ll>& b){
		CLR(b);
		if (n==0)return false;
		FE(it, list)
			for(b.pb(0);n%it->p==0;++b.back()){
				n/=it->p;
				assert(b.back()>=0);
			}
		return n==1;
	}

	bool getSmoothDecomp(BigNum n, const vector<BigNum>& list, vector<ll>& b){
		CLR(b);
		if (n==0)return false;
		FE(it, list)
			for(b.pb(0);n%(*it)==0;++b.back()){
				n/=*it;
				assert(b.back()>=0);
			}
		return n==1;
	}

	vector<char> decompToF2(const vector<ll>& b){
		vector<char> a;
		FE(it, b)
			a.pb(((*it)%2)==1);
		return a;
	}

	bool isQuadraticResidue(BigNum n, const BigNum& p){ cout<<p<<">>>>>>>"<<n.powm((p-1)/2, p)<<endl;return n.powm((p-1)/2, p)==1; }//p odd prime
	BigNum quadraticResidue(const BigNum& n, const BigNum& p){
		//quadratic residue: outut^2 = n(p)
		BigNum r, z, t, q, ta, b, c;
		int leg, s, m, i;
		if (p==2)return 1;

		s=(p-1).ctz();
		q=(p-1)>>s;//q odd
		FOR(z, 2, p-1)
			if (mpz_legendre(z.getMpz(), p.getMpz())==-1)break;


		if (z==p){
			assert(0);
			return -1;
		}
		c=z.powm(q, p);
		r=n.powm((q+1)/2, p);
		t=n.powm(q, p);
		m=s;
		while(t!=1){
			ta=t.powm(2, p);
			i=1;
			while(ta!=1 && i<m)
				ta.spowm(2, p), ++i;
			if (i==m)assert(0);
			b=c.powm(BigNum(2)^(m-i-1), p);
			c=b.powm(2, p);
			r=(r*b)%p; t=(t*c)%p;
			m=i;
		}

		assert((r*r)%p==n%p);

		return r;
	}



	BigNum solveCongruentSystem(const BigNum& n, const vector<BigNum>& list, const vector<DixonRow>& mo){
		vector<DixonRow> m=mo;
		BigNum a, b, ea, eb;
		int i, j, k, z;

		REP(z, min(1, SZ(mo)-SZ(list))){
			int p=-1;
			m=mo;
			random_shuffle(ALL(m));
			//			FE(it, m){
			//				FE(ita, it->vb)
			//					printf("%d ", *ita);
			//				printf("=========");
			//				cout<<it->a<<"=>>>>";
			//				FE(ita, it->decomp)
			//					cout<<*ita<<" ";
			//
			//				cout<<endl;
			//
			//			}
			//printf("<\n\n\n");
			REP(j, SZ(list)){ //now changing the matrix to row echelon form
				FOR(k, p+1, SZ(m)-1)
					if (m[k].vb[j]==1)break;

				if (k==SZ(m))continue;
				++p;
				swap(m[p], m[k]);

				FOR(k, p+1, SZ(m)-1)
					if (m[k].vb[j]==1){
						//			cout<<m[p].a<<"*"<<m[k].a<<"="<<(m[k].a*m[p].a)%n<<endl;

						REP(i, SZ(list))
							m[k].vb[i]^=m[p].vb[i], m[k].decomp[i]+=m[p].decomp[i];
						m[k].a=(m[k].a*m[p].a)%n;
					}
			}
			//FE(it, m){
			//	FE(ita, it->vb)
			//		printf("%d ", *ita);
			//	printf("=========");
			//	cout<<it->a<<"=>>>>";
			//	FE(ita, it->decomp)
			//		cout<<*ita<<" ";
			//	printf("=========");
			//	cout<<endl;

			//}
			vector<char> vb(SZ(list), 0);
			FEV(it, m){
				if (it->vb!=vb)break;
				a=it->a;
				//cout<<a<<endl;

				b=1;
				REP(i, SZ(list)){
					assert(it->decomp[i]%2==0);
					b=(b*list[i].powm((ull)(it->decomp[i]/2), n))%n;
				}
				//	cout<<"oon "<<it->a<<">>>>>>>><"<<b<<endl;
				//a*a == b*b
				//cout<<b<<endl;

				if ((ea=__gcd(a-b, n))!=1 && (eb=__gcd(a+b, n))!=1){
					cout<<"Factorization succeeded: "<<ea<<"*"<<eb<<"="<<n<<endl;
					return ea;
				}
			}
		}
		printf("noooooooooooooooooooooooooooooooo\n");

		return 1;
	}

	BigNum dixonRandomSquare(const BigNum& n, const BigNum& lim){
		vector<BigNum> list=primeBaseN(lim);
		cout<<"Up to "<<list.back()<<endl;
		vector<DixonRow> la;
		vector<ll> decomp;
		BigNum b=-1, a, oa;
		BigNum nl;
		BigNum ea, eb;
		vector<char> vb;
		int i, j, k;
		FE(it, list)
			cout<<*it<<endl;

		oa=a=sqrt(n);
		vector<vector<char> > ma;
		while(SZ(la)<SZ(list)+20){

			a=(a+1)%n;
			if (a==oa){
				printf("couldn't collect enough data\n");
				return 1;
			}
			if (getSmoothDecomp((a*a)%n, list, decomp)){
				printf("collected %d over %d\n", SZ(la), SZ(list)+10);
				la.pb({decompToF2(decomp), decomp, a});
			}
			b=a;
		}
		return solveCongruentSystem(n, list, la);
	}

	void *_qsWorkRange(void* a){
		DummyPThread *b=(DummyPThread*)a;
		pair<Polynomial, vector<DixonRow> > *r=new pair<Polynomial, vector<DixonRow> >;
		*r=MP(b->p, qsWorkRange(b->a, b->b, b->qr, b->n, b->p, b->logRes));
		pthread_exit((void*)r);
		return r;
	}

	vector<DixonRow> qsWorkRangeLow(const BigNum& a, const BigNum& b, const vector<Factor>& factors, const BigNum& n, const Polynomial& p){
		vector<DixonRow> ra, rb;
		vector<ll> decomp;
		BigNum i;

		if (b-a<=MAX_QS_RANGE){
			vector<BigNum> state;
			FOR(i, a, b)
				state.pb(p.eval(i)-n);
			FE(it, factors){
				i=((a-it->qr[0])/it->p)*it->p+it->qr[0];
				if (i<a)i+=it->p;
				assert(i>=a);

				//cout<<"on " <<it->p<<", "<<it->qr[0]<<endl;
				//cout<<"start on "<<i<<endl;
				while(i<=b){
					assert((i*i-n)%it->p==0);
					//      cout<<it->ST<<" divide " << (i-a)<<">>>>>><<"<<state[(i-a).toUi()]<<endl;
					while(state[(i-a).toUi()]%it->p==0)
						state[(i-a).toUi()]/=it->p;
					i+=it->p;
				}   

			}   
			FOR(i, a, b)
				if (i-a!=0 && state[(i-a).toUi()]==1){
					assert(getSmoothDecomp(p.eval(i)-n, factors, decomp));
					ra.pb({decompToF2(decomp), decomp, p.eval2(i)});
				}

		}else{
			BigNum c=a-1;
			while(++c<=b){
				rb=qsWorkRangeLow(c, min(b, c+MAX_QS_RANGE), factors, n, p);
				ra.insert(ra.end(), ALL(rb));
				c=min(b, c+MAX_QS_RANGE);
			}

		}
		return ra;

	}






	vector<DixonRow> qsWorkRange(const BigNum& a, const BigNum& b, const vector<Factor>& factors, const BigNum& n, const Polynomial& p, int *logRes){
		vector<DixonRow> ra, rb;
		vector<ll> decomp;
		BigNum t, temp;
		int j;
		long int i, blocksize;
		blocksize=(b-a).toUi()+1;
		memset(logRes, 0, sizeof(int)*blocksize);

		int ths=a.log2()-10;//log threshold

		//cout<<"range "<<a<<"   "<<b<<endl;

		FE(it, factors){
			t=it->p;
			REP(j, min(SZ(it->qr), 1)){//polynomial (a*x+b)²-n=0 , qr2=n(p) => (a*x+b)=qr
				i=((((it->qr[j]-p.b)%t)*p.invL[it-factors.begin()][j])%t).toUi();

				//assert((p.a*p.invL[it-factors.begin()][j])%t==1);
				//assert((it->qr[j]*it->qr[j])%t==n%t);
				//assert((p.a*i+p.b)%t==it->qr[j]%t);
				//assert((p.eval(i)-n)%t==0);
				assert(i>=0);

				//	cout<<"on " << it->ST<<", "<<it->ND<<endl;
				//	cout<<"start on "<<i<<endl;
				temp=((a-i)/t)*t+i;
				assert((p.eval(temp)-n)%t==0);
				if (temp<a)temp+=t;
				i=(temp-a).toUi();

				while(i<=blocksize){
					logRes[i]+=it->log;
					i+=t.toUi();
				}
				t*=it->p;
			}

		}
		FOR(i, 0, (b-a).toUi())
			if (logRes[i]>=ths && getSmoothDecomp(p.eval(a+i)-n, factors, decomp))
				ra.pb({decompToF2(decomp), decomp, p.eval2(a+i)});

		return ra;
		//FOR(i, a, b)
		//	if (i-a!=0 && state[(i-a).toUi()]==1)ra.pb(i);
	}

	BigNum quadraticSieve(const BigNum& n, const BigNum& lim, int nthread){
		int temp=10;
		vector<BigNum> list=primeBaseNQS(lim, n);
		vector<BigNum> nList=nextPrimes(list.back(), 10);
		vector<Factor> factors;
		pthread_t *thd=new pthread_t[nthread];
		int i, j, powLim;
		BigNum y, a, p, pe;



		powLim=2;
		FE(it, list){
			pe=p=*it, a=n%p;
			factors.pb({p, vector<BigNum>(), it->log2()});
			factors.back().qr.pb(y=quadraticResidue(a, p));

			if (*it==2)continue;
			assert((y*y)%p==a);

			FOR(i, 2, powLim){ //y²=a(p), x²=a(p^e) =>>> x=y^(p^(e-1))*a^((p^e-2p^(e-1)+1)/2) (p^e) ...proof? -_-
				pe*=p, a=n%pe;
				factors.back().qr.pb((y.powm(p^(i-1), pe)*a.powm((pe-(p^(i-1))*2+1)/2, pe))%pe);
				assert(sqr(factors.back().qr.back())%pe == n%pe);

			}
		}
		Polynomial test={1, 10, vector<vector<BigNum> >(SZ(list))};
		REP(i, SZ(factors)){
			a=factors[i].p;
			REP(j, SZ(factors[i].qr)){
				assert(isCoprime(test.a, a));
				test.invL[i].pb(test.a.inv(a));
			}
		}


		//Polynomial test={251162, -120880, 0};
		DummyPThread dp={0, 0, factors, n, test};

		cout<<"Up to "<<list.back()<<endl;
		FE(it, list)
			cout<<"prime: "<<*it<<endl;
		BigNum u=MAX_QS_RANGE, ou=0;

		cout<<"quadratic residues\n";
		FE(it, factors)
			cout<<it->p<<"=>>>"<<it->qr[0]<<endl;
		cout<<"end qr\n";

		BigNum center=sqrt(n)+2, b;
		vector<DixonRow> m;
		pair<Polynomial, vector<DixonRow> > *ma;
		while(1){
			dp.a=center+ou+1, dp.b=center+u;

			//ns=qsWorkRange(center-u, center-ou-1, quadRes, n);
			//smooth.insert(smooth.end(), ALL(ns));
			REP(i, nthread)
				if (pthread_create(thd+i, NULL, _qsWorkRange, (void*)&dp)){
					cerr<<"Error creating thread, exiting"<<endl;
					exit(-1);
				}

			REP(i, nthread){
				if (pthread_join(thd[i], (void**)&ma)){
					cerr<<"Error in thread execution, exiting"<<endl;
					exit(-1);
				}
				m.insert(m.end(), ALL(ma->ND));
				cout<<"collected "<<SZ(m)<<"/"<<SZ(list)+1<<" elems"<<endl;
				delete ma;
			}


			ou=u, u+=MAX_QS_RANGE;
			if (SZ(m)>=SZ(list)+1)
				break;
			if (u>n){
				cerr<<"failed, try smaller/bigger base\n";
				return -1;
			}

		}
		delete[] thd;

		cout<<"found "<<SZ(m)<<" smooth elems"<<endl;
		//FE(it, m){
		//	cout<<it->a<<"=>>>>";
		//	FE(ita, it->decomp)
		//		cout<<*ita<<" ";
		//	cout<<endl;

		//}
		cout<<solveCongruentSystem(n, list, m)<<endl;

		return 0;

	}





};









