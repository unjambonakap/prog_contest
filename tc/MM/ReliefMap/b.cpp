#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <algorithm>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <climits>
//#include <ext/hash_map>


using namespace std;

//////////////////////////////////////////////////////////////////////////
// TIME MANAGEMENT

#include <time.h>
#ifndef WIN32
#include <sys/time.h>
#else
#include <windows.h>
#endif

inline double get_time()
{
#ifndef WIN32
    timeval tv;
    gettimeofday(&tv, 0);
    return tv.tv_sec+1e-6*tv.tv_usec;
#else
    __int64 qw;
    QueryPerformanceCounter((LARGE_INTEGER *)&qw);
    __int64 f;
    QueryPerformanceFrequency((LARGE_INTEGER *)&f);
    return (double)qw/f;
#endif
}

typedef vector<int> VI;
typedef vector<pair<int,int> > VII;
typedef vector<vector<int> > VVI;
typedef vector<vector<double> > VVD;

namespace Relief{
 
double measure(int x, int y){ 
    puts("?");
    fprintf(stdout,"%d\n%d\n", x,y);
    fflush(stdout);
    double res; scanf(" %lf", &res);
    return res;
}

};

#define NMAXC 20000


double g_start_time = 0;
double hh[501][501];
int    cidx[501][501]; // contour idx : >0 for contour lines, <0 for regions
int    ridx[501][501]; // region idx
double ch[NMAXC+1]; // contour height
char cbord[NMAXC+1]; // 1 if contour i touches the border
int NC; // number of contours (index 1..NC)
int NIC;
int NR; // number of regions (index -1 .. -NR)
int cx[NMAXC+1], cy[NMAXC+1]; // first x,y of each contour
int cminx[NMAXC+1], cmaxx[NMAXC+1], cminy[NMAXC+1], cmaxy[NMAXC+1];
char ce[NMAXC+1];
char known[NMAXC+1];
VVD measures;
vector<char> terminal;
int g_minc = 1, g_maxc = 1;
double gD = 10;

#define NPATTERNS 6
int cpatterns[NPATTERNS][3][3] = {
    {{1,0,1},
        {1,1,1},
        {0,1,0}},

    {{0,1,0},
        {1,1,1},
        {1,0,1}},

    {{1,1,0},
        {0,1,1},
        {1,1,0}},

    {{0,1,1},
        {1,1,0},
        {0,1,1}},

    {{1,1,1},
        {0,1,0},
        {1,1,1}},

    {{1,0,1},
        {1,1,1},
        {1,0,1}},
};

vector<VII > vcp;

int mark_dir = 0;
int mark_dx[4] = {1,0,-1,0};
int mark_dy[4] = {0,-1,0,1};

struct MarkPoint{
    int cx, cy;

    bool operator == (const struct MarkPoint &s)
    {
        return (cx == s.cx) && (cy==s.cy);
    }
};

class ReliefMap{
    public:
        int H,W;
        int nmaxmeasures;

        inline double sqrdist(int x1, int y1, int x2, int y2)
        {
            return (x1-x2)*(x1-x2)+ (y1-y2)*(y1-y2);
        }

        double B0(double t) { return pow(1-t,3)/6;}
        double B1(double t) { return (3*t*t*t - 6*t*t +4)/6;}
        double B2(double t) { return (-3*t*t*t + 3*t*t + 3*t + 1)/6; }
        double B3(double t) { return t*t*t/6; }

        double B(int k, double t)
        {
            switch(k)
            {
                case 0:return B0(t);
                case 1:return B1(t);
                case 2:return B2(t);
                case 3:return B3(t);
            }
            return 0;
        }

        double fi[203][203];
        double newfi[203][203];
        double weightfi[203][203];
        int BSW, BSH;
        int bsofsx, bsofsy;

        inline int vcpsize(int c)
        {
            if(c<0 || c>=(int)vcp.size())
                return 0;
            return (int)vcp[c].size();
        }

        double evalf(int x, int y)
        {
            double xx = 1 + (1.0*(x+bsofsx)*BSW/W);
            double yy = 1 + (1.0*(y+bsofsy)*BSH/H);
            int i = (int)xx - 1;
            int j = (int)yy - 1;
            double s = xx - (int)xx;
            double t = yy - (int)yy;

            double res = 0 ;
            for(int k=0;k<=3;k++)
                for(int l=0;l<=3;l++)
                    res += B(k, s) * B(l, t) * fi[j+l][i+k];


            return res;
        }

        void init_fi(int xxx)
        {
            BSH = H/xxx;
            BSW = W/xxx;
            for(int i=0;i<=BSH+3;i++)
                for(int j=0;j<=BSW+3;j++)
                {
                    fi[i][j] = 0;
                }
        }

        double iterate_fi(int maxc)
        {
            for(int i=0;i<=BSH+3;i++)
                for(int j=0;j<=BSW+3;j++)
                {
                    newfi[i][j] = 0;
                    weightfi[i][j] = 0;
                }

            double err = 0;
            int nerr = 0;

            for(int c=1;c<=maxc;c++)
                if(ch[c]>=0)
                {
                    for(int n=0;n<(int)vcpsize(c);n++)
                    {
                        int xc = vcp[c][n].first, yc = vcp[c][n].second;
                        double zc = ch[c] - evalf(xc, yc);
                        err += zc*zc;
                        nerr++;

                        double xx = 1 + (1.0*(xc+bsofsx)*BSW/W);
                        double yy = 1 + (1.0*(yc+bsofsy)*BSH/H);
                        int i = (int)xx - 1;
                        int j = (int)yy - 1;
                        double s = xx - (int)xx;
                        double t = yy - (int)yy;

                        double res = 0 ;
                        for(int k=0;k<=3;k++)
                            for(int l=0;l<=3;l++)
                            {
                                double w = B(k, s) * B(l, t);
                                newfi[j+l][i+k] += zc * w;
                                weightfi[j+l][i+k] += w;
                            }
                    }
                }

            for(int i=0;i<=BSH+3;i++)
                for(int j=0;j<=BSW+3;j++)
                {
                    if(weightfi[i][j] > 0)
                    {
                        fi[i][j] = fi[i][j] + (newfi[i][j]/weightfi[i][j]) * 0.5;
                    }
                }

            err/=nerr;
            return err;
        }

        inline double ffi(int i, int j)
        {
            if(i<0 || j<0)return 0;
            return fi[i][j];
        }

        void refine_fi()
        {
            int new_BSW = BSW*2;
            int new_BSH = BSH*2;
            cerr<<"Refining b-spline matrix... "<<BSW<<","<<BSH<<"->"<<new_BSW<<","<<new_BSH<<endl;

            double test = evalf(0,0);

            for(int i=0;i<BSH+3;i++)
                for(int j=0;j<BSW+3;j++)
                {
                    //if(i>0 && j>0 && i<BSH+1 && j<BSW+1)
                    {
                        newfi[2*i][2*j] = (1.0/64)*(ffi(i-1,j-1) + ffi(i-1,j+1) + ffi(i+1,j-1) + ffi(i+1,j+1)
                                + 6*(ffi(i-1,j) + ffi(i,j-1) + ffi(i,j+1) + ffi(i+1,j))
                                + 36*ffi(i,j));
                        newfi[2*i][2*j+1] = (1.0/16)*(ffi(i-1,j) + ffi(i-1,j+1) + ffi(i+1,j) + ffi(i+1,j+1)
                                + 6*(ffi(i,j) + ffi(i,j+1)));
                        newfi[2*i+1][2*j] = (1.0/16)*(ffi(i,j-1) + ffi(i,j+1) + ffi(i+1,j-1) + ffi(i+1,j+1)
                                + 6*(ffi(i,j) + ffi(i+1,j)));
                        newfi[2*i+1][2*j+1] = (1.0/4)*(ffi(i,j)+ffi(i,j+1)+ffi(i+1,j)+ffi(i+1,j+1));
                    }
                    /*            else 
                                  {
                                  newfi[2*i][2*j] = 0;
                                  newfi[2*i][2*j+1] = 0;
                                  newfi[2*i+1][2*j] = 0;
                                  newfi[2*i+1][2*j+1] = 0;
                                  }*/
                }

            BSW = new_BSW;
            BSH = new_BSH;
            for(int i=0;i<BSH+3;i++)
                for(int j=0;j<BSW+3;j++)
                {
                    fi[i][j] = newfi[i+1][j+1];
                }

            double test2 = evalf(0,0);
        }

