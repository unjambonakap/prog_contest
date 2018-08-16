//Back.cc
// 2012 ECNA

#include <iostream>
using namespace std;

const bool DEBUG=false;

#define IFDB if(DEBUG)

int A[15504][6];   //  A[k][] = the 6-tuple stored at loc k

// +++++++++++++++++++++

void PrintTuples(){
  for(int i=0;i<15504;i++){
    cout<<"("<<A[i][0];
    for(int j=1;j<6;j++)
      cout<<","<<A[i][j];
    cout<<")"<<endl;
  }
}

//++++++++++++++

int main(){
  char c;
  int Pts[6];
  int num;
  int k=0,i5;
  int left0, left1, left2, left3, left4;

  //1st create the array of 6-tuples
  for(int i0=0;i0<16;i0++) {   // # of pips on pt 0
    left0 = 15 - i0;            // # of pips for remaining pts
    for(int i1=0;i1<=left0;i1++){   //# pips on pt 1
      left1= left0 - i1;
      for(int i2=0;i2<=left1;i2++) {  //etc
        left2 = left1 - i2;
        for(int i3=0;i3<=left2;i3++) {
          left3 = left2 - i3;
          for(int i4=0;i4<=left3;i4++) {
            i5 = left3 - i4;
            //assign pips to loc k
            A[k][0]=i0;
            A[k][1]=i1;
            A[k][2]=i2;
            A[k][3]=i3;
            A[k][4]=i4;
            A[k][5]=i5;
            k++;
          }
        }
      }
    }
  }

//IFDB PrintTuples();

  cin>>c;
  int icase=0;
  while (c!='e'){
    cout << "Case " << ++icase << ": ";
    if(c=='m'){
      for(int i=0;i<6;i++) cin>>Pts[i];
      //now find Pts[] in A[][]
      int k=0;
      while(k<15504){
        if(A[k][0]==Pts[0] && A[k][1]==Pts[1] &&
           A[k][2]==Pts[2] && A[k][3]==Pts[3] &&
           A[k][4]==Pts[4] && A[k][5]==Pts[5])  {
          cout<<k<<endl;
          break;
        }
        k++;
      }
    }
    else if (c=='u'){
      cin>>num;
      cout<<A[num][0];
      for(int i=1;i<6;i++)
        cout<<" "<<A[num][i];
      cout<<endl;
    }
    else
      cout<<"***ERROR***  char="<<c<<endl;

    cin>>c;
  }


return 0;
}
