#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <bitset>
#include <cctype>
#include <sstream>

#define mp make_pair
#define pb push_back
#define all(v) (v).begin(),(v).end()
#define sz(v) ((int)(v.size()))

using namespace std;

typedef long long int64;
typedef pair<int,int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<string> vs;

template<class T> T abs(T x){return x>0 ? x:(-x);}
template<class T> T sqr(T x){return x*x;}

vector<string> v;
int val[1000];
int n;
bool u[1000];

int calc()
{
	int d[100];
	memset(d,0,sizeof(d));
	int res=0;
	for(int i=0;i<n;i++){
		if(u[i]) continue;
		d[i]=1;
		for(int j=0;j<i;j++)
			if(!u[j] && val[j]<val[i])
				d[i]=max(d[i],d[j]+1);
		res=max(res,d[i]);
		printf("%d => %d\n", i, d[i]);
	}
	return res;
}

int main()
{
	int nc;
	char ts[1000];
	gets(ts);
	sscanf(ts,"%d",&nc);
	for(int ic=0;ic<nc;ic++){
		printf("Case #%d: ",ic+1);
		gets(ts);
		stringstream ss(ts);
		v.clear();
		string s;
		n=0;
		while(ss >> s){
			n++;
			v.push_back(s);
		}
		gets(ts);
		stringstream tt(ts);
		for(int i=0;i<n;i++)
			tt >> val[i];
		memset(u,0,sizeof(u));
		int rn=calc();
		string res="";
		while(1){
			int ind=-1;
			for(int i=0;i<n;i++)
				if(!u[i]){
					u[i]=true;
					if(calc()==rn){
						if(ind==-1 || v[ind]>v[i])
							ind=i;
					}
					u[i]=false;
				}
			if(ind==-1) break;
			u[ind]=true;
			if(sz(res)) res+=" ";
			res+=v[ind];
		}
		cout << res << "\n";
	}
	return 0;
}
