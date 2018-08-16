//
//  main.c
//  C
//
//  Created by alle on 12/9/26.
//  Copyright (c) 2012年 alle. All rights reserved.
//

#include <stdio.h>

int main(int argc, const char * argv[])
{
    int n, m, i=0, j;
    int d;
    int g[10];
    printf("Input n, m:\n");
    do{
        scanf("%d %d", &n, &m);
        d=n-m;
        if(d!=1);
        else if(n==1 || n==2){
            g[i]=1;
        }
        else{
            g[i]=(2*(n-2)-1)*n;
        }
        //g[i]%=mod;
        i++;
    }while(i<10 && n!=0 && m!=0);
    /*if(n<1 || n>100 || m<0 || m>100){
        printf("Error !\n");
        return -1;
    }*/
    for(j=0; j<i-1; j++){
        printf("%d\n", g[j]);
    }
    return 0;
}

