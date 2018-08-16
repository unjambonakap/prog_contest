#include<iostream>
#include<set>
#include<queue>
#include<cmath>
#include<cassert>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>

using namespace std;

typedef vector<string> vs;
typedef pair<int,int> pii; 
typedef  vector<int> vi;



#define FOR(i,a,b) for (int i=(a); i<(b); ++i)
#define REP(i,n) FOR(i,0,n)
#define MP make_pair
#define ALL(a) (a).begin(),(a).end()
#define pb push_back
#define ST first
#define ND second

void checkmin(int &a, int b){if (a>b) a=b;}

const int maxn=1111;
const int maxm=111111;

struct interval{
	int sz, a, b;
	interval(int sz, int a, int b):sz(sz),a(a),b(b){}
	bool operator<(const interval &e)const{
		if (sz!=e.sz) return sz<e.sz;
		if (b!=e.b) return b>e.b;
		return a>e.a;
	}
};

struct event{
	int t, type, id;
	event(int t, int type, int id):t(t),type(type),id(id){}
	bool operator<(const event &e)const{
		if (t!=e.t) return t>e.t;
		if (type!=e.type) return type<e.type;
		return id>e.id;
	}
};

set<interval> list, list2;
set<pii> space[maxn];
priority_queue<event> q;

int pos[maxm], sz[maxm], wh[maxm], served[maxm];
int C[maxn], empty[maxn];
int n, m;
int ta[maxm], wa[maxm], ea[maxm];
double res=0;

void addinterval(int a, int b, int c){
	if (a>b) return;

	if (a==0&&b==C[c]-1){ empty[c]=1; return;}
	if (a==0 || b==C[c]-1) list2.insert(interval(b-a+1,a,c));
	else list.insert(interval(b-a+1,a,c));
	space[c].insert(MP(a,b));
}

void removeinterval(int a, int b, int c){

    //printf("removing interval %d %d %d\n", a, b , c);
	if (a==0&&b==C[c]-1) assert(0);
	if (a==0 || b==C[c]-1) assert(list2.find(interval(b-a+1,a,c))!=list2.end()), list2.erase(interval(b-a+1,a,c));
    else assert(list.find(interval(b-a+1,a,c))!=list.end()), list.erase(interval(b-a+1,a,c));
    assert(space[c].find(MP(a,b))!=space[c].end());
	space[c].erase(MP(a,b));
}


int findslot(int a, int tx){
	set<interval>::iterator ita, itb;
	REP(i,n) if (empty[i]&&C[i]>=sz[a]){
        //printf("%d is free at %d\n", i, tx);
		empty[i]=0;
        pos[a]=0; wh[a]=i;
		addinterval(sz[a],C[i]-1,i);
		goto found;
	}

	ita=list.end();
	itb=list2.end();
	if (ita!=list.begin()) --ita;
	if (itb!=list2.begin()) --itb;
    //if (itb!=list2.end()) printf("find interval %d %d %d\n", itb->sz, itb->a, itb->b);
    //if (ita!=list.end()) printf("find interval %d %d %d\n", ita->sz, ita->a, ita->b);


	if (ita==list.end() && itb==list2.end()) return 0;
	else if (itb==list2.end()){
		interval x=*ita;
        if (x.sz<sz[a]) return 0;
		int u=x.a+(x.sz-sz[a])/2;
        pos[a]=u; wh[a]=x.b;

		removeinterval(x.a,x.a+x.sz-1, x.b);
		addinterval(x.a,u-1,x.b);
		addinterval(u+sz[a],x.a+x.sz-1,x.b);
	}else if (ita==list.end()){
		interval x=*itb;
        if (x.sz<sz[a]) return 0;
		removeinterval(x.a,x.a+x.sz-1, x.b);
        wh[a]=x.b;
        //printf("fuuu here %d %d %d\n", x.sz, x.a, x.b);
		if (x.a==0) addinterval(x.a+sz[a],x.a+x.sz-1,x.b), pos[a]=0;
        else addinterval(x.a,x.a+x.sz-sz[a]-1,x.b),pos[a]=x.a+x.sz-sz[a];
	}else{
		interval x=*ita, y=*itb;
        if (x.sz<sz[a] && y.sz<sz[a]) return 0;
		int u=(x.sz-sz[a])/2, v=y.sz-sz[a];
		if (v>=u){
			x=y;
			removeinterval(x.a,x.a+x.sz-1, x.b);
            wh[a]=x.b;
			if (x.a==0) addinterval(x.a+sz[a],x.a+x.sz-1,x.b), pos[a]=0;
			else addinterval(x.a,x.a+x.sz-sz[a]-1,x.b),pos[a]=x.a+x.sz-sz[a];
		}else{
            u+=x.a;
            pos[a]=u; wh[a]=x.b;
			removeinterval(x.a,x.a+x.sz-1, x.b);
			addinterval(x.a,u-1,x.b);
			addinterval(u+sz[a],x.a+x.sz-1,x.b);
		}
	}
found:
	res+=1.*sz[a]*(wa[a]-tx+ta[a])/wa[a];
    served[a]=1;

    assert(pos[a]!=-1);
    assert(wh[a]!=-1);
    //printf("going on %d %d\n", pos[a], wh[a]);
    //printf("%d can start eating at %d\n", a, tx);
    //puts("");
    q.push(event(tx+ea[a],0,a));
	return 1;
}

