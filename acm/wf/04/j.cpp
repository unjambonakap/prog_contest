#include<iostream>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cassert>
#include<cstring>


using namespace std;

typedef long double ld;
typedef pair<int,int>		pii;
typedef vector<int> vi;
typedef pair<ld,int> pdi;
typedef pair<ld,ld> pdd;

#define FOR(i,a,b)		for(int i=(a);i<(b);i++)
#define REP(i,n)		FOR(i,0,n)
#define SORT(v)			sort((v).begin(),(v).end())
#define pb			push_back
#define ST first
#define ND second
#define MP make_pair
#define ALL(a) (a).begin(),(a).end()

const int maxn=111;
const ld eps=1e-9;
const ld eps2=1e-9;
ld xa[maxn], ya[maxn];
int nc[maxn];

ld crossp(ld a, ld b, ld c, ld d){return a*d-c*b;}
struct line{
	ld a, b;
	ld x, y;
	line(ld a, ld b, ld x, ld y):a(a),b(b),x(x),y(y){}
};

int cmp(pdd a, pdd b){
	if (fabs(a.ND-b.ND)<eps2) return a.ST>b.ST+eps2;
	return a.ND>b.ND+eps2;
}
int intersect(line &la, line &lb, ld &xo, ld &yo){
	ld M[2][3];

	M[0][0]=la.a; M[0][1]=-lb.a; M[0][2]=lb.x-la.x;
	M[1][0]=la.b; M[1][1]=-lb.b; M[1][2]=lb.y-la.y;
	if (fabs(M[0][0])<eps) REP(i,3) swap(M[0][i],M[1][i]);
	ld cx=M[0][0];
    assert(fabs(cx)>eps);
	//assert(fabs(M[0][0])>eps);
	REP(i,3) M[0][i]/=cx;
	cx=M[1][0];
	REP(i,3) M[1][i]-=M[0][i]*cx;
    assert(fabs(M[1][1])>eps);

	//if (fabs(M[1][1])<eps) return 0;
	M[1][2]/=M[1][1];
	xo=M[1][2]*lb.a+lb.x;
	yo=M[1][2]*lb.b+lb.y;
	return 1;
}
ld dist(ld a, ld b){return sqrt(a*a+b*b);}


