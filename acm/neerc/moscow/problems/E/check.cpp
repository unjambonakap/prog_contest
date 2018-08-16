#define EJUDGE
#include "testlib.h"
#include <stdio.h>
const int MAX_N=100;

int H,W;
int NR;
int C[MAX_N][2];
bool F[MAX_N];
int S[MAX_N][4];

int main(int na,char **aa){
	registerTestlibCmd(na,aa);

	NR = inf.readInt();
	W = inf.readInt();
	H = inf.readInt();

	for(int i=0;i<NR;i++){
		C[i][0]=inf.readInt();
		C[i][1]=inf.readInt();
	}
	for(int i=0;i<NR;i++){
		S[i][0]=ouf.readInt();
		S[i][1]=ouf.readInt();
		S[i][2]=ouf.readInt();
		S[i][3]=ouf.readInt();
		if(S[i][0]<0 || S[i][0]>=S[i][2] || S[i][2]>W ||
			S[i][1]<0 || S[i][1]>=S[i][3] || S[i][3]>H) 
			quitf(_wa,"Wrong rectangle position (%d,%d)-(%d,%d)",S[i][0],S[i][1],S[i][2],S[i][3]);
		int dx=S[i][2]-S[i][0],dy=S[i][3]-S[i][1];
		bool qf=false;
		for(int j=0;j<NR;j++){
			if(!F[j] && (dx==C[j][0] && dy==C[j][1])||(dx==C[j][1] && dy==C[j][0])){
				F[j]=true; qf=true; break;
			}
		}
		if(!qf)	quitf(_wa,"Wrong rectangle size (%d,%d) (line %d)",dx,dy,i+1);
	}
	for(int i=0;i<NR;i++){
		for(int j=i+1;j<NR;j++){
			bool ih=S[i][0]<S[j][0] ? S[i][2]>S[j][0] : S[i][0]<S[j][2];
			bool iv=S[i][1]<S[j][1] ? S[i][3]>S[j][1] : S[i][1]<S[j][3];
			if(ih && iv) quitf(_wa,"Rectangles %d and %d intersect",i+1,j+1);
		}
	}
	quitf(_ok, "All OK");

	return 0;
}