        void bspline(int xxx = 20)
        {
            double prec = 0.05;
            int best_ofsx = 0, best_ofsy=0;
            /*    double best_err = 1e20;
                  for(bsofsx=0;bsofsx<5;bsofsx+=2)
                  for(bsofsy=0;bsofsy<5;bsofsy+=2)
                  {
                  init_fi(xxx);
                  double err = iterate_fi(NC);
                  err = iterate_fi(NC);
                  if(err<best_err)
                  {
                  best_err = err;
                  best_ofsx = bsofsx;
                  best_ofsy = bsofsy;
                  }
                  }

                  cerr<<"bestofsx = "<<best_ofsx<<" bestofsy="<<best_ofsy<<endl;*/
            bsofsx = best_ofsx;
            bsofsy = best_ofsy;
            init_fi(xxx);
            double prev_err = iterate_fi(NC);
            double err= prev_err;
            int nsteps = 1;
            cerr<<err<<endl;
            while(err > 10 && err <= prev_err && nsteps++<10)
            {
                err = iterate_fi(NC);
                cerr<<err<<endl;
            }
            prev_err = iterate_fi(NIC);
            err = prev_err;
            nsteps = 1;
            cerr<<err<<endl;
            while(err > prec && err <= prev_err && nsteps++<20  && get_time()-g_start_time < 9)
            {
                err = iterate_fi(NIC);
                cerr<<err<<endl;
            }

            int nrsteps = 0;
            while(err>prec && get_time()-g_start_time < 9 && BSW<100 && BSH<100 && nrsteps++ < 2) 
            {
                refine_fi();
                prev_err = iterate_fi(NIC);
                err = prev_err;
                nsteps = 1;
                cerr<<err<<endl;
                while(err > prec && err <= prev_err && nsteps++<20 && get_time()-g_start_time < 9)
                {
                    err = iterate_fi(NIC);
                    cerr<<err<<endl;
                }
            }
        }

        vector<map<int, char> > clinks;
        vector<set<int> > rlinks;

        void set_link(int id1, int id2, char dir)
        {
            if(id1>=(int)clinks.size())clinks.resize(id1+1);
            if(id2>=(int)clinks.size())clinks.resize(id2+1);
            clinks[id1][id2] = dir;
            clinks[id2][id1] = -dir;
        }

        bool is_link(int id1, int id2)
        {
            if(id1>=(int)clinks.size())return false;
            if(id2>=(int)clinks.size())return false;

            if(clinks[id1].find(id2) == clinks[id1].end())return false;
            return true;
        }

        int num_links(int id)
        {
            if(id>=(int)clinks.size())return 0;
            return (int)clinks[id].size();
        }

        int num_real_links(int id)
        {
            if(id>=(int)clinks.size())return 0;
            int res = 0;
            for(map<int, char>::iterator it = clinks[id].begin(); it != clinks[id].end(); it++)
            {
                int c = it->first;
                if(vcpsize(c) > 5)
                    res++;
            }
            return res;
        }

        void get_real_links(int id, vector<int> &res)
        {
            if(id>=(int)clinks.size())return;
            for(map<int, char>::iterator it = clinks[id].begin(); it != clinks[id].end(); it++)
            {
                int c = it->first;
                if(vcpsize(c) > 5)
                    res.push_back(c);
            }
        }

        bool is_real_contour(int c)
        {
            if(c >= (int)vcp.size())
                return false;
            return vcpsize(c)>9;
        }

        void blur(const vector<double> &input, vector<double> &output, double f)
        {
            for(int y = 0; y < H; y++)
                for(int x = 0; x< W; x++)
                {
                    if(hh[y][x]>=0)
                        output[y*W+x] = hh[y][x];
                    else
                    {
                        int n=0;
                        double h=0;
                        for(int dx=-1;dx<=1;dx++)if(dx+x>=0 && dx+x<W)
                            for(int dy=-1;dy<=1;dy++)if(dy+y>=0 && dy+y<H)
                            {
                                h += input[(dy+y)*W+dx+x];
                                n++;
                            }

                        if(n)
                            output[y*W+x] = input[y*W+x]*(1-f)+(h/n)*f;
                    }
                }
        }

        void blur2(const vector<double> &input, vector<double> &output, double f)
        {
            for(int y = 0; y < H; y++)
                for(int x = 0; x< W; x++)
                {
                    if(cidx[y][x]>0)
                        output[y*W+x] = ch[cidx[y][x]];
                    else
                    {
                        int n=0;
                        double h=0;
                        for(int dx=-1;dx<=1;dx++)if(dx+x>=0 && dx+x<W)
                            for(int dy=-1;dy<=1;dy++)if(dy+y>=0 && dy+y<H)
                            {
                                h += input[(dy+y)*W+dx+x];
                                n++;
                            }

                        if(n)
                            output[y*W+x] = input[y*W+x]*(1-f)+(h/n)*f;
                    }
                }
        }


        void blur3(const vector<double> &input, vector<double> &output, double f)
        {
            for(int y = 0; y < H; y++)
                for(int x = 0; x< W; x++)
                {
                    if(cidx[y][x]>0 && cidx[y][x]<=NIC)
                        output[y*W+x] = ch[cidx[y][x]];
                    else
                    {
                        int n=0;
                        double h=0;
                        for(int dx=-1;dx<=1;dx++)if(dx+x>=0 && dx+x<W)
                            for(int dy=-1;dy<=1;dy++)if(dy+y>=0 && dy+y<H)
                            {
                                h += input[(dy+y)*W+dx+x];
                                n++;
                            }

                        if(n)
                            output[y*W+x] = input[y*W+x]*(1-f)+(h/n)*f;
                    }
                }
        }

        int get_nmeasures(int c)
        {
            if(c >= (int)measures.size())
                measures.resize(c+1);
            return (int)measures[c].size();
        }

        void add_measure(int c, double h)
        {
            if(c >= (int)measures.size())
                measures.resize(c+1);
            measures[c].push_back(h);
        }

        double get_height(int c, int nminsamples = 1)
        {
            if(c >= (int)measures.size())
                measures.resize(c+1);

            for(int i = (int)measures[c].size(); i < nminsamples; i++)
            {
                double h = Relief::measure(cx[c],cy[c]);
                add_measure(c, h);
            }

            double res = 0;
            for(int i=0;i<(int)measures[c].size();i++)
                res += measures[c][i];
            ch[c] = res/measures[c].size();
            return ch[c];
        }


