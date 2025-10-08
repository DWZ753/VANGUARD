#include<stdio.h>
int main()
{
	int hour,minute;
	scanf("%d:%d",&hour,&minute);
	if(hour<12){
		printf("%d:%d AM",hour,minute);
	}else if(hour==12){
		printf("%d:%d PM",hour,minute);
	}else if(hour==0){
		printf("%d:%d AM",hour,minute);
    }else{
		printf("%d:%d PM",hour-12,minute);
	}
	
	return 0;
}
