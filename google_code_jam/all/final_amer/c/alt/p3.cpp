#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <assert.h>


#define REP(i,n) for(i = 0; i < (n); i++)
#define REPV(i, n) for (i = (n) - 1; i >= 0; i--)
#define FOR(i, a, b) for(i = (a); i < (b); i++)
#define FORV(i, a, b) for(i = (b) - 1; i >= (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define pb push_back
#define SZ(a) ((a).size())
#define two(x) (1 << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()
#define SWAP(a,b,c) (c=a, a=b, b=c)

#define ll long long
using namespace std;
typedef pair<int,int> pii;

#define MAX_M 10000
#define MAX_Q 30
#define NA 4

class State{
	public:
		State(){}
		State(double _f, int *_state, int _low){f=_f, low=_low;memcpy(state, _state, sizeof(state)), proc=false;}
		~State(){}
		bool operator<(const State &s)const{return this->f > s.f;}
		double f;
		int state[MAX_Q];
		int low;
		bool proc;

};



double q[MAX_Q][NA];

int m, nq;



double solve(){
	int i, j, k;
	double d, e;
	double sum = 0, nf;
	if (m >= pow(NA, nq))return 1.;

	priority_queue<State> qa, pa;
	priority_queue<State> *a, *b, *c;

	a = &qa, b = &pa;
	State s;

	s.f=1, s.low=0;
	REP(i, nq)
		s.state[i]=0, s.f*=q[i][0];

	a->push(s);
	if (m >= pow(NA, nq))
		return 1.;

	while(1){
		bool change = false;

		while(!a->empty()){
			s=a->top();a->pop();
			if (s.proc==true){ b->push(s);continue; }
			s.proc=true;
			b->push(s);
			change=true;
			FOR(i, s.low, nq){
				int os=s.state[i];
				if (os==NA-1 || q[i][os]==0)continue;
				s.state[i]++;
				nf=s.f/q[i][os]*q[i][os+1];
				assert(nf<=1.0001);
				if (SZ(*b) >= m && nf >= b->top().f){
					b->pop();
					b->push(State(nf, s.state, i));
				}else if (SZ(*b) < m)
					b->push(State(nf, s.state, i));
				
				s.state[i]--;
			}
		}
		SWAP(a,b,c);
		if (!change)
			break;
	}

	while(SZ(*a) > m)
		a->pop();
	sum=0;
	while(!a->empty()){
		s=a->top();a->pop();
		sum+=s.f;
	assert(sum <= 1.0001);
	}




	return sum;

}

int main(){
	int i, j, k;
	int T;

	scanf("%d", &T);
	REP(i, T){
		scanf("%d %d", &m, &nq);
		REP(j, nq){
			REP(k, NA)
				scanf("%lf", &q[j][k]);
			sort(&q[j][0], &q[j+1][0]);
			reverse(&q[j][0], &q[j+1][0]);
		}

		printf("Case #%d: %.7lf\n", i+1, solve());
	}


	return EXIT_SUCCESS;
}

