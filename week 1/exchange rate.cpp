#include <stdio.h>
int main()
{
	double CNY;
	double USD;
	printf("请输入您要兑换的金额（￥）\n（如\"7.65\"）\n");
	scanf("%lf",&CNY);
	USD = CNY / 7.1246;
	printf("当前可兑换%f$",USD);
	return 0;
}
