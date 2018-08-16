// Usage: ./validator locks.in program.out locks.out
// If nothing is printed to stdout, the output is correct.
// Should be used in DomJudge using the compare_wrapper script.
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

const int maxn = 1500;

int lock[maxn][maxn];
int key_at[maxn];

int numline, pos;

FILE *valoutfile;

void check(bool b, const char* msg) {
  if (!b) { fprintf(valoutfile, "error at line %i: %s\n", numline, msg); fclose(valoutfile); exit(0); }
}

const int error = -73652341;

int readint(FILE* file) { // faster than scanf
  char c = 0;
  while (isspace((c = fgetc(file))));
  if (!isdigit(c)) return error;

  int ret = c - '0';
  while (!isspace((c = fgetc(file)))) {
    if (!isdigit(c)) return error;
    ret = ret * 10 + c - '0';
  }
  ungetc(c, file);
  return ret;
}

// validator {:infile} {:outfile} {:ansfile} {:valoutfile}
int main(int argc, char** argv) {
  FILE *infile, *outfile, *ansfile;
  infile = fopen(argv[1], "r");
  ansfile = fopen(argv[3], "r");
  outfile = fopen(argv[2], "r");
  valoutfile = (argc == 5) ? fopen(argv[4], "w") : stdout;

  int n, numlocks, src, dest;
  numline = 1;
  while (fscanf(infile, "%i %i %i %i", &n, &numlocks, &src, &dest), n) {
    fill(&key_at[0], &key_at[n], -1);
    for (int i = 0; i < numlocks; ++i) {
      int x;
      fscanf(infile, "%i", &x);
      key_at[x] = i;
    }

    fill(&lock[0][0], &lock[n][0], -1);
    for (int i = 0; i < n - 1; ++i) {
      int a, b, l;
      fscanf(infile, "%i%i%i", &a, &b, &l);    // l=-1 means that no lock is required
      if (l < 0) l = n;
      lock[a][b] = lock[b][a] = l;
    }

    char cans = fgetc(ansfile), cout = fgetc(outfile);
    check(!feof(outfile), "premature end of file");
    ungetc(cans, ansfile);
    ungetc(cout, outfile);
    while (fgetc(ansfile) != '\n');

    if (cans == 'I') {
      char line[20];
      check(fgets(line, sizeof(line), outfile) && !strcmp(line, "Impossible\n"), "answer should be Impossible");
    } else {
      int len;
      check(fscanf(outfile, "%i:", &len) == 1, "unable to read path length");
//      printf("reading %i: \n", len);
      check(0 <= len, "negative path length");
      check(len <= 4 * n * (numlocks + 1), "path too long");

      char msg[1000];
      vector<int> v(len + 1);
      
      // Set of edges unlocked, set of each of the possible keys that can be being carried.
      set<int> opened, curr_keys;

      for (int i = 0; i <= len; ++i) {
        v[i] = readint(outfile);
        check(v[i] != error, "unable to read next vertex in path");
//        printf("reading %i; curr = %i opened = %i\n", v[i], curr_keys, opened);
        sprintf(msg, "invalid vertex; read %i", v[i]);
        check(v[i] >= 0 && v[i] < n, msg);
        check(!((i == 0 && v[i] != src) || (i == len - 1 && v[i] == dest)), "incorrect path endpoint");

        if (i > 0) {
          int l = lock[v[i - 1]][v[i]];
          sprintf(msg, "non-existent edge %i %i", v[i-1], v[i]);
          check(l >= 0, msg);
          if (l < n && opened.find(l) == opened.end()) {
            sprintf(msg, "cannot traverse edge %i %i; key %i needed", 
                v[i-1], v[i], l);
            check(curr_keys.find(l) != curr_keys.end(), msg);
            curr_keys.clear();
            opened.insert(l);
          }
        }
        if (key_at[v[i]] >= 0) curr_keys.insert(key_at[v[i]]);
      }
      check(fgetc(outfile) == '\n', "line too long or line terminator not found");
    }
    ++numline;
  }
  check(fgetc(outfile) == EOF && feof(outfile), "garbage at end of file");

  return 0;
}
