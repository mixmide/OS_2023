#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 4

// создаем структуру строки
struct list
{
    struct list* prev;
    struct list* next;
    char* c;
};

// функция создания нового слова (принимает параметр-флаг, указывающий на конец строки)
char *read_word(char* check) {
    int i = 0;
    int c;
    char *p_str = NULL;
    while (((c = fgetc(stdin)) != '\n') && (c != EOF) && (c != ' ')) {
        if (i % LEN == 0)
            p_str = realloc(p_str, LEN + i);
        p_str[i] = (char) (c % 256);
        i++;
    }
    if ((c == '\n') || (c == EOF))
        *check = '1';                                       // достигнут конец строки!
    if (i == 0) {
        p_str = NULL;
    } else {
        if (i % LEN == 0)
            p_str = realloc(p_str, LEN + i);
        p_str[i] = '\0';
    }
    return p_str;
}

// функция удаления списка
void deleteList(struct list* head) {
    struct list* prev = NULL;
    if (head == NULL)
        return;
    while (head->next != NULL) {
        prev = head;
        head = head->next;
        free(prev->c);
        free(prev);
    }
    free(head->c);
    free(head);
}


// основная функция
int main(void) {
    printf("Зверев Дмитрий, 210 группа, задание 2 ДЗ-4\n");
    struct list* L1 = NULL;                     // указатель на начало списка
    struct list* L_last = NULL;                 // указатель на конец списка
    char check = '0';                           // флаг конца строки (будет равен '1' при окончании)
    char* word = NULL;                          // здесь будем создавать слова
    
    // начинаем создание списка: вводим слова
    printf("Напечатайте строку:\n");
    while (check != '1') {
        word = read_word(&check);                // читаем слово
        if (word != NULL) {                      // проверка на пробельное слово или конец строки
            if (L1 == NULL) {
                // если слово первое, создаем список
                L1 = calloc(1, sizeof(struct list));
                L1->next = NULL;
                L1->prev = NULL;
                L1->c = word;
                L_last = L1;
            }
            else {
                L_last->next = calloc(1, sizeof(struct list));  // создаем новый узел
                L_last->next->prev = L_last;                    // в новом узле указываем на старый
                L_last = L_last->next;                          // сдвигаем указатель посл-го узла
                L_last->c = word;                               // значение-слово для нового узла
                L_last->next = NULL;                            // указатель на след. узел пустой
            }
        }
    }

    // выводим список
    int length = 0;                                             // будет считать кол-во слов
    if(L1 != NULL) {
        struct list* p = L1;                                    // указатель для прохода по списку
        printf("Список в прямом порядке:\n");
        while(p->next != NULL) {
            printf("%s ", p->c);
            p = p->next;
            length++;
        }
        printf("%s\n", p->c);                                    // выдача последнего эл-та
        length++;

        printf("Список в обратном порядке:\n");
        while(p != NULL) {
            printf("%s ", p->c);
            p = p->prev;
        }

        printf("\nСписок в алфавитном порядке:\n");  
        // ИСПОЛЬЗОВАН МЕТОД ПУЗЫРЬКА (меняем существующий список, при желании можно создать копию)
        p = L1;
        char* help;                           // переменная для перестановки 2-х эл-в
        for (int i = length - 1; i > 0; i--) {
            p = L1;
            for(int j = 1; j <= i ; j++) {
                if (strcmp(p->c, p->next->c) > 0) {
                    help = p->c;
                    p->c = p->next->c;
                    p->next->c = help;
                }
                p = p->next;
            }
        }
        p = L1;
        while(p->next != NULL) {
            printf("%s ", p->c);
            p = p->next;
        }
        printf("%s\n", p->c);

        deleteList(L1);                    // очистка памяти
        printf("\n");
    } else
        printf("Задан пустой список!");
    return 0;
}