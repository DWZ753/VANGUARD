#include<stdio.h>
#include<math.h>
int main()
{
	int x;
	int count=1;
	int sum=0;
	int t;
	int n=1;
	int f;
	int m;
	int a=0;
	scanf("%d",&count);
	for(x=1;a<count-1;a++){
		x*=10;
//		printf("x=%d\n",x);//
	}a=x*10;
	for(sum=0,n=1;x<a-1;x++){
		t=x;
		while(t>=10){
			t/=10;
			n*=10;
		}
		for(t=0,m=x;t<count;t++){
		f=m/n;
		sum=sum+pow(f,count);
		m%=n;
		n/=10;
//		printf("f=%d\n",f);//
//		printf("x=%d",x);//
		if(x==sum&&n==0){
			printf("%d\n",x);
			}
		}
//		printf("sum=%d\n",sum);//
		n=1;sum=0;
	}
	
	return 0;
}
