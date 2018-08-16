//#define LOCAL
//#define DEBUG
#ifdef DEBUG
//#define PRINT
#endif

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
#include <ctime>
#include <stdarg.h>

/*
#include <emmintrin.h>
#include <pmmintrin.h>
#include <xmmintrin.h>
*/

using namespace std;

#define SIZE(A) ((int)A.size())
#define LENGTH(A) ((int)A.length())
typedef long long int64;
typedef unsigned long long uint64;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef pair<int,int> ipair;
#define MP(A,B) make_pair(A,B)
typedef vector<string> VS;
typedef vector<int> VI;
#define two(X) (1<<(X))
#define contain(S,X) ((S&two(X))>0)
const double pi=acos(-1.0);
inline int sqr(int x) { return x*x; }
inline double sqr(double x) { return x*x; }
template<class T> string toString(const T& x) { ostringstream sout; sout<<x; sout.flush(); return sout.str(); }

int TRACE(const char* s,...)
{
#ifdef PRINT
    va_list va;
    va_start(va,s);
    int ret=vprintf(s,va);
    va_end(va);
    fflush(stdout);
    return ret;
#else
    return 0;
#endif
}

int LOG(const char* s,...)
{
#ifdef PRINT
    va_list va;
    va_start(va,s);
    FILE *f=fopen("test.log","a");
    int ret=vfprintf(f,s,va);
    fclose(f);
    va_end(va);
    return ret;
#else
    return 0;
#endif
}

#ifdef DEBUG
#define ASSERT(_Expression) (void)((!!(_Expression)||(__assert((#_Expression),__LINE__),0)));
void __assert(const char *_Message,const unsigned _Line)
{
    printf("ASSERTION FAILED\n");
    printf("Message = %ls\n",_Message);
    printf("Line = %u\n",_Line);
    exit(0);
}
#endif

uint64 rdtsc()
{
#ifdef _MSC_VER
    __asm { rdtsc }
#else
    uint64 time;
    __asm__ volatile ("rdtsc" : "=A" (time));
    return time;
#endif
}
uint64 starttime_acrush=0;
uint64 timeused_acrush=0;
uint64 gettime()
{
    return rdtsc()-starttime_acrush+timeused_acrush;
}
#ifdef LOCAL
    #ifdef _MSC_VER
        #define TIMES_PER_SEC (1.75e9)
    #else
        #define TIMES_PER_SEC (1.6508566e9)
    #endif
#else
    #define TIMES_PER_SEC (3.589e9)
#endif

#ifdef LOCAL
class Timer
{
public:
    static uint64 timeUsed[1000];
    int id;
    uint64 startTime;
    Timer(int id=0)
    {
        this->id=id;
        startTime=rdtsc();
    }
    ~Timer()
    {
        timeUsed[id]+=(rdtsc()-startTime);
    }
    static void show()
    {
        for (int i=0;i<1000;i++) if (timeUsed[i]>0)
        {
            char str[100];
            sprintf(str,"%.6lf",timeUsed[i]/TIMES_PER_SEC);
            string s=str;
            if (LENGTH(s)<15) s=" "+s;
            TRACE("%4d %s\n",i,s.c_str());
        }
    }
};
uint64 Timer::timeUsed[1000]={0};

class Counter
{
public:
    static int cnt[1000];
    Counter(int id=0)
    {
        cnt[id]++;
    }
    ~Counter()
    {
    }
    static void show()
    {
        for (int i=0;i<1000;i++) if (cnt[i]>0)
            TRACE("Counter %d %d\n",i,cnt[i]);
    }
};
int Counter::cnt[1000]={0};
#endif

const int PARAM_INIT_NUM_WORKERS=1;
const int PARAM_SMALL_NUM_WORKERS=8;
const int PARAM_ADJUST_NUM_WORKERS_MAX_INC=3;
const int PARAM_ADJUST_NUM_WORKERS_BUFFER_SIZE=125;
const int PARAM_ADJUST_NUM_WORKERS_BUFFER_SIZE_MAX=150;
const int PARAM_ADJUST_NUM_WORKERS_BUFFER_SIZE_MAX_CUTROUND=100;
const int PARAM_ADJUST_NUM_WORKERS_CHECK_REALDATA_BUFFER=80;
const int PARAM_CLUSTER_SPLIT_DISTANCE=4;
const int PARAM_NON_SNOWS_TIMESTAMP_GAP=3;
const int PARAM_MIN_NEW_WORKER_PER_SNOW=1;
const int PARAM_MAX_IDLE_WORKERS_PER_CLUSTER=0;
const double PARAMS_PREDICTION_DAMPING=0.2;
const int PARAM_FINAL_OPT_ROUND=1900;
const int PARAM_FINAL_OPT_BUFFER_SIZE=40;
const int PARAM_KMEAN_ROUNDS=7;
const double PARAM_KMEAN_SHRINK_SIDE=2.6;
const double PARAM_KMEAN_SHRINK_SIDE_SMALL=2.3;
const double PARAM_KMEAN_SHRINK_SIDE_SMALL_LIMIT=5;
const double PARAM_KMEAN_SHRINK_SIDE_TINY=1.6;
const double PARAM_KMEAN_SHRINK_SIDE_TINY_LIMIT=3;

const double TIME_ADJUST_NUM_WORKERS=9*TIMES_PER_SEC;
const double TIME_MAIN_PATH_BEFORE_FINAL_ADJUST=6*TIMES_PER_SEC;
const double TIME_FINAL_ADJUST=2*TIMES_PER_SEC;
double timeleft_adjust_num_workers;
double timeleft_main_path_before_final_adjust;
double timeleft_final_adjust;

const double TIMELIMIT_CLOSETO_TIMEOUT=18*TIMES_PER_SEC;
const double TIMELIMIT_OVERALL=19*TIMES_PER_SEC;
const double TIMELIMIT_FINAL=19.8*TIMES_PER_SEC;

const int MAX_BOARD_SIZE=50;
const int MAX_NUM_CELLS=MAX_BOARD_SIZE*MAX_BOARD_SIZE;
const int MAX_NUM_WORKERS=100;
const int MAX_NUM_ROUNDS=2000;
const int oo=1000000000;
const int DELTA_X[]={-1,1,0,0};
const int DELTA_Y[]={0,0,-1,1};
const char DELTA_C[]={'U','D','L','R'};
const double PI=acos(-1.0);

struct Point
{
    int x,y;
    Point(int _x=0,int _y=0) { x=_x; y=_y; }
};
bool operator<(const Point& a,const Point& b)
{
    return (a.x!=b.x)?(a.x<b.x):(a.y<b.y);
}

#ifdef LOCAL
//setseed
int case_study_seed=5;
#else
int case_study_seed=-1;
#endif

