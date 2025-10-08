#include<stdio.h>
int main()
{
	int x=0;
	int a,b,c;
	int count=0;
	scanf("%d",&x);
	for(a=x;a<x+4;a++){
		for(b=x;b<x+4;b++){
			for(c=x;c<x+4;c++){
				if(a!=b&&a!=c&&b!=c){
					printf("%d%d%d ",a,b,c);
					count++;
					if(count%6==0){
						printf("\n");
					}
				}
			}
		}
	}
	
	
	return 0;
} 
