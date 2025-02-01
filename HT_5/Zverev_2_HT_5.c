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

// ф-ия создания слова (принимает параметр-флаг, указывающий на конец строки)
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
        *check = '1';                           // достигнут конец строки!
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

// ТРЕБУЕМЫЕ ФУНКЦИИ
// функция добавления слова в список перед позицией p (отсчёт от 1)
struct list* insert(struct list* L1, char* x, int p) {
    // при прохождении по списку нам нужно запоминать 2 узла, 
    // а именно текущий и предыдущий.
    struct list* buf_now = L1;
    struct list* buf_before = buf_now;
    int i = 1;
    while ((i < p) && (buf_now != NULL)) {
        buf_before = buf_now;
        buf_now = buf_now -> next;
        i++;
    }
    // далее мы создаем новый узел и в зависимости от 3х возможных случаев 
    // перенаправляем те узлы, которые прилегают к только что созданному
    if (p == 1) {                           // вставляем в начало списка?
        L1 -> prev = calloc(1, sizeof(struct list));
        L1 -> prev -> next = L1;
        L1 -> prev -> prev = NULL;
        L1 -> prev -> c = x;
        L1 = L1 -> prev;
    } else if (buf_now == NULL) {           // вставляем в конец списка?
        buf_before -> next = calloc(1, sizeof(struct list));
        buf_before -> next -> next = NULL;
        buf_before -> next -> c = x;
        buf_before -> next -> prev = buf_before;
    } else {                                // вставляем в середину списка
        buf_before -> next = calloc(1, sizeof(struct list));
        buf_now -> prev = buf_before -> next;
        buf_now -> prev -> next = buf_now;
        buf_now -> prev -> prev = buf_before;
        buf_now -> prev -> c = x;
    }
    return L1;
}

// функция удаления слова из списка с позицией p (отсчёт от 1)
struct list* erase(struct list* L1, int p) {
    // при прохождении по списку нам нужно запоминать 2 узла, 
    // а именно текущий и предыдущий.
    struct list* buf_now = L1;
    struct list* buf_before = buf_now;
    int i = 1;
    while ((i < p) && (buf_now != NULL)) {
        buf_before = buf_now;
        buf_now = buf_now -> next;
        i++;
    }
    // далее мы удаляем нужный узел и в зависимости от 4х возможных случаев 
    // перенаправляем те узлы, которые прилегают к удаляемому
    if (p == 1) {                           // удаляем первый эл-т списка?
        L1 = L1-> next;
        free(L1 -> prev -> c);
        free(L1 -> prev);
        L1 -> prev = NULL;
    } else if (buf_now == NULL) {           // удаляем посл-й эл-т списка, p больше номера посл-го эл-та?
        buf_before -> prev -> next = NULL;
        free(buf_before -> c);
        free(buf_before);
    } else if (buf_now -> next == NULL) {   // удаляем посл-й эл-т списка, p совпадает с номером посл-го эл-та?
        free(buf_now -> c);
        buf_now -> prev -> next = NULL;
        free(buf_now);
    } else {                                // удаляем эл-т из середины списка
        buf_before -> next = buf_now -> next;
        free(buf_now -> c);
        free(buf_now);
        buf_before -> next -> prev = buf_before;
    }
    return L1;
}



/*  ОСНОВНАЯ ФУНКЦИЯ: задание во многом повторяет задание 2 ДЗ-4, добавлены
    лишь функции insert и erase. */
int main(void) {
    printf("Зверев Дмитрий, 210 группа, задание 2 ДЗ-5\n");
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

    // выводим исходный список
    if(L1 != NULL) {
        struct list* p = L1;                 // указатель для прохода по списку
        printf("Исходный список:\n");
        while(p->next != NULL) {
            printf("%s ", p->c);
            p = p->next;
        }
        printf("%s\n", p->c);                // выдача последнего эл-та

        // добавляем слово в список перед позицией p и выдаем новый список
        printf("Введите слово, которое нужно добавить: ");
        word = read_word(&check);
        int number;
        printf("Введите номер позиции, перед которой вставить слово: ");
        scanf("%d", &number);
        L1 = insert(L1, word, number);
        p = L1;                              // указатель для прохода по списку
        printf("Список после добавления слова:\n");
        while(p->next != NULL) {
            printf("%s ", p->c);
            p = p->next;
        }
        printf("%s\n", p->c);               // выдача последнего эл-та

        // удаляем слово из списка с позицией p и выдаем новый список
        printf("Введите номер позиции слова для удаления: ");
        scanf("%d", &number);
        L1 = erase(L1, number);
        p = L1;                             // указатель для прохода по списку
        printf("Список после удаления:\n");
        while(p->next != NULL) {
            printf("%s ", p->c);
            p = p->next;
        }
        printf("%s\n", p->c);               // выдача последнего эл-та

        // очистка памяти
        deleteList(L1);
        printf("\n");
    } else
        printf("Задан пустой список!");
    return 0;
}