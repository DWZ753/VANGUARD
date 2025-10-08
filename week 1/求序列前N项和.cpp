#include<stdio.h>
int main()
{
	int x;
	int up=1;
	int down=1;
	int t;
	int count=0;
	double sum=0;
	scanf("%d",&x);
	do{
		t=down;
		down=up;
		up=t+down;
		sum+=(up*1.0/down);
		count++;
	}while(count<x);
	printf("%.2f",sum);
	return 0;
}
