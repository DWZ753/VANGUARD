#include <stdio.h>

int main() {
    int a = 10;
    int b = 20;
    
    printf("�л��з������:\n");
    printf("%d %d\n", a, b);  // ʹ�� \n
    printf("������һ������\n");
    
    printf("\nû�л��з������:\n");
    printf("%d %d", a, b);    // ��ʹ�� \n
    printf("������һ������");
    
    return 0;
}