int board_size;
int salary;
int snow_fine;
int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int snow_log[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int num_workers;
Point workers[MAX_NUM_WORKERS];
vector<Point> prev_workers_path[MAX_NUM_WORKERS];
int num_snows;
Point snows[MAX_NUM_CELLS];
int snow_idx[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int expected_max_num_workers;
int num_clusters;
int cluster_idx[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int cluster_size[MAX_NUM_WORKERS+2];
Point cluster_pts_all[MAX_NUM_WORKERS+2][MAX_NUM_CELLS];

int total_snow_fine;
int total_salary;

bool is_main_path;
bool closeto_timeout;

vector<int> saved_snow_falls[MAX_NUM_ROUNDS];
int current_round;
int first_snow_round;
int last_snow_round;
int max_no_snow_period;

struct State
{
    int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    int snow_log[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    int num_snow_falls;
    Point snow_falls[MAX_NUM_CELLS];
    int num_workers;
    Point workers[MAX_NUM_WORKERS];
    vector<Point> prev_workers_path[MAX_NUM_WORKERS];
    int total_snow_fine;
    int total_salary;

    void copy_from_global_var()
    {
        memcpy(board,::board,sizeof(board));
        memcpy(snow_log,::snow_log,sizeof(snow_log));
        num_workers=::num_workers;
        memcpy(workers,::workers,sizeof(workers));
        for (int i=0;i<num_workers;i++) prev_workers_path[i]=::prev_workers_path[i];
        total_snow_fine=::total_snow_fine;
        total_salary=::total_salary;
    }
    void copy_to_global_var()
    {
        memcpy(::board,board,sizeof(board));
        memcpy(::snow_log,snow_log,sizeof(snow_log));
        ::num_workers=num_workers;
        memcpy(::workers,workers,sizeof(workers));
        for (int i=0;i<num_workers;i++) ::prev_workers_path[i]=prev_workers_path[i];
        ::total_snow_fine=total_snow_fine;
        ::total_salary=total_salary;
    }
};
State tmp_state;
void save_state()
{
    tmp_state.copy_from_global_var();
}
void load_state()
{
    tmp_state.copy_to_global_var();
}

int cmp_adjust_round[MAX_NUM_WORKERS+1];
int cmp_adjust_score[MAX_NUM_WORKERS+1][MAX_NUM_ROUNDS+1];
State cmp_adjust_state[MAX_NUM_WORKERS+1];

struct BipartiMatching
{
    int nleft,nright;
    int cost[MAX_NUM_WORKERS][MAX_NUM_CELLS];

    int p1[MAX_NUM_WORKERS];
    int p2[MAX_NUM_CELLS];
    bool v1[MAX_NUM_WORKERS];
    bool v2[MAX_NUM_CELLS];
    int l1[MAX_NUM_WORKERS];
    int l2[MAX_NUM_CELLS];
    int que[MAX_NUM_WORKERS];
    int prev[MAX_NUM_WORKERS];
    int h[MAX_NUM_WORKERS];

    void solve()
    {
#ifdef DEBUG
        ASSERT(nleft<=MAX_NUM_WORKERS && nright<=MAX_NUM_CELLS);
#endif
        for (int i=0;i<nleft;i++) p1[i]=-1;
        for (int i=0;i<nright;i++) p2[i]=-1;
        for (int i=0;i<nleft;i++) l1[i]=oo;
        for (int i=0;i<nright;i++) l2[i]=0;
        for (int i=0;i<nleft;i++) for (int j=0;j<nright;j++) if (cost[i][j]<l1[i]) l1[i]=cost[i][j];
        for (int s=0;s<nleft;s++)
        {
            for (int i=0;i<nleft;i++) v1[i]=false;
            for (int i=0;i<nright;i++) v2[i]=false;
            int sizeq=0;
            que[sizeq++]=s;
            prev[s]=-1;
            v1[s]=true;
            for (int i=0;i<nleft;i++) h[i]=0;
            bool find_path=false;
            while (1)
            {
                int m=oo;
                for (int i=0;i<nleft;i++) if (v1[i] && h[i]<m) m=h[i];
                if (m>0)
                {
                    for (int cl=0;cl<sizeq;cl++) h[que[cl]]-=m;
                    for (int i=0;i<nleft;i++) if (v1[i]) h[i]-=m,l1[i]+=m;
                    for (int i=0;i<nright;i++) if (v2[i]) l2[i]-=m;
                }
                for (int cl=0;cl<sizeq;cl++)
                {
                    int v=que[cl];
                    if (h[v]>0) continue;
                    h[v]=oo;
                    for (int p=0;p<nright;p++) if (!v2[p])
                    {
                        int t=cost[v][p]-l1[v]-l2[p];
                        if (t==0)
                        {
                            v2[p]=true;
                            int u=p2[p];
                            if (u<0)
                            {
                                do { int t=p1[v]; p1[v]=p; p2[p]=v; v=prev[v]; p=t; } while (v>=0);
                                find_path=true;
                                break;
                            }
                            prev[u]=v;
                            v1[u]=true;
                            que[sizeq++]=u;
                        }
                        else if (t<h[v])
                            h[v]=t;
                    }
                    if (find_path) break;
                }
                if (find_path) break;
            }
        }
#ifdef DEBUG
        for (int i=0;i<nleft;i++) ASSERT(p1[i]>=0 && p2[p1[i]]==i);
#endif
    }
};
BipartiMatching bm;

struct BipartiMatchingMulti
{
    int nleft,nright;
    int cost[MAX_NUM_WORKERS][MAX_NUM_WORKERS];
    int dup[MAX_NUM_WORKERS];

    int c1[MAX_NUM_WORKERS],p1[MAX_NUM_WORKERS][MAX_NUM_WORKERS];
    int p2[MAX_NUM_WORKERS];
    bool v1[MAX_NUM_WORKERS];
    bool v2[MAX_NUM_WORKERS];
    int l1[MAX_NUM_WORKERS];
    int l2[MAX_NUM_WORKERS];
    int que[MAX_NUM_WORKERS];
    int prev[MAX_NUM_WORKERS];
    int h[MAX_NUM_WORKERS];

    void solve()
    {
#ifdef DEBUG
        ASSERT(nleft<MAX_NUM_WORKERS && nright<=MAX_NUM_WORKERS);
#endif
        for (int i=0;i<nleft;i++) c1[i]=0;
        for (int i=0;i<nright;i++) p2[i]=-1;
        for (int i=0;i<nleft;i++) l1[i]=oo;
        for (int i=0;i<nright;i++) l2[i]=0;
        for (int i=0;i<nleft;i++) for (int j=0;j<nright;j++) if (cost[i][j]<l1[i]) l1[i]=cost[i][j];
        for (int s=0;s<nleft;s++) while (c1[s]<dup[s])
        {
            for (int i=0;i<nleft;i++) v1[i]=false;
            for (int i=0;i<nright;i++) v2[i]=false;
            int sizeq=0;
            que[sizeq++]=s;
            prev[s]=-1;
            v1[s]=true;
            for (int i=0;i<nleft;i++) h[i]=0;
            bool find_path=false;
            while (1)
            {
                int m=oo;
                for (int i=0;i<nleft;i++) if (v1[i] && h[i]<m) m=h[i];
                if (m>0)
                {
                    for (int cl=0;cl<sizeq;cl++) h[que[cl]]-=m;
                    for (int i=0;i<nleft;i++) if (v1[i]) h[i]-=m,l1[i]+=m;
                    for (int i=0;i<nright;i++) if (v2[i]) l2[i]-=m;
                }
                for (int cl=0;cl<sizeq;cl++)
                {
                    int v=que[cl];
                    if (h[v]>0) continue;
                    h[v]=oo;
                    for (int p=0;p<nright;p++) if (!v2[p])
                    {
                        int t=cost[v][p]-l1[v]-l2[p];
                        if (t==0)
                        {
                            v2[p]=true;
                            int u=p2[p];
                            if (u<0)
                            {
                                while (v!=s)
                                {
                                    int new_p=prev[v]>>16;
                                    int new_v=prev[v]&65535;
                                    for (int i=0;i<c1[v];i++) if (p1[v][i]==new_p) { p1[v][i]=p; break; }
                                    p2[p]=v;
                                    p=new_p;
                                    v=new_v;
                                }
                                p1[s][c1[s]++]=p;
                                p2[p]=s;
                                find_path=true;
                                break;
                            }
                            else if (u!=v && !v1[u])
                            {
                                prev[u]=(p<<16)|v;
                                v1[u]=true;
                                que[sizeq++]=u;
                            }
                        }
                        else if (t<h[v])
                            h[v]=t;
                    }
                    if (find_path) break;
                }
                if (find_path) break;
            }
        }
    }
};
BipartiMatchingMulti bm2;

struct MaxMatching
{
    int nleft,nright,nedge;
    int head[MAX_NUM_CELLS];
    int point[MAX_NUM_WORKERS*MAX_NUM_CELLS];
    int next[MAX_NUM_WORKERS*MAX_NUM_CELLS];
    int p1[MAX_NUM_CELLS],p2[MAX_NUM_CELLS];
    bool visited[MAX_NUM_CELLS];

    void clear()
    {
        for (int i=0;i<nleft;i++) p1[i]=-1;
        for (int i=0;i<nright;i++) p2[i]=-1;
    }
    void init(int _nleft,int _nright)
    {
        nleft=_nleft;
        nright=_nright;
        nedge=0;
        for (int i=0;i<nleft;i++) head[i]=-1;
        clear();
    }
    void addedge(int u,int v)
    {
        point[nedge]=v,next[nedge]=head[u],head[u]=(nedge++);
    }
    bool find_path(int v)
    {
        for (int k=head[v];k>=0;k=next[k])
        {
            int p=point[k];
            if (!visited[p])
            {
                visited[p]=true;
                if (p2[p]<0 || find_path(p2[p]))
                {
                    p1[v]=p;
                    p2[p]=v;
                    return true;
                }
            }
        }
        return false;
    }
    int doMatch()
    {
        for (int i=0;i<nleft;i++) if (p1[i]<0)
        {
            for (int k=0;k<nright;k++) visited[k]=false;
            find_path(i);
        }
        int result=0;
        for (int i=0;i<nleft;i++) if (p1[i]>=0) result++;
        return result;
    }
};
MaxMatching mm;

inline bool is_inside(const Point &a)
{
    return a.x>=0 && a.x<board_size && a.y>=0 && a.y<board_size;
}
inline bool is_inside(int x,int y)
{
    return x>=0 && x<board_size && y>=0 && y<board_size;
}
inline int get_distance(const Point &a,const Point &b)
{
    return abs(a.x-b.x)+abs(a.y-b.y);
}
inline bool is_same(const Point &a,const Point &b)
{
    return a.x==b.x && a.y==b.y;
}
void init()
{
    memset(board,0,sizeof(board));
    memset(snow_log,0,sizeof(snow_log));
    total_snow_fine=total_salary=0;
}

int get_direction(const Point& src,const Point &dest)
{
    int dx=abs(src.x-dest.x);
    int dy=abs(src.y-dest.y);
    if (dx+dy==0) return -1;
    if (dx>=dy)
        return (src.x>dest.x)?0:1;
    else
        return (src.y>dest.y)?2:3;
}

void DFS_cluster(int x,int y,int idx)
{
    cluster_idx[x][y]=idx;
    for (int dx=-PARAM_CLUSTER_SPLIT_DISTANCE;dx<=PARAM_CLUSTER_SPLIT_DISTANCE;dx++)
        for (int e=PARAM_CLUSTER_SPLIT_DISTANCE-abs(dx),dy=-e;dy<=e;dy++)
        {
            int x2=x+dx,y2=y+dy;
#ifdef DEBUG
            ASSERT(abs(x-x2)+abs(y-y2)<=PARAM_CLUSTER_SPLIT_DISTANCE);
#endif
            if (x2>=0 && y2>=0 && x2<board_size && y2<board_size && board[x2][y2] && cluster_idx[x2][y2]<0) DFS_cluster(x2,y2,idx);
        }
}

int get_medium(int n,int a[])
{
    int s=0,d=0;
    for (int i=0;i<n;i++) s+=a[i];
    for (int i=0;i<n;i++)
    {
        if (d<=s/2 && d+a[i]>=s/2) return i;
        d+=a[i];
    }
    return n/2;
}

//DEBUG ONLY.
void show_board()
{
    char s[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    memset(s,'.',sizeof(s));
    for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) if (board[x][y]) s[x][y]='#';
    for (int i=0;i<num_workers;i++) s[workers[i].x][workers[i].y]='*';
    for (int x=0;x<board_size;x++)
    {
        for (int y=0;y<board_size;y++)
            printf("%c",s[x][y]);
        printf("\n");
    }
}

int get_root(int root[],int p)
{
    return (root[p]<0)?p:(root[p]=get_root(root,root[p]));
}

void gen_clusters()
{
#ifdef DEBUG
    Timer t5(5);
#endif
    memset(cluster_idx,255,sizeof(cluster_idx));
    if (num_snows==0) { num_clusters=0; return; }
    if (expected_max_num_workers==1 || closeto_timeout)
    {
        num_clusters=1;
        for (int i=0;i<num_snows;i++) cluster_idx[snows[i].x][snows[i].y]=0;
    }
    else
    {
        num_clusters=0;
        for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) if (board[x][y] && cluster_idx[x][y]<0)
        {
            DFS_cluster(x,y,num_clusters);
            num_clusters++;
        }
        if (num_clusters>expected_max_num_workers)
        {
            int *dst=new int[num_clusters*num_clusters];
            for (int i=0;i<num_clusters*num_clusters;i++) dst[i]=oo;
            vector<int> edges;
            for (int i=0;i<num_snows;i++) for (int j=i+1;j<num_snows;j++)
            {
                int a=cluster_idx[snows[i].x][snows[i].y];
                int b=cluster_idx[snows[j].x][snows[j].y];
                if (a>b) swap(a,b);
                int t=get_distance(snows[i],snows[j]);
                if (t<dst[a*num_clusters+b]) dst[a*num_clusters+b]=t;
            }
            edges.reserve(num_clusters*(num_clusters-1)/2);
            for (int i=0;i<num_clusters;i++) for (int j=i+1;j<num_clusters;j++)
                edges.push_back((dst[i*num_clusters+j]<<20)|(i<<10)|j);
            sort(edges.begin(),edges.end());
            int *root=new int[num_clusters];
            for (int i=0;i<num_clusters;i++) root[i]=-1;
            int nleft=num_clusters-expected_max_num_workers;
            for (int step=0;nleft>0 && step<SIZE(edges);step++)
            {
                int a=(edges[step]>>10)&1023;
                int b=edges[step]&1023;
                a=get_root(root,a);
                b=get_root(root,b);
                if (a==b) continue;
                root[a]=b;
                nleft--;
            }
            int *color=new int[num_clusters],cnt=0;
            for (int i=0;i<num_clusters;i++) if (root[i]<0) color[i]=(cnt++);
#ifdef DEBUG
            ASSERT(cnt==expected_max_num_workers);
#endif
            for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) if (cluster_idx[x][y]>=0)
                cluster_idx[x][y]=color[get_root(root,cluster_idx[x][y])];
            delete[] color;
            delete[] dst;
            delete[] root;
            num_clusters=expected_max_num_workers;
        }
    }
#ifdef DEBUG
    ASSERT(num_clusters<=expected_max_num_workers);
    for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) if (board[x][y])
    {
        ASSERT(cluster_idx[x][y]>=0 && cluster_idx[x][y]<num_clusters);
    }
#endif
    for (int i=0;i<num_clusters;i++) cluster_size[i]=0;
    for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) if (cluster_idx[x][y]>=0)
    {
        int idx=cluster_idx[x][y];
        cluster_pts_all[idx][cluster_size[idx]++]=Point(x,y);
    }
#ifdef DEBUG
    for (int i=0;i<num_clusters;i++) ASSERT(cluster_size[i]>0);
#endif
}

int get_estimate_cost(int idx,
                      int est_cluster_size,
                      vector<int> &cluster_workers,
                      int g[MAX_NUM_WORKERS][MAX_NUM_WORKERS])
{
    int m=SIZE(cluster_workers);
#ifdef DEBUG
    ASSERT(m>0 && est_cluster_size>0);
#endif
    int *p=&cluster_workers[0];
#ifdef DEBUG
    for (int i=0;i<m;i++) ASSERT(p[i]>=0 && p[i]<expected_max_num_workers);
#endif
    int d[MAX_NUM_WORKERS];
    for (int i=0;i<m;i++) d[i]=max(1,g[p[i]][idx]);
    sort(d,d+m);
    if (d[0]==10000) return 10000000;
    int s=0,left=est_cluster_size;
    for (int k=0,t=d[0];;t++)
    {
        for (;k<m && d[k]==t;k++);
        if (k>=left) { s+=left*t; break; }
        left-=k;
        s+=k*t;
    }
    return s;
}


int get_cut_distance(int idx,
                      int est_cluster_size,
                      vector<int> &cluster_workers,
                      int g[MAX_NUM_WORKERS][MAX_NUM_WORKERS])
{
    int m=SIZE(cluster_workers);
#ifdef DEBUG
    ASSERT(m>0 && est_cluster_size>0);
#endif
    int *p=&cluster_workers[0];
#ifdef DEBUG
    for (int i=0;i<m;i++) ASSERT(p[i]>=0 && p[i]<expected_max_num_workers);
#endif
    int d[MAX_NUM_WORKERS];
    for (int i=0;i<m;i++) d[i]=max(1,g[p[i]][idx]);
    sort(d,d+m);
    if (d[0]==10000) return 10000;
    int left=est_cluster_size;
    for (int k=0,t=d[0];;t++)
    {
        for (;k<m && d[k]==t;k++);
        if (k>=left) return t;
        left-=k;
    }
    return -1;
}

void run_sa_allocate_workers_to_clusters(int num_clusters,
                                         int max_cluster_size[],
                                         int real_cluster_size[],
                                         vector<int> cluster_workers[],
                                         int g[MAX_NUM_WORKERS][MAX_NUM_WORKERS])
{
    if (num_clusters<=1) return;
    int est_cost[MAX_NUM_WORKERS],cut_distance[MAX_NUM_WORKERS];
    for (int i=0;i<num_clusters;i++) est_cost[i]=get_estimate_cost(i,real_cluster_size[i],cluster_workers[i],g);
    for (int i=0;i<num_clusters;i++) cut_distance[i]=get_cut_distance(i,real_cluster_size[i],cluster_workers[i],g);
    for (int step=0;step<10;step++)
    {
        int total_cost=0;
        for (int i=0;i<num_clusters;i++) total_cost+=est_cost[i];
        for (int i=0;i<num_clusters;i++) if (SIZE(cluster_workers[i])>1)
            for (int j=0;j<SIZE(cluster_workers[i]);j++)
            {
                int key=cluster_workers[i][j];
                cluster_workers[i].erase(cluster_workers[i].begin()+j);
                int old_cost_i=est_cost[i];
                est_cost[i]=get_estimate_cost(i,real_cluster_size[i],cluster_workers[i],g);
#ifdef DEBUG
                ASSERT(est_cost[i]>=old_cost_i);
#endif
                int best_delta=-1,target=-1,new_cost_target=-1;
                for (int x=0;x<num_clusters;x++) 
                    if (SIZE(cluster_workers[x])<max_cluster_size[x] && (x==i || g[key][x]<cut_distance[x]))
                    {
                        cluster_workers[x].push_back(key);
                        int cost=(x==i)?old_cost_i:get_estimate_cost(x,real_cluster_size[x],cluster_workers[x],g);
                        cluster_workers[x].pop_back();
                        int delta=((est_cost[x]-cost)<<1);
#ifdef DEBUG
                        ASSERT(delta>=0);
#endif
                        if (x==i) delta++;
                        if (delta>best_delta) best_delta=delta,target=x,new_cost_target=cost;
                    }
#ifdef DEBUG
                ASSERT(target>=0);
                if (target==i) ASSERT(new_cost_target==old_cost_i);
#endif
                if (target==i)
                {
                    // no change.
                    cluster_workers[target].insert(cluster_workers[i].begin()+j,key);
                    est_cost[target]=new_cost_target;
                }
                else
                {
                    cluster_workers[target].push_back(key);
                    est_cost[target]=new_cost_target;
                    cut_distance[i]=get_cut_distance(i,real_cluster_size[i],cluster_workers[i],g);
                    cut_distance[target]=get_cut_distance(target,real_cluster_size[target],cluster_workers[target],g);
                }
            }
        for (int i=0;i<num_clusters;i++) for (int j=i+1;j<num_clusters;j++)
            for (int x=0;x<SIZE(cluster_workers[i]);x++) for (int y=0;y<SIZE(cluster_workers[j]);y++)
            {
                int pi=cluster_workers[i][x],pj=cluster_workers[j][y];
                if (g[pi][i]<=g[pj][i] && g[pj][j]<=g[pi][j]) continue;
                if (g[pi][j]>=cut_distance[j] && g[pj][i]>=cut_distance[i]) continue;
                int old_i=est_cost[i],old_j=est_cost[j];
                swap(cluster_workers[i][x],cluster_workers[j][y]);
                int new_i=get_estimate_cost(i,real_cluster_size[i],cluster_workers[i],g);
                int new_j=get_estimate_cost(j,real_cluster_size[j],cluster_workers[j],g);
                if (new_i+new_j<old_i+old_j)
                {
                    est_cost[i]=new_i;
                    est_cost[j]=new_j;
                    cut_distance[i]=get_cut_distance(i,real_cluster_size[i],cluster_workers[i],g);
                    cut_distance[j]=get_cut_distance(j,real_cluster_size[j],cluster_workers[j],g);
                }
                else
                    swap(cluster_workers[i][x],cluster_workers[j][y]);
            }
        int new_total_cost=0;
        for (int i=0;i<num_clusters;i++) new_total_cost+=est_cost[i];
#ifdef DEBUG
        for (int i=0;i<num_clusters;i++)
        {
            ASSERT(SIZE(cluster_workers[i])>0 && SIZE(cluster_workers[i])<=max_cluster_size[i]);
            ASSERT(est_cost[i]==get_estimate_cost(i,real_cluster_size[i],cluster_workers[i],g));
        }
        ASSERT(new_total_cost<=total_cost);
#endif
        if (new_total_cost==total_cost) break;
    }
}