        double get_height(int c, double max_err = 0.5)
        {
            // minimum of 2 samples
            int ns = 2;
            double err;
            do{
                get_height(c, ns);

                err = 0;
                for(int i=0;i<(int)measures[c].size();i++)
                    err += (measures[c][i] - ch[c])*(measures[c][i] - ch[c]);
                err/=(int)measures[c].size();
                ns++;
            }while(err> max_err && ns<10);

            return ch[c];
        }

        double measure(int x, int y, int ntries = 1)
        {
            double res = 0;
            for(int i = 0 ; i < ntries; i++)
                res += Relief::measure(x,y);
            return res/ntries;
        }

        // mark all
        void mark(int x, int y, const vector <string> &contourMap, int id)
        {
            char c = contourMap[y][x];
            queue<pair<int,int> > q;
            q.push(make_pair(x,y));
            cidx[y][x] = id;
            cx[id] = x;
            cy[id] = y;

            while(!q.empty())
            {
                x = q.front().first;
                y = q.front().second;
                q.pop();

                for(int dx=-1;dx<=1;dx++)if(x+dx>=0 && x+dx<W)
                    for(int dy=-1;dy<=1;dy++)if(y+dy>=0 && y+dy<H)
                        if(dx==0||dy==0)
                            if(contourMap[y+dy][x+dx]==c && cidx[y+dy][x+dx] == 0)
                            {
                                mark_point(x+dx, y+dy, id);
                                //cidx[y+dy][x+dx] = id;
                                q.push(make_pair(x+dx, y+dy));
                            }
            }
        }


        bool mark_next(int &cx, int &cy, int &D, const vector <string> &contourMap, int id)
        {
            int ux, uy;
            ux = cx + mark_dx[D];
            uy = cy + mark_dy[D];
            if(ux<0||uy<0||ux>=W||uy>=H)
            {
                D = (D+1)%4;
                return false;
            }
            if(contourMap[uy][ux] == '1' && (cidx[uy][ux] == 0 || cidx[uy][ux] == id))
            {
                mark_point(ux,uy,id);
                D = (D+3)%4;
                cx = ux, cy = uy;
                return true;
            }

            D = (D+1)%4;
            return false;
        }

        void mark_point(int x, int y, int id)
        {
            if(cidx[y][x] == 0)
            {
                cidx[y][x] = id;
                if(id>=(int)vcp.size())
                    vcp.resize(id+1);
                vcp[id].push_back(make_pair(x,y));
            }
        }

        void mark2(int sx, int sy, const vector <string> &contourMap, int id)
        {
            mark_point(sx,sy,id);
            cx[id] = sx;
            cy[id] = sy;

            int D = 0;
            int cx = sx, cy = sy;
            int k;
            // search the second contour point
            for(k=0;k<4;k++)
            {
                if(mark_next(cx, cy, D, contourMap, id))
                    break;
            }
            if(k == 4)
            {
                // isolated point
                return;
            }

            int DD = D;
            int nfalse = 0;
            while(cx != sx || cy != sy/* || D != DD*/)
            {
                if(!mark_next(cx, cy, D, contourMap, id))
                {
                    nfalse++;
                    if(nfalse>3)
                        break;
                }
                else nfalse = 0;
            }
        }

        void find_contours(const vector <string> &contourMap)
        {
            cerr<<"Finding contours...."<<endl;
            NC = 0;

            for(int y = 0; y < H; y++)
                for(int x = 0; x < W; x++)
                {
                    char c = contourMap[y][x];
                    if(c == '1' && cidx[y][x]==0)
                    {
                        mark(x,y, contourMap, ++NC);
                    }
                }
        }

        void find_contours2(const vector <string> &contourMap)
        {
            cerr<<"Finding contours...."<<endl;
            NC = 0;

            for(int y = 1; y < H-1; y++)
                for(int x = 1; x < W-1; x++)
                {
                    if(contourMap[y][x] == '1' && contourMap[y-1][x] == '1' && contourMap[y+1][x] == '1'
                            && contourMap[y][x-1] == '1' && contourMap[y][x+1] == '1' && cidx[y][x] == 0 && cidx[y-1][x] == 0 && cidx[y][x-1] == 0 && cidx[y][x+1] == 0 && cidx[y+1][x] == 0
                            && contourMap[y-1][x-1] != '1' && contourMap[y-1][x+1] != '1' 
                            && contourMap[y+1][x-1] != '1' && contourMap[y+1][x+1] != '1')
                    {
                        int id = ++NC;
                        cx[id] = x;
                        cy[id] = y;
                        //mark_point(x, y, id);
                        for(int dx=-1;dx<=1;dx++)
                            for(int dy=-1;dy<=1;dy++)
                                if(dx == 0 || dy ==0)
                                {
                                    mark_point(x+dx, y+dy, id);
                                }
                    }
                }

            for(int y = 0; y < H; y++)
            {
                if(contourMap[y][0] == '1' && cidx[y][0] == 0)
                    mark2(0,y, contourMap, ++NC);
                if(contourMap[y][W-1] == '1' && cidx[y][W-1] == 0)
                    mark2(W-1,y, contourMap, ++NC);
            }

            for(int x = 0; x < W; x++)
            {
                if(contourMap[0][x] == '1' && cidx[0][x] == 0)
                    mark2(x,0, contourMap, ++NC);
                if(contourMap[H-1][x] == '1' && cidx[H-1][x] == 0)
                    mark2(x,H-1, contourMap, ++NC);
            }

            for(int y = 0; y < H; y++)
                for(int x = 0; x < W; x++)
                {
                    char c = contourMap[y][x];
                    if(c == '1' && cidx[y][x]==0)
                    {
                        mark2(x,y, contourMap, ++NC);
                    }
                }
        }

        void comp_cbord(int c)
        {
            if(c >= (int)vcp.size())
                vcp.resize(c+1);
            for(int i = 0; i < (int)vcpsize(c); i++)
            {
                int x = vcp[c][i].first;
                int y = vcp[c][i].second;
                if(x==0||y==0||x==W-1 || y == H-1)
                {
                    cbord[c] = 1;
                    return;
                }
            }
            cbord[c] = 0;
        }

        void comp_cbord()
        {
            for(int c=1;c<=NC;c++)
                comp_cbord(c);
        }

        void comp_cbb(int c)
        {
            if(c >= (int)vcp.size())
                vcp.resize(c+1);

            int minx = W, miny = H, maxx = 0, maxy = 0;
            for(int i = 0; i < (int)vcpsize(c); i++)
            {
                int x = vcp[c][i].first;
                int y = vcp[c][i].second;
                if(x<minx)minx = x;
                if(y<miny)miny = y;
                if(x>maxx)maxx = x;
                if(y>maxy)maxy = y;
            }
            cminx[c] = minx;cmaxx[c] = maxx;
            cminy[c] = miny;cmaxy[c] = maxy;
        }

        void comp_cbb()
        {
            for(int c=1;c<=NC;c++)
                comp_cbb(c);
        }

        void interpolate2(vector<double> &res)
        {
            cerr<<"Interpolating..."<<endl;
            for(int y = 0; y < H; y++)
                for(int x = 0; x < W; x++)
                {
                    if(cidx[y][x]>0)
                    {
                        res[y*W+x] = ch[cidx[y][x]];
                    }
                    else
                    {
                        vector<pair<double,double> > v;
                        int minyy = max(0,y-(int)30), maxyy = min(H,y+(int)30);
                        int minxx = max(0,x-(int)30), maxxx = min(W,x+(int)30);
                        for(int yy = minyy; yy < maxyy; yy++)
                            for(int xx = minxx; xx < maxxx; xx++)
                            {
                                if(cidx[yy][xx]>0)
                                {
                                    v.push_back(make_pair(ch[cidx[yy][xx]], sqrdist(x,y,xx,yy)));
                                };
                            }

                        if(v.size())
                        {
                            double havg = 0, hf = 0;
                            for(int i = 0 ;i < (int)v.size(); i++)
                            {
                                havg += v[i].first/v[i].second;
                                hf += 1.0/v[i].second;
                            }
                            havg /= hf;
                            res[y*W+x] = havg;
                        }

                        //cerr<<x<<","<<y<<":"<<v.size()<<" samples"<<" avg="<<havg<<" hf="<<hf<<endl;
                        //res[y*W+x] = hh[y][x]<0?0:hh[y][x];
                    }
                }
        }

