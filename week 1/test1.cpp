#include <stdio.h>

int main() {
    int a = 10;
    int b = 20;
    
    printf("有换行符的输出:\n");
    printf("%d %d\n", a, b);  // 使用 \n
    printf("这是下一行内容\n");
    
    printf("\n没有换行符的输出:\n");
    printf("%d %d", a, b);    // 不使用 \n
    printf("这是下一行内容");
    
    return 0;
}