void allocate_workers_to_clusters(vector<int> cluster_workers[],
                                  int &new_num_workers,
                                  int g[MAX_NUM_WORKERS][MAX_NUM_WORKERS])
{
#ifdef DEBUG
    Timer t3(3);
#endif
    int c_worker[MAX_NUM_WORKERS];
    for (int i=0;i<num_clusters;i++) c_worker[i]=1;
    int real_num_workers;
    if (current_round>PARAM_FINAL_OPT_ROUND)
    {
        int max_new_workers=0;
        for (int i=0;i<num_clusters;i++) max_new_workers+=max(1,cluster_size[i]/PARAM_MIN_NEW_WORKER_PER_SNOW);
        real_num_workers=min(expected_max_num_workers,max_new_workers+num_workers);
    }
    else
    {
        real_num_workers=0;
        for (int i=0;i<num_clusters;i++) real_num_workers+=max(1,cluster_size[i]);
        if (real_num_workers<num_workers) real_num_workers=num_workers;
        if (real_num_workers>expected_max_num_workers) real_num_workers=expected_max_num_workers;
    }
    int real_cluster_size[MAX_NUM_WORKERS];
    for (int i=0;i<num_clusters;i++) real_cluster_size[i]=cluster_size[i];
    int snow_cnt[MAX_NUM_WORKERS][30];
    memset(snow_cnt,0,sizeof(snow_cnt));
    bool visited6[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    memset(visited6,false,sizeof(visited6));
    for (int i=0;i<num_snows;i++)
    {
        int x=snows[i].x,y=snows[i].y;
        int t=cluster_idx[x][y];
#ifdef DEBUG
        ASSERT(t>=0 && t<num_clusters);
#endif
        for (int dx=-PARAM_CLUSTER_SPLIT_DISTANCE/2;dx<=PARAM_CLUSTER_SPLIT_DISTANCE/2;dx++) 
            for (int dy=-PARAM_CLUSTER_SPLIT_DISTANCE/2;dy<=PARAM_CLUSTER_SPLIT_DISTANCE/2;dy++) if (abs(dx)+abs(dy)<=PARAM_CLUSTER_SPLIT_DISTANCE/2)
            {
                int x2=x+dx,y2=y+dy;
                if (x2>=0 && y2>=0 && x2<board_size && y2<board_size && !visited6[x2][y2])
                {
                    visited6[x2][y2]=true;
                    for (int b=0;b<30;b++) if (contain(snow_log[x2][y2],b)) snow_cnt[t][b]++;
                }
            }
    }
    int left_rounds=MAX_NUM_ROUNDS-current_round;
    int remain_moves=left_rounds+1+min(3,left_rounds);
    for (int i=0;i<num_clusters;i++)
    {
        int L=0,s1=0,s2=0,c=0;
        for (int b=0;b<30;b++)
            if (snow_cnt[i][b]>0)
                s1++,s2+=snow_cnt[i][b],c=b,L=0;
            else if ((++L)>=PARAM_NON_SNOWS_TIMESTAMP_GAP)
                break;
        if (s2<=0) continue;
        double f=0;
        if (c<=25) f=(25.0+max(10,c))/2.0-c;
        if (f<0) f=0;
        if (f>left_rounds) f=left_rounds;
        double g=sqrt((double)s2/s1);
#ifdef DEBUG
        ASSERT(f>=-1e-6 && g>=-1e-6);
#endif
        real_cluster_size[i]+=(int)(f*g*PARAMS_PREDICTION_DAMPING+0.5);
    }
    for (int i=num_clusters;i<real_num_workers;i++)
    {
        int target=-1;
        for (int j=0;j<num_clusters;j++) if (c_worker[j]<cluster_size[j])
            if (target<0 || real_cluster_size[j]*c_worker[target]>real_cluster_size[target]*c_worker[j])
                target=j;
        if (target<0) break;
        c_worker[target]++;
    }
    bm2.nleft=num_clusters;
    bm2.nright=real_num_workers;
    for (int i=0;i<num_clusters;i++) bm2.dup[i]=c_worker[i];
    for (int i=0;i<real_num_workers;i++)
        if (i>=num_workers)
            for (int k=0;k<num_clusters;k++) bm2.cost[k][i]=0,g[i][k]=1;
        else
        {
            int mincost[MAX_NUM_WORKERS],avgcost[MAX_NUM_WORKERS];
            for (int j=0;j<num_clusters;j++) mincost[j]=oo,avgcost[j]=0;
            int wx=workers[i].x,wy=workers[i].y;
            for (int j=0;j<num_snows;j++)
            {
                int x=snows[j].x,y=snows[j].y;
                int d=abs(x-wx)+abs(y-wy);
                int t=cluster_idx[x][y];
#ifdef DEBUG
                ASSERT(t>=0 && t<num_clusters);
#endif
                if (d<mincost[t]) mincost[t]=d;
                avgcost[t]+=d;
            }
            for (int k=0;k<num_clusters;k++)
            {
                if (mincost[k]>remain_moves) mincost[k]=10000;
                g[i][k]=mincost[k];
                avgcost[k]=avgcost[k]*100/cluster_size[k];
            }
            for (int k=0;k<num_clusters;k++) bm2.cost[k][i]=mincost[k]*10000+avgcost[k];
        }
    if (num_clusters>1)
    {
        bm2.solve();
        for (int i=0;i<num_clusters;i++) for (int k=0;k<bm2.dup[i];k++) cluster_workers[i].push_back(bm2.p1[i][k]);
    }
    else
    {
        ipair order[MAX_NUM_WORKERS];
        for (int i=0;i<real_num_workers;i++) order[i]=MP(bm2.cost[0][i],i);
        sort(order,order+real_num_workers);
        for (int i=0;i<bm2.dup[0];i++) cluster_workers[0].push_back(order[i].second);
    }
#ifdef DEBUG
    for (int i=0;i<num_clusters;i++)
    {
        ASSERT(SIZE(cluster_workers[i])>0 && SIZE(cluster_workers[i])<=cluster_size[i]);
        ASSERT(SIZE(cluster_workers[i])==c_worker[i]);
    }
#endif
    if (!closeto_timeout)
        run_sa_allocate_workers_to_clusters(num_clusters,cluster_size,real_cluster_size,cluster_workers,g);
#ifdef DEBUG
    for (int i=0;i<num_clusters;i++) ASSERT(SIZE(cluster_workers[i])>0 && SIZE(cluster_workers[i])<=cluster_size[i]);
#endif
    new_num_workers=real_num_workers;
}

bool covered3[MAX_NUM_CELLS];
Point cluster_pts[MAX_NUM_CELLS];
int nearest_dst[MAX_NUM_CELLS];

int diag1[MAX_BOARD_SIZE+MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int diag1_size[MAX_BOARD_SIZE+MAX_BOARD_SIZE];
int diag2[MAX_BOARD_SIZE+MAX_BOARD_SIZE][MAX_BOARD_SIZE];
int diag2_size[MAX_BOARD_SIZE+MAX_BOARD_SIZE];
int idx_to_cluster_pos[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

void remove_from_list(int p[],int &cnt,int key)
{
#ifdef DEBUG
    int H=0,T=cnt;
    for (;H+1<T;)
    {
        int M=(H+T)/2;
        if (p[M]>key) T=M;
        else H=M;
    }
    ASSERT(p[H]==key);
#endif
    int last=-1;
    for (int i=cnt-1;last!=key;i--) swap(last,p[i]);
    cnt--;
}

void remove_pts_from_diag(int x,int y)
{
    int d1=x-y+board_size,d2=x+y;
    remove_from_list(diag1[d1],diag1_size[d1],x);
    remove_from_list(diag2[d2],diag2_size[d2],x);
}

void build_diag(int cnt)
{
    memset(diag1_size,0,(board_size+board_size)*sizeof(int));
    memset(diag2_size,0,(board_size+board_size)*sizeof(int));
    for (int i=0;i<cnt;i++) if (!covered3[i])
    {
        int x=cluster_pts[i].x,y=cluster_pts[i].y;
        int d1=x-y+board_size,d2=x+y;
        diag1[d1][diag1_size[d1]++]=x;
        diag2[d2][diag2_size[d2]++]=x;
    }
    //for (int i=0;i<board_size+board_size;i++) sort(diag1[i],diag1[i]+diag1_size[i]);
    //for (int i=0;i<board_size+board_size;i++) sort(diag2[i],diag2[i]+diag2_size[i]);
}

int findall(int *p,int cnt,int s,int t,int *&rp)
{
    if (cnt==0) return 0;
    if (s<0) s=0;
    if (t>=board_size) t=board_size-1;
    if (s>t) return 0;
    int H,T;
    if (cnt<=4)
        for (T=0;T<cnt && p[T]<s;T++);
    else
    {
        H=-1,T=cnt;
        for (;H+1<T;)
        {
            int M=(H+T)/2;
            if (p[M]<s) H=M;
            else T=M;
        }
    }
    for (H=T;H<cnt && p[H]<=t;H++);
    rp=p+T;
    return H-T;
}

ipair edges3[MAX_NUM_WORKERS*MAX_NUM_CELLS];
int clean_snow_per_cluster(int current_cluster_idx,
                           vector<int> _cluster_workers,
                           vector<Point> prev_workers_path[],
                           int use_prev_path,
                           vector<Point> workers_path[])
{
    if (closeto_timeout && use_prev_path) return -1;
#ifdef DEBUG
    Timer t1(1);
#endif
    int total_score=0;
    int cnt=cluster_size[current_cluster_idx],num_candidates=SIZE(_cluster_workers);
#ifdef DEBUG
    ASSERT(num_candidates>0);
#endif
    int *cluster_workers=&_cluster_workers[0];
    memcpy(cluster_pts,cluster_pts_all[current_cluster_idx],cnt*sizeof(Point));
    for (int i=0;i<cnt;i++) idx_to_cluster_pos[cluster_pts[i].x][cluster_pts[i].y]=i;
#ifdef DEBUG
    ASSERT(cnt==cluster_size[current_cluster_idx]);
#endif
    int lasttime[MAX_NUM_WORKERS];
    Point lastpos[MAX_NUM_WORKERS];
    int pts_reindex[MAX_NUM_CELLS];
    for (int i=0;i<num_candidates;i++) lasttime[i]=0,lastpos[i]=workers[cluster_workers[i]];
    for (int i=0;i<cnt;i++) covered3[i]=false;
    bool have_new_workers=false;
    for (int i=0;i<num_candidates;i++) if (cluster_workers[i]>=num_workers) have_new_workers=true;
    if (have_new_workers)
    {
        // Choose the points maximize the distance among others.
        for (int i=0;i<cnt;i++)
        {
            int d=100000;
            Point p=cluster_pts[i];
            for (int j=0;j<num_candidates;j++) if (cluster_workers[j]<num_workers)
            {
                int t=get_distance(p,workers[cluster_workers[j]]);
                if (t<d) d=t;
            }
            nearest_dst[i]=d;
        }
        for (int i=0;i<num_candidates;i++) if (cluster_workers[i]>=num_workers)
        {
            int k=-1,opt_cost=-1;
            for (int j=0;j<cnt;j++) if (!covered3[j])
            {
#ifdef DEBUG
                ASSERT(board[cluster_pts[j].x][cluster_pts[j].y]>0);
#endif
                int cost=nearest_dst[j]*16+min(15,board[cluster_pts[j].x][cluster_pts[j].y]);
                if (cost>opt_cost) opt_cost=cost,k=j;
            }
#ifdef DEBUG
            ASSERT(k>=0);
#endif
            covered3[k]=true;
            lasttime[i]=1;
            total_score++;
            lastpos[i]=cluster_pts[k];
            // update nearest_dst[]
            for (int j=0;j<cnt;j++) if (!covered3[j])
            {
                int t=get_distance(cluster_pts[k],cluster_pts[j]);
                if (t<nearest_dst[j]) nearest_dst[j]=t;
            }
        }
    }
    for (int i=0;i<num_candidates;i++) workers_path[i].clear();
    for (int i=0;i<num_candidates;i++) workers_path[i].push_back(lastpos[i]);
    if (use_prev_path)
    {
        if (have_new_workers) return -1;
        int length_prev_path=0;
        for (int i=0;i<num_candidates;i++) if (SIZE(prev_workers_path[i])>0)
        {
#ifdef DEBUG
            ASSERT(is_same(workers_path[i][0],prev_workers_path[i][0]));
#endif
            for (int j=1;j<SIZE(prev_workers_path[i]);j++)
            {
#ifdef DEBUG
                ASSERT(!is_same(prev_workers_path[i][j],prev_workers_path[i][j-1]) && is_inside(prev_workers_path[i][j]));
#endif
                Point dest=prev_workers_path[i][j];
                if (board[dest.x][dest.y] && cluster_idx[dest.x][dest.y]==current_cluster_idx)
                {
                    int p_id=idx_to_cluster_pos[dest.x][dest.y];
                    if (!covered3[p_id])
                    {
                        length_prev_path++;
                        int d=max(1,get_distance(lastpos[i],dest));
                        lasttime[i]+=d;
                        lastpos[i]=dest;
                        total_score+=lasttime[i];
                        covered3[p_id]=true;
                        workers_path[i].push_back(dest);
                    }
                }
            }
        }
        if (length_prev_path==0) return -1;
        build_diag(cnt);
        priority_queue<int> heap;
        int next_seg_at[MAX_NUM_WORKERS],sum_length[MAX_NUM_WORKERS];
        for (int i=0;i<num_candidates;i++) if (SIZE(workers_path[i])>=2)
        {
            sum_length[i]=0;
            next_seg_at[i]=1;
            heap.push(-i);
        }
        while (!heap.empty())
        {
            int i=(-heap.top())&255;
#ifdef DEBUG
            ASSERT(i>=0 && i<num_candidates);
#endif
            heap.pop();
            int s=sum_length[i];
            int j=next_seg_at[i];
#ifdef DEBUG
            ASSERT(j>0 && j<SIZE(workers_path[i]));
#endif
            int x1=workers_path[i][j-1].x,y1=workers_path[i][j-1].y;
            int x2=workers_path[i][j].x,y2=workers_path[i][j].y;
#ifdef DEBUG
            ASSERT(x1!=x2 || y1!=y2);
#endif
            if (x1>x2) swap(x1,x2);
            if (y1>y2) swap(y1,y2);
            int min_dst=oo,p_id=-1;
            for (int sxy=x1+y1;sxy<=x2+y2;sxy++)
            {
                int *lst,count=findall(diag2[sxy],diag2_size[sxy],max(x1,sxy-y2),min(x2,sxy-y1),lst);
                for (int k=0;k<count;k++)
                {
                    int x=lst[k],y=sxy-x;
                    if (x==workers_path[i][j-1].x && y==workers_path[i][j-1].y) continue;
                    if (x==workers_path[i][j].x && y==workers_path[i][j].y) continue;
#ifdef DEBUG
                    ASSERT(board[x][y] && cluster_idx[x][y]==current_cluster_idx && !covered3[idx_to_cluster_pos[x][y]]);
#endif
                    int d=abs(x-workers_path[i][j-1].x)+abs(y-workers_path[i][j-1].y);
                    if (d<min_dst) min_dst=d,p_id=idx_to_cluster_pos[x][y];
                }
            }
            if (p_id>=0) 
            {
#ifdef DEBUG
                ASSERT(get_distance(workers_path[i][j-1],cluster_pts[p_id])>0);
                ASSERT(get_distance(workers_path[i][j],cluster_pts[p_id])>0);
                ASSERT(get_distance(workers_path[i][j-1],cluster_pts[p_id])+get_distance(workers_path[i][j],cluster_pts[p_id])
                    ==get_distance(workers_path[i][j-1],workers_path[i][j]));
#endif
                total_score+=s+get_distance(workers_path[i][j-1],cluster_pts[p_id]);
                workers_path[i].push_back(Point());
                for (int k=SIZE(workers_path[i])-1;k>j;k--) workers_path[i][k]=workers_path[i][k-1];
                workers_path[i][j]=cluster_pts[p_id];
                covered3[p_id]=true;
                remove_pts_from_diag(cluster_pts[p_id].x,cluster_pts[p_id].y);
            }
#ifdef DEBUG
            ASSERT(!is_same(workers_path[i][j-1],workers_path[i][j]));
#endif
            sum_length[i]+=get_distance(workers_path[i][j-1],workers_path[i][j]);
            next_seg_at[i]++;
            if (next_seg_at[i]<SIZE(workers_path[i])) heap.push(-((sum_length[i]<<8)|i));
        }
    }
    else
        build_diag(cnt);
    int num_uncovered=0;
    for (int i=0;i<cnt;i++) if (!covered3[i]) num_uncovered++;
    set<ipair> lasttime_set;
    for (int i=0;i<num_candidates;i++) lasttime_set.insert(MP(lasttime[i],i));
    int used_workers[MAX_NUM_WORKERS],workers_reindex[MAX_NUM_WORKERS];
    ipair matched_pairs[MAX_NUM_WORKERS];
    for (int last_distance=0;num_uncovered>0;last_distance++)
    {
        if (last_distance<=lasttime_set.begin()->first) last_distance=lasttime_set.begin()->first+1;
        int n_edges=0,n_used_workers=0;
        for (set<ipair>::iterator it=lasttime_set.begin();it!=lasttime_set.end();++it)
        {
            int w_id=it->second;
#ifdef DEBUG
            ASSERT(it->first==lasttime[w_id]);
#endif
            int d=last_distance-lasttime[w_id];
            if (d<=0) break;
            int x=lastpos[w_id].x,y=lastpos[w_id].y;
            int old_n_edges=n_edges;
            if (d==1 && board[x][y] && cluster_idx[x][y]==current_cluster_idx)
            {
                int p_id=idx_to_cluster_pos[x][y];
#ifdef DEBUG
                ASSERT(p_id>=0 && cluster_pts[p_id].x==x && cluster_pts[p_id].y==y);
#endif
                if (!covered3[p_id]) edges3[n_edges++]=MP(p_id,w_id);
            }
            int rcnt[4]={0,0,0,0},*rlst[4];
            int d1=x-y+board_size,d2=x+y;
            if (d1-d>=0)
                rcnt[0]=findall(diag1[d1-d],diag1_size[d1-d],x-d+1,x,rlst[0]);
            if (d1+d<board_size+board_size)
                rcnt[1]=findall(diag1[d1+d],diag1_size[d1+d],x,x+d-1,rlst[1]);
            if (d2-d>=0)
                rcnt[2]=findall(diag2[d2-d],diag2_size[d2-d],x-d,x-1,rlst[2]);
            if (d2+d<board_size+board_size)
                rcnt[3]=findall(diag2[d2+d],diag2_size[d2+d],x+1,x+d,rlst[3]);
            int cnt_added=0;
            for (int p=0;p<4;p++) 
            {
                if (closeto_timeout && cnt_added>=num_candidates) break;
                for (int i=0;i<rcnt[p];i++)
                {
                    int x0=rlst[p][i],y0;
                    if (p==0) y0=x0-d1+d+board_size;
                    else if (p==1) y0=x0-d1-d+board_size;
                    else if (p==2) y0=d2-d-x0;
                    else y0=d2+d-x0;
#ifdef DEBUG
                    ASSERT(board[x0][y0] && cluster_idx[x0][y0]==current_cluster_idx
                        && idx_to_cluster_pos[x0][y0]>=0 && !covered3[idx_to_cluster_pos[x0][y0]]);
                    ASSERT(get_distance(cluster_pts[idx_to_cluster_pos[x0][y0]],lastpos[w_id])+lasttime[w_id]==last_distance);
#endif
                    edges3[n_edges++]=MP(idx_to_cluster_pos[x0][y0],w_id);
                    cnt_added++;
                    if (closeto_timeout && cnt_added>=num_candidates) break;
                }
            }
            if (old_n_edges<n_edges) used_workers[n_used_workers++]=w_id;
        }
        if (n_edges==0) continue;
        set<int> pts_set;
        for (int i=0;i<n_edges;i++) pts_set.insert(edges3[i].first);
        vector<ipair> pts_order;
        int n_pts=SIZE(pts_set);
        for (set<int>::iterator it=pts_set.begin();it!=pts_set.end();++it)
        {
            int p_idx=*it;
            int cost;
            if (closeto_timeout || n_pts<=2 && n_used_workers>=n_pts)
                cost=0;
            else
            {
                int total=0,md1=200,md2=200;
                int x=cluster_pts[p_idx].x;
                int y=cluster_pts[p_idx].y;
                for (int i=0;i<num_candidates;i++)
                {
                    int t=abs(lastpos[i].x-x)+abs(lastpos[i].y-y);
                    if (t==0) t=1;
                    total+=t;
                    t+=lasttime[i]-last_distance;
                    if (t==0) continue;
                    if (t<md1) md2=md1,md1=t;
                    else if (t<md2) md2=t;
                }
                if (last_distance<=4)
                {
#ifdef DEBUG
                    ASSERT(board[x][y]>0 && last_distance>0);
#endif
                    cost=md1*10000000+md2*50000+min(4,board[x][y]+last_distance-2)*10000+total;
                }
                else
                    cost=md1*10000000+md2*50000+total;
            }
            pts_order.push_back(MP(-cost,p_idx));
        }
        sort(pts_order.begin(),pts_order.end());
        for (int i=0;i<n_pts;i++) pts_reindex[pts_order[i].second]=i;
        for (int i=0;i<n_used_workers;i++) workers_reindex[used_workers[i]]=i;
        mm.init(n_pts,n_used_workers);
        for (int i=n_edges-1;i>=0;i--) mm.addedge(pts_reindex[edges3[i].first],workers_reindex[edges3[i].second]);
        int c_match=mm.doMatch();
#ifdef DEBUG
        ASSERT(c_match>0);
#endif
        int new_pts=0;
        if (lasttime[used_workers[c_match-1]]==lasttime[used_workers[n_used_workers-1]])
        {
            for (int i=0;i<n_used_workers;i++)if (mm.p2[i]>=0)
                matched_pairs[new_pts++]=MP(used_workers[i],pts_order[mm.p2[i]].second);
        }
        else
        {
            for (int i=0;i<n_pts;i++) pts_reindex[pts_order[i].second]=-1;
            for (int i=0;i<n_pts;i++) if (mm.p1[i]>=0) pts_reindex[pts_order[i].second]=i;
            mm.init(n_used_workers,n_pts);
            for (int i=n_edges-1;i>=0;i--)
            {
                int p_id=pts_reindex[edges3[i].first];
                if (p_id>=0) mm.addedge(workers_reindex[edges3[i].second],p_id);
            }
            int c_match2=mm.doMatch();
#ifdef DEBUG
            ASSERT(c_match==c_match2);
#endif
            for (int i=0;i<n_used_workers;i++) if (mm.p1[i]>=0)
                matched_pairs[new_pts++]=MP(used_workers[i],pts_order[mm.p1[i]].second);
        }
        for (int i=0;i<new_pts;i++)
        {
            int w_id=matched_pairs[i].first;
            int p_id=matched_pairs[i].second;
#ifdef DEBUG
            ASSERT(!covered3[p_id]);
#endif
            workers_path[w_id].push_back(cluster_pts[p_id]);
#ifdef DEBUG
            ASSERT(lasttime_set.find(MP(lasttime[w_id],w_id))!=lasttime_set.end());
#endif
            lasttime_set.erase(MP(lasttime[w_id],w_id));
            lasttime[w_id]=last_distance;
            lasttime_set.insert(MP(lasttime[w_id],w_id));
            lastpos[w_id]=cluster_pts[p_id];
            covered3[p_id]=true;
            total_score+=last_distance;
            remove_pts_from_diag(cluster_pts[p_id].x,cluster_pts[p_id].y);
            num_uncovered--;
        }
        if (closeto_timeout)
        {
            bool allset=true;
            for (int i=0;i<num_candidates;i++) if (SIZE(workers_path[i])<=1) { allset=false; break; }
            if (allset)
            {
                for (int i=0;i<cnt;i++) if (!covered3[i])
                {
                    covered3[i]=true;
                    num_uncovered--;
                    int idx=i%num_candidates;
                    int d=lasttime[idx]+max(1,get_distance(lastpos[idx],cluster_pts[i]));
                    total_score+=d;
                    lasttime[idx]=d;
                    lastpos[idx]=cluster_pts[i];
                    workers_path[idx].push_back(cluster_pts[i]);
                }
#ifdef DEBUG
                ASSERT(num_uncovered==0);
#endif
            }
        }
    }
#ifdef DEBUG
    ASSERT(num_uncovered==0);
    for (int i=0;i<cnt;i++) ASSERT(covered3[i]);
    for (int i=0;i<num_candidates;i++)
    {
        ASSERT(SIZE(workers_path[i])>0);
        if (cluster_workers[i]<num_workers) 
        {
            ASSERT(get_distance(workers_path[i][0],workers[cluster_workers[i]])==0);
            ASSERT(is_inside(workers_path[i][0]));
        }
    }
    int __cnt=0;
    for (int i=0;i<num_candidates;i++) __cnt+=SIZE(workers_path[i])-1+(int)(cluster_workers[i]>=num_workers);
    ASSERT(cnt==__cnt);
#endif
    return total_score;
}

void handle_idle_workers(bool is_idle_worker[],vector<string>* results)
{
#ifdef DEBUG
    Timer t2(2);
#endif
#ifdef DEBUG
    for (int k=0;k<num_workers;k++) ASSERT(is_inside(workers[k]));
#endif
    int num_idle_workers=0,idle_workers_idx[MAX_NUM_WORKERS];
    for (int k=0;k<num_workers;k++) if (is_idle_worker[k]) idle_workers_idx[num_idle_workers++]=k;
    if (num_idle_workers==0) return;
    if (closeto_timeout)
    {
        for (int i=0;i<num_idle_workers;i++)
        {
            int k=idle_workers_idx[i];
            int d=get_direction(workers[k],Point((board_size-1)/2,(board_size-1)/2));
            if (d<0) continue;
            if (results!=NULL)
            {
                char str[100];
                sprintf(str,"M %d %c",k,DELTA_C[d]);
                results->push_back(str);
            }
            workers[k].x+=DELTA_X[d];
            workers[k].y+=DELTA_Y[d];
#ifdef DEBUG
            ASSERT(is_inside(workers[k]));
#endif
        }
        return;
    }
    double cx[MAX_NUM_WORKERS],cy[MAX_NUM_WORKERS];
    double shrink_side=PARAM_KMEAN_SHRINK_SIDE;
    if (board_size/sqrt((double)num_idle_workers)<=PARAM_KMEAN_SHRINK_SIDE_SMALL_LIMIT)
        shrink_side=PARAM_KMEAN_SHRINK_SIDE_SMALL;
    if (board_size/sqrt((double)num_idle_workers)<=PARAM_KMEAN_SHRINK_SIDE_TINY_LIMIT)
        shrink_side=PARAM_KMEAN_SHRINK_SIDE_TINY;
    const double min_boundary=shrink_side;
    const double max_boundary=board_size-1-shrink_side;
    if (num_idle_workers==1)
        cx[0]=cy[0]=(board_size-1)/2.0;
    else
    {
        int order[MAX_NUM_WORKERS][MAX_NUM_WORKERS];
        for (int i=0;i<num_idle_workers;i++) 
        {
            int x0=workers[idle_workers_idx[i]].x;
            int y0=workers[idle_workers_idx[i]].y;
            cx[i]=x0;
            cy[i]=y0;
            bool dup=false;
            for (int j=0;j<num_idle_workers;j++)
            {
                int d=sqr(x0-workers[idle_workers_idx[j]].x)+sqr(y0-workers[idle_workers_idx[j]].y);
                order[i][j]=((d<<8)|j);
                if (i!=j && d==0) dup=true;
            }
            if (dup)
            {
                double ptr=(double)i/num_idle_workers*PI*2.0;
                cx[i]+=0.3*cos(ptr);
                cy[i]+=0.3*sin(ptr);
            }
            sort(order[i],order[i]+num_idle_workers);
            for (int j=0;j<num_idle_workers;j++) order[i][j]&=255;
        }
        double px[MAX_NUM_WORKERS+10],py[MAX_NUM_WORKERS+10],pd[MAX_NUM_WORKERS+10];
        double px2[MAX_NUM_WORKERS+10],py2[MAX_NUM_WORKERS+10],pd2[MAX_NUM_WORKERS+10];
        int side[MAX_NUM_WORKERS+10];
        for (int step=0;step<PARAM_KMEAN_ROUNDS;step++) for (int key=0;key<num_idle_workers;key++)
        {
            int m=4;
            px[0]=min_boundary,py[0]=min_boundary;
            px[1]=max_boundary,py[1]=min_boundary;
            px[2]=max_boundary,py[2]=max_boundary;
            px[3]=min_boundary,py[3]=max_boundary;
            double ox=cx[key],oy=cy[key];
            for (int i=0;i<4;i++) pd[i]=sqr(px[i]-ox)+sqr(py[i]-oy);
            double md=0;
            for (int i=0;i<4;i++) if (pd[i]>md) md=pd[i];
            for (int o=0;o<num_idle_workers;o++)
            {
                int i=order[key][o];
                if (i==key) continue;
                double a=ox-cx[i];
                double b=oy-cy[i];
                if (sqr(a)+sqr(b)>=4*md) continue;
                double c=-(a*(cx[i]+ox)/2+b*(cy[i]+oy)/2);
                int c1=0,c2=0;
                for (int k=0;k<m;k++)
                {
                    double t=a*px[k]+b*py[k]+c;
                    if (fabs(t)<=1e-7) side[k]=0;
                    else if (t<0) side[k]=-1,c1++;
                    else side[k]=1,c2++;
                }
                if (c1==0) continue;
                if (c2==0) { m=0; break; }
                side[m]=side[0];
                px[m]=px[0];
                py[m]=py[0];
                int m2=0;
                for (int k=0;k<m;k++)
                {
                    if (side[k]>=0)
                    {
                        px2[m2]=px[k];
                        py2[m2]=py[k];
                        pd2[m2++]=pd[k];
                    }
                    if (side[k]*side[k+1]<0)
                    {
                        double a2=py[k]-py[k+1];
                        double b2=px[k+1]-px[k];
                        double c2=px[k]*py[k+1]-px[k+1]*py[k];
                        double t=a*b2-a2*b;
                        double x=(b*c2-b2*c)/t;
                        double y=-(a*c2-a2*c)/t;
                        px2[m2]=x;
                        py2[m2]=y;
                        pd2[m2++]=sqr(x-ox)+sqr(y-oy);
                    }
                }
                if (m2<3) { m=0; break; }
                m=m2;
                for (int k=0;k<m;k++) px[k]=px2[k],py[k]=py2[k],pd[k]=pd2[k];
                md=0;
                for (int k=0;k<m;k++) if (pd[k]>md) md=pd[k];
            }
            if (m<3) continue;
            double mx=0,my=0,area=0;
            for (int k=2;k<m;k++)
            {
                double x1=px[k-1],y1=py[k-1];
                double x2=px[k],y2=py[k];
                double x3=px[0],y3=py[0];
                double s=fabs((x2-x1)*(y3-y1)-(x3-x1)*(y2-y1));
                double ox=(x1+x2+x3)/3,oy=(y1+y2+y3)/3;
                mx=(mx*area+ox*s)/(area+s);
                my=(my*area+oy*s)/(area+s);
                area+=s;
            }
            cx[key]=mx;
            cy[key]=my;
        }
    }
    for (int i=0;i<num_idle_workers;i++)
    {
        int k=idle_workers_idx[i];
        int x=workers[k].x;
        int y=workers[k].y;
        double ox=cx[i],oy=cy[i];
        if (ox<min_boundary) ox=min_boundary;
        if (oy<min_boundary) oy=min_boundary;
        if (ox>max_boundary) ox=max_boundary;
        if (oy>max_boundary) oy=max_boundary;
        double min_dst=sqr(x-ox)+sqr(y-oy);
        int best_direction=-1;
        for (int d=0;d<4;d++)
        {
            int x2=x+DELTA_X[d];
            int y2=y+DELTA_Y[d];
            if (!is_inside(x2,y2)) continue;
            double dst=sqr(x2-ox)+sqr(y2-oy);
            if (dst<min_dst) min_dst=dst,best_direction=d;
        }
        if (best_direction>=0)
        {
            int d=best_direction;
            if (results!=NULL)
            {
                char str[100];
                sprintf(str,"M %d %c",k,DELTA_C[d]);
                results->push_back(str);
            }
            workers[k].x+=DELTA_X[d];
            workers[k].y+=DELTA_Y[d];
#ifdef DEBUG
            ASSERT(is_inside(workers[k]));
#endif
        }
    }
}

ipair get_path_cost(int n,Point p[],bool is_new_worker)
{
    if (n==0) return MP(0,0);
    int s,d;
    if (is_new_worker)
        s=d=1;
    else
        s=d=0;
    for (int i=1;i<n;i++) { int t=get_distance(p[i-1],p[i]); if (t==0) d++; else d+=t; s+=d; }
    return MP(d,s);
}

ipair get_path_cost(vector<Point>& a,bool is_new_worker)
{
    if (SIZE(a)==0) return MP(0,0);
    return get_path_cost(SIZE(a),&a[0],is_new_worker);
}

void list_erase(Point a[],int &size,int pos)
{
    int tsize=(--size);
    for (int i=pos;i<tsize;i++) a[i]=a[i+1];
}
void list_insert(Point a[],int &size,int pos,Point key)
{
    size++;
    for (int i=size-1;i>pos;i--) a[i]=a[i-1];
    a[pos]=key;
}

Point a[MAX_NUM_WORKERS][MAX_NUM_CELLS];
int d1[MAX_NUM_CELLS],d2[MAX_NUM_CELLS],e1[MAX_NUM_CELLS],e2[MAX_NUM_CELLS];
Point vx[MAX_NUM_CELLS],vy[MAX_NUM_CELLS];

void run_sa_per_cluster(int n,vector<Point> _a[],int idx[],double timelimit)
{
    if (closeto_timeout || gettime()>timelimit) return;
#ifdef DEBUG
    Timer t4(4);
    Counter c20(20);
    Timer t41(40+(int)is_main_path);
#endif
    int size[MAX_NUM_WORKERS];
    for (int i=0;i<n;i++) size[i]=SIZE(_a[i]);
    for (int i=0;i<n;i++) for (int j=0;j<size[i];j++) a[i][j]=_a[i][j];
#ifdef DEBUG
    for (int i=0;i<n;i++) ASSERT(size[i]>0);
#endif
    ipair old_cost=MP(-1,-1);
    int lastchanged[MAX_NUM_WORKERS];
    for (int i=0;i<n;i++) lastchanged[i]=0;
    for (int step=0;step<20 && gettime()<timelimit;step++)
    {
        ipair total_cost=MP(0,0);
        for (int i=0;i<n;i++) 
        {
            ipair t=get_path_cost(size[i],a[i],idx[i]>=num_workers);
            total_cost.first+=t.first;
            total_cost.second+=t.second;
        }
        if (total_cost==old_cost) break;
        old_cost=total_cost;
        for (int i=0;gettime()<timelimit && i<n;i++) for (int j=0;j<size[i];j++)
        {
            if (j==0 && (idx[i]<num_workers || size[i]==1)) continue;
            Point key=a[i][j];
            list_erase(a[i],size[i],j);
#ifdef DEBUG
            ASSERT(size[i]>0);
#endif
            int bx=-1,by=-1;
            int min_delta1=oo,min_delta2=oo;
            if (j==0)
            {
                int d=get_distance(a[i][0],key);
#ifdef DEBUG
                ASSERT(d>0);
#endif
                min_delta1=d*size[i]+1;
            }
            else
            {
                int sd=(int)(idx[i]>=num_workers);
                for (int y=1;y<j;y++)
                {
                    int d=get_distance(a[i][y-1],a[i][y]);
                    if (d==0) d=1;
                    sd+=d;
                }
                int d1=get_distance(a[i][j-1],key);
                if (d1==0) d1=1;
                min_delta1=sd+d1;
                if (j<size[i])
                {
                    int d=get_distance(a[i][j-1],a[i][j]);
                    if (d==0) d=1;
                    int d2=get_distance(a[i][j],key);
#ifdef DEBUG
                    ASSERT(d2>0);
#endif
                    int t=d1+d2-d;
                    if (t>0) min_delta1+=t*(size[i]-j);
                }
            }
            for (int x=0;x<n;x++)
            {
                if (x!=i && lastchanged[i]<step && lastchanged[x]<step) continue;
                int size_x=size[x];
                if (size_x>0 && idx[x]>=num_workers)
                {
                    // add at pos[0]
                    int delta2=get_distance(a[x][0],key);
#ifdef DEBUG
                    ASSERT(delta2>0);
#endif
                    int delta1=delta2*size_x+1;
                    delta2<<=1;
                    if (x==i && j==0) delta2--;
                    if (delta1<min_delta1 || delta1==min_delta1 && delta2<min_delta2) 
                        min_delta1=delta1,min_delta2=delta2,bx=x,by=0;
                }
                for (int sd=(int)(idx[x]>=num_workers),d1=max(1,get_distance(a[x][0],key)),y=1;y<=size_x;y++)
                {
                    int delta1=sd+d1;
                    if (delta1>min_delta1) break;
                    int delta2=d1;
                    if (y<size_x)
                    {
                        int d=get_distance(a[x][y-1],a[x][y]);
                        if (d==0) d=1;
                        int d2=get_distance(a[x][y],key);
#ifdef DEBUG
                        ASSERT(d2>0);
#endif
                        delta2+=d2-d;
                        int t=d1+d2-d;
                        if (t>0) delta1+=t*(size_x-y);
                        sd+=d;
                        d1=d2;
                    }
                    delta2<<=1;
                    if (x==i && y==j) delta2--;
                    if (delta1<min_delta1 || delta1==min_delta1 && delta2<min_delta2) 
                        min_delta1=delta1,min_delta2=delta2,bx=x,by=y;
                }
            }
#ifdef DEBUG
            ASSERT(by>0 || by==0 && idx[bx]>=num_workers);
            ipair old_costx=get_path_cost(size[bx],a[bx],idx[bx]>=num_workers);
#endif
            if (bx!=i || by!=j) lastchanged[i]=lastchanged[bx]=step+1;
            list_insert(a[bx],size[bx],by,key);
#ifdef DEBUG
            ipair new_costx=get_path_cost(size[bx],a[bx],idx[bx]>=num_workers);
            int exp_delta2=min_delta2;
            if (exp_delta2&1) exp_delta2++;
            ASSERT(new_costx.second==old_costx.second+min_delta1 && new_costx.first==old_costx.first+exp_delta2/2);
#endif
        }
        for (int i=0;gettime()<timelimit && i<n;i++) for (int j=0;j+1<size[i];j++)
        {
            if (j==0 && (idx[i]<num_workers || size[i]==2)) continue;
            Point key=a[i][j];
            Point key2=a[i][j+1];
#ifdef DEBUG
            ASSERT(!is_same(key,key2));
#endif
            if (get_distance(key,key2)!=1) continue;
            list_erase(a[i],size[i],j);
            list_erase(a[i],size[i],j);
#ifdef DEBUG
            ASSERT(size[i]>0);
#endif
            int bx=-1,by=-1,rev=-1;
            int min_delta1=oo,min_delta2=oo;
            if (j==0)
            {
                int d=get_distance(a[i][0],key2)+1;
#ifdef DEBUG
                ASSERT(d>1);
#endif
                min_delta1=d*size[i]+3;
            }
            else
            {
                int sd=(int)(idx[i]>=num_workers);
                for (int y=1;y<j;y++)
                {
                    int d=get_distance(a[i][y-1],a[i][y]);
                    if (d==0) d=1;
                    sd+=d;
                }
                int d1=get_distance(a[i][j-1],key);
                if (d1==0) d1=1;
                min_delta1=((sd+d1)<<1)+1;
                if (j<size[i])
                {
                    int d=get_distance(a[i][j-1],a[i][j]);
                    if (d==0) d=1;
                    int d2=get_distance(a[i][j],key2);
#ifdef DEBUG
                    ASSERT(d2>0);
#endif
                    int t=d1+d2+1-d;
                    if (t>0) min_delta1+=t*(size[i]-j);
                }
            }
            for (int x=0;x<n;x++)
            {
                if (x!=i && lastchanged[i]<step && lastchanged[x]<step) continue;
                int size_x=size[x];
                if (size_x>0 && idx[x]>=num_workers)
                {
                    // add at pos[0]
                    int delta2=get_distance(a[x][0],key2)+1;
                    int delta1=delta2*size_x+3;
                    delta2<<=1;
                    if (x==i && j==0) delta2--;
                    if (delta1<min_delta1 || delta1==min_delta1 && delta2<min_delta2) 
                        min_delta1=delta1,min_delta2=delta2,bx=x,by=0,rev=0;
                    delta2=get_distance(a[x][0],key)+1;
                    delta1=delta2*size_x+3;
                    delta2<<=1;
                    if (delta1<min_delta1 || delta1==min_delta1 && delta2<min_delta2) 
                        min_delta1=delta1,min_delta2=delta2,bx=x,by=0,rev=1;
                }
                for (int sd=(int)(idx[x]>=num_workers),y=1;y<=size_x;y++)
                {
                    int d1=get_distance(a[x][y-1],key);
                    if (d1==0) d1=1;
                    int delta1=((sd+d1)<<1)+1;
                    if (delta1>min_delta1) break;
                    int delta2=d1+1;
                    if (y<size_x)
                    {
                        int d=get_distance(a[x][y-1],a[x][y]);
                        if (d==0) d=1;
                        int d2=get_distance(a[x][y],key2);
#ifdef DEBUG
                        ASSERT(d2>0);
#endif
                        delta2+=d2-d;
                        int t=d1+d2+1-d;
                        if (t>0) delta1+=t*(size_x-y);
                        sd+=d;
                    }
                    delta2<<=1;
                    if (x==i && y==j) delta2--;
                    if (delta1<min_delta1 || delta1==min_delta1 && delta2<min_delta2) 
                        min_delta1=delta1,min_delta2=delta2,bx=x,by=y,rev=0;
                }
                for (int sd=(int)(idx[x]>=num_workers),y=1;y<=size_x;y++)
                {
                    int d1=get_distance(a[x][y-1],key2);
                    if (d1==0) d1=1;
                    int delta1=((sd+d1)<<1)+1;
                    if (delta1>min_delta1) break;
                    int delta2=d1+1;
                    if (y<size_x)
                    {
                        int d=get_distance(a[x][y-1],a[x][y]);
                        if (d==0) d=1;
                        int d2=get_distance(a[x][y],key);
#ifdef DEBUG
                        ASSERT(d2>0);
#endif
                        delta2+=d2-d;
                        int t=d1+d2+1-d;
                        if (t>0) delta1+=t*(size_x-y);
                        sd+=d;
                    }
                    delta2<<=1;
                    if (delta1<min_delta1 || delta1==min_delta1 && delta2<min_delta2) 
                        min_delta1=delta1,min_delta2=delta2,bx=x,by=y,rev=1;
                }
            }
#ifdef DEBUG
            ASSERT(by>0 || by==0 && idx[bx]>=num_workers);
            ASSERT(bx>=0 && rev>=0 && rev<=1);
#endif
            if (bx!=i || by!=j || rev!=0) lastchanged[i]=lastchanged[bx]=step+1;
#ifdef DEBUG
            ipair old_costx=get_path_cost(size[bx],a[bx],idx[bx]>=num_workers);
#endif
            if (rev==0)
            {
                list_insert(a[bx],size[bx],by,key2);
                list_insert(a[bx],size[bx],by,key);
            }
            else
            {
                list_insert(a[bx],size[bx],by,key);
                list_insert(a[bx],size[bx],by,key2);
            }
#ifdef DEBUG
            ipair new_costx=get_path_cost(size[bx],a[bx],idx[bx]>=num_workers);
            int exp_delta2=min_delta2;
            if (exp_delta2&1) exp_delta2++;
            ASSERT(new_costx.second==old_costx.second+min_delta1 && new_costx.first==old_costx.first+exp_delta2/2);
#endif
        }
        if (gettime()<timelimit && is_main_path)
        {
            for (int k=0;gettime()<timelimit && k<n;k++) if (size[k]>1)
            {
                if (lastchanged[k]<step) continue;
                for (int i=((idx[k]>=num_workers)?0:1);i<size[k];i++)
                {
                    int s=i;
                    if (s>0) s--;
                    ipair old_cost=get_path_cost(size[k]-s,a[k]+s,false);
                    for (int j=i+1;j<size[k];j++)
                    {
                        reverse(a[k]+i,a[k]+j+1);
                        ipair new_cost=get_path_cost(size[k]-s,a[k]+s,false);
                        if (new_cost.second<old_cost.second)
                        {
                            lastchanged[k]=step+1;
                            old_cost=new_cost;
                        }
                        else
                            reverse(a[k]+i,a[k]+j+1);
                    }
                }
            }
            for (int i=0;gettime()<timelimit && i<n;i++) if (size[i]>1)
                for (int j=i+1;gettime()<timelimit && j<n;j++) if (size[j]>1)
                {
                    if (lastchanged[i]<step && lastchanged[j]<step) continue;
                    int si=size[i],sj=size[j];
                    bool changed=false;
                    d1[0]=(int)(idx[i]>=num_workers);
                    for (int x=0;x+1<si;x++) 
                    {
                        e1[x]=max(1,get_distance(a[i][x],a[i][x+1]));
                        d1[x+1]=d1[x]+e1[x];
                    }
                    d2[0]=(int)(idx[j]>=num_workers);
                    for (int y=0;y+1<sj;y++)
                    {
                        e2[y]=max(1,get_distance(a[j][y],a[j][y+1]));
                        d2[y+1]=d2[y]+e2[y];
                    }
                    for (int x=1;!changed && x<si;x++) for (int y=1;!changed && y<sj;y++)
                    {
                        int oldcost=d1[x]+d2[y];
                        int t1=d1[x-1]+max(1,get_distance(a[i][x-1],a[j][y]));
                        int t2=d2[y-1]+max(1,get_distance(a[j][y-1],a[i][x]));
                        int newcost=t1+t2;
                        if (x+1<si) oldcost+=d1[x+1]*(si-x-1);
                        if (y+1<sj) oldcost+=d2[y+1]*(sj-y-1);
                        if (x+1<si) newcost+=(t1+get_distance(a[j][y],a[i][x+1]))*(si-x-1);
                        if (y+1<sj) newcost+=(t2+get_distance(a[i][x],a[j][y+1]))*(sj-y-1);
                        if (newcost<oldcost)
                        {
#ifdef DEBUG
                            int _old_cost=get_path_cost(size[i],a[i],idx[i]>=num_workers).second+get_path_cost(size[j],a[j],idx[j]>=num_workers).second;
#endif
                            swap(a[i][x],a[j][y]);
                            lastchanged[i]=lastchanged[j]=step+1;
                            changed=true;
#ifdef DEBUG
                            int _new_cost=get_path_cost(size[i],a[i],idx[i]>=num_workers).second+get_path_cost(size[j],a[j],idx[j]>=num_workers).second;
                            ASSERT(_new_cost-_old_cost==newcost-oldcost);
#endif
                        }
                    }
                    for (int x=1;!changed && x<=si;x++) for (int y=1;!changed && y<=sj;y++)
                    {
                        if (x==si && y==sj) continue;
                        int c1=si-x,c2=sj-y;
                        int L1,L2,D1,D2;
                        if (x==si) L1=0,D1=0;
                        else L1=e1[x-1],D1=max(1,get_distance(a[j][y-1],a[i][x]));
                        if (y==sj) L2=0,D2=0;
                        else L2=e2[y-1],D2=max(1,get_distance(a[i][x-1],a[j][y]));
                        if ((d2[y-1]+D1)*c1+(d1[x-1]+D2)*c2<(d1[x-1]+L1)*c1+(d2[y-1]+L2)*c2)
                        {
#ifdef DEBUG
                            int old_cost=get_path_cost(size[i],a[i],idx[i]>=num_workers).second+get_path_cost(size[j],a[j],idx[j]>=num_workers).second;
                            int delta_cost=((d2[y-1]+D1)*c1+(d1[x-1]+D2)*c2)-((d1[x-1]+L1)*c1+(d2[y-1]+L2)*c2);
#endif
                            memcpy(vx,a[i]+x,c1*sizeof(Point));
                            memcpy(vy,a[j]+y,c2*sizeof(Point));
                            memcpy(a[i]+x,vy,c2*sizeof(Point));
                            memcpy(a[j]+y,vx,c1*sizeof(Point));
                            size[i]=x+c2;
                            size[j]=y+c1;
                            changed=true;
                            lastchanged[i]=lastchanged[j]=step+1;
#ifdef DEBUG
                            int new_cost=get_path_cost(size[i],a[i],idx[i]>=num_workers).second+get_path_cost(size[j],a[j],idx[j]>=num_workers).second;
                            ASSERT(new_cost==old_cost+delta_cost);
#endif
                        }
                    }
                }
        }
    }
    for (int i=0;i<n;i++) _a[i].resize(size[i]);
    for (int i=0;i<n;i++) for (int j=0;j<size[i];j++) _a[i][j]=a[i][j];
}

void remove_idle_new_workers(int &new_num_workers,
                             vector<Point> workers_path[MAX_NUM_WORKERS])
{
    int cnt=num_workers;
    for (int i=num_workers;i<new_num_workers;i++)
        if (SIZE(workers_path[i])>0)
            workers_path[cnt++]=workers_path[i];
    new_num_workers=cnt;
}

void generate_moves(int new_num_workers,
                    vector<Point> workers_path[MAX_NUM_WORKERS],
                    vector<string> *results,
                    bool is_idle_worker[])
{
#ifdef DEBUG
    Timer t6(6);
#endif
    int g[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    if (num_workers==expected_max_num_workers)
    {
        for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) g[x][y]=oo;
        for (int i=0;i<num_workers;i++)
        {
            vector<Point>& path=workers_path[i];
            for (int d=0,j=1;j<SIZE(path);j++) if (is_inside(path[j]))
            {
                d+=max(1,get_distance(path[j-1],path[j]));
                if (d<g[path[j].x][path[j].y]) g[path[j].x][path[j].y]=d;
            }
        }
    }
    vector<ipair> edges;
    if (!closeto_timeout && num_workers==expected_max_num_workers)
        for (int i=0;i<num_workers;i++) if (SIZE(workers_path[i])>1 && is_inside(workers_path[i][1]))
        {
            Point src=workers_path[i][0];
            Point dest=workers_path[i][1];
            int dst=get_distance(src,dest);
            for (int j=0;dst>=2 && j<num_snows;j++) 
            {
                int d1=get_distance(src,snows[j]);
                int d2=get_distance(snows[j],dest);
                if (d1>0 && d2>0 && d1+d2==dst && d1<g[snows[j].x][snows[j].y])
                    edges.push_back(MP(g[snows[j].x][snows[j].y]-d1,(i<<16)|j));
            }
        }
    int pre_fixed[MAX_NUM_WORKERS];
    memset(pre_fixed,255,num_workers*sizeof(int));
    bool covered[MAX_NUM_CELLS];
    memset(covered,false,num_snows*sizeof(bool));
    sort(edges.begin(),edges.end());
    for (int i=SIZE(edges)-1;i>=0;i--)
    {
        int w_idx=edges[i].second>>16;
        int p_idx=edges[i].second&65535;
        if (pre_fixed[w_idx]<0 && !covered[p_idx])
        {
            pre_fixed[w_idx]=get_direction(workers_path[w_idx][0],snows[p_idx]);
#ifdef DEBUG
            ASSERT(pre_fixed[w_idx]>=0);
#endif
            covered[p_idx]=true;
        }
    }
    for (int i=0;i<new_num_workers;i++)
        if (i<num_workers)
        {
            if (SIZE(workers_path[i])==0) workers_path[i].push_back(workers[i]);
#ifdef DEBUG
            ASSERT(is_same(workers_path[i][0],workers[i]));
#endif
            if (SIZE(workers_path[i])>1)
            {
                int d=pre_fixed[i];
                if (d<0) d=get_direction(workers_path[i][0],workers_path[i][1]);
                if (d>=0)
                {
                    if (results!=NULL)
                    {
                        char str[100];
                        sprintf(str,"M %d %c",i,DELTA_C[d]);
                        results->push_back(str);
                    }
                    workers[i].x+=DELTA_X[d];
                    workers[i].y+=DELTA_Y[d];
#ifdef DEBUG
                    ASSERT(is_inside(workers[i]));
#endif
                }
                is_idle_worker[i]=false;
            }
        }
        else
        {
#ifdef DEBUG
            ASSERT(SIZE(workers_path[i])>=1);
#endif
            if (results!=NULL)
            {
                char str[100];
                sprintf(str,"H %d %d",workers_path[i][0].x,workers_path[i][0].y);
                results->push_back(str);
            }
            workers[i]=workers_path[i][0];
            is_idle_worker[i]=false;
#ifdef DEBUG
            ASSERT(is_inside(workers[i]));
#endif
        }
}

void update_board()
{
    for (int i=0;i<num_workers;i++) board[workers[i].x][workers[i].y]=0;
    for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) if (board[x][y]) board[x][y]++;

    int num_snow_falls_left=0;
    for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) if (board[x][y]) num_snow_falls_left++;
    //update the cost.
    total_snow_fine+=num_snow_falls_left*snow_fine;
    total_salary+=num_workers*salary;
}

int get_overall_cost(int n,vector<Point> allpath[],vector<int> &idx)
{
    int s=0;
    for (int i=0;i<n;i++)
    {
        vector<Point>& path=allpath[i];
        if (idx[i]>=num_workers) s+=SIZE(path);
        if (SIZE(path)<=1) continue;
        for (int d=0,i=1;i<SIZE(path);i++)
        {
            int t=get_distance(path[i-1],path[i]);
            if (t==0) t=1;
            d+=t;
            s+=d;
        }
    }
    return s;
}

int get_overall_cost(int n,vector<Point> allpath[])
{
    vector<int> idx;
    for (int i=0;i<n;i++) idx.push_back(i);
    return get_overall_cost(n,allpath,idx);
}

int opt_cost[MAX_NUM_WORKERS];
vector<Point> opt_workers_path[MAX_NUM_WORKERS];
int g_pts_to_cluster[MAX_NUM_WORKERS][MAX_NUM_WORKERS];

void process2(vector<int> snow_falls,vector<string> *results,bool main_path,double timelimit,int rnd_round)
{
#ifdef DEBUG
    Timer t0(0);
#endif
    if (results!=NULL) results->clear();
    if (num_workers==0 && SIZE(snow_falls)==0)
    {
#ifdef DEBUG
        for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) ASSERT(board[x][y]==0);
#endif
        return;
    }
    double starttime=gettime();
#ifdef DEBUG
    int saved_num_workers=num_workers;
    Point saved_workers[MAX_NUM_WORKERS];
    for (int i=0;i<num_workers;i++) saved_workers[i]=workers[i];
#endif
    is_main_path=main_path;
    if (closeto_timeout) is_main_path=false;

    // update snow_falls.
    for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++)
        snow_log[x][y]=(snow_log[x][y]<<1)&(two(29)-1);
    for (int i=0;i<SIZE(snow_falls)/2;i++)
    {
        int x=snow_falls[i+i],y=snow_falls[i+i+1];
        board[x][y]=1;
        snow_log[x][y]|=1;
    }
