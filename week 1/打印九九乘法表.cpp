#include<stdio.h>
int main()
{
	int a=1;
	int b=1;
	int x;
	int boundary;
	int result;
	int count=4;
	scanf("%d",&x);
	boundary=x;
	while(a<=boundary){
		a=1;
		while(a!=b+1){
			result=a*b;
			printf("%d*%d=%d",a,b,result);
			while(result>0){
				result/=10;
				count--;
			}while(count>0){
				printf(" ");
				count--;
			}count=4;
			a++;
		}
		printf("\n");
		b++;
	}
	return 0;
}
