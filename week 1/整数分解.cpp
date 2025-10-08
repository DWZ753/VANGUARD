#include<stdio.h>
int main()
{
	int x;
	int count=1;
	int t;
	int first;
	int tool=1;
	scanf("%d",&x);
	t=x;
	while(t>=10){
		t/=10;
		count++;
		tool*=10;
	}
//	printf("count=%d,tool=%d,x=%d\n",count,tool,x);//Î»Êý
	while(tool>0){
		first=x/tool;
		printf("%d",first);
		if(tool>0){
			printf(" ");
		}
		x%=tool;
		tool/=10;
	}
	
	return 0;
}
