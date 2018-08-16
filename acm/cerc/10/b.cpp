#include<iostream>
#include<cassert>
#include<cmath>
#include<memory.h>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<set>
#include<algorithm>

using namespace std;

typedef pair<int,int>		pii;
typedef long long		ll;
typedef long double ld;
#define MP make_pair

#define FOR(i,a,b)		for(int i=(a);i<(b);i++)
#define REP(i,n)		FOR(i,0,n)
#define pb			push_back
#define CL(a,b)			memset(a,b,sizeof a)
#define SORT(v)			sort((v).begin(),(v).end())

const int maxn=3*111111;
const ld inf=1e15;
const ld eps=1e-9;
int aa[maxn], bb[maxn], cc[maxn];

struct point{
	ld x, y;
	int id;
	point(){}
	point(ld x, ld y, int id):x(x),y(y),id(id){}
	bool operator<(const point &p)const{
		if (fabs(p.x-x)<eps) return y<p.y;
		return x<p.x;
	}
	bool operator==(const point &p)const{
		return fabs(p.x-x)<eps&&fabs(p.y-y)<eps;}
};

int crossp(ld xa, ld ya, ld xb, ld yb){return xa*yb-ya*xb<-eps;}
ld dist(ld x, ld y){return x*x+y*y;}

ld closest(int la, ld x, ld y, ld oxa, ld oxb){
    //line > aa[la]*x+bb[la]*y+cc[la]=0

    ld xa=oxa, xb=oxb;
    if (oxa<-inf/2) xa=xb-1;
    else if (oxb>inf/2) xb=xa+1;

    ld ya=(aa[la]*xa+cc[la])/-bb[la];
    ld yb=(aa[la]*xb+cc[la])/-bb[la];
    ld dy=yb-ya, dx=xb-xa;
    ld u=(x-xa)/dx, v=-dy/dx;

    ld k=(ya-y+dy*u)/(dx-dy*v);
    ld xu=x-k*dy, yu=y+k*dx;
    if (xu>=oxa && xu<=oxb) return k*k*(dx*dx+dy*dy);
    return min(dist(x-xa,y-ya),dist(x-xb,y-yb));
}

ld a[2][3];
pair<ld,ld> intersection(int la, int lb){
    a[0][0] = aa[la];a[0][1] = bb[la];a[0][2] = -cc[la];
    a[1][0] = aa[lb];a[1][1] = bb[lb];a[1][2] = -cc[lb];
    REP(i,2){
        if(i==0 && fabs(a[0][0]) < fabs(a[1][0])){
            REP(j,3) swap(a[0][j],a[1][j]);
        }
        assert(fabs(a[i][i])>eps);
        ld k = a[i][i];
        REP(j,3) a[i][j]/=k;
        REP(j,2)if(j!=i){
            k = a[j][i];
            REP(q,3) a[j][q]-=k*a[i][q];
        }
    }


    //printf("%d %d %d XXX %d %d %d\n", aa[la], bb[la], cc[la], aa[lb], bb[lb], cc[lb]);
    //printf("intersect %d %d >> %Lf %Lf\n", la, lb, a[0][2], a[1][2]);
    return make_pair(a[0][2],a[1][2]);

}

void go(vector<point> &pl, vector<point> &lhull, vector<point> &uhull){
    SORT(pl);
    pl.resize(unique(pl.begin(),pl.end())-pl.begin());

    //REP(i,pl.size()) printf("(%Lf %Lf) ", pl[i].x, pl[i].y); puts("");

    int na=0;
    REP(i,pl.size()){
        if (na>=1 && fabs(pl[i].x-uhull[na-1].x)<eps && pl[i].y>uhull[na-1].y) uhull.pop_back(), --na;
        while(na>=2 && crossp(pl[i].x-uhull[na-2].x,pl[i].y-uhull[na-2].y,
                    uhull[na-1].x-uhull[na-2].x,uhull[na-1].y-uhull[na-2].y)) uhull.pop_back(), --na;
        uhull.pb(pl[i]); ++na;
    }

    na=0;
    for (int i=pl.size()-1; i>=0; --i){
        if (na>=1 && fabs(pl[i].x-lhull[na-1].x)<eps) if (pl[i].y<lhull[na-1].y) lhull.pop_back(), --na;
        while(na>=2 && crossp(pl[i].x-lhull[na-2].x,pl[i].y-lhull[na-2].y,
                    lhull[na-1].x-lhull[na-2].x,lhull[na-1].y-lhull[na-2].y)) lhull.pop_back(), --na;
        lhull.pb(pl[i]); ++na;
    }
    reverse(lhull.begin(),lhull.end());
    reverse(uhull.begin(),uhull.end());
}


