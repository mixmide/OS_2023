#include <stdio.h>

int main(void) {
    int num;
    // Открываем файл для записи в бинарном режиме
    FILE *file = fopen("numbers.bin", "wb");
    if (file == NULL) {
        printf("Ошибка при открытии файла!\n");
        return 1;
    }
    // Ввод 10 чисел и запись в файл
    printf("Введите числа: ");
    for (int i = 0; i < 10; i++) {
        scanf("%d", &num);
        fwrite(&num, sizeof(int), 1, file);
    }
    
    fclose(file);
    return 0;
}
