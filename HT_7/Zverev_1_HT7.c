#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>	
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    printf("Зверев Дмитрий, 210 группа, задание 1 ДЗ-7\n");
    
    /* проверка на ошибку при открытии файлов */
    int input = open(argv[1], O_RDWR);
    int output = open(argv[2], O_WRONLY);
    if ((input < 0) || (output < 0)) {
        printf("Ошибка при открытии файлов!\n");
        return 0;
    }

    /* проверка на один и тот же файл */
    struct stat stat1;
    struct stat stat2;
    fstat(input, &stat1);
    fstat(output, &stat2);
    if ((stat1.st_dev == stat2.st_dev) && (stat1.st_ino == stat2.st_ino)) {
        printf("Указан один и тот же файл!\n");
        close(input);
        close(output);
        return 0;
    } 
    close(output);

    /*  анализ исходного файла  */
    /*  Шаг 1: проходимся по файлу до тех пор, пока он не закончится или не встретится
        неотрицательное (первое) число. 
        Шаг 2: Затем продолжаем проходиться по файлу, пока он не закончится или
        не встретится отрицательное число. Если оно встретилось, перемещаем его в начало
        (то есть меняем местами первое неотрицательное число с текущим отрицательным), 
        и продолжаем проход по файлу. 
        * Не забываем, что размер int - 4 байта, т.е. sizeof(int) = 4. */
    int buf, buf_first_nonegative;      // буферные переменные для обмена чисел местами
    int i = 0;                          // i - номер текущего считываемого числа (от 0)
    int k = 0;                          // k - номер первого неотрицательного числа
    // шаг 1
    while ((read(input, &buf, sizeof(int)) > 0) && (buf < 0))
        i++;
    k = i;
    // шаг 2 
    while (read(input, &buf, sizeof(int)) > 0) {
        i++;
        if (buf < 0) {
            lseek(input, k*4, SEEK_SET);
            read(input, &buf_first_nonegative, 4);
            lseek(input, k*4, SEEK_SET);
            write(input, &buf, 4);
            lseek(input, i*4, SEEK_SET);
            write(input, &buf_first_nonegative, 4);
            k++;                        // индекс первого неотриц. эл-та увеличился!
        }
    }

    /* записываем результат обработки во второй файл в текстовом виде */
    FILE* F = fopen(argv[2], "w");
    lseek(input, 0, SEEK_SET);          // возвращаем указатель на начало файла
    while(read(input, &buf, sizeof(int)) > 0)
        fprintf(F, "%d ", buf);
    close(input);
    fclose(F);
    printf("...completed...\n");
    return 0;
    }