        void interpolate3(vector<double> &res)
        {
            cerr<<"Interpolating..."<<endl;
            for(int y = 0; y < H; y++)
                for(int x = 0; x < W; x++)
                {
                    if(cidx[y][x]>0)
                    {
                        res[y*W+x] = ch[cidx[y][x]];
                    }
                    else
                    {
                        //vector<pair<double,double> > v;
                        set<int> s;
                        int ang = 0;
                        for(int i = 0; i < 360; i+=20)
                        {
                            double incx = cos(i*M_PI/180);
                            double incy = sin(i*M_PI/180);
                            for(int n=1;n<1000;n++)
                            {
                                int xx = x + (int)(incx*n+0.5);
                                int yy = y + (int)(incy*n+0.5);
                                if(xx<0 || xx>=W || yy<0 || yy>=H)
                                    break;
                                if(cidx[yy][xx]>0)
                                {
                                    s.insert(yy*W+xx);
                                    //v.push_back(make_pair(ch[cidx[yy][xx]], sqrdist(x,y,xx,yy)));
                                    break;
                                }
                            }
                        }
                        if(!s.empty())
                        {
                            double havg = 0, hf = 0;
                            for(set<int>::iterator it = s.begin(); it != s.end(); it++)
                            {
                                int xx = (*it)%W;
                                int yy = (*it)/W;
                                double val = ch[cidx[yy][xx]];
                                double dist = sqrdist(x,y,xx,yy);
                                havg += val/dist;
                                hf += 1.0/dist;
                            }
                            havg /= hf;
                            res[y*W+x] = havg;
                            /*
                               if(fabs(Relief::hs[y][x] - havg)>10)
                               {
                               cerr<<"error!"<<endl;
                               }*/
                        }
                        else
                        {
                            cerr<<"error!"<<endl;
                        }

                        //cerr<<x<<","<<y<<":"<<v.size()<<" samples"<<" avg="<<havg<<" hf="<<hf<<endl;
                        //res[y*W+x] = hh[y][x]<0?0:hh[y][x];
                    }
                }
        }

        int erosion(int *input, int *output, int src_id)
        {
            static int dx[4] = {0, -1, 1, 0};
            static int dy[4] = {-1, 0, 0, 1};
            int n=0;
            for(int y=0;y<H;y++)
                for(int x=0;x<W;x++)
                {
                    if( (src_id>=0 && src_id != input[y*W+x]) || cidx[y][x]>0)
                        output[y*W+x] = input[y*W+x];
                    else
                    {
                        int val = input[y*W+x];
                        for(int i=0;i<4;i++)
                        {
                            int xx = x+dx[i], yy = y+dy[i];
                            if(xx>=0 && xx<W && yy>=0 && yy<H)
                                val = min(val, input[yy*W+xx]);
                        }
                        output[y*W+x] = val;
                        n++;
                    }
                }
            return n;
        }

        int dilation(int *input, int *output, int src_id)
        {
            static int dx[4] = {0, -1, 1, 0};
            static int dy[4] = {-1, 0, 0, 1};
            int n=0;
            for(int y=0;y<H;y++)
                for(int x=0;x<W;x++)
                {
                    if( (src_id>=0 && src_id != input[y*W+x]) || cidx[y][x]>0)
                        output[y*W+x] = input[y*W+x];
                    else
                    {
                        int val = input[y*W+x];
                        for(int i=0;i<4;i++)
                        {
                            int xx = x+dx[i], yy = y+dy[i];
                            if(xx>=0 && xx<W && yy>=0 && yy<H)
                                val = max(val, input[yy*W+xx]);
                        }
                        output[y*W+x] = val;
                        n++;
                    }
                }
            return n;
        }

        int morph()
        {
            static int t1[501*501]; 
            static int t2[501*501]; 

            for(int y=0;y<H;y++)
                for(int x=0;x<W;x++)
                    if(cidx[y][x])
                        t1[y*W+x] = cidx[y][x];
                    else t1[y*W+x] = 1000000;

            while(true)
            {
                if(!erosion(t1, t2, 1000000))
                {
                    dilation(t2, t1, -1);
                    break;
                }
                if(!erosion(t2,t1, 1000000))
                {
                    dilation(t1, t2, -1);
                    break;
                }
            }

            map<pair<int,int>, int> new_contours;
            int nnc = 0;
            for(int y=0;y<H;y++)
                for(int x=0;x<W;x++)
                    if(!cidx[y][x] && t1[y*W+x] != t2[y*W+x])
                    {
                        int c1 = t1[y*W+x], c2 = t2[y*W+x];
                        int id = new_contours[make_pair(c1,c2)];
                        if(!id)
                        {
                            id = ++NC;
                            new_contours[make_pair(c1,c2)] = id;
                            ch[id] = (ch[c1] + ch[c2])/2;
                            nnc++;
                        }
                        mark_point(x, y, id);
                    }

            cerr<<" "<<nnc;
            fflush(stderr);
            return nnc;
        }

        void check_vcp()
        {
#ifdef HOME
            for(int c=1;c<=NC;c++)
            {
                for(int i=0;i<(int)vcpsize(c);i++)
                {
                    int x = vcp[c][i].first;
                    int y = vcp[c][i].second;
                    if(cidx[y][x] != c)
                        assert(false);
                }
            }
#endif
        }

        bool fix_error;

        bool fix_contour(int c, const vector<string> &contourMap)
        {
            cerr<<"Fixing contour "<<c<<"..."<<endl;
            check_vcp();

            for(int i=0;i<vcpsize(c);i++)
            {
                int x = vcp[c][i].first;
                int y = vcp[c][i].second;

                for(int dx=-1;dx<=1;dx++)
                    for(int dy=-1;dy<=1;dy++)
                    {
                        if(x+dx>=0 && y+dy>=0 && x+dx<W && y+dy<H)
                        {
                            if(cidx[y+dy][x+dx] > 0 && cidx[y+dy][x+dx] != c)
                            {
                                //lst.insert(cidx[y+dy][x+dx]);
                                //lst.insert(cidx[y+dy][x+dx]);
                                //__asm int 3
                                cerr<<"$1"<<endl;
                                return fix_contour(c,x,y,x+dx,y+dy);
                            }
                        }
                    }
            }

            for(int i=0;i<vcpsize(c);i++)
            {
                int x = vcp[c][i].first;
                int y = vcp[c][i].second;

                for(int dx=-2;dx<=2;dx+=2)
                    for(int dy=-2;dy<=2;dy+=2)if(dx==0||dy==0)
                    {
                        if(x+dx>=0 && y+dy>=0 && x+dx<W && y+dy<H)
                        {
                            if(cidx[y+dy][x+dx] > 0 && cidx[y+dy][x+dx] != c)
                            {
                                cerr<<"$2"<<endl;
                                //lst.insert(cidx[y+dy][x+dx]);
                                //lst.insert(cidx[y+dy][x+dx]);
                                return fix_contour(c,x,y,x+dx/2,y+dy/2);
                            }
                        }
                    }
            }

            //__asm int 3
            int midx = cminx[c];//(cmaxx[c] + cminx[c])/2;
            int midy = cminy[c];//(cmaxy[c] + cminy[c])/2;

            int xc, yc, xe, ye;

            if(cminx[c] != 0)
            {
                for(int x = 1; x< W; x++)
                {
                    if(cidx[midy][x] == c)
                    {
                        xc = x;yc = midy;
                        xe = x-1; ye = midy;
                        break;
                    }
                }
            }
            else if(cmaxx[c] < W-1)
            {
                for(int x = W-2; x>=0; x--)
                {
                    if(cidx[midy][x] == c)
                    {
                        xc = x;yc = midy;
                        xe = x+1; ye = midy;
                        break;
                    }
                }
            }
            else if(cminy[c] != 0)
            {
                for(int y = 1; y < H; y++)
                {
                    if(cidx[y][midx] == c)
                    {
                        xc = midx; yc = y;
                        xe = midx; ye = y-1;
                        break;
                    }
                }
            }
            else if(cmaxy[c] < H - 1)
            {
                for(int y = H-2; y >= 0; y--)
                {
                    if(cidx[y][midx] == c)
                    {
                        xc = midx; yc = y;
                        xe = midx; ye = y+1;
                        break;
                    }
                }
            }
            else
            {
                cerr<<"ERROR!!! could not fix contour!!!";
                fix_error = true;
                ce[c] = 1;
                return false;
            }

            return fix_contour(c, xc, yc, xe, ye);
        }

