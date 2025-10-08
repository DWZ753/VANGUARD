#include<stdio.h>
int main()
{
	int A,B,C,X,Y;
	scanf("%d",&X);
	A = X/100;
	B = (X-A*100)/10; 
	C = (X-A*100-B*10);
	Y = C*100+B*10+A;
	printf("%d",Y);
	return 0;
}
