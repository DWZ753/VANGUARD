#include<stdio.h>
int main()
{
	int hour;
	int minute;
	int time;
	int past;
	int pasttime;
	scanf("%d %d",&time,&pasttime);
	hour = time % 100;
	minute = time - hour * 100;
	past = hour * 60 + minute + pasttime;
	hour = past/60;
	minute = past % 60;
	printf("%d%d",hour,minute);
	
	return 0;
}