        bool fix_contour(int c, int xc, int yc, int xe, int ye)
        {
            // xc, yc = first point of contour
            // xe, ye = exterior contour point
            int newid = NC+1;
            queue<pair<int,int> > q;
            set<int> visited;
            q.push(make_pair(xe,ye));
            visited.insert(ye*W+xe);
            while(!q.empty())
            {
                int x = q.front().first;
                int y = q.front().second;
                //cerr<<"processing "<<x<<","<<y<<endl;
                q.pop();
                for(int dx=-1;dx<=1;dx++)
                    for(int dy=-1;dy<=1;dy++)if(dx!=0 || dy!=0)
                        //if(x+dx>=0 && y+dy>=0 && x+dx<W && y+dy<H)
                    {
                        if((x+dx<0 || y+dy<0 || x+dx>=W || y+dy>=H) || (cidx[y+dy][x+dx] != c && cidx[y+dy][x+dx] != newid))
                        {
                            bool ok  = false;
                            for(int dx2=-1;dx2<=1 && !ok;dx2++)
                                for(int dy2=-1;dy2<=1;dy2++)if(dx2!=0 || dy2!=0)
                                    if(x+dx+dx2>=0 && y+dy+dy2>=0 && x+dx+dx2<W && y+dy+dy2<H)
                                        if(cidx[y+dy+dy2][x+dx+dx2] == c)
                                        {
                                            ok = true;
                                            break;
                                        }
                            if(ok)
                            {
                                //cerr<<"pushing"<<x+dx<<","<<y+dy<<endl;
                                if(visited.find((y+dy)*W+x+dx) == visited.end())
                                {
                                    q.push(make_pair(x+dx, y+dy));
                                    visited.insert((y+dy)*W+x+dx);
                                }
                            }
                        }
                    }

                for(int dx=-1;dx<=1;dx++)
                    for(int dy=-1;dy<=1;dy++)if(dx!=0 || dy!=0)
                        if(x+dx>=0 && y+dy>=0 && x+dx<W && y+dy<H)
                        {
                            if(cidx[y+dy][x+dx] == c)
                            {
                                //cerr<<"remarking"<<x+dx<<","<<y+dy<<endl;
                                cidx[y+dy][x+dx] = 0;
                                mark_point(x+dx, y+dy, newid);
                            }
                        }
            }

            VII newv;
            for(int i=0;i<(int)vcpsize(c);i++)
            {
                int x = vcp[c][i].first, y = vcp[c][i].second;
                if(cidx[y][x] == c)
                    newv.push_back(make_pair(x, y));
            }

            bool fixed = false;
            if(newv.size() == 0 || vcpsize(newid) == 0)
            {
                // nothing left => revert, mark back all points from newid to c
                for(int i=0;i<(int)vcpsize(newid);i++)
                {
                    int x = vcp[newid][i].first, y = vcp[newid][i].second;
                    assert(cidx[y][x] == newid);
                    cidx[y][x] = c;
                }
                vcp[newid].clear();
                cerr<<"no fix to do"<<endl;
            }
            else
            {
                cerr<<"new contour created: "<<newid<<" with "<<vcpsize(newid)<<"points"<<endl;
                vcp[c] = newv;
                NC = max(NC, newid);
                cx[newid] = vcp[newid][0].first;
                cy[newid] = vcp[newid][0].second;
                cx[c] = vcp[c][0].first;
                cy[c] = vcp[c][0].second;
                comp_cbb(c);
                comp_cbb(newid);
                comp_cbord(c);
                comp_cbord(newid);
                fixed = true;
            }

            check_vcp();
            return fixed;
        }


        bool fix_contours(const vector<string> &contourMap)
        {
            fix_error = false;
            cerr<<"Fixing contours..."<<endl;
            comp_cbord();
            comp_cbb();

            static char tofix[NMAXC+1];
            for(int c=1;c<=NC;c++)
            {
                tofix[c] = 0;
            }

            for(int y=0;y<H-3;y++)
                for(int x=0;x<W-3;x++)
                {
                    int cc = cidx[y][x];
                    if(!ce[cc] && cidx[cc]>0)
                    {
                        for(int c = 0; c < NPATTERNS; c++)
                        {
                            // check pattern c
                            bool ok = true;
                            for(int i = 0; i < 3 && ok; i++)
                                for(int j=0;j<3;j++)
                                {
                                    if(cpatterns[c][i][j] == 1 && cidx[y+i][x+j] != cc)
                                    {ok = false;break;}
                                    if(cpatterns[c][i][j] == 0 && cidx[y+i][x+j] == cc)
                                    {ok = false;break;}
                                }

                            if(ok)
                            {
                                // pattern match!
                                tofix[cc] = 1;
                                break;
                            }
                        }
                    }
                }

            int nfix = 0;
            for(int c=1;c<=NC;c++)
                nfix += (tofix[c]!=0);
            if(nfix)
            {
                cerr<<nfix<<"contours need to be fixed! ";
                for(int c=1;c<=NC;c++)
                    if(tofix[c]!=0)
                        cerr<<c<<" ";
                cerr<<endl;
            }

            for(int c=1;c<=NC;c++)
                if(tofix[c]!=0)
                {
                    while(fix_contour(c, contourMap) && vcpsize(c)>4);
                }

            return !fix_error;
        }

        bool find_unfixable_contours()
        {
            int sz = 8;
            bool res = false;
            for(int y=0;y<H-sz;y++)
                for(int x=0;x<W-sz;x++)
                {
                    int c = cidx[y][x];
                    if(c > 0 && ce[c]==0)
                    {
                        bool ok = true;
                        for(int dx=0;dx<sz && ok;dx++)
                            for(int dy=0;dy<sz && ok;dy++)
                                if(cidx[y+dy][x+dx] != c)
                                    ok = false;
                        if(ok)
                        {
                            ce[c] = 1;
                            res = true;
                            cerr<<"********* Unfixable contour: "<<c<<endl;
                        }
                    }
                }
            return res;
        }