#ifdef DEBUG
    for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++)
        if (board[x][y]>0 && board[x][y]<20)
            ASSERT((snow_log[x][y]&(1<<(board[x][y]-1)))>0);
#endif
    num_snows=0;
    for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) if (board[x][y]) 
        snow_idx[x][y]=num_snows,snows[num_snows++]=Point(x,y);
#ifdef DEBUG
    for (int k=0;k<num_workers;k++) ASSERT(is_inside(workers[k]));
#endif
    // clustering.
    bool is_idle_worker[MAX_NUM_WORKERS];
    for (int i=0;i<MAX_NUM_WORKERS;i++) is_idle_worker[i]=true;
    if (num_snows>0)
    {
        gen_clusters();
#ifdef DEBUG
        ASSERT(num_clusters>0 && num_clusters<=expected_max_num_workers);
#endif
        vector<Point> workers_path[MAX_NUM_WORKERS];
        vector<int> cluster_workers[MAX_NUM_WORKERS];
        int new_num_workers;
        allocate_workers_to_clusters(cluster_workers,new_num_workers,g_pts_to_cluster);
#ifdef DEBUG
        ASSERT(new_num_workers>0);
        ASSERT(num_workers<=new_num_workers && new_num_workers<=expected_max_num_workers);
        bool __allocated[MAX_NUM_WORKERS];
        memset(__allocated,false,sizeof(__allocated));
        for (int i=0;i<num_clusters;i++)
        {
            ASSERT(SIZE(cluster_workers[i])>0);
            for (int j=0;j<SIZE(cluster_workers[i]);j++)
            {
                int idx=cluster_workers[i][j];
                ASSERT(idx>=0 && idx<new_num_workers && !__allocated[idx]);
                __allocated[idx]=true;
            }
        }
#endif
        vector<Point> cluster_workers_path[MAX_NUM_WORKERS];
        vector<Point> cluster_prev_workers_path[MAX_NUM_WORKERS];
#ifdef DEBUG
        Counter __cc(num_clusters);
#endif
        for (int i=0;i<new_num_workers;i++) opt_workers_path[i].clear();
        for (int i=0;i<num_workers;i++) opt_workers_path[i].push_back(workers[i]);
        // Compute path.
        for (int k=0;k<num_clusters;k++) opt_cost[k]=oo;
        set<vector<int> > visited;
        for (int step=0;step<rnd_round;step++) for (int use_prev_path=0;use_prev_path<=1;use_prev_path++) for (int k=0;k<num_clusters;k++)
        {
            if ((closeto_timeout || gettime()>timelimit) && (use_prev_path || step>0)) continue;
            vector<int> w=cluster_workers[k];
            int h=SIZE(w);
            if (step>0 && h<=1) continue;
            bool findw=false;
            for (int p=0;p<10;p++)
            {
                if (step>0) for (int i=0;i<SIZE(w);i++) swap(w[i],w[i+rand()%(SIZE(w)-i)]);
                vector<int> state;
                state.push_back(k);
                state.push_back(use_prev_path);
                for (int i=0;i<SIZE(w);i++) state.push_back(w[i]);
                if (visited.find(state)!=visited.end()) continue;
                visited.insert(state);
                findw=true;
                break;
            }
            if (!findw) continue;
            int cost;
            if (use_prev_path) for (int i=0;i<h;i++) cluster_prev_workers_path[i]=prev_workers_path[w[i]];
            if (use_prev_path)
                cost=clean_snow_per_cluster(k,w,cluster_prev_workers_path,1,cluster_workers_path);
            else
                cost=clean_snow_per_cluster(k,w,NULL,0,cluster_workers_path);
            if (cost<0) continue;
            run_sa_per_cluster(h,cluster_workers_path,&w[0],timelimit);
            cost=get_overall_cost(h,cluster_workers_path,w);
            if (cost>=opt_cost[k]) continue;
            opt_cost[k]=cost;
            for (int i=0;i<h;i++) opt_workers_path[w[i]]=cluster_workers_path[i];
#ifdef DEBUG
            int s_cost=0;
            for (int i=0;i<h;i++) s_cost+=get_path_cost(opt_workers_path[w[i]],w[i]>=num_workers).second;
            ASSERT(s_cost==cost);
            for (int i=0;i<h;i++) 
                if (SIZE(cluster_workers_path[i])>0 && w[i]<num_workers)
                    ASSERT(is_same(cluster_workers_path[i][0],workers[w[i]]));
#endif
        }
#ifdef DEBUG
        for (int i=0;i<num_workers;i++) if (SIZE(opt_workers_path[i])>0)
            ASSERT(is_same(opt_workers_path[i][0],workers[i]));
        int __snows=0;
        for (int i=0;i<new_num_workers;i++) if (SIZE(opt_workers_path[i])>0) __snows+=SIZE(opt_workers_path[i])-1+(int)(i>=num_workers);
        ASSERT(__snows==num_snows);
#endif
        if (!closeto_timeout && num_clusters>1 && gettime()<timelimit)
        {
            int cnt=0,idx[MAX_NUM_WORKERS];
            for (int i=0;i<new_num_workers;i++) if (SIZE(opt_workers_path[i])>0)
            {
                cluster_workers_path[cnt]=opt_workers_path[i];
                idx[cnt++]=i;
            }
#ifdef DEBUG
            for (int i=0;i<num_workers;i++) if (SIZE(opt_workers_path[i])>0)
                ASSERT(is_same(opt_workers_path[i][0],workers[i]));
#endif
            run_sa_per_cluster(cnt,cluster_workers_path,idx,timelimit);
            for (int i=0;i<cnt;i++) opt_workers_path[idx[i]]=cluster_workers_path[i];
#ifdef DEBUG
            for (int i=0;i<num_workers;i++) if (SIZE(opt_workers_path[i])>0)
                ASSERT(is_same(opt_workers_path[i][0],workers[i]));
#endif
        }
        if (!closeto_timeout && main_path && num_clusters>1 && gettime()<timelimit)
        {
            int best_cost=get_overall_cost(new_num_workers,opt_workers_path);
            int tmp_cluster_idx[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
            memcpy(tmp_cluster_idx,cluster_idx,sizeof(cluster_idx));
            cluster_size[MAX_NUM_WORKERS]=0;
            for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) if (cluster_idx[x][y]>=0)
            {
                cluster_idx[x][y]=MAX_NUM_WORKERS;
                cluster_pts_all[MAX_NUM_WORKERS][cluster_size[MAX_NUM_WORKERS]++]=Point(x,y);
            }
            vector<int> all_workers;
            for (int i=0;i<new_num_workers;i++) all_workers.push_back(i);
            for (int strategy=0;gettime()<timelimit && strategy<3;strategy++)
            {
                int cost;
                if (strategy==0)
                    cost=clean_snow_per_cluster(MAX_NUM_WORKERS,all_workers,NULL,0,cluster_workers_path);
                else if (strategy==1)
                {
                    for (int i=0;i<new_num_workers;i++)
                        if (i>=num_workers)
                            cluster_prev_workers_path[i].clear();
                        else
                            cluster_prev_workers_path[i]=prev_workers_path[i];
                    cost=clean_snow_per_cluster(MAX_NUM_WORKERS,all_workers,cluster_prev_workers_path,1,cluster_workers_path);
                }
                else
                {
                    if (num_workers!=new_num_workers) continue;
                    for (int i=0;i<new_num_workers;i++)
                    {
                        cluster_prev_workers_path[i].clear();
                        vector<Point>& path=opt_workers_path[i];
                        if (SIZE(path)>=1) cluster_prev_workers_path[i].push_back(path[0]);
                        if (SIZE(path)>=2 && !is_same(path[0],path[1])) cluster_prev_workers_path[i].push_back(path[1]);
                    }
                    cost=clean_snow_per_cluster(MAX_NUM_WORKERS,all_workers,cluster_prev_workers_path,1,cluster_workers_path);
                }
                if (cost<0) continue;
#ifdef DEBUG
                int old_cost=get_overall_cost(new_num_workers,cluster_workers_path);
                ASSERT(old_cost==cost);
#endif
#ifdef DEBUG
                for (int i=0;i<num_workers;i++) if (SIZE(cluster_workers_path[i])>0)
                    ASSERT(is_same(cluster_workers_path[i][0],workers[i]));
#endif
                int all_idx[MAX_NUM_WORKERS];
                for (int i=0;i<new_num_workers;i++) all_idx[i]=i;
                run_sa_per_cluster(new_num_workers,cluster_workers_path,all_idx,timelimit);
#ifdef DEBUG
                for (int i=0;i<num_workers;i++) if (SIZE(cluster_workers_path[i])>0)
                    ASSERT(is_same(cluster_workers_path[i][0],workers[i]));
#endif
                int new_cost=get_overall_cost(new_num_workers,cluster_workers_path);
#ifdef DEBUG
                ASSERT(new_cost<=old_cost);
#endif
                if (new_cost<best_cost)
                {
                    best_cost=new_cost;
                    for (int i=0;i<new_num_workers;i++) opt_workers_path[i]=cluster_workers_path[i];
                }
            }
            memcpy(cluster_idx,tmp_cluster_idx,sizeof(cluster_idx));
        }
        if (SIZE(snow_falls)==0 && num_workers==new_num_workers)
        {
            int total_cost=get_overall_cost(num_workers,opt_workers_path);
            int prev_path_total_cost=get_overall_cost(num_workers,prev_workers_path);
            if (prev_path_total_cost<total_cost)
                for (int i=0;i<num_workers;i++) 
                {
                    vector<Point>& path=prev_workers_path[i];
                    opt_workers_path[i].clear();
                    opt_workers_path[i].reserve(SIZE(path));
                    for (int j=0;j<SIZE(path);j++) if (j==0 || board[path[j].x][path[j].y]) opt_workers_path[i].push_back(path[j]);
                }
        }
        for (int i=0;i<new_num_workers;i++) workers_path[i]=opt_workers_path[i];
        int left_round=MAX_NUM_ROUNDS-current_round;
        int dst_limit=left_round+1+min(3,left_round);
        for (int i=0;i<num_workers;i++) 
            if (SIZE(workers_path[i])>1 && get_distance(workers_path[i][0],workers_path[i][1])>dst_limit)
                workers_path[i].clear();
        remove_idle_new_workers(new_num_workers,workers_path);
        generate_moves(new_num_workers,workers_path,results,is_idle_worker);
        num_workers=new_num_workers;
#ifdef DEBUG
        ASSERT(num_workers<=expected_max_num_workers);
#endif
        for (int i=0;i<MAX_NUM_WORKERS;i++) prev_workers_path[i].clear();
        for (int i=0;i<num_workers;i++) if (!is_idle_worker[i])
        {
            prev_workers_path[i].clear();
            prev_workers_path[i].push_back(workers[i]);
            for (int k=1;k<SIZE(workers_path[i]);k++)
            {
                Point p=workers_path[i][k];
#ifdef DEBUG
                if (!is_inside(p)) ASSERT(k==1 && SIZE(workers_path[i])==2);
#endif
                if (k==1 && is_same(p,workers[i])) continue;
                if (is_inside(p))
                {
#ifdef DEBUG
                    ASSERT(board[p.x][p.y]);
#endif
                    prev_workers_path[i].push_back(p);
                }
            }
        }
    }
    else
        for (int i=0;i<MAX_NUM_WORKERS;i++) prev_workers_path[i].clear();
    handle_idle_workers(is_idle_worker,results);
