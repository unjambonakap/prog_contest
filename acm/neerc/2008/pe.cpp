#include<cassert>
#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
#include<sstream>
#include<map>

#include<set>

#define FOR(i,a,b) for (int i=(a); i<(b); ++i)
#define REP(i, n) FOR(i,0,n)
#define two(x) (1<<(x))

using namespace std;

typedef vector<int> vi;
const int maxn=1111;
const int maxm=11;

int pos;
int n;
map<string,int> mp;

int g[maxn][2];
int na[2];
int type[2][maxm];
int nip[2][maxm];
int tmpA[2][maxm][2];
int iscs[maxn];
int ncs[maxn];

string toStr(int a){
	ostringstream os;
	os<<a;
	return os.str();
}

struct Vertex{
    int id;
    set<int> can[1<<4];//first two bits: which played, last 2 bits: entered cs or not


    void start();
    void dfsX(int v, int f);

};

Vertex v[maxn];

void Vertex::start(){
    dfsX(id, 0);
}
void Vertex::dfsX(int v, int f){
    if (can[f].count(v)) return;
    can[f].insert(v);

    REP(i, 2){
        int nf=f|two(i);
        if (iscs[v]&two(i)) nf|=two(i+2);
        dfsX(g[v][i], nf);
    }
}

int checkdeadlock(){
    REP(i, n) REP(f, two(4)){
        if (!(f&3)) continue;
        int fa=f>>2&3;
        if ((f|ncs[i])==3 && fa==0 && v[i].can[f].count(i)){
            return 0;
        }
    }
    return 1;
}
int checkstarv(){
    REP(i, n) REP(f, two(4)){
        if (!(f&3)) continue;
        int fa=f>>2&3;
        if ((f&3|ncs[i])==3 && fa!=(f&3) && v[i].can[f].count(i)) return 0;
    }
    return 1;
}





int dfs(vi ipx, int sa){
    string x=toStr(ipx[0])+";"+toStr(ipx[1])+";"+toStr(sa);
    if (mp.count(x)) return mp[x];
    int z=mp[x]=pos++;

    REP(i, 2){
        vi nipx=ipx;
        int op=ipx[i];
        if (type[i][op]==1){
            nipx[i]=nip[i][op];
            g[z][i]=dfs(nipx, sa);
            ncs[z]|=two(i);

        }else if (type[i][op]==2){
            nipx[i]=nip[i][op];
            g[z][i]=dfs(nipx, sa);
            iscs[z]|=two(i);
        }else if (type[i][op]==3){
            if (sa&(1<<tmpA[i][op][0])) nipx[i]=nip[i][op];
            else nipx[i]=tmpA[i][op][1];
            g[z][i]=dfs(nipx, sa);
        }else if (type[i][op]==4){
            int A=sa&(1<<tmpA[i][op][0]);
            int B=tmpA[i][op][1]?1<<tmpA[i][op][0]:0;
            nipx[i]=nip[i][op];
            g[z][i]=dfs(nipx, (sa^A)|B);
        }
    }
    return mp[x];
}

int main(){
    //freopen("exclusive.in", "r", stdin);
    //freopen("exclusive.out", "w", stdout);
    cin>>na[0]>>na[1];
    REP(id, 2) REP(i, na[id]){
        int fu; cin>>fu;
        string sx; cin>>sx;
        if (sx=="NCS"){
            type[id][i]=1;
        }else if (sx=="CS"){
            type[id][i]=2;
        }else if (sx=="TEST"){
            type[id][i]=3;
            char c; cin>>c;
            tmpA[id][i][0]=c-'A';
            cin>>tmpA[id][i][1];
            --tmpA[id][i][1];
        }else if (sx=="SET"){
            type[id][i]=4;
            char c; cin>>c;
            tmpA[id][i][0]=c-'A';
            cin>>tmpA[id][i][1];
        }else assert(0);
        assert(type[id][i]!=0);
        cin>>nip[id][i];
        --nip[id][i];
    }


    dfs(vi(2,0),0); n=pos;



    int ok=1;
    REP(i, n) if (iscs[i]==3){ ok=0; break;}
    printf("%c", ok?'Y':'N');

    REP(i,n) v[i].id=i;
    REP(i,n) v[i].start();

    printf("%c", checkdeadlock()?'Y':'N');
    printf("%c", checkstarv()?'Y':'N');
    puts("");

    return 0;
}


