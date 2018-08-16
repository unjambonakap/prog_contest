// BEGIN CUT HERE

// END CUT HERE
#line 5 "CompressedStringSearch.cpp"

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

#define SZ(a) (int((a).size()))
#define two(x) (1 << (x))
#define twoll(x) (1LL << (x))
#define ALL(a) (a).begin(), (a).end()
#define CLR(a) (a).clear()


#define pb push_back
#define PF push_front
#define ST first
#define ND second
#define MP(x,y) make_pair(x, y)

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef vector<string> vs;
typedef queue<int> qi;

template<class T> void checkmin(T &a, T b){if (b<a)a=b;}
template<class T> void checkmax(T &a, T b){if (b>a)a=b;}
template<class T> void out(T t[], int n){REP(i, n)cout<<t[i]<<" "; cout<<endl;}
template<class T> void out(vector<T> t, int n=-1){for (int i=0; i<(n==-1?t.size():n); ++i) cout<<t[i]<<" "; cout<<endl;}
inline int count_bit(int n){return (n == 0)?0:1+count_bit(n&(n-1));}
inline bool bit_set(int a, int b){return (a&two(b));}
inline int low_bit(int n){return (n^n-1)&n;}
inline int ctz(int n){return (n==0?-1:(n==1?0:ctz(n>>1)+1));}
int toInt(string s){int a; istringstream(s)>>a; return a;}
string toStr(int a){ostringstream os; os<<a; return os.str();}

const int maxn=55;
int lnk[two(8)];
int n, m;
string ne;

string tb[two(8)];
int dpa[two(8)][maxn];//node, str pos
int dpb[two(8)][maxn];//node, str pos
ll fit[two(8)];
ll expand[two(8)];

ll dfsa(int p){

    if (expand[p]!=-1) return expand[p];
    if (!lnk[p]) return expand[p]=1;

    expand[p]=0;
    REP(i, tb[p].length()) expand[p]+=dfsa(tb[p][i]);
    
    return expand[p];
}

int solvea(char c, ll p){//start at charpos p, and end string c
    int &r=dpa[c][p];
    if (r!=-1) return r;

    if (!lnk[c]) return r=(ne[p]==c);

    REP(i, tb[c].length()){
        if (!solvea(tb[c][i], p)) return r=0;

        p+=expand[tb[c][i]];
        if (p>=m) return r=1;
    }
    return r=1;

}

int solveb(char c, ll p){//end with ne, at charpos p
    int &r=dpb[c][p];
    assert(p<=m);
    if (r!=-1) return r;

    if (!lnk[c]) return r=(ne[p]==c);

    REPV(i, tb[c].length()){
        if (!solveb(tb[c][i], p)) return r=0;
        p-=expand[tb[c][i]];
        if (p<0) return r=1;
        assert(p<=m);
    }
    return r=1;
}

ll solve_fit(char p){
    ll &r=fit[p];
    if (r!=-1) return r;

    string s=tb[p];
    ll pos=0;
    REP(i, s.length()){
        ll tmp=solve_fit(s[i]);
        if (tmp!=-2){
            return r=tmp+pos;
        }
        ll sz=expand[s[i]];

        for(ll j=max(sz-m, 0LL); j<sz; ++j){
            ll rem=sz-1-j;
            assert(rem<=m);
            if (!solveb(s[i], rem)) continue;
            int ok=1, k=i+1;
            ++rem;
            while(rem<m){
                if (k==s.length()){ok=0; break;}
                if (!solvea(s[k], rem)){ok=0; break;}
                rem+=expand[s[k]];
                ++k;
            }
            if (ok) return r=pos+j;
            

        }

        pos+=sz;

    }
    return r=-2;



}

