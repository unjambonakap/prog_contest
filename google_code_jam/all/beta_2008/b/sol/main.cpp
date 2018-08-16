#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cstdlib>

using namespace std;

#define sz(v) ((int)(v).size())
#define all(v) v.begin(), v.end()
#define pb push_back
#define mp make_pair
#define forn(i,n) for (int i=0; i<(n); i++)

typedef long long ll;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<string> vs;

template<class T>T abs(T x) { return (x>0) ? x : -x; }
template<class T>T sqr(T x) { return x*x;            }

int a[70][70];

int len(vs was, vs names) {
	int n=sz(was), m=sz(names);
	memset(a,0,sizeof(a));
	for (int i=1; i<=n; i++)
		for (int j=1; j<=m; j++) {
			if (was[i-1]==names[j-1]) 
				a[i][j]=a[i-1][j-1]+1;
			if (a[i-1][j]>a[i][j]) 
				a[i][j]=a[i-1][j];
			if (a[i][j-1]>a[i][j]) 
				a[i][j]=a[i][j-1];
		}
	return a[n][m];
}

int main()
{
	freopen("b.in","r",stdin);
	freopen("b.out","w",stdout);

	int tn;
	char buf[1000];	
	gets(buf);
	sscanf(buf,"%d",&tn);
	for (int tst=0; tst<tn; tst++) {
		printf("Case #%d: ",tst+1);
		gets(buf);
		string tmp=buf;
		istringstream in(tmp);
		vs names;
		string s;
		while (in>>s) names.pb(s);
		vs was=names;
		int n=sz(names);
		vi pr(n);
		gets(buf);
		tmp=buf;
		istringstream in1(tmp);
		for (int i=0; i<n; i++) {
			int t;
			in1>>t;
			pr[i]=t;
		}
		for (int i=0; i<n; i++)
			for (int j=i+1; j<n; j++)
				if (pr[i]>pr[j])
					swap(pr[i],pr[j]), swap(names[i],names[j]);
		
		int ans=len(was,names);
		vs cur=was; sort(all(cur));
		for (int i=0; i<sz(cur); i++) {
			vs w=was;
			int j=find(all(w),cur[i])-w.begin();
			w.erase(w.begin()+j);
			if (len(w,names)==ans) {
				cout<<cur[i]<<" ";
				was=w;
			}
		}
		cout<<endl;
	}

	return 0;
}
