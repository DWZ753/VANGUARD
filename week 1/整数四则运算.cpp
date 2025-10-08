#include<stdio.h>
int main()
{
	int A,B,X,Y,Z,W;
	scanf("%d %d",&A,&B);
	X = A + B;
	Y = A - B;
	Z = A * B;
	W = A / B;
	printf("%d + %d = %d\n",A,B,X); 
	printf("%d - %d = %d\n",A,B,Y);
	printf("%d * %d = %d\n",A,B,Z);
	printf("%d / %d = %d\n",A,B,W);
	return 0;
}
