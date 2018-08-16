#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <cassert>


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


#include "matching.hpp"

vector<pii> get_matching(vector<pii> edges, int nv){
	vector<pii> match, path;
	int i, count;


	count = 0;
	while(1){
		count++;

		path=find_augmenting_path(match, edges, nv);
		if (SZ(path) == 0)
			return match;
		
		match=augment_matching(match, path, nv);

	}
}

vector<int> get_blossom(int a, int b, int *parent, int nv){
	vector<int> blossom;
	stack<int> pta, ptb;
	int i, j, l;


	while(a != -1){
		pta.push(a);
		a=parent[a];
	}
	while(b != -1){
		ptb.push(b);
		b=parent[b];
	}
	while(!(pta.empty() || ptb.empty())){
		if (pta.top() != ptb.top())
			break;
		l = pta.top();
		pta.pop();
		ptb.pop();
	}

	blossom.pb(l);
	while(!pta.empty()){
		blossom.pb(pta.top());
		pta.pop();
	}

	while(!ptb.empty()){
		pta.push(ptb.top());
		ptb.pop();
	}

	while(!pta.empty()){
		blossom.pb(pta.top());
		pta.pop();
	}
	return blossom;

}

vector<pii> augment_matching(vector<pii> match, vector<pii> ap, int nv){
	int i, j, **tbe;

	tbe=(int**)malloc(sizeof(int*)*nv);

	REP(i, nv){
		tbe[i]=(int*)malloc(sizeof(int)*nv);
		memset(tbe[i], 0, sizeof(int)*nv);
	}
		

	REP(i, SZ(ap))
		tbe[ap[i].first][ap[i].second]=1, tbe[ap[i].second][ap[i].first]=1;

	REP(i, SZ(match))
		tbe[match[i].first][match[i].second]^=1, tbe[match[i].second][match[i].first]^=1;
	match.clear();
	REP(i, nv)
		FOR(j, i, nv)
		if (tbe[i][j])
			match.pb(pii(i, j));

	REP(i, nv)
		free(tbe[i]);
	free(tbe);
	return match;

}

