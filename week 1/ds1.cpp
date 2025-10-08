#include <stdio.h>

int main() {
    int day = 3;
    switch (day) {
        case 1:
            printf("Monday, ");
        case 2:
            printf("Tuesday, ");
        case 3:
            printf("Wednesday, ");
        case 4:
            printf("Thursday, ");
        case 5:
            printf("Friday, ");
        case 6:
            printf("Saturday, ");
            break;
        case 7:
            printf("Sunday, ");
        default:
            printf("End of week.");
    }
    return 0;
}