//ans: 41 27 32
int main(){
	freopen("traffic.in", "r", stdin);
	//freopen("traffic.out", "w", stdout);
	int na, nb;
	int tn=0;
	while(cin>>na>>nb,na||nb){
		printf("Trial %d:", ++tn);

		vector<pdd> tb;
		REP(i,na) scanf(" %Lf%Lf", xa+i,ya+i), tb.pb(MP(xa[i],ya[i]));
		sort(ALL(tb),cmp);
		REP(i,na) xa[i]=tb[i].ST, ya[i]=tb[i].ND;
		REP(i,na) REP(j,i) assert(dist(xa[i]-xa[j],ya[i]-ya[j])>eps2);

		//REP(i,na) printf("%d >> %Lf %Lf\n", i, xa[i], ya[i]);

		memset(nc,0,sizeof(nc));
		int fd=0;
        vector<vector<pair<pdd,double> > > cnd;

		REP(step,nb){
            cnd.resize(cnd.size()+1);
			ld xu, yu, xv, yv;
			int N;
			scanf(" %d", &N);
			scanf(" %Lf%Lf%Lf%Lf\n", &xu,&yu,&xv,&yv);
            printf("READING %Lf %Lf %Lf %Lf\n", xu, yu, xv, yv);
			ld bestx, besty=-1e9, bestd;

			int fdb=0;
			vi bestcan(na,0);
			if (!N){
				//if (dist(xu-xv,yu-yv)>eps2) fd=1;
				fd=1;
			
				continue;
			}
            printf("AAAAAAAAAAAAAAA\n");
			REP(i,na){
				int ok=1;
				vi can(na,0);
				//if (fabs(crossp(xa[i]-xu,ya[i]-yu,xv-xu,yv-yu))<eps2) continue;
				line la(-(ya[i]-yu),xa[i]-xu,(xa[i]+xu)/2,(ya[i]+yu)/2);
				line lb(-(ya[i]-yv),xa[i]-xv,(xa[i]+xv)/2,(ya[i]+yv)/2);
				ld xo, yo;
				if (!intersect(la,lb,xo,yo)) continue;
				ld D=dist(xo-xu,yo-yu);
				assert(fabs(D-dist(xa[i]-xo,ya[i]-yo))<eps);
				assert(fabs(D-dist(xu-xo,yu-yo))<eps);
				assert(fabs(D-dist(xv-xo,yv-yo))<eps);

				int cnt=0;
				ld AA=-1e9, BB=-1e9;
                int cnta=0;
				REP(j,na){
					ld dx=dist(xo-xa[j],yo-ya[j]);
					if (dx<=D+eps2){
						if (fabs(dx-D)<eps2) ++cnta;
						if (dx+eps2>D && j>i) continue;
                        
						++cnt;
						can[j]=1;
						if (yo>BB+eps || (fabs(yo-BB)<eps && xo>AA)) AA=xo, BB=yo;
					}

				}
                //printf("%Lf %Lf %Lf >>> %d ((%d >> %d\n", xo, yo, D, cnt, N, cnta);
                if (step==0 && i!=5) continue;
                cnd.back().pb(MP(MP(xo,yo),D));
                if (step==0 && i==5){
                    REP(j,na){
                        ld dx=dist(xo-xa[j],yo-ya[j]);
                        if (dx+10>D && dx-10<D) printf("%Lf %Lf >>> %Lf (%Lf xx %d\n", xa[j], ya[j], dx, D, j);
                    }
                    printf(">> %d (%d\n", cnt, N);
                }
                if (step==0 && i==13) printf(">> %d (%d\n", cnt, N);
				if (cnt==N){
                    assert(cnta==1);
				//	printf("%d %d %d\n", step, i, cnt);

                    int old[maxn];
                    memcpy(old,nc,sizeof(old));
                    REP(i,na) if (can[i]) ++old[i];
                    vi res(nb+1,0);
                    REP(i,na) ++res[old[i]];
                    //if (step==0 && res[0]!=41) continue;
                    //printf("FUUU %d (( %d\n", cnt, N);
					//printf("%Lf %Lf %Lf\n", xo, yo, D);
                    //printf("FUU %Lf  %Lf\n", AA, BB);
                    REP(i,nb+1) printf("  %d", res[i]); puts("");
                    puts("");
				//	REP(j,na) printf("%d ", can[j]); puts("");
				//	REP(j,na) printf("%Lf ", dist(xa[j]-xo,ya[j]-yo)); puts("");
					fdb=1;
					if (BB>besty+eps || (fabs(besty-BB)<eps && AA>bestx)) bestx=AA, besty=BB, bestd=D, bestcan=can;
				}
			}
            printf("CHOOSE %Lf %Lf %Lf\n", bestx,besty,bestd);
			if (!fdb) fd=1;
			else{
                int cntx=0;
                REP(i,na) cntx+=bestcan[i];
                cout<<cntx<<endl;
                REP(i,na) if (bestcan[i]) ++nc[i];
            }
			vi res(nb+1,0);
			REP(i,na) ++res[nc[i]];
			REP(i,nb+1) printf("  %d", res[i]); puts("");
			
		}

        REP(i,cnd[0].size()) REP(j,cnd[1].size()){
            int u[3]={0};
            int cnta=0, cntb=0;
            REP(k,na){
                int cnt=0;
                double xo=cnd[0][i].ST.ST, yo=cnd[0][i].ST.ND, D=cnd[0][i].ND;
                ld dx=dist(xo-xa[k],yo-ya[k]);
                if (dx<=D+eps+1) ++cnt, ++cnta;
                xo=cnd[1][j].ST.ST, yo=cnd[1][j].ST.ND, D=cnd[1][j].ND;
                dx=dist(xo-xa[k],yo-ya[k]);
                if (dx<=D+eps+1) ++cnt, ++cntb;
                ++u[cnt];

            }
            if (u[0]!=41 || u[1]!=27) continue;
            printf("FUUU %d %d\n",i,j);
            printf("ON %Lf %Lf xx %Lf %Lf\n", cnd[0][i].ST.ST, cnd[0][i].ST.ND, cnd[1][j].ST.ST, cnd[1][j].ST.ND);
            printf("%d %d %d\n", u[0], u[1], u[2]);
            printf("%d %d\n", cnta, cntb);
            puts("");

        }

		if (fd) puts("  Impossible");
		else{
			vi res(nb+1,0);
			REP(i,na) ++res[nc[i]];
			REP(i,nb+1) printf("  %d", res[i]); puts("");
		}
		puts("");

	}
	return 0;
}