#ifdef DEBUG
    for (int i=0;i<num_workers;i++) ASSERT(is_inside(workers[i]));
#endif
    update_board();

#ifdef DEBUG
    if (results!=NULL)
    {
        bool __is_moved[MAX_NUM_WORKERS];
        memset(__is_moved,false,sizeof(__is_moved));
        int __new_worker_idx=saved_num_workers;
        for (int i=0;i<results->size();i++)
        {
            string s=(*results)[i];
            if (s[0]=='M')
            {
                int idx;
                char dir[4];
                sscanf(s.c_str()+1,"%d%s",&idx,dir);
                ASSERT(idx>=0 && idx<saved_num_workers && !__is_moved[idx]);
                __is_moved[idx]=true;
                ASSERT(strlen(dir)==1);
                int j=0;
                for (;j<4 && DELTA_C[j]!=dir[0];j++);
                ASSERT(j<4);
                saved_workers[idx].x+=DELTA_X[j];
                saved_workers[idx].y+=DELTA_Y[j];
            }
            else if (s[0]=='H')
            {
                int x,y;
                sscanf(s.c_str()+1,"%d%d",&x,&y);
                saved_workers[__new_worker_idx++]=Point(x,y);
            }
            else { ASSERT(0); }
        }
        ASSERT(__new_worker_idx==num_workers);
        for (int i=0;i<num_workers;i++) ASSERT(is_same(workers[i],saved_workers[i]));
    }
