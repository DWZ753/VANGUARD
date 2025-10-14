#include<stdio.h>
enum GPIO_Speed_Type{
	GPIO_Speed_2MHz,GPIO_Speed_10MHz,GPIO_Speed_50MHz
};
struct GPIO{
	enum GPIO_Speed_Type GPIO_Speed; 
};
void GPIO_StructureInit(struct GPIO *p)
{
	p->GPIO_Speed=GPIO_Speed_2MHz;
}

int main()
{
	struct GPIO test;
	GPIO_StructureInit(&test);
	
	return 0;
}
