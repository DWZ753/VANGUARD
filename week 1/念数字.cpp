#include<stdio.h>
int main()
{
	int x;
	int t;
	int first;
	int cnt=0;
	int divisor=1;
	scanf("%d",&x);
	if(x<0){
		printf("fu ");
		x=-x;
	}
	t=x;
	while(t!=0){
		t/=10;
		divisor*=10;
		cnt++;		//Î»Êý 
	}divisor/=10;
	t=x;
//	printf("%d\n",divisor);//
	while(divisor>0){
		first=t/divisor;
		t%=divisor;
		divisor/=10;
//		printf("%d",first);//
		switch(first){
			case 0:
				printf("ling");
				break;
			case 1:
				printf("yi");
				break;
			case 2:
				printf("er");
				break;
			case 3:
				printf("san");
				break;
			case 4:
				printf("si");
				break;
			case 5:
				printf("wu");
				break;
			case 6:
				printf("liu");
				break;
			case 7:
				printf("qi");
				break;
			case 8:
				printf("ba");
				break;
			case 9:
				printf("jiu");
				break;
		}if(cnt>1){
			printf(" ");
			cnt--;
		}
	}
	
	return 0;
}
