#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#define LEN 4

/* структура списка: в одном эл-те хранится строка и её кол-во в файле */
struct list
{
    char* str;
    int count;
    struct list* next;
};

/* функция удаления списка*/
void deleteList(struct list* head) {
    struct list* prev = NULL;
    if (head == NULL)
        return;
    while (head->next != NULL) {
        prev = head;
        head = head->next;
        free(prev->str);
        free(prev);
    }
    free(head->str);
    free(head);
}

/* функция чтения строк (использовалась в заданиях ранее) */
char *read_string(FILE* F, char* flag) {
    int i = 0;
    int c;
    char *p_str = NULL;
    while (((c = fgetc(F)) != '\n') && (c != EOF)) {
        if (i % LEN == 0)
            p_str = realloc(p_str, LEN + i);
        p_str[i] = (char) (c % 256);
        i++;
    }
    if (i == 0) {
        p_str = realloc(p_str, 1);
        p_str[0] = '\0';
    } else {
        if (i % LEN == 0)
            p_str = realloc(p_str, LEN + i);
        p_str[i] = '\0';
    }
    if (c == EOF)
        *flag = 1;
    else
        *flag = 0;
    return p_str;
}

/*  функция добавления строки в список ИЛИ увеличение на 1 кол-ва строки в списке
    (использовалась в заданиях ранее, здесь же модификация) */
struct list* append(struct list* L, char* new_str, int shift) {
    // список пустой?
    if (L == NULL) {
        L = calloc(1, sizeof(struct list));
        L->str = new_str;
        L->count = 1;
        L->next = NULL;
        return L;
    }
    // проход по списку, пока не найдем совпадение строк
    struct list* L1 = L;
    struct list* L2 = NULL;     // для запоминания последнего эл-та
    while (L1 != NULL) {
        L2 = L1;
        if ((strlen(new_str) > shift) && (strlen(L1->str) > shift)) {
            // далее сравнение строк начиная со след. эл-та
            if (strcmp(&L1->str[shift], &new_str[shift]) == 0) {
                (L1->count)++;
                free(new_str);  // очищение памяти, строка получилась лишней
                return L;
            }
        }
        L1 = L1->next;
    }
    // строка не найдена, добавляем ее в список
    L2->next = calloc(1, sizeof(struct list));
    L2 = L2->next;
    L2->str = new_str;
    L2->count = 1;
    L2->next = NULL;
    return L;
}

/* ТРЕБУЕМАЯ ФУНКЦИЯ */
void uniq(int argc, ...) {
    // получаем данные с параметров (в виде строк)
    char* argv[argc];
    va_list factor;
    va_start(factor, argc);
    for (int i = 1; i < argc; i++)
        argv[i] = va_arg(factor, char*);
    va_end(factor);
    // переводим параметры во флаги, по умолчанию считаем, что "опций" нет
    int multiplicity = 0;   // перед каждой выводимой строкой помещать ее кратность в файле
    int no_unique = 0;      // подавить вывод неповторяющихся строк
    int yes_unique = 0;     // выводить только уникальные строки
    int shift = 0;          // при сравнении игнорировать заданное число начальных символов строки
    for(int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0)
            multiplicity = 1;
        else if (strcmp(argv[i], "-d") == 0)
            no_unique = 1;
        else if (strcmp(argv[i], "-u") == 0)
            yes_unique = 1;
        else if (strcmp(argv[i], "-s") == 0) {
            shift = atoi(argv[i+1]);
            break;
        } else {
            printf("Данные в командной строке заданы некорректно!\n");
            return;
        }
    }
    // открываем файл
    FILE *F = fopen(argv[1], "r");
    if (F == NULL) {
        printf("Ошибка при открытии файла!\n");
        return;
    }
    // считываем строки из файла и добавляем их в список строк
    char* str = NULL;       // для считывания строк
    char flag = 0;          // флаг достижимости конца файла
    struct list* L = NULL;  // список строк
    // если опций нет ИЛИ подключена только опция -s, то выдаем содержимое файла
    if ((argc == 2) || (strcmp(argv[2], "-s") == 0)) {        
        while (flag == 0) {
            str = read_string(F, &flag);
            printf("%s\n", str);
        }
        fclose(F);
        return;
    } else {
        while (flag == 0) {
            str = read_string(F, &flag);
            L = append(L, str, shift);
        }
    }
    // анализ строк из списка
    struct list* L1 = L;
    if ((no_unique == 0) && (yes_unique == 0)) {        // случай когда надо просто вывести кратность строк
        if (multiplicity) {
            while(L1 != NULL) {
                printf("[%d]%s\n", L1->count, L1->str);
                L1 = L1->next;
            }
        }
    } else if (no_unique + yes_unique != 2) {           // случай когда надо вывести только уникальные/неуникальные строки
        if (multiplicity) {
            while(L1 != NULL) {
                if ((no_unique && (L1->count != 1)) || (yes_unique && (L1->count == 1)))
                    printf("[%d]%s\n", L1->count, L1->str);
                L1 = L1->next;
            }
        } else {
            while(L1 != NULL) {
                if ((no_unique && (L1->count != 1)) || (yes_unique && (L1->count == 1)))
                    printf("%s\n", L1->str);
                L1 = L1->next;
            }
        }
    }
    // закрываем файл и очищаем память
    fclose(F);
    deleteList(L);
}


/* основная функция */
int main(int argc, char **argv) {
    if (argc == 2)
        uniq(argc, argv[1]);
    else if (argc == 3)
        uniq(argc, argv[1], argv[2]);
    else if (argc == 4)
        uniq(argc, argv[1], argv[2], argv[3]);
    else if (argc == 5)
        uniq(argc, argv[1], argv[2], argv[3], argv[4]);
    else if (argc == 6)
        uniq(argc, argv[1], argv[2], argv[3], argv[4], argv[5]);
    else if (argc == 7)
        uniq(argc, argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
    else
        printf("Данные в командной строке заданы некорректно!\n");
    return 0;
}