        void mark_region(int sx, int sy, int id)
        {
            set<int> sc;
            ridx[sy][sx] = id;
            queue<pair<int,int> > q;
            q.push(make_pair(sx,sy));
            while(!q.empty())
            {
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                for(int dx=-1;dx<=1;dx++)if(x+dx>=0&&x+dx<W)
                    for(int dy=-1;dy<=1;dy++)if(dx==0||dy==0)if(y+dy>=0&&y+dy<H)
                        if(cidx[y+dy][x+dx]<=0)
                        {
                            if(ridx[y+dy][x+dx] == 0)
                            {
                                ridx[y+dy][x+dx] = id;
                                q.push(make_pair(x+dx,y+dy));
                            }
                        }
                        else
                        {
                            sc.insert(cidx[y+dy][x+dx]);
                        }
            }

            vector<int> vc(sc.begin(), sc.end());
            for(int i = 0; i < (int)vc.size()-1; i++)
                for(int j = i+1; j < (int)vc.size(); j++)
                    set_link(vc[i],vc[j],0);

            if(id >= (int)rlinks.size())
                rlinks.resize(id+1);

            for(int i = 0; i < (int)vc.size(); i++)
                rlinks[id].insert(vc[i]);

            /*
               cerr<<"Region "<<id<<" links:";
               for(int i=0;i<(int)vc.size();i++)
               {
               cerr<<" "<<vc[i];
               }
               cerr<<endl;
               */
        }

        void comp_links()
        {
            NR = 0;
            for(int y = 0; y < H; y++)
                for(int x = 0; x < W; x++)
                {
                    ridx[y][x] = 0;
                }

            for(int y = 0; y < H; y++)
                for(int x = 0; x < W; x++)
                {
                    if(cidx[y][x] == 0 && ridx[y][x] == 0)
                    {
                        mark_region(x,y,++NR);
                    }
                }
        }

        vector<int> find_shortest_path(int cstart, int cend)
        {
            vector<int> res;
            if(cstart == cend)
                return res;

            static int mindist[NMAXC];
            static int prev[NMAXC];
            for(int i=1;i<=NC;i++)
            {
                mindist[i] = 100000;
                prev[i] = -1;
            }

            mindist[cend] = 0;
            set<pair<int,int> > q;
            q.insert(make_pair(0, cend));
            bool found = false;
            while(!q.empty() && !found)
            {
                int c = q.begin()->second;
                int dist = q.begin()->first;
                q.erase(q.begin());

                for(map<int, char>::iterator it = clinks[c].begin(); it != clinks[c].end(); it++)
                {
                    int nextc = it->first;
                    if(mindist[nextc] > dist+1)
                    {
                        mindist[nextc] = dist+1;
                        prev[nextc] = c;
                        if(nextc == cstart)
                        {
                            found = true;
                            break;
                        }
                        q.insert(make_pair(dist+1, nextc));
                    }
                }
            }

            assert(found);
            if(found)
            {
                int c = cstart;
                res.push_back(c);
                while(prev[c] != -1)
                {
                    c = prev[c];
                    res.push_back(c);
                }
            }

            return res;
        }

        int dist_to_known_world(int cstart, int &cend)
        {
            vector<int> mindist(NC+1, 100000);

            mindist[cstart] = 0;
            set<pair<int,int> > q;
            q.insert(make_pair(0, cstart));
            cend = -1;
            while(!q.empty())
            {
                int c = q.begin()->second;
                int dist = q.begin()->first;
                q.erase(q.begin());

                //if(dist == mindist[c])
                for(map<int, char>::iterator it = clinks[c].begin(); it != clinks[c].end(); it++)
                {
                    int nextc = it->first;
                    if(mindist[nextc] > dist+1)
                    {
                        mindist[nextc] = dist+1;
                        //if(known[nextc])
                        if(terminal[nextc] == 2)
                        {
                            cend = nextc;
                            return dist+1;
                        }
                        q.insert(make_pair(dist+1, nextc));
                    }
                }
            }

            return -1;
        }

        void extract_subpath(vector<int> &path, int &istart, int &iend)
        {
            istart = -1, iend = -1;
            for(int i=0;i<(int)path.size();i++)
            {
                if(is_real_contour(path[i]))
                {
                    istart = i;
                    break;
                }
            }
            for(int i=0; i < (int)path.size();i++)
            {
                if(known[path[i]])
                {
                    iend = i;
                    break;
                }
            }
        }

        bool process_extreme_path()
        {
            g_minc = -1;
            g_maxc = -1;

            int minc = -1, maxc = -1;
            double minh=101, maxh = -1;
            for(int i=1;i<=NC;i++)
            {
                if(terminal[i]==1)
                {
                    if(ch[i]<minh){minh = ch[i], minc = i;}
                    if(ch[i]>maxh){maxh = ch[i], maxc = i;}
                }
            }

            if(minc < 0 || maxc < 0)
                return false;

            // find the shortest path between minc and maxc
            cerr<<"Min contour = "<<minc<<" height = "<<ch[minc]<<" Max contour = "<<maxc<<" height = "<<ch[maxc]<<endl;
            vector<int> path = find_shortest_path(minc, maxc);
            cerr<<"Shortest path = ";
            for(int i = 0; i < (int)path.size(); i++)
                cerr<<path[i]<<" ";
            cerr<<endl;

            terminal[minc] = terminal[maxc] = 2;

            int cstart = -1, cend =  -1;
            int istart = -1, iend = -1;
            for(int i=0;i<(int)path.size();i++)
            {
                if(is_real_contour(path[i]))
                {
                    cstart = path[i];
                    istart = i;
                    break;
                }
            }
            for(int i=(int)path.size()-1; i >= 0;i--)
            {
                if(is_real_contour(path[i]))
                {
                    cend = path[i];
                    iend = i;
                    break;
                }
            }

            if(cstart>0 && cend>0 && cstart!=cend)
            {
                //get_height(cstart,max(2,NC/5));
                //get_height(cend,max(2,NC/5));
                int nmeas = max(4,nmaxmeasures/50);
                cerr<<"------- Using "<<nmeas<<" measures..."<<endl;
                get_height(cstart,nmeas);
                get_height(cend,nmeas);

                known[cstart] = known[cend] = 1;

                int n = iend-istart;

                gD = (ch[cend]-ch[cstart])/(iend-istart);

                cerr<<"cstart = "<<cstart<<" cend="<<cend<<" Estimated D = "<<gD<<endl;

                double hstart = ch[cstart];
                double hend = ch[cend];
                for(int i=0;i<3;i++)
                {
                    hstart = max(gD, hstart);
                    gD = (hend-hstart)/(iend-istart);
                }
                ch[cstart] = hstart;
                ch[cend] = hend;

                cerr<<"cstart = "<<cstart<<" cend="<<cend<<" Estimated D = "<<gD<<endl;
                for(int k=istart+1;k< iend ;k++)
                {
                    ch[path[k]] = ch[cstart] + gD*(k-istart);
                    known[path[k]]=1;
                }

                g_minc = minc;
                g_maxc = maxc;

                return true;
            }
            return false;
        }

