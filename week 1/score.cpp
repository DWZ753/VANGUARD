#include<stdio.h>
int main()
{
	int score,PASS=60;
	printf("������ɼ���");
	scanf("%d",&score);
	
	printf("������ĳɼ���%d��\n",score);
	if (score<PASS) 
	   printf("���ź�������ɼ�û�м���"); 
	else
	   printf("ף���㣬����ɼ������ˡ�");
	printf("�ټ���\n"); 
	
	
	return 0;
}
