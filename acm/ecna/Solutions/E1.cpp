// Parens.cc
// ECNA 2012 - Parencedence!

#include <iostream>
#include <list>
using namespace std;

const bool DEBUG = false;
#define IFDB if (DEBUG)
#define FOR(i,n) for(int i=0;i<n;i++)

int nums[10];
char ops[9];
int operators;

// ------

void GetExp(){

  cin>>operators;
  FOR(i,operators)
    cin>>nums[i]>>ops[i];
  cin>>nums[operators];
}

// ------

void PrintExp(int n, int nums[], char ops[]){
  cout<<"exp: ("<<n<<") ";
  FOR(i,n) cout<<nums[i]<<" "<<ops[i]<<" ";
  cout << nums[n];
  cout<< " // "<<endl;
}

// ------

int Max(int numops, int numbers[], char * opers, int & bestop);

// ------

int Min(int numops, int numbers[], char * opers, int & bestop){
  int numbers2[10];
  char ops2[9];
  int best, b, left, right;
  int value;

  if(numops == 0) return numbers[0];
  best = 500000000; bestop = -1;
  FOR(i, numops){  //try each operator
    FOR(j,i){  //1st part of exp unchanged
      numbers2[j]=numbers[j];
      ops2[j] = opers[j];
    }
 
      //exp to collapse is
      //numbers[i] opers[i] numbers[i+1]
      left = numbers[i]; right = numbers[i+1];
      //build new expression
      if(opers[i]=='+') numbers2[i] = left + right;
      if(opers[i]=='-') numbers2[i] = left - right;
      if(opers[i]=='*') numbers2[i] = left * right;
      for(int k=i+1; k<numops; k++){
        ops2[k-1] = opers[k];
        numbers2[k] = numbers[k+1];
      }
    //make max call

    value = Max(numops-1, numbers2, ops2, b);
    if (value<best){
      best = value;
      bestop = i;
    }
  }
  return best;
}

// ------

int Max(int numops, int numbers[], char * opers, int & bestop){
  int numbers2[10];
  char ops2[9];
  int best, left, right;
  int value, b;

  if(numops == 0) return numbers[0];
  best = -500000000; bestop = -1;
  FOR(i, numops){  //try each operator
    FOR(j,i){  //1st part of exp unchanged
      numbers2[j]=numbers[j];
      ops2[j] = opers[j];
    }
      //exp to collapse is
      //numbers[i] opers[i] numbers[i+1]
      left = numbers[i]; right = numbers[i+1];
      //build new expression
      if(opers[i]=='+') numbers2[i] = left + right;
      if(opers[i]=='-') numbers2[i] = left - right;
      if(opers[i]=='*') numbers2[i] = left * right;
      for(int k=i+1; k<numops; k++){
        ops2[k-1] = opers[k];
        numbers2[k] = numbers[k+1];
      }
    //make min call
    value = Min(numops-1, numbers2, ops2, b);
    if (value>best){
      best = value;
      bestop = i;
    }
  }
  return best;
}

// ------

int main(){
  string line;
  char myline[80];
  int n, result1 , result2, bestop, caseno=1;

  cin>>n;
  FOR(i,n){
    GetExp();
    result1 = Max(operators, nums, ops, bestop);

    cout<<"Case "<<caseno++<<":"<<endl;
    cout<<"Player 1 ";
    cout<<"("<<nums[bestop]<<ops[bestop]<<nums[bestop+1]<<") leads to "<<result1<<endl;

    result2 = Min(operators, nums, ops, bestop);
    cout<<"Player 2 ";
    cout<<"("<<nums[bestop]<<ops[bestop]<<nums[bestop+1]<<") leads to "<<result2<<endl;

    if (result1>-1*result2)
      cout<<"Player 1 wins";
    else if (result1<-1*result2)
      cout<<"Player 2 wins";
    else   //tie
      cout<<"Tie";
    cout<<endl;
  }

  return 0;
}

