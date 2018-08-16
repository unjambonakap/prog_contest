#pragma comment(linker, "/STACK:65777216")
 
#include<cassert>
#include <algorithm>
#include <iostream>
#include <string>
#include<sstream>
#include<string.h>
#include <cstdio>
#include <complex>
#include <vector>
#include <bitset>
#include <cmath>
#include <queue>
#include<stack>
#include <set>
#include <map>
#include<ctime>
#include<list>

using namespace std;
 
typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;
typedef unsigned long long ull;
 
#define FOR(i,a,b) for (int i(a); i < (b); i++)
#define REP(i,n) FOR(i,0,n)
#define SORT(v) sort((v).begin(),(v).end())
#define UN(v) sort((v).begin(),(v).end()),v.erase(unique(v.begin(),v.end()),v.end())
#define CL(a,b) memset(a,b,sizeof(a))
#define pb push_back

bool OUTPUT_TO_FILE = 0;

bool DEBUG;

struct Node{
	int l,r;
	bool null;
	ll add,sum,totsum;
	Node *lf;
	Node *rg;
	Node(){lf=rg=0;l=r=0;totsum=add=sum=0;null=0;}
};

Node *buildTree(int l,int r){
	Node *curr = new Node();
	curr->l = l;
	curr->r = r;
	if(l!=r){
		curr->lf = buildTree(l,(l+r)/2);
		curr->rg = buildTree((l+r)/2+1,r);
	}
	return curr;
}

ll getSum(Node *curr){
	if(curr->null) return 0;
	return curr->sum + curr->add * (curr->r - curr->l+1);
}
ll getTotSum(Node *curr){
	if(curr->null) return 0;
	return curr->totsum + curr->add * ((curr->r - curr->l+1)*(curr->r - curr->l+2)/2);
}
void update(Node *curr){
	if(curr->null){
		curr->sum=0;
		curr->totsum=0;
	}else{
		curr->sum = getSum(curr->lf) + getSum(curr->rg);
		curr->totsum = getTotSum(curr->lf) + getTotSum(curr->rg) + getSum(curr->lf) * (curr->rg->r - curr->rg->l + 1);
	}
}

void push(Node *curr){
	if(curr->null){
		if(curr->lf){
			curr->rg->null=curr->lf->null=true;
			curr->lf->sum = curr->lf->totsum = curr->lf->add = 0;
			curr->rg->sum = curr->rg->totsum = curr->rg->add = 0;
		}
		curr->sum = curr->totsum = curr->add = 0;
		curr->null = 0;
	}
}

void addVal(Node *curr,int l,int r, ll val){
	if(r < curr->l || l > curr->r) return;
	if(curr->null) push(curr);
	if(l<=curr->l && curr->r<=r){
		curr->add += val;
	}else{
		addVal(curr->lf, l, r, val);
		addVal(curr->rg, l, r, val);
		update(curr);
	}
}

void nullVal(Node *curr, int l, int r){
	if(r < curr->l || l > curr->r) return;
	//if(curr->null) return;
	if(l <= curr->l && curr->r <= r){
		curr->null = true;
		curr->sum=0;
		curr->totsum=0;
		curr->add=0;
	}else{
		if(curr->add){
			curr->lf->add += curr->add;
			curr->rg->add += curr->add;
			curr->add = 0;
		}

		nullVal(curr->lf, l, r);
		nullVal(curr->rg, l, r);
		update(curr);
	}
}

ll getSum(Node *curr, int upto){
	if(curr->null) return 0;
	if(upto < curr->l) return 0;
	if(curr->r <= upto) return getSum(curr);
	return getSum(curr->lf, upto) + getSum(curr->rg, upto) + curr->add * (upto - curr->l + 1);
}


ll getSumSum(Node *curr, int upto){
	if(curr->null) return 0;
	if(upto < curr->l) return 0;
	if(curr->r <= upto) return getTotSum(curr) + getSum(curr)*(upto - curr->r);
	ll t1 = getSumSum(curr->lf, upto);
	ll t2 = getSumSum(curr->rg, upto);
	ll num = upto - curr->l + 1;
	ll add = num * (num+1) / 2 * curr->add;
	return t1 + t2 + add;
}

long long data[250001];
void A( int st, int nd ) {
    for( int i = st; i <= nd; i++ ) data[i] = data[i] + (i - st + 1);
}
void B( int st, int nd ) {
    for( int i = st; i <= nd; i++ ) data[i] = data[i] + (nd - i + 1);
}
void C( int st, int nd, int x ) {
    for( int i = st; i <= nd; i++ ) data[i] = x;
}
long long S( int st, int nd ) {
    long long res = 0;
    for( int i = st; i <= nd; i++ ) res += data[i];
    return res;
}

const char *sx="ABCS";

int main(){
#ifdef LocalHost
    freopen("input.txt","r",stdin);
	if(OUTPUT_TO_FILE) freopen("output.txt","w",stdout);
#endif

	Node *root = buildTree(0, 250001);

	int tc;
	//cin>>tc;
    tc=100;
	REP(TC,tc){
		char type;int st,en;
		//scanf(" %c %d %d",&type,&st,&en);
        type=sx[rand()%4];
        en=rand()%10+1;
        st=rand()%en+1;
		if(type=='A'){
			addVal(root, st, en, 1);
			addVal(root, en+1, en+1, -(en-st+1));
			//A(st,en);
		}
		if(type=='B'){
			addVal(root, st, st, en - st + 1);
			addVal(root, st + 1, en + 1, -1);
			//B(st,en);
		}
		if(type=='C'){
			int x;
			//scanf("%d",&x);
            x=rand()%10;
			ll t = getSum(root, en + 1);
			addVal(root, st, st, x - getSum(root, st));
			if(st+1<=en) nullVal(root, st+1, en);
			addVal(root, en+1, en+1, t - getSum(root, en + 1));
			//C(st,en,x);
		}
		if(type=='S'){
            assert(S(st,en)==getSumSum(root, en) - getSumSum(root, st - 1));
            //printf("%Ld\n",getSumSum(root, en) - getSumSum(root, st - 1));
        }
	}

#ifdef LocalHost
	if(!OUTPUT_TO_FILE) cout<<endl<<endl<<"TIME: "<<clock()<<endl;
#endif
    return 0;
}
