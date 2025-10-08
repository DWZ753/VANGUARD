#include<stdio.h>
int main()
{
	int a,b;
	int A,B;
	int t=1;
	scanf("%d/%d",&a,&b);
	if(a==b){
		printf("1/1"); 
	}
	else{
		if(a>b){
		A=a;
		B=b;
	}else{
		A=b;
		B=a;
	}do{
		t=A%B;
		if(t==0){
			break;
		} 
		A=B;
		B=t;
	}while(t!=0);
	a/=B;
	b/=B;
	printf("%d/%d",a,b);
	}
	
	return 0;
}