#endif
}

State final_imp_best_state;
void process(vector<int> snow_falls,vector<string> *results,bool main_path,double timelimit,int rnd_round=1)
{
    if (closeto_timeout || current_round<=PARAM_FINAL_OPT_ROUND || expected_max_num_workers==MAX_NUM_WORKERS)
    {
#ifdef DEBUG
        if (main_path) 
        {
            Timer t31(31);
            process2(snow_falls,results,main_path,timelimit,rnd_round);
            return;
        }
#endif
        process2(snow_falls,results,main_path,timelimit,rnd_round);
        return;
    }
#ifdef DEBUG
    ASSERT(main_path);
#endif
#ifdef DEBUG
    Timer t32(32);
#endif
    int saved_final_cost[MAX_NUM_WORKERS+1];
    int MAXD=3;
    for (int d=expected_max_num_workers;d<=MAX_NUM_WORKERS && d<=expected_max_num_workers+MAXD;d++)
    {
        double current_time=gettime();
        if (d>expected_max_num_workers && current_time>=timelimit) break;
        double local_timelimit;
        if (d==expected_max_num_workers)
        {
            local_timelimit=(current_time+timelimit)/2.0;
            if (d==MAX_NUM_WORKERS) local_timelimit=timelimit;
        }
        else
        {
            int left_round=1+min(MAX_NUM_WORKERS-d,expected_max_num_workers+MAXD-d);
            local_timelimit=current_time+(timelimit-current_time)/left_round;
        }
        int old_expected_max_num_workers=expected_max_num_workers;
        save_state();
        expected_max_num_workers=d;
        vector<string> tmp_results;
        process2(snow_falls,&tmp_results,true,local_timelimit,rnd_round);
        if (d==old_expected_max_num_workers) 
        {
            *results=tmp_results;
            final_imp_best_state.copy_from_global_var();
        }
        bool adjusted=false;
        int left_after_this_round=min(PARAM_FINAL_OPT_BUFFER_SIZE,MAX_NUM_ROUNDS-current_round);
        if (d==old_expected_max_num_workers || num_workers==expected_max_num_workers)
        {
            saved_final_cost[d]=total_snow_fine+total_salary;
            saved_final_cost[d]+=num_workers*salary*left_after_this_round;
            int g[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
            for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) g[x][y]=left_after_this_round;
            for (int i=0;i<num_workers;i++) for (int d=0,j=1;j<SIZE(prev_workers_path[i]);j++)
            {
                const Point& p=prev_workers_path[i][j];
#ifdef DEBUG
                ASSERT(!is_same(prev_workers_path[i][j-1],p));
#endif
                d+=get_distance(prev_workers_path[i][j-1],p);
                if (d>left_after_this_round) break;
                if (d-1<g[p.x][p.y]) g[p.x][p.y]=d-1;
            }
            for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) if (board[x][y]) 
                saved_final_cost[d]+=snow_fine*g[x][y];
            if (d>old_expected_max_num_workers &&
                saved_final_cost[d]<saved_final_cost[old_expected_max_num_workers])
            {
                if (case_study_seed>=0)
                    printf("finali #num_workers = %d -> %d   @ %d\n",old_expected_max_num_workers,d,current_round);
                *results=tmp_results;
                final_imp_best_state.copy_from_global_var();
                adjusted=true;
            }
        }
        load_state();
        expected_max_num_workers=((adjusted)?d:old_expected_max_num_workers);
    }
    final_imp_best_state.copy_to_global_var();
}

