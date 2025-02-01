#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 4

/* Функция поиска подстроки в строке */
char *str_find(char *str, char *substr) {
    // отсекаем дефолтные случаи
    if ((str[0] == '\0') || (substr[0] == '\0'))
        return NULL;
    // подсчитываем длины строки и подстроки
    int i = 0;
    while (str[i] != '\0')
        i++;
    int len_str = i;
    i = 0;
    while (substr[i] != '\0')
        i++;
    int len_substr = i;
    char *ptr = NULL;                       // будет хранить результат
    i = 0;
    int j = 0;
    // анализируем пока не достигнем конца строки либо длина подстроки превысит длину строки
    while ((i < len_str) && (len_str >= len_substr + i)) {
        j = 0;
        // сравниваем строку, начиная с элемента i, и подстроку
        while((j < len_substr) && (str[i+j] == substr[j]))
            j++;
        if(j == len_substr) {                // подстрока найдена!
            ptr = &str[i];
            return ptr;
        }
        i++;
    }
    return NULL;
}

// Функция чтения строк (использовалась в заданиях ранее)
char *read_string() {
    int i = 0;
    int c;
    char *p_str = NULL;
    printf("Напечатайте строку: \n");
    while (((c = fgetc(stdin)) != '\n') && (c != EOF)) {
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
    return p_str;
}

// ОСНОВНАЯ ФУНКЦИЯ
int main(void) {
    printf("Зверев Дмитрий, 210 группа, задание 1 ДЗ-3\n");
    char* str1 = read_string();
    char* str2 = read_string();
    char* res = str_find(str1, str2);
    printf("ОТВЕТ:\n");
    if (res == NULL)
        printf("Вхождений нет либо какая-то строка пуста!\n");
    else {
        while (res != NULL) {
            printf("%s\n", res);
            res = str_find(res + strlen(str2), str2);
        }
    }
    
    free(str1);
    free(str2);
    return 0;
}