void go1(event e){
    int x=e.id;
    int lb, ub;
    lb=pos[x], ub=pos[x]+sz[x]-1;

    set<pii> &u=space[wh[x]];
    set<pii>::iterator next, prev;
    next=u.lower_bound(MP(pos[x],0));

    if (next==u.begin()) prev=u.end();
    else prev=next, --prev;

    if (prev!=u.end() && prev->ND==pos[x]-1) lb=prev->ST;
    else prev=u.end();

    if (next!=u.end() && next->ST==pos[x]+sz[x]) ub=next->ND;
    else next=u.end();

    pii tmpa, tmpb;
    tmpa=tmpb=MP(-1,-1);

    if (prev!=u.end()) tmpa=*prev;
    if (next!=u.end()) tmpb=*next;
    if (tmpa.ST!=-1) removeinterval(tmpa.ST,tmpa.ND,wh[x]);
    if (tmpb.ST!=-1) removeinterval(tmpb.ST,tmpb.ND,wh[x]);
    addinterval(lb,ub,wh[x]);
}


int main(){
    int T;
    cin>>n>>m>>T;
    REP(i,n) cin>>C[i], addinterval(0,C[i]-1,i);
    memset(wh,-1,sizeof(wh));
    memset(pos,-1,sizeof(pos));

    queue<int> waiting;

    REP(step,m){
        scanf(" %d%d%d%d", ta+step, sz+step, wa+step, ea+step);
        while(!q.empty() && q.top().t<=ta[step]){
            int ot=q.top().t;
            while(!q.empty()&&q.top().t==ot && q.top().type==1){
                event e=q.top(); q.pop();
                int x=e.id;
                if (!served[x]) res+=-sz[x], served[x]=-1;
            }

            while(!q.empty()&&q.top().t==ot && q.top().type==0){
                event e=q.top(); q.pop();
                go1(e);
            }
            while(waiting.size()){
                if (served[waiting.front()]>=0 && !findslot(waiting.front(),ot)) break;
                waiting.pop();
            }

        }

        if (waiting.size() || !findslot(step,ta[step])){
            //printf("PUSH %d\n", ta[step]+wa[step]);
            waiting.push(step), q.push(event(ta[step]+wa[step]+1,1,step));
        }
    }

    while(!q.empty()){
        int ot=q.top().t;
        if (ot==T) break;
        while(!q.empty()&&q.top().t==ot && q.top().type==1){
            event e=q.top(); q.pop();
            int x=e.id;
            if (!served[x]) res+=-sz[x], served[x]=-1;
        }

        //printf("fuuu here at time %d >> %d\n", ot, waiting.size());
        while(!q.empty()&&q.top().t==ot && q.top().type==0){
            event e=q.top(); q.pop();
            go1(e);
        }
        while(waiting.size()){
            if (served[waiting.front()]>=0 && !findslot(waiting.front(),ot)) break;
            waiting.pop();
        }

    }

    //REP(i,m) printf("%d ", served[i]); puts("");
    REP(i,m) if (!served[i]) res-=sz[i];
    int sum=0;
    REP(i,m) sum+=sz[i];
    printf("%.15lf\n", res/sum);

    return 0;
}