class CompressedStringSearch {
    public:
        long long indexOf(vector <string> d, string haystack, string needle) {
            memset(lnk, 0, sizeof(lnk));

            n=0;
            FE(it, d){
                string tmp=*it;
                lnk[tmp[0]]=1;
                tb[tmp[0]]=tmp.substr(2);
            }
            memset(expand, -1, sizeof(expand));
            REP(i, two(8)) dfsa(i);

            memset(dpa, -1, sizeof(dpa)); memset(dpb, -1, sizeof(dpb)); memset(fit, -1, sizeof(fit));


            ne=needle; m=ne.length();


            string s=haystack;
            ll pos=0;
            REP(i, s.length()){
                ll tmp=solve_fit(s[i]);
                if (tmp!=-2) return tmp+pos;
                
                
                ll sz=expand[s[i]];

                for(ll j=max(sz-m, 0LL); j<sz; ++j){
                    ll rem=sz-1-j;
                    if (!solveb(s[i], rem)) continue;
                    ++rem;
                    int ok=1, k=i+1;
                    while(rem<m){
                        if (k==s.length()){ok=0; break;}
                        if (!solvea(s[k], rem)){ok=0; break;}
                        rem+=expand[s[k]];
                        ++k;
                    }
                    if (ok) return pos+j;
                    

                }

                pos+=sz;

            }

            return -1;

        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        //void test_case_0() { string Arr0[] = {"A=bCc","c=123","b=c119"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "abCca"; string Arg2 = "9C1"; long long Arg3 = 6LL; verify_case(0, Arg3, indexOf(Arg0, Arg1, Arg2)); }
        

        void test_case_0() { string Arr0[] = {"A=abbaabaababaababaaaabaabaaabbabbaabbbabaaabaaaab", "B=bAAaAAAabbAabAbAAbaAaAaAAAAAAAAbaAAAAAaAAbAbbbbA", "C=aabbaaaAAAaaabBbBbbAaBABaAabBBABAbbaBabBAAbabBBb", "D=bCACaCCBAabBbCaCCCABbAbbbAaCAaBbbAaBbCAbaAbBCBaa", "E=babDDaADaCDBbCAaCCbCBDaBabaAAbDCbbCbCCbCDaaaaBbB", "F=DbCaBBbCCAbabbDaEEbaAabCbDbabbBDACbAbBbBCabBBBDa", "G=baCBbbbaEbbabFbbbFBaCCFFbCDbDbabaFFBDDCaabBEaaEB", "H=abBbbCGbbAGCaFaEBaDaaFEAaGGbbaAaaaBCabaFaaBabbaa", "I=aHbaabECBabbbbaCGAaGabFaDGBbEabFCCAFbCbAHaaCbFGA", "J=baaDFIHabbaICbaabABEabaFFbbbbbbAIbHFbADCGabaBIIb", "K=aHGDabbabbIBJBEbJBIGbbabJJIbDbEbGADAbFICabAaFJEH", "L=CbHbFCabaBIaJBIaabaaCDaCbGCHJbabaaKHHDaaaGBbHbba", "M=aabLAEGaHaBbbbDHaEbLGbCbAaBbbbaaBbICbHHHbBaCBbba", "N=EaFbbJJBaaLbMaCIGLaabaBHIMaLaHaabKaLEbbabJbbLBJB", "O=aaLaLIabaADBbbaaAMMCJbbBaDaLKbabbbCaHKaKbbJEbKFG", "P=IGbFbDaObFbBbCNbabbDaaFIbbaGaaObbNbDbbKCbbaADaaI", "Q=aaDLbbaHbbLbEaCbIaNbLBbbabbbEHIDaFPbNHDabHIKOaDa", "R=EKPaaBbbLBabPbaJDOMaMbaJLaIbDbOMBLbMIBCEaMbaaCaH", "S=HDabaBRQBLbLbbQCaQCKbDBLbBOPKaaMbbaDbbDGaRaDCbbE", "T=aIbAabCJbaaEbNLOJbaHBSbObbaOMaObaDaMaQbabJDHbCPb", "U=MbbNFGFabHabTbaaaNbLAGbabbSbaFDaaaaSbKaaaLOCTaaa", "V=PJaCabMaAKJaHNAbTbRaLbaJBTBCaPDJaJOabbFabFRNIGbS", "W=DJPbabaKIbaFGaaaQCaMVEBaMMbaSbbNbbbLRQNaNbabaPaa", "X=ObIAbaabaVaHaWCIbGbaTUbabVSHWRFabaaATQbOQKQaORaJ", "Y=EbaaaKLabJababbabaaITTabbQbaCVHabHbJabbbMabaHbaa", "Z=INSbbMLJbabTCbBCaaKabaFSRaYGbVaBVaIbTObbPJMabHaK"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "CVbTBaFaCOaGJQYDQaQaISaLZOJaLRMAababLYBbbPbaaQIN"; string Arg2 = "baaabaaaabbaaaa"; long long Arg3 = 6LL; verify_case(0, Arg3, indexOf(Arg0, Arg1, Arg2)); }
        void test_case_1() { string Arr0[] = {}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "nowisthetimeforallgoodmen"; string Arg2 = "time"; long long Arg3 = 8LL; verify_case(1, Arg3, indexOf(Arg0, Arg1, Arg2)); }
        void test_case_2() { string Arr0[] = {}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "time"; string Arg2 = "nowisthetimeforallgoodmen"; long long Arg3 = -1LL; verify_case(2, Arg3, indexOf(Arg0, Arg1, Arg2)); }
        void test_case_3() { string Arr0[] = {"A=BBB","B=CCC","C=DDD","D=EEE","E=FFF","F=GGG","G=HHH","H=III","I=JJJ",
            "J=KKK","K=LLL","L=MMM","M=NNN","N=OOO","O=PPP","P=QQQ","Q=RRR","R=SSS",
            "S=TTT","T=UUU","U=VVV","V=WWW","W=XXX","X=YYY","Y=ZZZ","Z=000","0=111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "Atime"; string Arg2 = "1time"; long long Arg3 = 7625597484986LL; verify_case(3, Arg3, indexOf(Arg0, Arg1, Arg2)); }
        void test_case_4() { string Arr0[] = {"A=three_blind_mice","B=_the","C=By_","D=_see_","E=_a_","F=ife_","G=_you","H=DhowCrun","I=all_ran_after",
            "J=_farmers_w","K=who_cut_offBir_tails_withEcarvingknF","L=didG_everDsuchEthing_in"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "A_AHHCIBJFKLGr_lFas_A"; string Arg2 = "your_life_as_three"; long long Arg3 = 181LL; verify_case(4, Arg3, indexOf(Arg0, Arg1, Arg2)); }

        // END CUT HERE

};

// BEGIN CUT HERE
int main(){
    CompressedStringSearch ___test; 
    ___test.run_test(0);
} 
// END CUT HERE
