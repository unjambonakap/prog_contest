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
#define FORV(i, b, a) for(i = (b); i > (a); i--)
#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#define ALL(a) (a).begin(), (a).end()
#define SZ(a) (a).size()
#define pb push_back
#define ll long long

using namespace std;
typedef pair<int,int> pii;

#define WIN 1000000


class Node;

double p, q;
int m, x;
vector<vector<Node*> > nodes;

class Node{
	public:
		Node(double _prob, int _mem, int _depth, int _root = 0){
			prob = _prob, mem = _mem, root = _root;
			f = left = right = NULL;
			depth = _depth;
		}
		Node();
		double prob;
		int mem, root, depth;
		double min;
		bool success;
		struct Node *left, *right, *f;



};

void fillNode(Node *r){
	Node *a, *b;
	if (r->depth >= nodes.size())
		nodes.pb(vector<Node*>());
	nodes[r->depth].pb(r);

	if (r->depth == m)
		return;
	

	a = new Node(r->prob * p, r->mem | (1 << r->depth), r->depth + 1);
	a->success = 1;
	b = new Node(r->prob * q, r->mem, r->depth + 1);
	b->success = 0;

	a->f = b->f = r;
	r->left = a, r->right = b;
	fillNode(a);
	fillNode(b);
}

void dfs(Node *r){
	if (r == NULL)
		return;
	if (r->depth==3)
	printf("Node: success %d, depth %d with prob %lf\n", r->success, r->depth, r->prob);
	dfs(r->left);
	dfs(r->right);

}


double solve(){
	double prob, cp;
	ll i, j, k;
	Node *root;

	if (x >= WIN)
		return 1.;

	nodes.clear();
	root = new Node(1, 0, 0, 1);

	fillNode(root);
	double temp;

	prob=0;
	FOR(i, 1, 1LL << nodes.back().size()){
		REP(j, nodes.size()){
			REP(k, nodes[j].size())
				nodes[j][k]->min=0;
		}

		temp=0;
		for(j = 0; j < nodes.back().size(); j += 2){
			if (i & 1 << j)
				nodes.back()[j]->min = WIN, temp+=nodes.back()[j]->prob;
			if (i & 1 << (j+1))
				nodes.back()[j+1]->min = WIN, temp+=nodes.back()[j+1]->prob;
		}
		if (temp <= prob)continue;

		FORV(j, nodes.size()-1, 0){
			for(k=0; k < nodes[j].size(); k+=2){
				nodes[j-1][k/2]->min = (MAX(nodes[j][k]->min, nodes[j][k+1]->min)+nodes[j][k+1]->min)/2;
			}
		}
		assert(temp <= 1.00001);
		if (x >= nodes[0][0]->min)
			prob=MAX(prob, temp);
		


	}

	return prob;

}



int main(){
	int i, j;
	int T;

	scanf("%d", &T);
	REP(i, T){
		scanf("%d %lf %d", &m, &p, &x);
		q = 1 - p;
		printf("Case #%d: %.7lf\n", i + 1, solve());


		

	}


	return EXIT_SUCCESS;
}

