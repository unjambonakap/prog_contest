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

bool queued[MAX_C][MAX_C];
char map[MAX_C+2][MAX_C+2];
int wc[MAX_C+2][MAX_C+2];

int pos[MAX_C][MAX_C];
int r, c;
int startx, starty, destx, desty;
int max_c;
std::priority_queue<State> q;

class State{
	public:
		State(){}
		State(int _x, int _y, int _cost){x = _x, y = _y, cost = _cost;}
		bool operator<(State const &a) const{return this->cost > a.cost;}
		int get_cost(){ return pos[x][y];}
		void set_queue(bool a){queued[x][y] = a;}
		int x, y, cost;

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

void set_wc(){
	int i, j, nx, ny, x, y, cost, k;

	std::queue<State*> list;
	State *s;

	memset(wc, -1, sizeof(wc));
	REP(i, r)
		REP(j, c){
			if (map[i][j] == EMPTY){
				
				REP(k, 4){
					move(j, i, &x, &y, k);
					if (map[y][x] == WALL){
						list.push(new State(j, i, 0));
						wc[j][i] = 0;
						break;
					}
				}
			}
		}
			

	while(!list.empty()){

		s = list.front();
		list.pop();

		x = s->x, y = s->y, cost = s->cost;
		delete s;
		cost++;

		REP(i, 4){

			move(x, y, &nx, &ny, i);
			if (map[ny][nx] != EMPTY || wc[nx][ny] != -1)
				continue;
			wc[nx][ny] = cost;
			list.push(new State(nx, ny, cost));
		}

	}
}


void next_wall(int x, int y, int *a, int *b, int dir){
	*a = x, *b = y;
	while(1){
		move(*a, *b, a, b, dir);
	   	if (map[*b][*a] == WALL)
			break;
	}
	move(*a, *b, a, b, inv(dir));
}
void update(int x, int y, int nc){
	bool *cur_q;
	int *cur;

	cur = &pos[x][y];
	cur_q = &queued[x][y];

	if (*cur == -1 || nc < *cur){
		*cur = nc;
		if (x == destx && y == desty)
			max_c = nc;

		if (*cur_q == 0){
			*cur_q = 1;
			
			q.push(State(x, y, nc));

		}
	}


}


int solve(){
	int i, j, k, l;
	int ret;
	int nx, ny;
	int step = 0;



	State s;

	set_wc();

	memset(pos, -1, sizeof(pos));
	memset(queued, 0, sizeof(queued));

	s = State(startx, starty, 0);
	pos[startx][starty] = 0;

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
				update(nx, ny, s.cost + 1);

			next_wall(s.x, s.y, &nx, &ny, i);


			update(nx, ny, s.cost + wc[s.x][s.y] + 1);

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

		//if (i != 4)continue;
		//REP(j, r){
		//	REP(k, c)
		//		printf("%c", map[j][k]);
		//	printf("\n");
		//}


			
		printf("Case #%d: ", i + 1);
		solve();
		printf("\n");





	}







	return EXIT_SUCCESS;
}


