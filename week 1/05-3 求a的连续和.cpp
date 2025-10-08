#include<stdio.h>
#include<math.h>
int main()
{
	int a,n;
	int sum=0;
	int t1=0;
	int t2;
	int cnt;
	scanf("%d %d",&a,&n);
	cnt=n;
	while(cnt>0){
		t2=a*pow(10,cnt-1);
		cnt--;
		t1+=t2;
	}
	while(t1>0){
		sum+=t1;
		t1/=10;
	} printf("%d",sum);
	
	return 0;
}
