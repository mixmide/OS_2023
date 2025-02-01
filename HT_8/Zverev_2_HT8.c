#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

// функция для определения причины завершения
int why_end(int stat) {
    if(WIFEXITED(stat))
        printf("Процесс завершился успешно!\n");
    else
        printf("Сработал сигнал остановки: %d\n", WTERMSIG(stat));
    return 0;
}

// ОСНОВНАЯ ФУНКЦИЯ
int main(int argc, char **argv) {
    int err;    // для аргумента wait()
    pid_t pid;
    pid_t pid2;
    // случай "параллельно"
    if(strcmp(argv[5], "p") == 0) {
        if((pid = fork()) > 0) {              // процесс-отец
            if((pid2 = fork()) > 0) {         // процесс-отец-отец
                // ждем завершения 1-го или 2-го
                pid_t pid_new = wait(&err);
                if (pid_new == pid)
                    printf("Процесс 1 завершился с кодом: %d\t", err);
                else
                    printf("Процесс 2 завершился с кодом: %d\t", err);
                why_end(err);
                // ждем завершения последнего (аналогично)
                pid_new = wait(&err);
                if (pid_new == pid)
                    printf("Процесс 1 завершился с кодом: %d\t", err);
                else
                    printf("Процесс 2 завершился с кодом: %d\t", err);
                why_end(err);
            }
            else if(pid2 == 0) {              // процесс-отец-сын
                if(execl(argv[3], argv[3], argv[4], NULL) < 0) {
                    printf("Процесс был остановлен!\n");
                    abort();
                }
            }
            else
                exit(-1);
        }
        else if(pid == 0) {                   // процесс-сын
            if(execl(argv[1], argv[1], argv[2], NULL) < 0) {
                printf("Процесс был остановлен!\n");
                abort();
            }
        }
        else
            exit(-1);
    }
    // случай "последовательно"
    else if(strcmp(argv[5], "s") == 0) {
        if((pid = fork()) < 0)
            exit(-1);
        else if(pid == 0) {                 // процесс-сын
            if(execl(argv[1], argv[1], argv[2], NULL) < 0) {
                printf("Процесс был остановлен!\n");
                abort();
            }
        }
        else {                              // процесс-отец
            wait(&err);
            printf("Процесс 1 завершился с кодом: %d\t", err);
            why_end(err);
            if ((pid2 = fork()) < 0)
                exit(-1);
            else if (pid2 == 0) {           // процесс-отец-сын
                if(execl(argv[3], argv[3], argv[4], NULL) < 0) {
                    printf("Процесс был остановлен!\n");
                    abort();
                }
            }
            else {                          // процесс-отец-отец
                wait(&err);
                printf("Процесс 2 завершился с кодом: %d\t", err);
                why_end(err);
            }
        }
    }
    else
        printf("Введены неверные данные!");
    return 0;
}