        void process_terminals_to_extremes()
        {
            while(true)
            {
                int best_dist = 100000, best_c = -1, best_endc = -1;
                vector<int> best_path_min, best_path_max;
                for(int c=1;c<=NC;c++)
                {
                    if(terminal[c] == 1)
                    {
                        vector<int> path_min = find_shortest_path(c, g_minc);
                        vector<int> path_max = find_shortest_path(c, g_maxc);
                        int dist = (int)min(path_min.size(), path_max.size());
                        if(dist < best_dist)
                        {
                            best_dist = dist;
                            best_c = c;
                            best_path_min = path_min, best_path_max = path_max;
                        }
                    }
                }
                if(best_c<0)
                    break;

                cerr<<"T2E: Processing point "<<best_c<<" h = "<<ch[best_c]<<" dist to extreme="<<best_dist<<endl;
                terminal[best_c] = 4;
                if(best_dist <= 1)
                {
                    cerr<<"    canceled"<<endl;
                    continue;
                }

                int c = best_c;
                vector<int> path_min = best_path_min;
                vector<int> path_max = best_path_max;
                           int istart_min = -1, iend_min = -1;
                int istart_max = -1, iend_max = -1;
                extract_subpath(path_min, istart_min, iend_min);
                extract_subpath(path_max, istart_max, iend_max);

                if(istart_min>=0 && iend_min>0 && istart_max>=0 && iend_max>0 && istart_min<iend_min && istart_max<iend_max)
                {
                    int cstart_min = path_min[istart_min], cend_min =  path_min[iend_min];
                    int cstart_max = path_max[istart_max], cend_max =  path_max[iend_max];

                    cerr<<"    path_min = ";
                    for(int i = istart_min; i <= iend_min; i++)
                        cerr<<path_min[i]<<" ";
                    cerr<<"end h = "<<ch[cend_min]<<endl;

                    cerr<<"    path_max = ";
                    for(int i = istart_max; i <= iend_max; i++)
                        cerr<<path_max[i]<<" ";
                    cerr<<"end h = "<<ch[cend_max]<<endl;

                    double hstart_min = 0, hstep_min = 0;
                    double hstart_max = 0, hstep_max = 0;

                    int n_min = iend_min-istart_min;
                    if(ch[cend_min] > ch[c])
                    {
                        hstep_min = gD;
                        n_min--;
                    }
                    else
                    {
                        hstep_min = -gD;
                    }
                    hstart_min = ch[cend_min] - hstep_min*n_min;

                    int n_max = iend_max-istart_max;
                    if(ch[cend_max] > ch[c])
                    {
                        hstep_max = gD;
                    }
                    else
                    {
                        hstep_max = -gD;
                        n_max--;
                    }
                    hstart_max = ch[cend_max] - hstep_min*n_max;

                    cerr<<"    hstart_min="<<hstart_min<<" hstart_max="<<hstart_max<<endl;
                    double maxhdiff = (istart_min==0)?3:gD+2;
                    if(fabs(hstart_min - hstart_max) < 1 && fabs(hstart_min-ch[best_c]) < maxhdiff)
                    {
                        cerr<<"    ok"<<endl;
                        terminal[c] = 2;

                        for(int k=istart_min; k < iend_min; k++)
                        {
                            ch[path_min[k]] = hstart_min + hstep_min*(k-istart_min);
                            known[path_min[k]] = 1;
                        }
                        for(int k=istart_max; k < iend_max; k++)
                        {
                            if(ch[path_max[k]]<0)
                            {
                                ch[path_max[k]] = hstart_max + hstep_max*(k-istart_max);
                                known[path_max[k]] = 1;
                            }
                        }
                    }
                    else
                    {
                        cerr<<"    canceled - hstart do not match"<<endl;
                        terminal[best_c] = 5;
                    }
                }
                else
                {
                    cerr<<"    canceled - extract_subpath failed"<<endl;
                }
            }

            for(int c=1;c<=NC;c++)
            {
                if(terminal[c] == 5)
                    terminal[c] = 1;
            }

                    }

        void process_terminals_to_terminals()
        {
            while(true)
            {
                int best_dist = 100000, best_c = -1, best_endc = -1;
                for(int c=1;c<=NC;c++)
                {
                    if(terminal[c] == 1)
                    {
                        int endc = -1;
                        int dist = dist_to_known_world(c, endc);
                        if(dist < best_dist)
                        {
                            best_dist = dist;
                            best_c = c;
                            best_endc = endc;
                        }
                    }
                }
                if(best_c<0)
                    break;

                cerr<<"T2T: Processing point "<<best_c<<" h = "<<ch[best_c]<<" dist to known="<<best_dist<<endl;
                terminal[best_c] = 3;
                if(best_dist <= 1)
                    continue;

                vector<int> path = find_shortest_path(best_c, best_endc);

                //            __asm int 3
                int istart = -1, iend = -1;
                extract_subpath(path, istart, iend);
                if(istart<0 || iend<0 || istart>=iend)
                {
                    cerr<<"ERROR extracting subpath!"<<endl;
                }
                else
                {
                    int cstart = path[istart], cend =  path[iend];
                    int cterm = path[path.size()-1];
                    cerr<<"    path = ";
                    for(int i = istart; i <= iend; i++)
                        cerr<<path[i]<<" ";
                    cerr<<"end h = "<<ch[cend]<<" cterm = "<<cterm<<" term h="<<ch[cterm]<<endl;

                    //__asm int 3
                    double hstart = 0, hstep = 0;
                    int n = iend-istart;
                    for(int i=iend+1;i<(int)path.size() && fabs(ch[path[iend]]-ch[path[i]])<1 && n>1 ;i++)
                    {
                        n--;
                        cerr<<"#";
                    }
                    if(ch[cend] > ch[best_c])
                    {
                        hstep = gD;
                        if(ch[cterm] < ch[cend])
                            n--;
                    }
                    else
                    {
                        hstep = -gD;
                        if(ch[cterm] > ch[cend])
                            n--;
                    }
                    hstart = ch[cend] - hstep*n;
                    cerr<<"    hstart="<<hstart<<endl;

                    double maxhdiff = (istart==0)?3:gD+2;
                    if(fabs(hstart-ch[best_c]) < maxhdiff)
                    {
                        for(int k=istart; k < iend; k++)
                        {
                            ch[path[k]] = hstart + hstep*(k-istart);
                            known[path[k]] = 1;
                        }
                        terminal[best_c] = 2;
                    }
                    else
                    {
                        cerr<<"    canceled - hstart do not match"<<endl;
                        terminal[best_c] = 5;
                    }
                }
            }
        }

        void get_heights_simple()
        {
            for(int i=1;i<=NC;i++)
            {
                ch[i] = -1;
                known[i] = 0;
            }

            for(int i=1;i<=NC;i++)
            {
                bool b = false;
                if(ch[i]<0)
                {
                    if(ce[i])
                        ch[i] = 0;
                    else
                    {
                        ch[i] = measure(cx[i], cy[i],1);
                        b = true;
                    }
                }
                cerr<<"height for contour "<<i<<" at "<<cx[i]<<","<<cy[i]<<" having "<<vcp[i].size()<<"points and "<<num_real_links(i)<<"links ="<<ch[i];
                if(b)cerr<<"*";
                cerr<<endl;
            }
        }

        void get_heights()
        {
            for(int i=1;i<=NC;i++)
            {
                ch[i] = -1;
                known[i] = 0;
            }

            terminal.resize(NC+1, 0);

            for(int i=1;i<=NC;i++)
            {
                if(num_links(i) == 1 || !is_real_contour(i))
                {
                    ch[i] = get_height(i, 1);
                    terminal[i] = 1;
                }
            }

            if(process_extreme_path())
            {
                process_terminals_to_extremes();
                process_terminals_to_terminals();
            }
            
            for(int i=1;i<=NC;i++)
            {
                bool b = false;
                if(ch[i]<0)
                {
                    ch[i] = measure(cx[i], cy[i],1);
                    b = true;
                }
                cerr<<"height for contour "<<i<<" at "<<cx[i]<<","<<cy[i]<<" having "<<vcp[i].size()<<"points and "<<num_real_links(i)<<"links ="<<ch[i];
                if(b)cerr<<"*";
                cerr<<endl;
            }
        }

