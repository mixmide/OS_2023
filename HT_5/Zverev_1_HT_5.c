#include <stdio.h>

/* Создаем макрос, который по своей сути является функцией вывода
числа в двоичном виде (алгоритм аналогичен заданию 2 ДЗ-2). */

#define BINPRINT(a) {\
    if (((((typeof(a))1) << (sizeof(typeof(a))*8 - 1)) & a) == 0)\
        putchar('0');\
    else\
        putchar('1');\
    for(int i = 1; i < sizeof(typeof(a))*8; i++) {\
        if (((((typeof(a))1) << (sizeof(typeof(a))*8 - (i+1))) & a) == 0)\
            putchar('0');\
        else\
            putchar('1');\
    }\
    printf("\n"); } \


int main(void) {
    printf("Зверев Дмитрий, 210 группа, задание 1 ДЗ-5\n");
    // ФРАГМЕНТ ПРОГРАММЫ ИЗ УСЛОВИЯ
    char c = -3;
    if(c)
        BINPRINT(c)
    else
        printf("Zero!\n");
    BINPRINT((short)7);
    long x = 15;
    if(x)
        BINPRINT(x)
    else
        printf("Zero!\n");
    BINPRINT((long long)x);
    return 0;
}