#include<stdio.h>
int main()
{
	int answer,input;
	int count=0;
	int bingo=0;
	int N; 
	scanf("%d %d/n",&answer,&N);
	do{
		scanf("%d",&input);
		count++;
		if(input==answer&&count==1){
			printf("Bingo!\n");
			break;
		}else if(input==answer&&count<=3){
			printf("Lucky You!\n");
			break;
		}else if(input==answer&&count<=N){
			printf("Good Guess!\n");
			break;
		}else if(input>answer&&count<N){
			printf("Too big\n");
		}else if(input>=0&&input<answer&&count<N){
			printf("Too small\n");
		}else if(count>=N||input<0){
			printf("Game Over\n");
			break;
		}
	}while(bingo!=1);
	
	return 0;
}