int get_buffer_length(int d)
{
    int buffer_length=PARAM_ADJUST_NUM_WORKERS_BUFFER_SIZE;
    if (first_snow_round>=0 && current_round-first_snow_round<PARAM_ADJUST_NUM_WORKERS_BUFFER_SIZE_MAX_CUTROUND)
        buffer_length=PARAM_ADJUST_NUM_WORKERS_BUFFER_SIZE_MAX;
    if (d<=3)
        buffer_length/=2;
    else if (d<=7)
        buffer_length=(int)((double)buffer_length*(double)(d+2)/10.0);
//    return max(max_no_snow_period,buffer_length);
    return buffer_length;
}

int get_real_next_cost(int d,double timelimit)
{
    save_state();
    int x=current_round-1;
    int old_expected_max_num_workers=expected_max_num_workers;
    expected_max_num_workers=d;
    process(saved_snow_falls[x],NULL,false,timelimit);
    int score=total_snow_fine+total_salary;
    int buffer_length=PARAM_ADJUST_NUM_WORKERS_CHECK_REALDATA_BUFFER;
    if (board_size<=25) buffer_length-=10;
    else if (board_size>40) buffer_length+=10;
    score+=num_workers*salary*buffer_length;
    int g[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) g[x][y]=buffer_length;
    for (int i=0;i<num_workers;i++) for (int d=0,j=1;j<SIZE(prev_workers_path[i]);j++)
    {
        const Point& p=prev_workers_path[i][j];
#ifdef DEBUG
        ASSERT(!is_same(prev_workers_path[i][j-1],p));
#endif
        d+=get_distance(prev_workers_path[i][j-1],p);
        if (d>buffer_length) break;
        if (d-1<g[p.x][p.y]) g[p.x][p.y]=d-1;
    }
    for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) if (board[x][y]) score+=snow_fine*g[x][y];
    expected_max_num_workers=old_expected_max_num_workers;
    load_state();
    return score;
}

