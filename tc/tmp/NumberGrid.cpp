// BEGIN CUT HERE

// END CUT HERE
#line 5 "NumberGrid.cpp"

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
#define FOR(i, a, b) for(int i = (int)(a); i < (int)(b); ++i)
#define FE(i,t) for (typeof((t).begin())i=(t).begin();i!=(t).end();++i)

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

const int mod=1e9+7;
const int maxn=55;
int mp[maxn][maxn];
int r, c;
int val[maxn][maxn];
int A[maxn], B[maxn];
int sa[maxn], sb[maxn];

int old[maxn][maxn];
int fd;
int dp[maxn*9];

int checkit(){

    memset(sa, 0, sizeof(sa));
    memset(sb, 0, sizeof(sb));

    REP(i, r) REP(j, c) sa[i]+=val[i][j], sb[j]+=val[i][j];
    REP(i, r) REP(j, c) if (mp[i][j]!=sa[i]+sb[j]-val[i][j]) return 0;
    return 1;
}


int doit(){
    fd=0;
    int res=0;
    if (r>1){
        ll ans=0;
        REP(v, 9*c+1){
            A[0]=v;
            FOR(j, 1, c){
                A[j]=(r-1)*A[0];
                REP(i, r) A[j]+=mp[i][j]-mp[i][0];
                if (A[j]<0 || A[j]%(r-1)) goto fail;
                A[j]/=r-1;
            }
            //now the value of each colunm
            REP(i, r){
                B[i]=0;
                REP(j, c) B[i]+=mp[i][j]-A[j];
                if (B[i]<0 || B[i]%(c-1)) goto fail;
                B[i]/=c-1;
            }
            REP(i, r) REP(j, c) val[i][j]=A[j]+B[i]-mp[i][j];
            REP(i, r) REP(j, c) if (val[i][j]<0 || val[i][j]>9) goto fail;
            REP(i, r){
                int y=0;
                REP(j, c) y+=val[i][j];
                if (y!=B[i]) goto fail;
            }
            REP(j, c){
                int y=0;
                REP(i, r) y+=val[i][j];
                if (y!=A[j]) goto fail;
            }

            if (++fd==1) memcpy(old, val, sizeof(old));
            ++res;
fail:;
        }
    }else{

        REP(i, c) if (mp[0][i]!=mp[0][0]) return 0;
        int x=mp[0][0];
        if (x>9*c) return 0;
        if (c==1) fd=1, old[0][0]=mp[0][0];
        else if (x==0){
            fd=1;
            REP(i, c) old[0][i]=0;
        }else if (x==9*c){
            fd=1;
            REP(i, c) old[0][i]=9;
        }else{
            memset(dp, 0, sizeof(dp));
            dp[0]=1;
            REP(i, c) for (int j=min(i*9, x); j>=0; --j) REP(k, 9) dp[j+k+1]=(dp[j+k+1]+dp[j])%mod;
            res=dp[x], fd=2;
        }

    }
    return res;
}
class NumberGrid {
    public:
        vector <string> decrypt(vector <string> hundreds, vector <string> tens, vector <string> ones) {
            r=ones.size(); c=ones[0].length();
            REP(i, r) REP(j, c) mp[i][j]=(hundreds[i][j]-'0')*100+(tens[i][j]-'0')*10+ones[i][j]-'0';
            int sw=0;
            if (c<r){
                REP(i, r) REP(j, min(i,c)) swap(mp[i][j], mp[j][i]);
                swap(r, c);
                sw=1;
            }
            int res=doit();
            vector<string> ans;
            if (!fd) ans.pb("NO SOLUTIONS");
            else if (fd>1) ans.pb(toStr(res)+" SOLUTIONS");
            else{
                if (sw){
                    REP(i, c){
                        string tmp(r, '0');
                        REP(j, r) tmp[j]=old[j][i]+'0';
                        ans.pb(tmp);
                    }


                }else{
                    REP(i, r){
                        string tmp(c, '0');
                        REP(j, c) tmp[j]=old[i][j]+'0';
                        ans.pb(tmp);
                    }
                }

            }
            return ans;


        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
        //void test_case_0() { string Arr0[] = {"000", "000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"001", "111"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"691", "457"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"013", "257" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, decrypt(Arg0, Arg1, Arg2)); }
        void test_case_0() { string Arr0[] = {"000000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"555555"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"444444"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"013", "257" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(0, Arg3, decrypt(Arg0, Arg1, Arg2)); }

        void test_case_1() { string Arr0[] = {"0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"3"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"3" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(1, Arg3, decrypt(Arg0, Arg1, Arg2)); }
        void test_case_2() { string Arr0[] = {"0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"4"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"2"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"NO SOLUTIONS" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(2, Arg3, decrypt(Arg0, Arg1, Arg2)); }
        void test_case_3() { string Arr0[] = {"23333333333322333333333333333333333333333333333332",
            "33333333343333333333333333333333334333333333443333",
            "12222222222211221222222222222222222222222222222221",
            "12222222222211221122222221111221222222112222222221",
            "12222222222211221122222221111221222222112222222221",
            "12222222222211221122222221111221222222112222222221",
            "12222222222211221122222221111221222222112222222221",
            "22222222232222222222222222222222223222222222232222",
            "12222222222222222222222222222222222222222222232221",
            "01111111111100110011111110000110111111001111111110",
            "01111111111100110011111110000110111111001111111110",
            "22222222232222222222222222222222223222222222332222",
            "22222222232222222222222222222222222222222222232222",
            "12222222222222222222222222222222222222222222222221",
            "11111112221111111112221111111111112222111112222211",
            "12221112222211221122222221111221222222112222222221",
            "11111112222211111122221221111221222222111222222221",
            "22222223333322322233332332222332333333222223333322",
            "33333333343333333333333333333333333333333333343333",
            "01111111111100110011111110000110111111001111111110",
            "01111111111100110011111110000110111111001111111110",
            "01111111111100110011111110000110111111001111111110"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"81221116682299220134442330000331447555001226795438",
                "14554449915522553457764553333554770777335559027651",
                "81221116682299229123331330011221336334111226783318",
                "60110004461188118901120119999119225223990115672106",
                "60110004461188118901120119999119225223990115672106",
                "60110004461188118901120119999119225223990115672106",
                "60110004461188118901120119999119225223990115572116",
                "14554448805522552356663663333553660667334558916651",
                "93333337793311331235542331111442558666112337806539",
                "70110005571188118912220229999229226334990115683217",
                "70110005571188118912220229999229226334990115683217",
                "15554449916633663356665663344663660888445659028761",
                "03443338803311431246653452233542558667333338806640",
                "92332227782200220134442331111331337556111236795439",
                "48998883348866896790008996677997993111778992351094",
                "60119994461188018912220119999119115333990114573216",
                "69999994460077997901119008899119114223999003462106",
                "68999994460077096801108008888008004112888993461096",
                "03443338804422552345554553333553559667333448916540",
                "70110005571188118912220229999229226334990115683217",
                "70110005571188118912220229999229226334990115683217",
                "70110005571188118912220229999229226334990115683217"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"86336665563355332604443002299076449111996335231408",
                    "64114443341133110482254880077884227229771883012586",
                    "38558880015577557152228224411551997996118557489283",
                    "94114446671133113748854880077887553552774113045849",
                    "94114446671133113748854880077887553552774113045849",
                    "94114446671133113748854880077887553552774113045849",
                    "94114446671133113748854880077887553552774113345819",
                    "16336668893355335930009002222339772774226338567731",
                    "72992224459911991593365991188665338007885224190397",
                    "16336665563355335937776002299009772441996335234731",
                    "16336665563355335937776002299009772441996335234731",
                    "83336665560022002937773779966779772118663035231408",
                    "49669998829988691560032635522365338774229991897064",
                    "05225554485544554826665221188228994330888527453620",
                    "83003332263322302604443709966776772118663005231408",
                    "94117776671133413715554810077887883229774116342519",
                    "20777776674466776048887443300110116552007449675842",
                    "08555554452244257126698291188221994663888557456950",
                    "97447776674433113048884880077110883552777446345849",
                    "16336665563355335937776002299009772441996335234731",
                    "16336665563355335937776002299009772441996335234731",
                    "16336665563355335937776002299009772441996335234731"}
            ; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"18888888888888881111111888888811111118888888881111", "18888888888888881111188888888881111888881118888811", "11111118881111111118881111111881118888111111188881", "11111118881111111188811111111111118888111111188881", "11111118881111111188811111111111118888111111188881", "11111118881111111188811111111111118888111111188881", "11111118881111111188811111111111118888111111888811", "11111118881111111118888111188881111888881118888111", "11111118881111111111188888888111111111888888811111", "11111111111111111111111111111111111111111111111111", "11111111111111111111111111111111111111111111111111", "11888888881111111888881111111118888111111188881111", "11111111188811188811188811111188888111111888881111", "11111111188811881111111881111881888111118818881111", "11111111188811811111111181111111888111111118881111", "11118888881111811111111181111111888111111118881111", "18881111111111881111111881111111888111111118881111", "18881111111111188811188811111888888888118888888881", "18888888888811111888881111111888888888118888888881", "11111111111111111111111111111111111111111111111111", "11111111111111111111111111111111111111111111111111", "11111111111111111111111111111111111111111111111111" }; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); verify_case(3, Arg3, decrypt(Arg0, Arg1, Arg2)); }

            // END CUT HERE

};

// BEGIN CUT HERE
int main(){ 
    NumberGrid ___test; 
    ___test.run_test(0); 
} 
// END CUT HERE
