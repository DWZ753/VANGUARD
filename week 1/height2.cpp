#include <stdio.h>
int main()
{
    printf("��ֱ�������ߵ�Ӣ�ߺ�Ӣ�磬"
    "������\"5 7\"��ʾ5Ӣ��7Ӣ��:");
    float foot;  // ��Ϊ float
    float inch;  // ��Ϊ float
    scanf("%f %f", &foot, &inch);  // ��Ϊ %f
    printf("�����%f�ס�\n", ((foot + inch / 12) * 0.3048));
    return 0;
}