void adjust_num_workers()
{
    if (current_round>=PARAM_FINAL_OPT_ROUND) return;
#ifdef DEBUG
    Timer t33(33);
#endif
    double starttime=gettime();
    double timelimit=starttime+timeleft_adjust_num_workers;
    int saved_next_cost[MAX_NUM_WORKERS+1];
    int buffer_length=get_buffer_length(expected_max_num_workers);
    int real_next_cost[MAX_NUM_WORKERS+1];
    for (int i=0;i<=MAX_NUM_WORKERS;i++) real_next_cost[i]=-1;
    for (int d=expected_max_num_workers;
        gettime()<timelimit && d<=MAX_NUM_WORKERS && 
        d<=max(expected_max_num_workers,1+PARAM_SMALL_NUM_WORKERS)+PARAM_ADJUST_NUM_WORKERS_MAX_INC;d++)
    {
        int old_expected_max_num_workers=expected_max_num_workers;
        expected_max_num_workers=d;
        save_state();
        cmp_adjust_state[d].copy_to_global_var();
#ifdef DEBUG
        ASSERT(cmp_adjust_round[d]<=current_round);
#endif
        for (;gettime()<timelimit && cmp_adjust_round[d]<current_round;cmp_adjust_round[d]++)
        {
            int x=cmp_adjust_round[d];
            process(saved_snow_falls[x],NULL,false,timelimit);
            cmp_adjust_score[d][x+1]=total_snow_fine+total_salary;
        }
        cmp_adjust_state[d].copy_from_global_var();
        bool adjusted=false;
        if (gettime()<timelimit && first_snow_round>=0 && (d==old_expected_max_num_workers || num_workers==expected_max_num_workers))
        {
            saved_next_cost[d]=total_snow_fine+total_salary;
            saved_next_cost[d]+=num_workers*salary*buffer_length;
            int g[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
            for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) g[x][y]=buffer_length;
            for (int i=0;i<num_workers;i++) for (int d=0,j=1;j<SIZE(prev_workers_path[i]);j++)
            {
                const Point& p=prev_workers_path[i][j];
#ifdef DEBUG
                ASSERT(!is_same(prev_workers_path[i][j-1],p));
#endif
                d+=get_distance(prev_workers_path[i][j-1],p);
                if (d>buffer_length) break;
                if (d-1<g[p.x][p.y]) g[p.x][p.y]=d-1;
            }
            for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) if (board[x][y]) saved_next_cost[d]+=snow_fine*g[x][y];
            if (d>old_expected_max_num_workers &&
                saved_next_cost[d]<saved_next_cost[old_expected_max_num_workers])
            {
                if (case_study_seed>=0)
                    printf("adjust #num_workers = %d -> %d   @ %d\n",old_expected_max_num_workers,d,current_round);
                adjusted=true;
            }
        }
        load_state();
        if (adjusted)
        {
            if (gettime()<timelimit && real_next_cost[old_expected_max_num_workers]<0)
                real_next_cost[old_expected_max_num_workers]=get_real_next_cost(old_expected_max_num_workers,timelimit);
            if (gettime()<timelimit && real_next_cost[d]<0)
                real_next_cost[d]=get_real_next_cost(d,timelimit);
            if (gettime()<timelimit && real_next_cost[d]>=real_next_cost[old_expected_max_num_workers])
            {
                adjusted=false;
                if (case_study_seed>=0) printf("rollback %d %d\n",real_next_cost[d],real_next_cost[old_expected_max_num_workers]);
            }
        }
        expected_max_num_workers=adjusted?d:old_expected_max_num_workers;
        int new_buffer_length=get_buffer_length(expected_max_num_workers);
        if (new_buffer_length!=buffer_length)
        {
            save_state();
            cmp_adjust_state[d].copy_to_global_var();
            buffer_length=new_buffer_length;
            saved_next_cost[d]=total_snow_fine+total_salary;
            saved_next_cost[d]+=num_workers*salary*buffer_length;
            int g[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
            for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) g[x][y]=buffer_length;
            for (int i=0;i<num_workers;i++) for (int d=0,j=1;j<SIZE(prev_workers_path[i]);j++)
            {
                const Point& p=prev_workers_path[i][j];
#ifdef DEBUG
                ASSERT(!is_same(prev_workers_path[i][j-1],p));
#endif
                d+=get_distance(prev_workers_path[i][j-1],p);
                if (d>buffer_length) break;
                if (d-1<g[p.x][p.y]) g[p.x][p.y]=d-1;
            }
            for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) if (board[x][y]) saved_next_cost[d]+=snow_fine*g[x][y];
            load_state();
        }
    }
    timeleft_adjust_num_workers-=gettime()-starttime;
}

class SnowCleaning
{
public:
    int init(int,int,int);
    vector<string> nextDay(vector<int>);
};
int SnowCleaning::init(int a,int b,int c)
{
    srand(1028);
    board_size=a;
    salary=b;
    snow_fine=c;
    expected_max_num_workers=PARAM_INIT_NUM_WORKERS;
    current_round=0;
    first_snow_round=-1;
    last_snow_round=-1;
    max_no_snow_period=-1;
    ::init();
    for (int i=0;i<=MAX_NUM_WORKERS;i++)
    {
        cmp_adjust_round[i]=0;
        cmp_adjust_score[i][0]=0;
        cmp_adjust_state[i].copy_from_global_var();
    }
    timeleft_adjust_num_workers=TIME_ADJUST_NUM_WORKERS;
    timeleft_main_path_before_final_adjust=TIME_MAIN_PATH_BEFORE_FINAL_ADJUST;
    timeleft_final_adjust=TIME_FINAL_ADJUST;
    return 0;
}

double rw[MAX_NUM_ROUNDS+10];
double rt[MAX_NUM_ROUNDS+10];

vector<string> SnowCleaning::nextDay(vector<int> a)
{
    starttime_acrush=rdtsc();
    if (current_round-last_snow_round-1>max_no_snow_period) max_no_snow_period=current_round-last_snow_round-1;
    if (SIZE(a)>0)
    {
        if (first_snow_round<0) first_snow_round=current_round;
        last_snow_round=current_round;
    }
    saved_snow_falls[current_round++]=a;
    double current_time=gettime();
    if (current_time>TIMELIMIT_OVERALL)
    {
#ifdef DEBUG
        ASSERT(0);
#endif
        vector<string> results;
        for (int i=0;i<SIZE(a);i+=2) board[a[i]][a[i+1]]=1;
        for (int i=0;i<num_workers;i++) board[workers[i].x][workers[i].y]=0;
        int num_snows=0;
        for (int x=0;x<board_size;x++) for (int y=0;y<board_size;y++) if (board[x][y]) num_snows++;
        total_snow_fine+=num_snows*snow_fine;
        total_salary+=num_workers*salary;
        return results;
    }
    else
    {
        if (current_round==1) rt[0]=rw[0]=0;
        vector<string> results;
        closeto_timeout=(current_time>TIMELIMIT_CLOSETO_TIMEOUT);
        if (closeto_timeout)
        {
            printf("closeto_timeout @ %d\n",current_round);
        }
        if (!closeto_timeout && timeleft_adjust_num_workers>0) adjust_num_workers();
        double timelimit;
        if (current_round<=PARAM_FINAL_OPT_ROUND)
        {
            timelimit=timeleft_main_path_before_final_adjust/(PARAM_FINAL_OPT_ROUND-current_round+1);
            double t=TIME_MAIN_PATH_BEFORE_FINAL_ADJUST/PARAM_FINAL_OPT_ROUND*(PARAM_FINAL_OPT_ROUND-current_round);
            t=timeleft_main_path_before_final_adjust-t;
            if (t>timelimit) timelimit=t;
        }
        else
        {
            timeleft_final_adjust+=timeleft_main_path_before_final_adjust+timeleft_adjust_num_workers;
            timeleft_main_path_before_final_adjust=timeleft_adjust_num_workers=0;
            timelimit=timeleft_final_adjust/(MAX_NUM_ROUNDS-current_round+1);
            double t=TIME_MAIN_PATH_BEFORE_FINAL_ADJUST+TIME_ADJUST_NUM_WORKERS+
                TIME_FINAL_ADJUST/(MAX_NUM_ROUNDS-PARAM_FINAL_OPT_ROUND)*(current_round-PARAM_FINAL_OPT_ROUND+1);
            t-=gettime();
            if (t>timelimit) timelimit=t;
        }
        int rnd_round=1;
        if (!closeto_timeout && current_round>=400)
        {
            int x=min(PARAM_FINAL_OPT_ROUND-1,current_round)-1;
            double avg=(rt[x]-rt[x-300])/(rw[x]-rw[x-300]);
            double e1,e2;
            if (current_round<PARAM_FINAL_OPT_ROUND)
            {
                e1=avg*(PARAM_FINAL_OPT_ROUND-current_round);
                e2=timeleft_main_path_before_final_adjust-0.6*TIMES_PER_SEC;
            }
            else
            {
                e1=avg*3*(MAX_NUM_ROUNDS-current_round);
                e2=timeleft_final_adjust-0.3*TIMES_PER_SEC;
            }
            rnd_round=(int)(e2/e1);
            if (rnd_round<1) rnd_round=1;
            if (rnd_round>20) rnd_round=20;
        }
        double start_time=gettime();
        process(a,&results,true,start_time+timelimit,rnd_round);
        double end_time=gettime();
        rw[current_round]=rw[current_round-1]+1+(rnd_round-1)*0.6;
        rt[current_round]=rt[current_round-1]+(end_time-start_time);
        if (current_round<=PARAM_FINAL_OPT_ROUND)
            timeleft_main_path_before_final_adjust-=(end_time-start_time);
        else
            timeleft_final_adjust-=(end_time-start_time);
        timeused_acrush+=rdtsc()-starttime_acrush;
        if (case_study_seed>=0 && current_round==MAX_NUM_ROUNDS)
        {
            printf("TimeUsed = %.3lf\n",(double)timeused_acrush/TIMES_PER_SEC);
            printf("#NumWorkers = %d\n",num_workers);
        }
#ifndef LOCAL
        if (current_round==MAX_NUM_ROUNDS)
        {
            printf("Fine   = %d\nSalary = %d\nScore  = %d\n",total_snow_fine,total_salary,total_snow_fine+total_salary);
            printf("TimeUsed = %.3lf\n",(double)timeused_acrush/TIMES_PER_SEC);
            printf("#NumWorkers = %d\n",num_workers);
        }
#endif
#ifdef DEBUG
        ASSERT(timeused_acrush<=TIMELIMIT_FINAL);
#endif
        return results;
    }
}

#ifdef LOCAL

int main(int argc,char** args)
{
    if (argc==1) case_study_seed=-1;
    if (argc==2) case_study_seed=atoi(args[1]);
    if (case_study_seed>=0)
    {
        char filename[100];
        sprintf(filename,"..\\Data\\%d.dat",case_study_seed);
        freopen(filename,"r",stdin);
    }
    int n,s1,s2;
    scanf("%d%d%d",&n,&s1,&s2);
    SnowCleaning *sp=new SnowCleaning();
    sp->init(n,s1,s2);
    if (case_study_seed>=0)
    {
        printf("board_size = %d\n",n);
        printf("salary = %d\n",s1);
        printf("snowfine = %d\n",s2);
    }
    for (int t=0;t<2000;t++)
    {
        int c,p;
        scanf("%d",&c);
        vector<int> d;
        for (int i=0;i<2*c;i++)
        {
            scanf("%d",&p);
            d.push_back(p);
        }
        vector<string> ret=sp->nextDay(d);
        if (case_study_seed<0)
        {
            printf("%d\n",SIZE(ret));
            for (int i=0;i<SIZE(ret);i++) printf("%s\n",ret[i].c_str());
            fflush(stdout);
        }
    }
    if (case_study_seed<0) return 0;
    printf("Fine   = %d\nSalary = %d\nScore  = %d\n",total_snow_fine,total_salary,total_snow_fine+total_salary);
#ifdef DEBUG
    Timer::show();
    Counter::show();
#endif
    return 0;
}
#endif
