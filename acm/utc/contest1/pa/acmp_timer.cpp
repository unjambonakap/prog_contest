// acmp_timer.cpp : définit le point d'entrée pour l'application console.
//


#include <iostream>
#include <fstream>
#include <vector>
#include <list>
struct testcase{
		long int timer;
		long int c1;
		long int c2;
		long int s1;
		long int s2;
		long int T1;
		long int T2;

};
int main()
{
	
	std::ifstream F("test.txt", std::ios::in);
	std::vector<testcase> Te;
	bool b=true;
	do{		
		testcase T;
		F>>T.timer;
		F>>T.c1;
		F>>T.c2;
		F>>T.s1;
		F>>T.s2;
		F>>T.T1;
		F>>T.T2;
		
		if(T.timer==0 && T.c1 ==0 && T.c2==0 && T.s1==0 && T.s2==0 && T.T1==0 && T.T2==0)
			b=false;
		Te.push_back(T);
	}while(b);
	Te.pop_back();

	for(int i=0;i<Te.size();i++){
		testcase C=Te[i];
		if(C.timer<0)
			std::cout<<-1<<std::endl;
		long int res=0;
		long int c1=C.c1,c2=C.c2;
		while(C.timer!=0){
			
			c1=(c1+1)%(C.T1);
			c2=(c2+1)%(C.T2);
			res++;
			
			if(c1==C.s1%C.T1 &&c2==C.s2%C.T2){
				C.timer--;
			}

			if(C.timer<0 ){
				std::cout<<-1<<std::endl;
				break;
			}
		}
		
		std::cout<<res<<std::endl;
	}
	std::cout<<std::endl;
	return 0;
}