        void fix_cx_cy()
        {
            for(int c=1;c<=NC;c++)
            {
                if(c<vcp.size())
                    for(int i = 0; i < (int)vcpsize(c); i++)
                    {
                        int x = vcp[c][i].first;
                        int y = vcp[c][i].second;
                        if(x==0 || y==0 || x==W-1 || y==H-1)
                        {
                            cx[c] = x;
                            cy[c] = y;
                            break;
                        }
                    }
            }
        }

        void get_border_xy(int n, int &x, int &y)
        {
            n = n%(2*(W+H));
            if(n<W){x = n; y =0;}
            else if(n<W+H) { x = W-1; y = n-W;}
            else if(n<W+H+W) { x = 2*W+H-n-1; y = H-1;}
            else {x = 0; y = 2*(W+H)-n-1;}
        }

        void add_new_points()
        {
            int last_known_pos = 0;
            for(int n = 0; n < 2*(W+H); n++)
            {
                int x,y;
                get_border_xy(n,x,y);
                if(cidx[y][x]>0)
                {
                    if(n-last_known_pos > 30 )
                    {
                        //__asm int 3
                        int mx, my;
                        get_border_xy(n-1,mx,my);
                        int rid = ridx[my][mx];
                        int nrc=0;
                        for(set<int>::iterator it = rlinks[rid].begin(); it != rlinks[rid].end(); it++)
                        {
                            int cid = *it;
                            if(is_real_contour(cid))
                                nrc++;
                        }

                        int nsteps = (n-last_known_pos)/ (150 - 50*(nrc<=1));
                        for(int i=0;i<nsteps;i++)
                        {
                            int stepsize = (n-last_known_pos)/(nsteps+1);
                            int mn = last_known_pos + stepsize*(i+1);
                            get_border_xy(mn,mx,my);

                            assert(cidx[my][mx] == 0);
                            mark_point(mx, my, ++NC);
                            comp_cbord(NC);
                            comp_cbb(NC);
                            cx[NC] = mx;
                            cy[NC] = my;
                            ch[NC] = measure(mx,my,1);

                            cerr<<"New measure at "<<mx<<","<<my<<" = "<<ch[NC]<<" ndiff="<<n-last_known_pos<<endl;
                        }
                    }

                    last_known_pos = n;
                }
            }
        }

        void fix_points()
        {
            for(int c=1;c<=NC;c++)
                if(vcpsize(c) <=5 && cmaxx[c]-cminx[c]<=2 && cmaxy[c]-cminy[c]<=2)
                {
                    int x = cminx[c]+1;
                    int y = cminy[c];
                    if(cidx[y][x]==c && cidx[y-1][x-1] == 0 && cidx[y-1][x+1] == 0 && cidx[y+1][x-1] == 0 && cidx[y+1][x+1]==0
                            &&cidx[y-1][x] == c  && cidx[y][x-1] == c && cidx[y][x+1] == c && cidx[y+1][x] == c)
                    {
                        /*cerr<<"fixing point "<<x<<","<<y<<endl;
                          for(int i=0;i<vcpsize(c);i++)
                          {
                          cidx[vcp[c][i].second][vcp[c][i].first] = 0;
                          }
                          vcp[c].clear();
                          mark_point(x,y, c);*/
                        cx[c] = x;
                        cy[c] = y;
                        //ct[c] = 1;

                        check_vcp();
                    }
                }
        }

        vector <double> getMap(vector <string> &contourMap)
        {
            g_start_time = get_time();
            H = (int)contourMap.size();
            W = (int)contourMap[0].size();

            nmaxmeasures = (int)floor(sqrt((double)W*H));

            cerr<<"W="<<W<<" H="<<H<<" MAXM="<<nmaxmeasures<<endl;
            vcp.clear();

            memset(ce,0,sizeof(ce));

            vector<double> res(W*H);

            for(int y = 0; y < H; y++)
                for(int x = 0; x < W; x++)
                {
                    hh[y][x] = -1;
                    cidx[y][x] = 0;
                }

            memset(ch, 0, sizeof(ch));

            find_contours(contourMap);
            if(!find_unfixable_contours() && fix_contours(contourMap))
            {
                fix_cx_cy();
                //fix_points();
                comp_links();
                NIC = NC;

                get_heights();
                add_new_points();

                cerr<<"Morphing...";
                while(morph());
                cerr<<endl;


                bspline();

                for(int y = 0; y < H; y++)
                    for(int x = 0; x < W; x++)
                    {
                        int contourIdx = cidx[y][x];
                        if(contourIdx>0 && contourIdx<=NIC)
                        {
                            res[y*W+x] = ch[contourIdx];
                        }
                        else
                        {
                            res[y*W+x] = min(100.0,max(0.0,evalf(x,y)));
                        }
                    }
            }
            else
            {
                cerr<<"PLAN B"<<endl;
                fix_contours(contourMap);
                NIC = NC;
                for(int c=1;c<=NIC;c++)
                    if(ce[c])
                    {
                        int na = 0;
                        int ystep = H/(int)(H/20.0)-1;
                        for(double dy=0;dy<H;dy+=ystep)
                        {
                            int y = (int)dy;
                            int lastpos = -1000;
                            int lastx = -1;
                            for(int x=0;x<W;x++)
                                if(cidx[y][x] == c)
                                    if(x-lastpos>20)
                                    {
                                        lastpos = x;
                                        cidx[y][x] = 0;
                                        mark_point(x,y, ++NC);
                                        cx[NC] = x;
                                        cy[NC] = y;
                                        na++;
                                    }
                                    else
                                    {
                                        lastx = x;
                                    }

                            /*if(lastx > 0 && lastx-lastpos > 10)
                              {
                              cidx[y][lastx] = 0;
                              mark_point(lastx,y, ++NC);
                              cx[NC] = lastx;
                              cy[NC] = y;
                              na++;
                              }*/

                        }

                        cerr<<"Contour "<<c<<" - "<<na<<" measuring points added"<<endl;
                        int n = vcpsize(c);
                        for(int i=0;i<n;i++)
                        {
                            int x= vcp[c][i].first;
                            int y = vcp[c][i].second;
                            cidx[y][x] = 0;
                        }
                        /*                        for(int i=0;i<n;i+=(n/50))
                                                  {
                                                  int x= vcp[c][i].first;
                                                  int y = vcp[c][i].second;
                                                  mark_point(x,y, ++NC);
                                                  cx[NC] = x;
                                                  cy[NC] = y;
                                                  }*/
                        vcp[c].clear();
                    }
                NIC = NC;
                get_heights_simple();
                bspline();

                for(int y = 0; y < H; y++)
                    for(int x = 0; x < W; x++)
                    {
                        res[y*W+x] = min(100.0,max(0.0,evalf(x,y)));
                    }
            }

            cerr<<"T = "<<get_time()-g_start_time<<"s"<<endl;
            return res;
        }

};

int main(){
    int H; cin>>H;
    vector<string> tb;
    getchar();
    for (int i=0; i<H; ++i){ string s; cin>>s; tb.push_back(s); }
    ReliefMap g;
    vector<double> res=g.getMap(tb);
    puts("!");
    for (int i=0; i<res.size(); ++i) fprintf(stdout,"%lf\n", res[i]);
    fflush(stdout);
    return 0;
}


