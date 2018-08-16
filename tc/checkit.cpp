#include <stdio.h>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <iostream>
#include <sstream>
using namespace std;

class BuildingReorganization
{
    public:
        long long real_calc(vector<long long> G, int remain) {
            G.push_back(99999999999LL);
            long long res = 0;
            int n = G.size();
            sort(G.begin(), G.end());
            for (int i=0; i<n; i++) {
                if (!remain) break;
                int now_cover = min((long long)remain, (i+1)*(long long)(G[i+1]-G[i]));
                remain -= now_cover;
                int same_cover = now_cover / (i+1);
                int partial_cover = now_cover % (i+1);
                res += (G[i]*(long long)same_cover+same_cover*(long long)(same_cover-1)/2)*(i+1);
                res += (G[i]+same_cover) * (long long)partial_cover;
            }
            return res;
        }

        long long calc(vector<int> H, int target, int ll, int rr, int A, int B, int cost) {
            vector<long long> G;
            for (int i=ll; i<=rr; i++)
                if (i != A && i != B) G.push_back(abs(target-i)*cost + H[i]);
            return real_calc(G, H[target]);
        }

        long long theMin(vector <int> H, int A, int B, int cost)
        {
            int n = H.size();
            long long def = H[A]*(long long)(H[A]-1)/2 + H[B]*(long long)(H[B]-1)/2;
            long long res = -1;
            for (int i=0; i<n; i++) {
                if (i) continue;
                if ((i==A) || (i==B)) continue;
                int p1_idx = 0;
                int p4_idx = H[A];
                if (i==0 || (A==0 && i==1) || (A==0 && B==1 && i==2)) p1_idx = H[A];
                while (p1_idx+100 < p4_idx) {
                    int p2_idx = (p1_idx * 29LL + p4_idx) / 30;
                    int p3_idx = (p1_idx + p4_idx * 29LL) / 30;
                    H[A] -= p2_idx; long long s2 = calc(H, A, 0, i-1, A, B, cost); s2 += p2_idx*(long long)abs(i-A)*cost + H[i]*(long long)p2_idx + p2_idx*(long long)(p2_idx-1)/2; H[i] += p2_idx;
                    s2 += calc(H, B, i, n-1, A, B, cost); H[i] -= p2_idx; H[A] += p2_idx;
                    H[A] -= p3_idx; long long s3 = calc(H, A, 0, i-1, A, B, cost); s3 += p3_idx*(long long)abs(i-A)*cost + H[i]*(long long)p3_idx + p3_idx*(long long)(p3_idx-1)/2; H[i] += p3_idx;
                    s3 += calc(H, B, i, n-1, A, B, cost); H[i] -= p3_idx; H[A] += p3_idx;
                    //        printf("%d [%d] [%d] %d : %lld %lld\n", p1_idx, p2_idx, p3_idx, p4_idx, s2, s3);
                    if (s2 > s3) p1_idx = p2_idx; else p4_idx = p3_idx;
                }
                for (int j=p1_idx; j<=p4_idx; j++) {
                    H[A] -= j; long long s2 = calc(H, A, 0, i-1, A, B, cost);
                    //        printf("i = %d j = %d s2 = %lld\n", i, j, s2);
                    printf("<< cost %d : %Ld \n",j, j*(long long)abs(i-A)*cost + H[i]*(long long)j + j*(long long)(j-1)/2);
                    s2 += j*(long long)abs(i-A)*cost + H[i]*(long long)j + j*(long long)(j-1)/2; H[i] += j+10000;
                    printf("%Ld\n", s2);
                    printf("%Ld\n", calc(H, B, i, n-1, A, B, cost));
                    //        printf("i = %d j = %d s2 = %lld\n", i, j, s2);
                    s2 += calc(H, B, i, n-1, A, B, cost); H[i] -= j; H[A] += j;
                    //        printf("i = %d j = %d s2 = %lld\n", i, j, s2);
                    cout<<s2<<endl;
                    if (res == -1 || res > s2){
                        res = s2;
                    }
                }
            }
            return def + res;
        };
        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { int Arr0[] = {5, 5, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 2; int Arg3 = 10; long long Arg4 = 215LL; verify_case(0, Arg4, theMin(Arg0, Arg1, Arg2, Arg3)); }
        void test_case_1() { int Arr0[] = {5, 5, 5, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 3; int Arg3 = 10; long long Arg4 = 190LL; verify_case(1, Arg4, theMin(Arg0, Arg1, Arg2, Arg3)); }
        void test_case_2() { int Arr0[] = {5, 50, 1, 50, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 4; int Arg3 = 10; long long Arg4 = 275LL; verify_case(2, Arg4, theMin(Arg0, Arg1, Arg2, Arg3)); }
        void test_case_3() { int Arr0[] = {5, 50, 1, 50, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 4; int Arg3 = 1000; long long Arg4 = 10540LL; verify_case(3, Arg4, theMin(Arg0, Arg1, Arg2, Arg3)); }
        void test_case_4() { int Arr0[] = {5, 50, 1, 50, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 3; int Arg3 = 1000; long long Arg4 = 104428LL; verify_case(4, Arg4, theMin(Arg0, Arg1, Arg2, Arg3)); }
        void test_case_5() { int Arr0[] = {4,1,1,1000,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 4; int Arg3 = 1; long long Arg4 = 20LL; verify_case(5, Arg4, theMin(Arg0, Arg1, Arg2, Arg3)); }
        void test_case_6() { int Arr0[] = {157,10,157,979797,152152152,156,4,77,157,79}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 4; int Arg3 = 123; long long Arg4 = 13041277280686205LL; verify_case(6, Arg4, theMin(Arg0, Arg1, Arg2, Arg3)); }
        void test_case_7() { int Arr0[] = {346455317,453638062,491871419,297060164,426458223,53746370,422461742,231053793,309679268,297959075,
            76653026,277375296,411684823,427164497,257399925,224643292,114988354,457289888,51199847,199807287,
            110648220,303379857,435712111,245040291,401790144,260999362,6953083,385721020,438059362,434000869,
            481788278,70215282,135651128,68577856,448298562,11191117,408997160,407134756,10781024,267655550,
            183460325,284786399,222774818,193425138,51658225,117130718,352764522,342521474,147243649,265160879}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 44; int Arg3 = 9986066; long long Arg4 = 234928185619577559LL; verify_case(7, Arg4, theMin(Arg0, Arg1, Arg2, Arg3)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    BuildingReorganization ___test; 
    ___test.run_test(7);
} 

