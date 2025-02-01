#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 200

int main(int argc, char* argv[]) {
    printf("Зверев Дмитрий, 210 группа, ДЗ-6\n");
    // выдаем на экран текст исходного файла (для наглядности)
    printf("\nТЕКСТ ИСХОДНОГО ФАЙЛА:\n");
    FILE* F = fopen(argv[argc-1], "r");
    char str[MAXLEN]; 
    while(fgets(str, MAXLEN, F) != NULL)
        printf("%s", str);
    printf("\n");
    fclose(F);

    /*  Выполнение программы: для начала считаем параметры more, учитывая,
        что какой-то из них может отсутствовать в программе. Отсюда получаем
        несколько возможных случаев, из-за чего будет много веток if...else */
        
    // задаем параметры по умолчанию
    int linenum = 1;
    int num = 10;
    int s = 0;              // 0 означает отсутствие параметра, 1 - присутствие
    if (atoi(argv[argc-2]) > 0) {
        linenum = atoi(argv[argc-2]);
        if (atoi(argv[argc-3]) < 0) {
            num = atoi(argv[argc-3]) * (-1);
            if (strcmp(argv[argc-4], "-s") == 0)
                s = 1;
        } else if (strcmp(argv[argc-3], "-s") == 0) {
            s = 1;
        }
    } else if (atoi(argv[argc-2]) < 0) {
        num = atoi(argv[argc-2]) * (-1);
        if (strcmp(argv[argc-3], "-s") == 0)
            s = 1;
    } else if (strcmp(argv[argc-2], "-s") == 0) {
        s = 1;
    }
    // Выдадим на экран получившиеся параметры
    printf("\ns = %d, num = %d, linenum = %d\n\n", s, num, linenum);
    // Проматываем строки в соответствии с параметром linenum
    F = fopen(argv[argc-1], "r");
    for (int i = 1; i < linenum; i++) {
        if (fgets(str, MAXLEN, F) == NULL)
            break;
    }

    // далее в зависимости от первого параметра выводим строки на экран (всего 2 случая)
    if (str != NULL) {      // проверка на то, что есть, что выводить из файла
        if (s == 0) {
            s = -1;             // с этого момента s становится флагом проверки на EOF
            while ((s != -2) && (getchar() != 'q')){
                getchar();
                for (int i = 0; i < num; i++) {         // выдача порциями в соотв-ии с num
                    if (fgets(str, MAXLEN, F) != NULL)
                        printf("%s", str);
                    else {
                        printf("\n");
                        s = -2;
                        fclose(F);
                        break;
                    }
                }
            }
        } else {
            s = -1;                 // с этого момента s становится флагом проверки на EOF
            // флаг: если последняя строка в порции оказалась пустой и после нее пошла
            // посл-ть пустых строк
            int space_pointer = 0; 
            // флаг: если последняя строка в порции оказалась пустой и после нее пошла
            // посл-ть пустых строк. Одна непустая строка окажется прочитанной, но
            // не напечатанной. Поэтому переносим ее в след порцию и отдельно выводим,
            // не забывая при этом уменьшить цикл for на 1 проход.
            int j = 0;
            while ((s != -2) && (getchar() != 'q')){
                getchar();
                j = 0;
                // с прошлой порции осталась ненапечатанная строка?
                if (space_pointer == 1) {
                    printf("%s", str);
                    space_pointer = 0;
                    j = 1;
                }
                for (int i = 0; i < (num - j); i++) {         // выдача порциями
                    if (fgets(str, MAXLEN, F) != NULL) {
                        if (strlen(str) == 1) {         // строка пустая?
                            printf("\n");
                            // далее проматываем все пустые строки
                            while ((fgets(str, MAXLEN, F) != NULL) && (strlen(str) == 1)) {
                            }
                            // мы выводим последнюю строку порции?
                            if (i != (num - j - 1))
                                printf("%s", str);      // да!
                            else
                                space_pointer = 1;      // нет, значит выводим ее в начале след порции
                            if (str == NULL) {
                                fclose(F);
                                break;
                            }
                        } else
                            printf("%s", str);
                    } else {
                        printf("\n");
                        s = -2;
                        fclose(F);
                        break;
                    }
                }
            }
        }
    } else
        printf("Нечего выводить!\n");
    return 0;
}