int main(){
    int tn; cin>>tn;
    REP(ti,tn){
        int n; cin>>n;
        REP(i,n) scanf(" %d%d%d", aa+i,bb+i,cc+i);
        if (n==1){printf("0\n"); continue;}

        vector<point> pl;
        REP(i,n) pl.pb(point(-ld(aa[i])/bb[i],ld(cc[i])/bb[i],i));


        vector<point> lhull, uhull;
        go(pl,uhull,lhull);
        //REP(i,lhull.size()){
        //    int x=lhull[i].id;
        //    printf("%d %d %d >> %Lf %Lf\n", aa[x],bb[x],cc[x], lhull[i].x, lhull[i].y);
        //}
        //puts("");
        //REP(i,uhull.size()){
        //    int x=uhull[i].id;
        //    printf("%d %d %d >> %Lf %Lf\n", aa[x],bb[x],cc[x], uhull[i].x, uhull[i].y);
        //}

        vector<pair<ld,ld> > ua, ub;
        ua.pb(MP(-inf,inf));
        ub.pb(MP(-inf,inf));
        REP(i,lhull.size()-1) ua.pb(intersection(lhull[i].id,lhull[i+1].id));
        REP(i,uhull.size()-1) ub.pb(intersection(uhull[i].id,uhull[i+1].id));
        ua.pb(MP(inf,inf));
        ub.pb(MP(inf,inf));

        ///puts("");
        ///REP(i,ua.size()) printf(" %Lf %Lf\n", ua[i].first, ua[i].second);
        ///puts("");
        ///REP(i,ub.size()) printf(" %Lf %Lf\n", ub[i].first, ub[i].second);
        double res=1e100;
        if (lhull.size()==1 && uhull.size()==1){
            res=uhull[0].y-lhull[0].y;
            res*=res;


        }
        FOR(i,1,ua.size()-1){
            int T=0, H=uhull.size()-1;
            //printf("FUFU %d\n", i);
            while(T+5<H){
                int R=(T+2*H)/3, L=(2*T+H)/3;
                double resa=closest(uhull[L].id,ua[i].first,ua[i].second,ub[L].first,ub[L+1].first);
                double resb=closest(uhull[R].id,ua[i].first,ua[i].second,ub[R].first,ub[R+1].first);
                res=min(res,min(resa,resb));
                if (resa<resb) H=R-1;
                else T=L+1;
            }
            //cout<<res<<endl;
            FOR(j,T,H+1){
                double resx=closest(uhull[j].id,ua[i].first,ua[i].second,ub[j].first,ub[j+1].first);
                //cout<<resx<<endl;
                res=min(res,resx);
            }
        }
        //puts("");
        //puts("");
        FOR(i,1,ub.size()-1){
            int T=0, H=lhull.size()-1;
            while(T+5<H){
                int R=(T+2*H)/3, L=(2*T+H)/3;
                double resa=closest(lhull[L].id,ub[i].first,ub[i].second,ua[L].first,ua[L+1].first);
                double resb=closest(lhull[R].id,ub[i].first,ub[i].second,ua[R+1].first,ua[R+1].first);
                res=min(res,min(resa,resb));
                if (resa<resb) H=R-1;
                else T=L+1;
            }
            FOR(j,T,H+1){
                double resx=closest(lhull[j].id,ub[i].first,ub[i].second,ua[j].first,ua[j+1].first);
                res=min(res,resx);
            }
        }
        printf("%.10lf\n", res);
    }
    return 0;
}



