#include <queue>
#include <algorithm>
#include <set>
#include <map>
#include <cmath>
#include <vector>
#include <cstdio>
#include <complex>
#include <stack>
#include <cctype>
#include <cstdlib>
#include <iostream>

#define X real()
#define Y imag()
#define PB push_back
#define MP make_pair
#define FR(i,n) for( long long i = 0; i < n; i ++ )
#define FOR(i,a,n) for(long long i = a; i < n; i ++)
#define FREACH(it,v) for( typeof(v.end()) it = v.begin(); it != v.end(); it ++ )
#define EPS 1e-9
using namespace std;

bool intseg(int a3, int b3, int a, int b, int a2, int b2){
	return ( 
		  (a3-a2)*(b3-b) == (a3-a)*(b3-b2) 
	   && ( ( a3 > min(a,a2) && a3 < max(a,a2) ) || a==a2 )
	   && ( ( b3 > min(b,b2) && b3 < max(b,b2) ) || b==b2 )
	);
}



int crs( int x1, int y1, int x2, int y2, int x3, int y3) {
	return (x2-x3)*(y1-y3) - (x1-x3)*(y2-y3);
}

int main () {
	
	int a,b,c;
	int a2,b2,c2;
	int a3,b3,c3;
	int a4,b4,c4;

	for( ; ;) {
		scanf("%d %d %d\n",&a,&b,&c);
		if(!a && !b && !c) break;
		scanf("%d %d %d\n",&a2,&b2,&c2);
		scanf("%d %d %d\n",&a4,&b4,&c4);
		scanf("%d %d %d\n",&a3,&b3,&c3);
		
		int val = crs(a, b, a2, b2, a4, b4);
		
		// the points are not collinear, check interior of triangle
		if(val!=0) { 
			
			long long val1 = crs(a3, b3, a, b, a2, b2);
			long long val2 = crs(a3, b3, a2, b2, a4, b4);
			long long val3 = crs(a3, b3, a4, b4, a, b);
			
			
			if( val1*val2 > 0 && val1*val3 > 0 ) {
				printf("YES\n");
				continue;
			}
					
		} else {
			// the points are collinear, check interior of segment			
			if( intseg(a3, b3, a, b, a2, b2) || 
			   intseg(a3, b3, a, b, a4, b4) ||
			   intseg(a3, b3, a2, b2, a4, b4) ) {
				printf("YES\n");
				continue;
			}			
			
		}
		
		printf("NO\n");				

	}
		
}