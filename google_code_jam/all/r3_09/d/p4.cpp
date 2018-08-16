#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
//#include <ext/hash_map>
#include <cmath>
#include <cassert>


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

#define MOD 1000000007
#define MAX_N 213

string l, r;


int tb[MAX_N];

ll powx(int a, int x){
	int i;
	if (a < 0)a=0;
	ll s=1;
	REP(i, a){
		s=(s*x)%MOD;
		assert(s>=0);
	}
	return s;
}

string prev_pal(string a){
	int i, mid;
	string t=a;


	mid=ceil(t.length()/2.)-1;


	REP(i, mid+1)
		t[t.length()-i-1]=t[i];

	if (t <= a)return t;


	t[mid]--;
	FORV(i, mid, 1){
		if (t[i] < '0')
			t[i]='9', t[i-1]--;
		else
			break;
	}
	if (t[0] == '0')
		t.erase(t.length()-1, 1), t[0]='9', t[mid]='9';
	mid=ceil(t.length()/2.)-1;

	REP(i, mid+1)
		t[t.length()-i-1]=t[i];
	return t;
}


string prev(string a){
	int i;
	a[a.length()-1]--;
	FORV(i, a.length()-1, 1){
		if (a[i] < '0')
			a[i]='9', a[i-1]--;
		else
			break;
	}
	return a;
}

string next_pal(string a){
	int i, mid;
	string t=a;

	mid=ceil(t.length()/2.)-1;

	REP(i, mid+1)
		t[t.length()-i-1]=t[i];

	if (t >= a)return t;

	t[mid]++;
	FORV(i, mid, 1){
		if (t[i] > '9')
			t[i]='0', t[i-1]++;
		else
			break;
	}

	REP(i, mid+1)
		t[t.length()-i-1]=t[i];
	return t;
}





ll get_ns(string a){
	int i, j, mid;
	ll s, p, add;

	if (a.length() == 1)
		return floor((a[0]-'0'+1)/2.);
	

	
	s=6;

	FOR(i, 2, a.length()){
		mid=ceil(i/2.)-1;
		if (i&1)
			add=1;
		else
			add=11;

		add=(add*powx(mid, 10))%MOD;
		assert(add >= 0);
		//printf("add on %Ld with mid %d\n", add, mid);
		if (i != a.length()){
			//s=(s+add*(5-((i==2)?1:0))*(powx(1-((mid == 0)?1:0), 9)*powx(mid-1, 10))%MOD)%MOD;
			ll temp=(powx(1-((mid == 0)?1:0), 9)*powx(mid-1, 10))%MOD;
			temp=(add*temp)%MOD;
			temp=(temp*(5-((i==2)?1:0)))%MOD;
			s=(s+temp)%MOD;
			
		}
		else{
			if (i == 2){
				//s=(s+add*(ll)floor((a[0]-'0'-1)/2.))%MOD;
				ll temp=(add*(ll)floor((a[0]-'0'-1)/2.))%MOD;
				s=(s+temp)%MOD;
			}
			else{

				s=(s+add*(ll)ceil((a[mid]-'0')/2.))%MOD;
				REP(j, mid){
					//s=(s+add*5*powx(mid-j-1, 10)*(a[j]-'0'-((j==0)?1:0)))%MOD;
					ll temp=(add*5*(a[j]-'0'-((j==0)?1:0)))%MOD;
					temp=(temp*powx(mid-j-1, 10))%MOD;
					s=(s+temp)%MOD;
				}
	//				printf("fact %Ld\n", add*5*powx(mid-j-1, 10)*(a[j]-'0'-((j==0)?1:0)));
				
		assert(s>=0);
			}
			
			
		}
		assert(s>=0);
	//	printf("on %Ld\n", s);
		s%=MOD;

	}

	//printf("ret %Ld\n", s);
	return s;


}

ll get_t(string a){
	ll s, p;
	int i;
	p=1, s=0;
	REPV(i, a.length())
		s=(s+(a[i]-'0')*p)%MOD, p=(p*10)%MOD;
	return s;
}


ll solve(){

	ll a, b, n;
	string pp, np;



	l=prev(l);
	pp=prev_pal(r), np=next_pal(l);
	

	a=(MOD+get_ns(pp)-get_ns(np))%MOD;
	n=(MOD+get_t(r)-get_t(l)+1)%MOD;

	if (pp.length() == 1 && (pp[0]-'0')&1)
		a=(MOD+a+get_t(r)-get_t(pp))%MOD;
	else if (pp != "" && !((pp[ceil(pp.length()/2.)-1]-'0')&1))
		a=(MOD+a+get_t(r)-get_t(pp)+1)%MOD;
	
	
	
	//printf("u1 =>>>>>>>> %Ld\n", a);
	if (np.length() == 1 && (np[0]-'0')&1)
		a=(MOD+a+get_t(np)-get_t(l)+1)%MOD;
	
	else if (np.length() > 1){
	   	if((np[ceil(np.length()/2.)-1]-'0')&1)
			a=(MOD+a+get_t(np)-get_t(l))%MOD;
		
	}
	
	

	
	b=(MOD+n-a)%MOD;
	
	ll ans;
	ans=(a*a)%MOD;
	ans=(ans+b*b)%MOD;
	ans=(ans-b-a)%MOD;
	ans=(MOD+ans)%MOD;
//	printf("%Ld %Ld %Ld\n", a, b, n);
	//cout << ">>>>>>>>>< " << r << "=> " << prev_pal(r) << endl;
	if (ans&1)
		ans=(ans+MOD)/2;
	else
		ans=ans/2;
	return ans%MOD;




}


int main(){
	int i, T;


	cin >> T;
	REP(i, T){
		cin >> l >> r;

	//	if (i!=42)continue;
		printf("Case #%d: %Ld\n", i+1, solve());


	}


	return EXIT_SUCCESS;
}