vector<pii> find_augmenting_path(vector<pii> match, vector<pii> edges, int nv){
	int i, j, k, l;
	int **tbe, *matched, *parent, *change, **visitede, *visitedv, *root, *dist;
	int inner;
	pii p;


	matched=(int*)malloc(sizeof(int)*nv);
	root=(int*)malloc(sizeof(int)*nv);
	dist=(int*)malloc(sizeof(int)*nv);
	parent=(int*)malloc(sizeof(int)*nv);
	change=(int*)malloc(sizeof(int)*nv);


	tbe=(int**)malloc(sizeof(int*)*nv);
	visitede=(int**)malloc(sizeof(int*)*nv);

	REP(i, nv){
		tbe[i]=(int*)malloc(sizeof(int)*nv);
		visitede[i]=(int*)malloc(sizeof(int)*nv);
		memset(tbe[i], 0, sizeof(int)*nv);
		memset(visitede[i], 0, sizeof(int)*nv);
	}


	memset(matched, -1, sizeof(int)*nv);
	REP(i, SZ(match))
		matched[match[i].first]=match[i].second, matched[match[i].second]=match[i].first, visitede[match[i].first][match[i].second]=visitede[match[i].second][match[i].first]=1;
	

	REP(i, SZ(edges))
		tbe[edges[i].first][edges[i].second]=tbe[edges[i].second][edges[i].first]=1;
	
	
	queue<int> q;


	memset(root, -1, sizeof(int)*nv);

	REP(i, nv)
		if (matched[i] == -1)
			q.push(i), root[i]=i, dist[i]=0;

	memset(parent, -1, sizeof(int)*nv);
	while(!q.empty()){
		int s=q.front();
		q.pop();

		REP(j, nv) if (tbe[s][j] && !visitede[s][j]){

			if (root[j] == -1){
				if (matched[j] != -1){
					root[j] = root[matched[j]] = root[s];
					dist[j]=dist[s]+1;
					dist[matched[j]]=dist[j]+1;
					parent[j]=s, parent[matched[j]]=j;
					q.push(matched[j]);
				}

			}else{
				if (dist[j]%2 == 1)
					continue;
				if (root[j] != root[s]){
					int a, b;
					a=j, b=s;
					stack<int> sa;
					vector<int> path;
					queue<int> sb;

					while(a != -1)
						sa.push(a), a=parent[a];
					

					while(b != -1)
						sb.push(b), b=parent[b];

					while(!sa.empty())
						path.pb(sa.top()), sa.pop();
					while(!sb.empty())
						path.pb(sb.front()), sb.pop();


					vector<pii> ap;
					REP(k, SZ(path)-1)
						ap.pb(pii(path[k], path[k+1]));
					




					free(parent);
					free(matched);
					free(change);
					free(root);
					free(dist);

					REP(k, nv)
						free(tbe[k]), free(visitede[k]);

					free(visitede);
					free(tbe);
					return ap;



				}else{
					vector<int> blossom=get_blossom(s, j, parent, nv);

					vector<pii> nm, ne;
					REP(k, nv)
						change[k]=k;
					REP(k, SZ(blossom))
						change[blossom[k]]=blossom[0];

					REP(k, SZ(match))
						if (change[match[k].first] != change[match[k].second])
							nm.pb(pii(change[match[k].first], change[match[k].second]));
						
						
					memset(dist, 0, sizeof(int)*nv);
					REP(k, SZ(edges))
						if (change[edges[k].first] != change[edges[k].second]){
							if (change[edges[k].first] == blossom[0]){
							   	if (dist[change[edges[k].second]])continue;
								dist[change[edges[k].second]]=1;
							}

							if (change[edges[k].second] == blossom[0]){
							   	if (dist[change[edges[k].first]])continue;
								dist[change[edges[k].first]]=1;
							}
							ne.pb(pii(change[edges[k].first], change[edges[k].second]));
						}
						
						
						



					vector<pii> npath = find_augmenting_path(nm, ne, nv);


					if (SZ(npath) == 0){
						free(parent);
						free(matched);
						free(change);
						free(root);
						free(dist);

						REP(k, nv)
							free(tbe[k]), free(visitede[k]);
						free(tbe);
						free(visitede);


						return npath;
					}

					vector<pii> path;
					REP(k, SZ(npath)){
						if (npath[k].first == blossom[0] || npath[k].second == blossom[0]){
							int a, b;
							b=blossom[0];
							if (npath[k].first == blossom[0])
								a=npath[k].second;
							else
								a=npath[k].first;
							if (tbe[a][b])
								path.pb(pii(a, b));
							else{
								REP(l, SZ(blossom)) if (tbe[a][blossom[l]]){
									b=blossom[l];

									assert(matched[b] != -1);

									path.pb(pii(a, b));

									if (matched[b] == parent[b]){
										while(b != blossom[0])
											path.pb(pii(b, parent[b])), b=parent[b];
									}else{
										int c;
										c = s;
										while(c != blossom[0] && c != b)
											path.pb(pii(c, parent[c])), c=parent[c];

										path.pb(pii(s, j));
										c=j;
										while(c != b && c != blossom[0])
											path.pb(pii(c, parent[c])), c=parent[c];

									}
									
									break;
								}


							}
										
							


						}else
							path.pb(npath[k]);

					}

					free(parent);
					free(matched);
					free(change);
					free(root);
					free(dist);

					REP(k, nv)
						free(tbe[k]), free(visitede[k]);
					free(tbe);
					free(visitede);



					return path;



				}



			}


			visitede[s][j]=visitede[j][s]=1;
		}
	}
	free(parent);
	free(matched);
	free(change);
	free(root);
	free(dist);

	REP(k, nv)
		free(tbe[k]), free(visitede[k]);
	free(tbe);
	free(visitede);



	return vector<pii>();




}





	//
	//	REP(i, nv) if (matched[i] == -1){
	//		queue<pii> q;
	//
	//
	//		q.push(pii(i,-1));
	//		while(!q.empty()){
	//			p=q.front();
	//			q.pop();
	//
	//			jtree[p.first]=0;
	//			parent[p.first]=p.second;
	//
	//			REP(j, nv) if (tbe[p.first][j] ){
	//				if (j == p.second || j == p.first)continue;//j => child of p.second 
	//				if (jtree[j] == 1);//j inner vertex => do nothing
	//				else if (jtree[j] == 0){//j in tree, outer vertex
	//					// => flowered planted tree => 
	//
	//					vector<int> blossom = get_blossom(j, p.first, parent, nv);
	//
	//					assert(SZ(blossom)>0);
	//
	//					REP(k, nv)
	//						change[k]=k;
	//					REP(k, SZ(blossom))
	//						change[blossom[k]]=blossom[0];
	//
	//					vector<pii> nm, ne;
	//
	//					REP(k, SZ(match))
	//						if (change[match[k].first] != change[match[k].second])
	//							nm.pb(pii(change[match[k].first], change[match[k].second]));
	//					REP(k, SZ(edges))
	//						if (change[edges[k].first] != change[edges[k].second])
	//							ne.pb(pii(change[edges[k].first], change[edges[k].second]));
	//
	//					nm=find_augmenting(nm, ne, nv);
	//
	//					
	//					if (SZ(nm) == 0)
	//						return match;
	//					
	//
	//					REP(k, SZ(nm)){
	//						if (nm[k].first == blossom[0] || nm[k].second == blossom[0]){
	//							int tipa, tipb;
	//							if (nm[k].first == blossom[0])
	//								tipa=nm[k].first;
	//							else
	//								tipa=nm[k].second;
	//
	//							REP(l, SZ(blossom))
	//								if (tbe[tipa][blossom[k]]){
	//									tipb=blossom[k];
	//									break;
	//								}
	//							
	//							for(l=1; l < SZ(blossom); l+=2){
	//								tipa=(tipb+l)%SZ(blossom);
	//								nm.pb(pii(blossom[tipa], blossom[(tipa+1)%SZ(blossom)]));
	//
	//							}
	//
	//							return nm;
	//						}
	//					}
	//					return match;
	//
	//
	//				}else{//j not in planted tree
	//					if (matched[j] == -1){
	//						
	//						// found augmenting path
	//						k=p.first;
	//						matched[j]=k, matched[k]=j;
	//						while(parent[k] != -1){
	//							j=parent[k], k=parent[j];
	//							matched[j]=k, matched[k]=j;
	//						}
	//						CLR(match);
	//						REP(j, nv)
	//							if (j < matched[j])
	//								match.pb(pii(j, matched[j]));
	//
	//						free(parent);
	//						free(jtree);
	//						free(matched);
	//						free(change);
	//
	//						REP(j, nv)
	//							free(tbe[j]);
	//						free(tbe);
	//
	//						return match;
	//
	//
	//
	//					}else{ // can increase planted tree J
	//						jtree[j]=1, parent[j]=p.first;
	//						jtree[matched[j]]=0, parent[matched[j]]=j;
	//						q.push(pii(matched[j], j));
	//					}
	//
	//
	//
	//				}
	//			}
	//			//if we go there without adding vertex to tree, we have a start of hungarian tree
	//






