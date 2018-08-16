#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstring>
#include <cassert>

using namespace std;

const int MAX_N=51;
int n, m;
vector<int> ca, cb;
int mp[MAX_N*2+2][MAX_N*2+2];
int mpa[MAX_N*2+2][MAX_N*2+2];
int rn[MAX_N*2+2][MAX_N*2+2];
int rna[MAX_N*2+2][MAX_N*2+2];
int parent[MAX_N*2+2];
int s, t;
int q[MAX_N*2+2];


//int dfs(int p){
//	int i, j, k;
//
//	if (p==t)return 1;
//	for (i=0; i<=t; ++i){
//		if (rn[p][i]!=0 && parent[i]==-1){
//			parent[i]=p;
//			if (dfs(i))return 1;
//		}
//	}
//	return 0;
//
//}
bool cmpa(int a, int b){ return mp[s][a]-rn[s][a]>mp[s][b]-rn[s][b]; }
bool cmpb(int a, int b){ return mp[a+n][t]-rn[a+n][t]>mp[b+n][t]-rn[b+n][t]; }

int find_flow(){
	int i, j, k, p, c;
	c=0;
	//build initial flow

	int ind1[n], ind2[n];
	for (i=0; i<n; ++i)
		ind1[i]=i;
	for (i=0; i<m; ++i)
		ind2[i]=i;
	bool ok=true;
	while(ok){
		sort(ind1, ind1+n, cmpa);
		int ia, ja;
		ok=false;
		for (ia=0; ia<n; ++ia){
			i=ind1[ia];
			sort(ind2, ind2+m, cmpb);
			for (ja=0; ja<m; ++ja){
				j=ind2[ja];
				if (rn[s][i]==mp[s][i])break;
				if (rn[j+n][t]==mp[j+n][t] || mp[i][j+n]-rn[i][j+n]==0)continue;
				ok=true;
				rn[s][i]++, --rn[i][s];
				rn[i][j+n]++, --rn[j+n][i];
				rn[j+n][t]++, --rn[t][j+n];
			}
		}

	}



	while(1){

		memset(parent, -1, sizeof(parent));
		parent[s]=-2;
		int qb, qe, e;
		qb=qe=0;
		q[qe++]=s;
		while(qb<qe){
			e=q[qb++];
			for (i=0; i<=t; ++i){
				if (parent[i]==-1 && mp[e][i]-rn[e][i]>0){
					parent[i]=e;
					q[qe++]=i;
					if (i==t)goto end;
				}
			}
		}
end:

//		if (!dfs(s))break;

		if (parent[t]!=-1){
			j=t;
			p=parent[j];
			int c;
			while(p!=-2){
				assert(p!=-1);
				++rn[p][j], --rn[j][p];
				j=p, p=parent[j];
			}
		}else break;
	}
//	for (i=0; i<n; ++i){
//		for (j=0; j<m; ++j)
//			printf("%d ", rn[i][j+n]);
//
//		printf("\n");
//	}


	for (i=0; i<n; ++i)
		if (mp[s][i]-rn[s][i]>0)return 0;
	return 1;
}

vector<string> solve(vector<int> _ca, vector<int> _cb){
	ca=_ca, cb=_cb;
	n=ca.size(); m=cb.size();
	int i, j, k;
	vector<string> res;
	s=n+m+1;
	t=s+1;

	int la, lb;
	la=lb=0;
	for (i=0; i<n; ++i){
		if (ca[i]>cb.size())return res;
		la+=ca[i];
	}
	for (i=0; i<m; ++i){
		if (cb[i]>ca.size())return res;
		lb+=cb[i];
	}

	if (la!=lb)return res;

	memset(mp, 0, sizeof(mp));
	for (i=0; i<n; ++i){
		mp[s][i]=ca[i];
		for (j=0; j<m; ++j)
			mp[i][j+n]=1;
	}
	for (i=0; i<m; ++i) mp[i+n][t]=cb[i];

	if (!find_flow())
		return res;
	

	//for (i=0; i<n; ++i){
	//	for (j=0; j<m; ++j)
	//		printf("%d ", rn[i][j+n]);

	//	printf("\n");
	//}

	memcpy(rna, rn, sizeof(rn));

	int r, c;
	r=0;
	c=-1;
	memset(mpa, 0, sizeof(mpa));
	for (r=0; r<n; ++r){
		for (c=0; c<m; ++c){
			mp[r][c+n]=0;
			if (rna[r][c+n]==0)
				continue;
			
			memcpy(rn, rna, sizeof(rn));



			rn[r][c+n]=rn[c+n][r]=0;
			rn[s][r]--, rn[r][s]++, rn[c+n][t]--, rn[t][c+n]++;
			if (find_flow())
				memcpy(rna, rn, sizeof(rn));
			else{
				rna[r][c+n]=rna[c+n][r]=0;
				rna[s][r]--, rna[r][s]++, rna[c+n][t]--, rna[t][c+n]++;
				mpa[r][c+n]=1, mp[r][c+n]=0, --mp[s][r], --mp[c+n][t];
			}
	//		exit(0);

		}

	}
	res=vector<string>(n);
	for (i=0; i<n; ++i){
		for (j=0; j<m; ++j)
			res[i]+=string(1, mpa[i][j+n]+'0');
	}
	return res;


}

int main(){

	int tn, ti;
	int i, j;
	cin>>tn;
	for (ti=0; ti<tn; ++ti){
		cin>>n>>m;
		ca=vector<int>(n);
		cb=vector<int>(m);
		for (i=0; i<n; ++i)
			cin>>ca[i];
		for (i=0; i<m; ++i)
			cin>>cb[i];

		vector<string> res=solve(ca, cb);

		for (i=0; i<res.size(); ++i)
			cout<<res[i]<<endl;




	}

}









