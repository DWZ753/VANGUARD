#include<stdio.h>

enum GPIO_Speed_Hz{
	GPIO_Speed_2MHz,GPIO_Speed_10MHz,GPIO_Speed_50MHz};
	
struct GPIO_parameter{
	enum GPIO_Speed_Hz GPIO_Speed;
	};

void GPIO_StructureInit(struct GPIO_parameter *p);

int main()
{
	struct GPIO_parameter test;
	GPIO_StructureInit(&test);
	
	return 0;
}

void GPIO_StructureInit(struct GPIO_parameter *p)
{
	p->GPIO_Speed=GPIO_Speed_2MHz;
}
