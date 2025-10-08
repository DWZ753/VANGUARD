#include<stdio.h>
int main()
{
	int n;
	double sum=0;
	int i;
	int sign=1;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		sum+=sign*1.0/i;
		sign=-sign;
	}printf("f(%d)=%f\n",n,sum);
	
	return 0;
}
