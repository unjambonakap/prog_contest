(defun prepare-for-codejam ()
 (defun insert-py (x)
  (insert
   "import getopt, sys\ndef CodeJamSolver(infilename, problemclasstype, outfilename):\n\tprint \"Parsing \" + infilename + \" to \" + outfilename\n"
   "\tinfileobject = open(infilename,'r')\n\toutfileobject = open(outfilename, 'w')\n\tN = int(infileobject.readline())\n\tfor i in range(N):\n\n"
   "\t\tprint 'Case #' + str(i+1)\n\t\tproblem = problemclasstype(infileobject)\n\t\tsolution = problem.solution()\n\t\tprint solution\n"
   "\t\toutfileobject.write('Case #' + str(i+1) + ': ' + solution + '\\n')\n\tinfileobject.close()\n\toutfileobject.close()\n\nclass Problem" x
   ":\n\tdef __init__(self, fileobject):\n\t\t## Read from fileobject into local variables with lines like\n\t\t## self.T = int(fileobject.readline())\n"
   "\t\t##  or\n\t\t## self.contents=fileobject.readline().rstrip('\\n')\n\t\t##  or\n\t\t## self.words=fileobject.readline().split(' ')\n\t\t##  or\n"
   "\t\t## self.nums = [int(x) for x in fileobject.readline().split(' ')]\n\t\tline = fileobject.readline()\n\n\tdef solution(self):\n\n"
   "\t\t## Use above local variables to return string\n\t\t## for example: return str(x) + ' ' + str(y)\n\t\t## parse floats with eg. \"%1.6f\" % f\n"
   "\t\tcount = map(lambda x:(map(lambda x: 0, range(3))), range(3))\n\t\treturn str(0)\n\ndef usage():\n\tprint \"prob"
   x ".py    runs on test data\"\n\tprint \"prob"
   x ".py -t runs on test data\"\n\tprint \"prob"
   x ".py -s runs on small data\"\n\tprint \"prob"
   x ".py -l runs on large data\"\n\tprint \"prob"
   x ".py -h prints this message\"\n\ndef main():\n\ttry:\n"
   "\t\topts, args = getopt.getopt(sys.argv[1:], \"hstl\", [\"help\", \"small\", \"test\", \"large\"])\n\texcept getopt.GetoptError, err:\n"
   "\t\tprint str(error)\n\t\tusage()\n\t\tsys.exit(2);\n\ttype = \"test\"\n\tfor o, a in opts:\n\t\tif o in (\"-h\", \"--help\"):\n\t\t\tusage()\n"
   "\t\t\tsys.exit()\n\t\telif o in (\"-s\", \"--small\"):\n\t\t\ttype = \"small\"\n\t\telif o in (\"-l\", \"--large\"):\n\t\t\ttype = \"large\"\n"
   "\tinfile = \"c:\\codejam\\semis\\problem" x "\\" x "-\" + type + \".in\"\n"
   "\toutfile = \"c:\\codejam\\semis\\problem" x "\\" x "-\" + type + \".out\"\n\tCodeJamSolver(infile, Problem" x ", outfile)\n\n"
   "if __name__ == \"__main__\":\n\tmain()\n\n"
  )
 )

 (defun proba-py () "Add the prewritten code for problem A in Python." (interactive)(save-excursion (push-mark)(insert-py "A")
												    (call-interactively 'indent-region)))
 (defun probb-py () "Add the prewritten code for problem B in Python." (interactive)(save-excursion (push-mark)(insert-py "B")
												    (call-interactively 'indent-region)))
 (defun probc-py () "Add the prewritten code for problem C in Python." (interactive)(save-excursion (push-mark)(insert-py "C")
												    (call-interactively 'indent-region)))
 (defun probd-py () "Add the prewritten code for problem D in Python." (interactive)(save-excursion (push-mark)(insert-py "D")
												    (call-interactively 'indent-region)))
 (defun probe-py () "Add the prewritten code for problem E in Python." (interactive)(save-excursion (push-mark)(insert-py "E")
												    (call-interactively 'indent-region)))
 (defun probf-py () "Add the prewritten code for problem F in Python." (interactive)(save-excursion (push-mark)(insert-py "F")
												    (call-interactively 'indent-region)))
 (defun insert-cpp (x)
  (insert
   "// Prewritten header. See lib.el\n\n#include <algorithm>\n#include <cmath>\n#include <fstream>\n#include <iostream>\n#include <map>\n"
   "#include <math.h>\n"
   "#include <queue>\n#include <set>\n#include <sstream>\n#include <string>\n#include <vector>\nusing namespace std;\n\ntypedef vector<int> vi;\n"
   "typedef vector<vi> vvi;\ntypedef pair<int, int> ii;\ntypedef pair<int, ii> iii;\ntypedef pair<ii, ii> iiii;\ntypedef vector<ii> vii;\n"
   "typedef vector<vii> vvii;\ntypedef unsigned long long ull;\n#define sz(a) int((a).size())\n#define pb push_back\n#define mp make_pair\n"
   "#define all(c) (c).begin(),(c).end()\n#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); ++i)\n"
   "#define present(c,x) ((c).find(x) != (c).end())\n#define cpresent(c,x) (find(all(c),x) != (c).end())\n\nclass Solver {\npublic:\n"
   "Solver(ifstream& i);\nstring solve();\nprivate:\nint numOfEngines;\nint numOfQueries;\nvector<int> engineNumbersRequested;\n};\n\n"
   "void solve(string type){\nstring infile=\"c:/codejam/semis/Problem" x "/" x "-\" + type + \".in\";\n"
   "string outfile=\"c:/codejam/semis/Problem" x "/" x "-\" + type + \".out\";\ncout << infile << \" to \" << outfile << endl;\n"
   "ifstream input(infile.c_str());\nofstream output(outfile.c_str());\nint N;\ninput >> N;\ncout << N << \" cases\" << endl;\n"
   "for (int i = 1; i <= N; ++i){\ncout << \"Case #\" << i << endl;\nSolver ps(input);\nstring soln=ps.solve();\n"
   "output << \"Case #\" << i << \": \" << soln << endl;\ncout << soln << endl;\n}\ninput.close();\noutput.close();\n}\n\n"
   "int main(int argc, char* argv[])\n{string type = \"test\";\nif (argc > 1){\nint loc = 0;\nchar param = argv[1][loc];\nwhile (param == '-'){\n++loc;\n"
   "param = argv[1][loc];\n}\nswitch (param){\ncase '2':\ncase 'l':\ncase 'L':\ntype = \"large\"; break;\ncase '1':\ncase 's':\ncase 'S':\n"
   "type = \"small\"; break;\ndefault:\ntype = \"test\"; break;}\n}\nsolve(type);\n}\n\nSolver::Solver(ifstream& i){\n"
   "// Read in data to local variables.\n// Remember to define local variables in class description at top\ni >> numOfEngines;\n"
   "cout << numOfEngines << \" Engines.\" << endl;\nmap<string, int> googleOfGoogles;\nfor (int x = 0; x < numOfEngines; ++x){\nstring google;\n"
   "getline(i, google);\nwhile (google.size() < 1){\ncout << \"Ignoring \" << google << endl;\ngetline(i, google);\n}\n"
   "cout << \"Storing \" << google << \" as engine #\" << x << endl;\ngoogleOfGoogles[google] = x;\n}\ni >> numOfQueries;\n"
   "cout << numOfQueries << \" Queries.\" << endl;\nfor (int x = 0; x < numOfQueries; ++x){\nstring request;\ngetline(i,request);\n"
   "while (request.size() < 1){\ngetline(i,request);\n}\nengineNumbersRequested.push_back(googleOfGoogles[request]);\n}\n}\n\nstring Solver::solve() {\n"
   "// Solve problem, using local variables, and return string.\n// If you need to parse a float with exactly 6 decimal\n// places, do:\n"
   "//  char floatBuffer[20];\n//  sprintf(floatBuffer, \".6f\", f);\nint numRequestsSinceSwitch = 0;\nint numSwitches = 0;\n"
   "vector<bool> requestedSinceSwitch;\nfor (int n = 0; n < numOfEngines; ++n){\nrequestedSinceSwitch.push_back(false);\n}\n"
   "for (int q = 0; q < numOfQueries; ++q){\nint r = engineNumbersRequested[q];\nif (!requestedSinceSwitch[r]){\n"
   "if (numRequestsSinceSwitch == numOfEngines - 1){\nnumRequestsSinceSwitch = 0;\n++numSwitches;\nfor (int n = 0; n < numOfEngines; ++n)\n"
   "requestedSinceSwitch[n] = false;\n}\nrequestedSinceSwitch[r] = true;\n++numRequestsSinceSwitch;\n}\n}\nstringstream s; s << numSwitches;\n"
   "return s.str();\n}\n\n"
  )
 )

 (defun proba-cpp () "Add the prewritten code for problem A in C++." (interactive)(save-excursion (push-mark)(insert-cpp "A")
												  (call-interactively 'indent-region)))
 (defun probb-cpp () "Add the prewritten code for problem B in C++." (interactive)(save-excursion (push-mark)(insert-cpp "B")
												  (call-interactively 'indent-region)))
 (defun probc-cpp () "Add the prewritten code for problem C in C++." (interactive)(save-excursion (push-mark)(insert-cpp "C")
												  (call-interactively 'indent-region)))
 (defun probd-cpp () "Add the prewritten code for problem D in C++." (interactive)(save-excursion (push-mark)(insert-cpp "D")
												  (call-interactively 'indent-region)))
 (defun probe-cpp () "Add the prewritten code for problem E in C++." (interactive)(save-excursion (push-mark)(insert-cpp "E")
												  (call-interactively 'indent-region)))
 (defun probf-cpp () "Add the prewritten code for problem F in C++." (interactive)(save-excursion (push-mark)(insert-cpp "F")
												  (call-interactively 'indent-region)))

 (defun djikstra-cpp () "Add the code for Djikstra's algorithm in C++" (interactive)(save-excursion (push-mark)
  (insert 
     "\nvi djikstra(vvii G,int orig){\nint N = sz(G);\nvi D(N, 1000000000);\nset<ii> Q;\nD[orig] = 0;\nQ.insert(ii(0,orig));\n\nwhile (!Q.empty()){\n"
     "ii top = *Q.begin();\nQ.erase(Q.begin());\nint v = top.second, d = top.first;\ntr(G[v], it){\nint v2 = it->first, cost = it->second;\n"
     "if(D[v2] > D[v] + cost){\nif (D[v2] != 1000000000){\nQ.erase(Q.find(ii(D[v2],v2)));\n}\nD[v2] = D[v] + cost;\nQ.insert(ii(D[v2],v2));\n}\n}\n}\n"
     "return D;\n}"
  ) (call-interactively 'indent-region) ) )

 (defun djikstra-float-cpp () "Add the code for Djikstra's algorithm with real weights in C++" (interactive)(save-excursion (push-mark)
  (insert
   "typedef vector<double> vd;\ntypedef pair<double, int> di;\ntypedef pair<int, double> id;\ntypedef vector<id> vid;\ntypedef vector<vid> vvid;\n\n"
   "vd djikstra(vvid G,int orig){\nint N = G.size();\nvd D(N, 1000000000.0);\nset<di> Q;\nD[orig] = 0;\nQ.insert(di(0,orig));\nwhile (!Q.empty()){\n"
   "di top = *Q.begin();\nQ.erase(Q.begin());\nint v = top.second;\ndouble d = top.first;\n"
   "for (vid::iterator it = G[v].begin(); it != G[v].end(); ++it){\nint v2 = it->first;double cost = it->second;\nif(D[v2] > D[v] + cost){\n"
   "if (D[v2] != 1000000000.0){\nQ.erase(Q.find(di(D[v2],v2)));\n}\nD[v2] = D[v] + cost;\nQ.insert(di(D[v2],v2));\n}\n}\n}\nreturn D;\n}\n\n"
 ) (call-interactively 'indent-region) ) )

 
 (defun push-relabel-cpp () "Add a C++ Push Relabel Class" (interactive)(save-excursion (push-mark)
  (insert
    "// Prewritten Push-Relabel algorithm. See lib.el\n\nclass PushRelabel {\npublic:\nPushRelabel(int numVertices);\n~PushRelabel();\n"
    "void addEdge(int i, int j, int cap);\nvoid initialize_preflow();\nvoid push(int u,int v);\nvoid relabel(int u);\nvoid runalg(int source, int sink);\n"
    "int maxFlow(){ return e[t]; }\nint** flow() {return f;}\n\nprivate:\nint n;\nint* h;\nint* e;\nint** f;\nset<int>* G;\nint** c;\nint** cf;\nint s;\n"
    "int t;\n};\n\nPushRelabel::PushRelabel(int numVertices){\nn = numVertices;\nh = new int[n];\ne = new int[n];\nG = new set<int>[n];\n"
    "f = new int*[n];\nc = new int*[n];\ncf = new int*[n];\nfor (int i = n-1; i >= 0; --i){\nf[i] = new int[n];\nc[i] = new int[n];\ncf[i] = new int[n];\n"
    "memset(c[i],0,sizeof(int)*n);\n}\n}\n\nPushRelabel::~PushRelabel(){\ndelete[] h; delete[] e; delete[] G;\nfor (int i = 0; i < n; ++i){\n"
    "delete[] f[i]; delete[] c[i]; delete[] cf[i];\n}\ndelete[] f; delete[] c; delete[] cf;\n}\n\nvoid PushRelabel::addEdge(int i, int j, int cap){\n"
    "if (present(G[i],j)){\nc[i][j] += cap;\n} else {\nG[i].insert(j);\nG[j].insert(i);\nc[i][j] = cap;\n}\n}\n\n"
    "void PushRelabel::initialize_preflow() {\nmemset(h,0,sizeof(int)*n);\nh[s] = n;\nmemset(e,0,sizeof(int)*n);\nfor (int i = n-1; i >= 0; --i){\n"
    "memset(f[i],0,sizeof(int)*n);\nfor (int j = n-1; j >= 0; --j)\ncf[i][j] = c[i][j];\n}\ntr(G[s],v){\nf[s][*v] = c[s][*v];\nf[*v][s] = -c[s][*v];\n"
    "e[*v] = c[s][*v];\ne[s] -= c[s][*v];\ncf[s][*v] = c[s][*v] - f[s][*v];\ncf[*v][s] = c[*v][s] - f[*v][s];\n}\n}\n\n"
    "void PushRelabel::push(int u, int v){\nint temp = min(e[u],cf[u][v]);\nf[u][v] += temp;\nf[v][u] -= temp;\ne[v] += temp;\ne[u] -= temp;\n"
    "cf[v][u] += temp;\ncf[u][v] -= temp;\n}\n\nvoid PushRelabel::relabel(int u){h[u] = 0;\ntr(G[u],v)\nif (cf[u][*v] > 0)\n"
    "if (h[u] == 0 || h[u] > 1 + h[*v])\nh[u]=1+h[*v];\n}\n\nvoid PushRelabel::runalg(int source, int sink){\ns = source;\nt = sink;\n"
    "initialize_preflow();\nqueue<int> q;\nchar* l = new char[n];\nint u,m;\nmemset(l,0,sizeof(char)*n);\ntr(G[s],w)\nif (*w != t) {\nq.push(*w);\n"
    "l[*w] = 1;\n}\nwhile (q.size() != 0){\nu = q.front();\nm = -1;\nfor (set<int>::iterator v = G[u].begin();\nv != G[u].end() && e[u] > 0;\n++v) {\n"
    "if (cf[u][*v] > 0){\nif (h[u] > h[*v]){\npush(u,*v);\nif (l[*v] == 0 && *v != s && *v != t) {\nl[*v] = 1;\nq.push(*v);\n}\n}\n"
    "else if (m == -1 || m > h[*v]) m = h[*v];\n}\n}\nif (e[u] != 0) h[u] = 1 + m;\nelse {\nl[u] = 0;\nq.pop();\n}\n}\n}\n\n";
  ) (call-interactively 'indent-region)))

 (defun binary-search-cpp () "Add a C++ Binary Search" (interactive)(save-excursion (push-mark)
  (insert
   "// Prewritten Binary Search code. See lib.el\n\nclass BinaryFunction{public: virtual bool operator ()(long x){ }};\n\n"
   "// Given a (subclass of) BinaryFunction f, and values of min and max\n// such that f(min) is true, and f(max) is false), returns a value i\n"
   "// for which f(i) is true and f(i+1) is false.\n\nlong binarySearch(long min, long max, BinaryFunction* f){\nwhile (max > min + 1){\n"
   "long half = (max + min) >> 1;\nif ((*f)(half)) min = half;\nelse max = half;\n}\nreturn min;\n}\n\n"
   "// Example usage: Suppose s is an increasing array of longs of length K\n// Suppose that t > s[0].\n"
   "// Then binarySearch(0,K,elementLessThan(s,t)) will return the largest\n// i such that s[i] < t.\nclass elementLessThan: public BinaryFunction{\n"
   "long* z;\nlong y;\npublic:\nelementLessThan(long* tz, long ty){\nz = tz;\ny = ty;\n}\n\nbool operator()(long x){\nreturn *(z + x) < y;\n}\n};\n\n"
 ) (call-interactively 'indent-region)))

 (defun disjoint-sets-cpp () "Add the Disjoint Sets data structure in C++" (interactive)(save-excursion (push-mark)
  (insert
   "// Prewritten Disjoint Sets data structure. See lib.el\n\nclass DisjointSets{\nprivate:\nmap<int, int> parent;\nmap<int, int> rank;\n\npublic:\n"
   "void clear(){\nparent.clear();\nrank.clear();\n}\n\nvoid MakeSet(int x){\nif (!present(parent, x)){\nparent[x] = x;\nrank[x] = 0;\n}\n}\n\n"
   "void setUp(int m, int n){\nfor (int x = m; x < n; ++x)\nMakeSet(x);\n}\n\nint Find(int x){\nint y = parent[x];\nif (x == y)\nreturn x;\nelse {\n"
   "parent[x]=Find(y);\nreturn parent[x];\n}\n}\n\nbool Union(int x,int y){\nint xR=Find(x);\nint yR=Find(y);\nif (xR == yR) return false;\n"
   "if (rank[xR]>rank[yR])\nparent[yR] = xR;\nelse if (rank[xR] < rank[yR])\nparent[xR] = yR;\nelse {\nparent[yR] = xR;\n++rank[xR];\n}\nreturn true;\n"
   "}\n};\n\n"
 ) (call-interactively 'indent-region)))

 (defun max-bipartite-matching-cpp () "Add the Maximum Bipartite Matching calculator in C++" (interactive)(save-excursion (push-mark)
  (insert
   "// Prewritten Maximum Matching Calculator. See lib.el\n\nclass MaxMatch{\nprivate:\nint N;\nint M;\nvector<set<int> > G;\nvector<int> pred;\n"
   "vector<int> seen;\n\npublic:\nMaxMatch(vector<set<int> > g, int m){\nG = g;\nN = G.size();\nM = m;\n}\n\nbool dfs(int i){\nif (i == -1) return true;\n"
   "if (seen[i]) return false;\nseen[i] = 1;\ntr(G[i], gv){\nint j = *gv;\nif (dfs(pred[j])){\npred[j] = i;\nreturn true;\n}\n}\nreturn false;\n}\n"
   "int max_matching(){\npred.resize(0);\npred.resize(M,-1);\nint ans = 0;\nfor (int i = 0; i < N; ++i){\nseen.resize(0);\nseen.resize(N,0);\n"
   "if (dfs(i))\n++ans;\n}\nreturn ans;\n}\n};\n"
 ) (call-interactively 'indent-region)))

 (defun gcd-cpp () "Add the GCD routine in C++" (interactive)(save-excursion (push-mark)
  (insert
   "// Prewritten GCD routine. See lib.el\n\nint gcd(int x, int y){\nx = (x > 0) ? x : -x;\ny = (y > 0) ? y : -y;\nwhile (x != 0){\nint z = y % x;\n"
   "x = y; y = z;\n}\nreturn y;\n}\n"
 ) (call-interactively 'indent-region)))

 (defun minimum-spanning-forest-cpp () "Add a minimum spanning forest algorithm in C++" (interactive)(save-excursion (push-mark)
  (insert
   "// Prewritten Min Spanning Forest algorithm. See lib.el\n\ntypedef iii Edge;\ntypedef pair<vector<Edge>, int> Forest;\n\n"
   "class MinimumSpanningForest{\nprivate:\nint N;\nDisjointSets ds;\nset<Edge> edges;\npublic:\nMinimumSpanningForest(int n){\nN = n;\n}\n\n"
   "void addEdge(int f, int t, int w){\nedges.insert(mp(w,mp(f,t)));\nif (f > N) N = f;\nif (t > N) N = t;\n}\n\nForest findForest(){\nds.clear();\n"
   "ds.setUp(0,N+1);\nvector<Edge> forest;\nint size=0;\ntr(edges, edgeit){\nEdge e = *edgeit;\nif (ds.Union(e.second.first, e.second.second)){\n"
   "forest.push_back(e);\nsize += e.first;\n}\n}\nreturn mp(forest,size);\n}\n};\n\n"
 ) (call-interactively 'indent-region)))

 (defun arithmetic-cpp () "Add some arithmetic methods in C++" (interactive)(save-excursion (push-mark)
  (insert
   "// Prewritten Arithmetic methods. See lib.el\n\n// Multiplication modulo c. 2*c must fit into unsigned long long.\n"
   "ull mulmod(ull a, ull b, ull c){\null x =0,y=a%c;\nwhile(b>0){\nif (b % 2 == 1)\nx=(x+y)%c;\ny=(y << 1)%c;\nb >>= 1;\n}\nreturn x%c;\n}\n\n"
   "// Exponentiaition modulo c. 2*c must fit into unsigned long long.\null expmod(ull a, ull b, ull c){\null x=1,y=a%c;\nwhile(B>0){\nif (b % 2 == 1)\n"
   "x=mulmod(x,y,c);\ny=mulmod(y,y,c);\n b >>= 1;\n}\nreturn x%c;\n}\n\n// Miller-Rabin Primality Testing\nbool Miller(ull p, int it){\n"
   "if (p < 2) return false;\nif (p > 2 && (p % 2 == 0)) return false;\null s = p-1;\nwhile ((s & 1) == 0) s >>= 1;\nfor (int i = 0; i < it; ++i){\n"
   "ull a=rand()%(p-1)+1,temp=s;\null mod=expmod(a,temp,p);\nwhile(temp!=p-1 && mod!=1 && mod != p-1){\nmod = mulmod(mod, mod, p);\ntemp <<= 1;}\n"
   "if (mod != p-1 && temp % 2 == 0)\nreturn false;\n}\nreturn true;\n}\n\n"
 ) (call-interactively 'indent-region)))

 (defun kmp-cpp () "Add KMP class in C++" (interactive)(save-excursion (push-mark)
  (insert
   "class KMP{\npublic:\nKMP(char* z, int n);\n~KMP();\nint next(int i, char x);\nprivate:\nint iterate(int i, char x);\nvector<int> F;\nint N;\n"
   "char* y;\n};\n\nint KMP::iterate(int i, char x){\nfor (;;){\nif (y[i] == x) return i+1;\nif (i == 0) return 0;\ni = F[i];\n}\n}\n\n"
   "KMP::KMP(char* z, int n){\nN = n;\ny = new char[N];\nmemcpy(y,z,n*sizeof(char));\nF.assign(n+1,0);\nfor (int i = 2; i <= n; ++i)\n"
   "F[i] = iterate(F[i-1],z[i-1]);\n}\n\nKMP::~KMP(){\ndelete[] y;\n}\n\nint KMP::next(int i, char x){\nif (i < N && y[i] == x) return i+1;\n"
   "return iterate(i,x);\n}\n\n"
 ) (call-interactively 'indent-region)))

 (defun hungarian-cpp () "Add the hungarian algorithm in C++" (interactive)(save-excursion (push-mark)
  (insert
   "// Prewritten Hungarian Algorithm. See lib.el\n\n#define HungN 100\n#defin HungINF 100000000\n\nclass Hungarian{\npublic:\nint cost[HungN][HungN];\n"
   "int n,max_match;\nint lx[HungN], ly[HungN], xy[HungN], yx[HungN], slack[HungN], slackx[HungN], prev[HungN];\nbool S[HungN], T[HungN];\n\n"
   "void init_labels(){\nmemset(ly, 0, sizeof(ly));\nfor(int x = 0; x < n; ++x)\nlx[x] = *max_element(cost[x],cost[x]+n);\n}\n\nvoid update_labels(){\n"
   "int x,y, delta=HungINF;\nfor (y = 0; y < n; ++y)\nif (!T[y])\ndelta = min(delta,slack[y]);\nfor (x = 0; x < n; ++x)\nif (S[x]) lx[x] -= delta;\n"
   "for (y = 0; y < n; ++y)\nif (T[y]) ly[y] += delta;\nelse slack[y] -= delta;\n}\n\nvoid add_to_tree(int x, int prevx){\nS[x] = true;\n"
   "prev[x] = prevx;\nfor (int y = 0; y < n; ++y)\nif (lx[x] + ly[y] - cost[x][y] < slack[y]){\nslack[y] = lx[x]+ly[y]-cost[x][y];\nslackx[y] = x;\n}\n"
   "}\n\nbool augment(){\nif (max_match == n) return false;\nint x,y,root;\nint q[HungN], wr=0, rd=0;\nmemset(S, false, sizeof(S));\n"
   "memset(T, false, sizeof(T));\nmemset(prev, -1, sizeof(prev));\nfor (x = 0; x < n; ++x)\nif (xy[x] == -1){\nq[wr++] = root = x;\nprev[x] = -2;\n"
   "S[x] = true;\nbreak;\n}\nfor (y=0; y < n; ++y){\nslack[y] = lx[root]+ly[y]-cost[root][y];\nslackx[y] = root;\n}\nwhile (true){\nwhile (rd < wr){\n"
   "x = q[rd++];\nfor (y=0; y < n; ++y)\nif (cost[x][y] == lx[x]+ly[y] && !T[y]){\nif (yx[y] == -1) break;\nT[y] = true;\nq[wr++] = yx[y];\n"
   "add_to_tree(yx[y],x);\n}\nif (y < n) break;\n}if (y < n) break;\nupdate_lbaels();\nwr = rd = 0;\nfor (y = 0; y < n; ++y)\n"
   "if (!T[y] && slack[y] == 0){\nif (yx[y] == -1){\nx = slackx[y]; break;\n} else {\nT[y] = true;\nif (!S[yx][y]){\nq[wr++] = yx[y];\n"
   "add_to_tree(yx[y], slackx[y]);}\n}\n}\nif (y < n) break;\n}\nif (y < n){\nmax_match++;\n"
   "for (int cx = x, cy = y, ty; cx != -2; cx = prev[cx], cy = ty){\nty = xy[cx]; yx[cy]=cx; xy[cx]=cy;\n}\n}\nreturne true;}\n\nint max_cost(){\n"
   "int ret = 0;\nmax_match = 0;\nmemset(xy, -1, sizeof(xy));\nmemset(yx, -1, sizeof(yx));\ninit_labels();\nwhile (augment());\n"
   "for (int x = 0; x < n; ++x)\nret += cost[x][xy[x]];\nreturn ret;\n}\n};"
 ) (call-interactively 'indent-region)))
)

(prepare-for-codejam)