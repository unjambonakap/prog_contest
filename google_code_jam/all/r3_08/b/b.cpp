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
#define pb push_back
#define ll long long

#define MAX_C 17
#define WALL '#'
#define CAKE 'X'
#define EMPTY '.'
#define START 'O'
#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define NONE 4

class State;

bool queued[MAX_C][MAX_C][5][MAX_C][MAX_C][5][MAX_C][MAX_C];
char map[MAX_C+2][MAX_C+2];
int r, c;
int startx, starty, destx, desty;
int pos[MAX_C][MAX_C][5][MAX_C][MAX_C][5][MAX_C][MAX_C];
int max_c;
std::priority_queue<State> q;

class State{
	public:
		State(){}
		State(int _x, int _y, int _da, int _xa, int _ya, int _db, int _xb, int _yb, int _cost){ 
			x = _x, y = _y, da = _da, xa = _xa, ya = _ya, db = _db, xb = _xb, yb = _yb, cost = _cost;
			if (da == NONE)
				xa = ya = 0;
			if (db == NONE)
				xb = yb = 0;
	   	}
		bool operator<(State const &a) const{return this->cost > a.cost;}
		int get_cost(){ return pos[x][y][da][xa][ya][db][xb][yb];}
		void set_queue(bool a){queued[x][y][da][xa][ya][db][xb][yb] = a;}
		int x, y, xa, ya, xb, yb, da, db, cost;

};




void move(int x, int y, int *a, int *b, int dir){
	*a = x, *b = y;
	if (dir == NORTH)
		(*b)++;
	else if (dir == SOUTH)
		(*b)--;
	else if (dir == EAST)
		(*a)--;
	else if (dir == WEST)
		(*a)++;
}

int inv(int dir){
	if (dir == SOUTH || dir == NORTH)
		return 1 - dir;
	return 2 + (3 - dir);

}


void next_wall(int x, int y, int *a, int *b, int dir){
	*a = x, *b = y;
	while(1){
		move(*a, *b, a, b, dir);
	   	if (map[*b][*a] == WALL)
			return;
	}
}
void update(int x, int y, int da, int xa, int ya, int db, int xb, int yb, int nc){
	bool *cur_q;
	int *cur;

	cur = &pos[x][y][da][xa][ya][db][xb][yb];
	cur_q = &queued[x][y][da][xa][ya][db][xb][yb];

	if (*cur == -1 || nc < *cur){
		*cur = nc;

		if (*cur_q == 0){
			*cur_q = 1;
			if (x == destx && y == desty){
				max_c = nc;
				//:printf("there %d %d %d %d %d %d %d %d\n", x, y, da, xa, ya, db, xb, yb);
			}
			
			q.push(State(x, y, da, xa, ya, db, xb, yb, nc));

		}
	}


}


int solve(){
	int i, j, k, l, da, db;
	int ret;
	int nx, ny;
	int step = 0;;



	State s;


	memset(pos, -1, sizeof(pos));
	memset(queued, 0, sizeof(queued));

	s = State(startx, starty, NONE, 0, 0, NONE, 0 ,0, 0);
	pos[startx][starty][NONE][0][0][NONE][0][0] = 0;

	q.push(s);

	max_c = -1;
	while(!q.empty()){
		s = q.top();
		q.pop();

		s.cost = s.get_cost();
		
		s.set_queue(false);

		if (max_c != -1 && s.cost >= max_c)
			continue;

		REP(i, 4){
			move(s.x, s.y, &nx, &ny, i);

			if (map[ny][nx] == EMPTY)
				update(nx, ny, s.da, s.xa, s.ya, s.db, s.xb, s.yb, s.cost + 1);
			else if (map[ny][nx] == WALL){

				if (s.da == NONE || s.db == NONE);
				else if (s.xa == nx && s.ya == ny){
					move(s.xb, s.yb, &nx, &ny, inv(s.db));
					update(nx, ny, s.da, s.xa, s.ya, s.db, s.xb, s.yb, s.cost + 1);
				}
				else if (s.xb == nx && s.yb == ny){
					move(s.xa, s.ya, &nx, &ny, inv(s.da));
					update(nx, ny, s.da, s.xa, s.ya, s.db ,s.xb, s.yb, s.cost + 1);
				}
			}


			next_wall(s.x, s.y, &nx, &ny, i);

			if (s.da == NONE)
				update(s.x, s.y, i, nx, ny, s.db, s.xb, s.yb, s.cost);
			else if (s.xb != nx || s.yb != ny)
				update(s.x, s.y, s.da, s.xa, s.ya, i, nx, ny, s.cost);

			if (s.db == NONE)
				update(s.x, s.y, s.da, s.xa, s.ya, i, nx, ny, s.cost);
			else if (s.xa != nx || s.ya != ny)
				update(s.x, s.y, i, nx, ny, s.db, s.xb, s.yb, s.cost);





		}


	}
	if (max_c  == -1)
		printf("THE CAKE IS A LIE");
	else
		printf("%d", max_c);

}

int main(){
	int i, j, k;
	int T;
	scanf("%d", &T);

	REP(i, T){

		scanf("%d %d", &r, &c);


		FOR(j, 1, r + 1){
			scanf("%s\n", map[j] + 1);
			FOR(k, 1, c + 1){
				if (map[j][k] == START)
					map[j][k] = EMPTY, startx = k, starty = j;
				else if (map[j][k] == CAKE)
					map[j][k] = EMPTY, destx = k, desty = j;
			}

		}
		
		c+= 2, r+= 2;
		REP(j, c)
			map[0][j] = map[r - 1][j] = WALL;
		REP(j, r)
			map[j][0] = map[j][c - 1] = WALL;
	//	REP(j, r){
	//		REP(k, c)
	//			printf("%c", map[j][k]);
	//		printf("\n");
	//	}


			
		printf("Case #%d: ", i + 1);
		solve();
		printf("\n");





	}







	return EXIT_SUCCESS;
}


