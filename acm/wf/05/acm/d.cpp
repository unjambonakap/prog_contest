//PROG: wtf
//LANG: C++
//ID: raveman.n2

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<memory.h>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

typedef pair<int,int>		pii;
typedef vector<int>		vi;

#define FOR(i,a,b)		for(int i=(a);i<(b);i++)
#define REP(i,n)		FOR(i,0,n)
#define CL(a,b)			memset(a,b,sizeof a)
#define SORT(v)			sort((v).begin(),(v).end())
#define UN(v)			SORT(v),(v).erase(unique((v).begin(),(v).end()),(v).end())
#define pb			push_back

vi v[20];

vi shuffle(vi v){
	vi res;
	REP(i,26) res.pb(v[26+i]),res.pb(v[i]);
	return res;
}

vi undo(vi v){
	vi res;
	REP(i,26) res.pb(v[2*i+1]);
	REP(i,26) res.pb(v[2*i]);
	return res;
}

int best = 1000;
vector<pii> err,bb;

void go(vi &curr,int current,int alreadydid=0){
	if(current==0){
		if(curr==v[0] && best > alreadydid){
			best = alreadydid;
			bb=err;
		}
		return;
	}
	int diff = 0;
	REP(i,52) if(curr[i]!=v[current][i]) diff++;
	if(alreadydid+(diff+1)/2 >= best) return;
	if((diff+1)/2 > current) return;
	
	vi t = undo(curr);
	go(t,current-1,alreadydid);
	
	FOR(i,1,52)if(curr[i]!=v[current][i] || curr[i-1]!=v[current][i-1]){
		vi t = curr;
		swap(t[i-1],t[i]);
		t=undo(t);
		err.pb(pii(current,i));
		go(t,current-1,alreadydid+1);
		err.pop_back();
	}
}

int main(){	
	REP(i,52) v[0].pb(i);
	FOR(i,1,20) v[i]=shuffle(v[i-1]);
	
	freopen("wtf.in","r",stdin);
	freopen("wtf.out","w",stdout);
	int n;
	cin>>n;
	REP(TC,n){
		printf("Case %d\n",TC+1);
		
		vi curr(52);
		REP(i,52) scanf("%d",&curr[i]);
		
		for(int i=1;i<=10;i++){
			best=1000;
			go(curr,i);
			if(best!=1000){
				printf("Number of shuffles = %d\n",i);
				if(best==0) puts("No error in any shuffle");
				else{
					reverse(bb.begin(),bb.end());
					REP(j,bb.size())
						printf("Error in shuffle %d at location %d\n",bb[j].first,bb[j].second-1);
				}
				break;
			}
		}
		
		puts("");	
	}
	//cout<<clock()/double(CLOCKS_PER_SEC)<<endl;
	return 0;
}
