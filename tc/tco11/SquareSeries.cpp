// BEGIN CUT HERE

// END CUT HERE
#line 5 "SquareSeries.cpp"

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
using namespace __gnu_cxx;



#define REP(i,n) for(int i = 0; i < int(n); ++i)
#define REPV(i, n) for (int i = (n) - 1; (int)i >= 0; --i)
#define FOR(i, a, b) for(int i = (int)(a); i <= (int)(b); ++i)
#define FORV(i, a, b) for(int i = (int)(a); i >= (int)(b); --i)

#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)
#define FEV(i,t) for (typeof((t).rbegin())i=(t).rbegin();i!=(t).rend();++i)

#define two(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()


#define pb push_back
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n==0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:ctz(n>>1)+1);}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

map<char, string> mp;

const char *tb="BW";
int fd=0;
string ans;

int diff(int a, int b){return a==b?-1:1;}
int id(char c){return c=='W';}

string build(int x, int v, int a, int b){
    if (v==0){
        if (a!=b) return x?"B":string(1, tb[b]);
        if (a){
            if (x) return "BBB";
            return "BWW";
        }else{
            if (x>=2) return "BBW";
            else if (x) return "BWB";
            return "WBB";
        }
    }else if (v>0){
        string res;
        int p=a;
        REP(i, v-1) res+=tb[p^=1];
        if (diff(p, b)==1) return res;
        res+=tb[p^1];
        if (a==0 && x==0) res="WB"+res.substr(1);
        else res=tb[0]+res;
        return res;


    }else{
        string res;
        v=-v;
        if (diff(a, b)==-1) REP(i, v-1) res+=tb[a];
        else{
            REP(i, v+1) res+=tb[0];
            if (x==v) res[v]=tb[1];

        }
        return res;
    }

}

void checkit(const string &nans){ if (fd==0 || nans.length()<ans.length() || (nans.length()==ans.length() && nans<ans)){fd=1; ans=nans;} }

class SquareSeries {
	public:
	string completeIt(string pattern, int l) {

        int m=pattern.length();
        int pos=0;
        int na=0, nb=0;
        --l;
        while(pos<m && pattern[pos]!='?'){
            if (pos) na+=diff(pattern[pos], pattern[pos-1]);
            if (na<0) return "...";
            ++pos;
        }
        
        FOR(j, pos+2, m-1) nb+=diff(pattern[j], pattern[j-1]);
        int ok=1;
        int prev=l-nb;
        FOR(j, pos+2, m-1){
            if (prev<0) return "...";
            prev+=diff(pattern[j], pattern[j-1]);
        }

        fd=0; ans="";
        //printf("\n\n\n");
        //printf("xxx %d %d %d\n", na, nb, l);
        //cout<<pattern<<endl;

        if (pos==0 && pos==m-1){
            if (l==0) return "B";
            REP(i, 2) REP(j, 2){
                string nans=tb[i]+build(0, l, i, j)+tb[j];
                checkit(nans);
            }
        }else if (pos==0){
            int b=id(pattern[pos+1]);
            if (nb!=l){
                REP(i, 2){
                    string nans=tb[i]+build(0, l-nb, i, b);
                    checkit(nans);
                }
            }
        }else if (pos==m-1){
            int a=id(pattern[pos-1]);
            if (na!=l){
                REP(i, 2){
                    string nans=build(na, l-na, a, i)+tb[i];
                    checkit(nans);
                }
            }
        }else{
            int a, b;
            a=id(pattern[pos-1]), b=id(pattern[pos+1]);
            string nans=build(na, l-na-nb, a, b);
            checkit(nans);
        }

        return pattern.substr(0, pos)+ans+pattern.substr(pos+1);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	//void test_case_0() { string Arg0 = "W?B"; int Arg1 = 2; string Arg2 = "WB"; verify_case(0, Arg2, completeIt(Arg0, Arg1)); }
	void test_case_0() { string Arg0 = "WB?B"; int Arg1 = 2; string Arg2 = "WBBWBB"; verify_case(0, Arg2, completeIt(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "?"; int Arg1 = 5; string Arg2 = "BWBWB"; verify_case(1, Arg2, completeIt(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "BWBBBBW?WB"; int Arg1 = 10; string Arg2 = "..."; verify_case(2, Arg2, completeIt(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "BWBWBW?WBWBWBW"; int Arg1 = 15; string Arg2 = "BWBWBWBBWBWBWBWBW"; verify_case(3, Arg2, completeIt(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "WBWBWBWBWBWWBB?W"; int Arg1 = 1; string Arg2 = "WBWBWBWBWBWWBBBBBBBBBBBWW"; verify_case(4, Arg2, completeIt(Arg0, Arg1)); }
	void test_case_5() { string Arg0 = "?WBWBWBBB"; int Arg1 = 3; string Arg2 = "..."; verify_case(5, Arg2, completeIt(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main(){
  SquareSeries ___test; 
        ___test.run_test(0);
        } 
// END CUT HERE
