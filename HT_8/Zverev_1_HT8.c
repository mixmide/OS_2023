#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

// требуемая функция
void function(char* name) {
    DIR* D = opendir(name); // открытие директории
    struct dirent *s;       // здесь считываемый файл
    struct stat stat;       // здесь инф-я о файле
    char* buf;              // здесь будем хранить имя файла
    while((s = readdir(D))) {
        // для начала получаем имя файла
        buf = calloc(strlen(name) + strlen(s->d_name) + 2, 1);
        strcpy(buf, name);
        buf[strlen(name)] = '/';
        strcpy(buf + strlen(name) + 1, s->d_name);
        lstat(buf, &stat);
        // переходим к чтению и печатанием его название
        if(S_ISREG(stat.st_mode) && (stat.st_mode & 72)) // обычный файл и права доступа ??1??1???
            printf("%s\n", s->d_name);
        else if(S_ISDIR(stat.st_mode) && (strcmp(s->d_name, "..") != 0) && (strcmp(s->d_name, ".") != 0)) { // каталог
            printf("%s\n", s->d_name);
            function(buf);  // переходим к рекурсии
        } else if(S_ISLNK(stat.st_mode)) {   // символьная ссылка?
            printf("%s\t", s->d_name);
            char* buf1 = calloc(100, 1);
            if (readlink(buf, buf1, 30) < 1) {
                free(buf);
                free(buf1);
                exit(-1);
            }
            printf("\tССЫЛОЧНЫЙ ФАЙЛ:%s\n", buf1);
            free(buf1);  
        }
        free(buf);
    }
    closedir(D);    // закрытие директории
}

// основная функции программы
int main(int argc, char **argv) {
    function(".");
    return 0;
}