#include <stdio.h>

/* ФУНКЦИЯ ВЫВОДА ЧИСЛА В ДВОИЧНОМ ВИДЕ */
/* ИДЕЯ: Создаем маску с единичкой в самой левой части числа и с помощью
побитового "И" получаем либо 1, либо 0, и выводим его на экран. Далее продолжаем
сдвигать маску с единичкой вправо до конца числа и проверять исходное число
на 1 и 0 по битам слева направо. Заметим, что первую проверку стоит произвести
отдельно, т.к. знаковый разряд (1-я единичка) при сдвиге вправо будет 
дублироваться. */
void print_binar(int x) {
    int mask = 1;
    mask <<= (sizeof(int)*8 - 1);
    (mask & x) == 0 ? putchar('0') : putchar('1');
    mask = 1;
    mask <<= (sizeof(int)*8 - 2);
    for (int i = 1; i < (sizeof(int)*8); i++) {
        (mask & x) == 0 ? putchar('0') : putchar('1');
        mask >>= 1;
    }
    printf("\n");
}

// вспомогательная функция для подсчета единичек в битовом представлении числа
int counter(int x) {
    int count = 0;
    int mask = 1;
    for (int i = 1; i <= (sizeof(int)*8); i++) {
        if ((mask & x) == 1)
            count++;
        x >>= 1;
    }
    return count;
}

// использован метод пузырька
void change(int *arr, int len) {
    int help;                           // переменная для перестановки 2-х эл-в
    for (int i = len - 1; i > 0; i--)
        for(int j = 1; j <= i ; j++)
            if (counter(arr[j-1]) > counter(arr[j])) {
                help = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = help;
            } else if (counter(arr[j-1]) == counter(arr[j])) {
                if (arr[j-1] < arr[j]) {
                    help = arr[j];
                    arr[j] = arr[j-1];
                    arr[j-1] = help;
                }
            }
}

int main(void) {
    printf("Зверев Дмитрий, 210 группа, задание 2 ДЗ-2\n");
    int n;
    printf("Введите размер массива: ");
    scanf("%d", &n);
    int arr[n];
    printf("Введите массив:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Выдача массива:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\nВыдача массива в двоичном виде:\n");
    for (int i = 0; i < n; i++)
        print_binar(arr[i]);
        
    change(arr, n);
    
    printf("Выдача нового массива:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\nВыдача нового массива в двоичном виде:\n");
    for (int i = 0; i < n; i++)
        print_binar(arr[i]);
    return 0;
}
