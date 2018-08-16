#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define MAX_ERROR (1e-5)
bool correct(double result,double expected){
  if(abs(result-expected)<MAX_ERROR)return true;
  double from=min(expected*(1-MAX_ERROR),expected*(1+MAX_ERROR)),to=max(expected*(1-MAX_ERROR),expected*(1+MAX_ERROR));
  return from<result && result<to;
}
int main(int argc,char *argv[]){
  FILE *in=fopen(argv[1],"r"),*out=fopen(argv[2],"r"),*correct_out=fopen(argv[3],"r");
  int Z;
  fscanf(in,"%d",&Z);
  for(int z=1;z<=Z;z++){
    double ans,correct_ans;
    if(fscanf(out,"%lf",&ans)!=1){printf("WRONG\nIncorrect answer format.\n");return 0;}
    fscanf(correct_out,"%lf",&correct_ans);
    if(!correct(ans,correct_ans)){printf("WRONG\nError is too big:\n%.8lf\n%.8lf\n",ans,correct_ans);return 0;}       
  }
  puts("OK");
}
