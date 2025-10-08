#include<stdio.h>
int main()
{
	int M,N;
	int x;
	int sum=0;
	int n=0;
	int t,k;
	int prime=0;
	scanf("%d %d",&M,&N);
	x=M;
	while(x<=N){
		if(M==1&&N==1){
			break;
		}
		prime=1;
		t=x;
		k=t-1;
		if(k==0&&x<N){
			x++;
			t=x;
			k=t-1;
		}
		while(prime!=0){
			if(k==1&&prime==1){
				n++;
				sum+=x;
				break;
			}
			t%=k;
			if(t==0){
				prime=0;
				break;
			}else{
				t=x;
				k--;
			}
			
		}x++;
		
	}
	printf("%d %d",n,sum);
	
	
	return 0;
} 
