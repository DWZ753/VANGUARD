#include<stdio.h>
int main()
{
	int days;
	scanf("%d",&days);
	if(days%5<=3&&days){
		printf("Fishing in day %d",days);
	}else{
		printf("Drying in day %d",days);
	}
	
	return 0;
} 
