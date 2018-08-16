#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

#define SIZE(X) ((int)(X.size()))//NOTES:SIZE(
#define LENGTH(X) ((int)(X.length()))//NOTES:LENGTH(
#define MP(X,Y) make_pair(X,Y)//NOTES:MP(
typedef long long int64;//NOTES:int64
typedef unsigned long long uint64;//NOTES:uint64
#define two(X) (1<<(X))//NOTES:two(
#define twoL(X) (((int64)(1))<<(X))//NOTES:twoL(
#define contain(S,X) (((S)&two(X))!=0)//NOTES:contain(
#define containL(S,X) (((S)&twoL(X))!=0)//NOTES:containL(
const double pi=acos(-1.0);//NOTES:pi
const double eps=1e-11;//NOTES:eps

double sqr(double x)
{
	return x*x;
}
double getS(double R,double x)
{
	double y=sqrt(sqr(R)-sqr(x));
	double p=atan2(y,x);
	double s1=p*R*R/2.0;
	double s2=x*y/2.0;
	return R*R*pi/4.0-(s1-s2);
}
double getS(double R,double s,double t)
{
	return getS(R,t)-getS(R,s);
}
double solve(double R0,double R,double w,double d)
{
	double result=0;
	int M=(int)ceil(R/d)+10;
	double side=(d-w);
	for (int x=0;x<M;x++)
		for (int y=0;y<M;y++)
		{
			double x1=x*d+w/2.0;
			double y1=y*d+w/2.0;
			double x2=x1+side;
			double y2=y1+side;
			if (sqr(x1)+sqr(y1)>=sqr(R)-eps)
				continue;
			if (sqr(x2)+sqr(y2)<=sqr(R)+eps) 
			{
				result+=side*side;
				continue;
			}
			bool tl=(sqr(x1)+sqr(y2)<=sqr(R));
			bool br=(sqr(x2)+sqr(y1)<=sqr(R));
			if (tl && br) 
			{
				double x0=sqrt(sqr(R)-sqr(y2));
				result+=side*side-((x2-x0)*y2-getS(R0,x0,x2));
			}
			else if (tl && !br)
			{
				double x0=sqrt(sqr(R)-sqr(y2));
				double x3=sqrt(sqr(R)-sqr(y1));
				result+=side*(x0-x1)+(getS(R0,x0,x3)-(x3-x0)*y1);
			}
			else if (!tl && br)
			{
				result+=getS(R0,x1,x2)-side*y1;
			}
			else if (!tl && !br)
			{
				double x0=sqrt(sqr(R)-sqr(y1));
				result+=getS(R0,x1,x0)-(x0-x1)*y1;
			}
//			printf("%0.6lf\n",result);
		}
	return result*4;
}
double solve(double f,double R,double t,double r,double g)
{
	if (t+f>=R-eps) return 1;
	if (f+f>=g-eps) return 1;
	double result=solve(R-t-f,R-t-f,r+f+f,g+r);
	result/=(sqr(R)*pi);
	return 1.0-result;
}
int main()
{
//	freopen("..\\C.in","r",stdin);
	freopen("..\\C-large.in","r",stdin);
	freopen("..\\C-large.out","w",stdout);
	double f,R,t,r,g;
	int testcase;
	scanf("%d",&testcase);
	for (int caseId=1;caseId<=testcase;caseId++)
	{
		scanf("%lf%lf%lf%lf%lf",&f,&R,&t,&r,&g);
		double result=solve(f,R,t,r+r,g);
		printf("Case #%d: %0.12lf\n",caseId,result);
	}
	return 0;
}
