#include <stdio.h>

int main(void) {
    printf("Зверев Дмитрий, 210 группа, задание 1 ДЗ-2\n");
    int m, n;
    printf("Введите размер матрицы: ");
    scanf("%d", &m);
    scanf("%d", &n);
    int x[m][n];

    int i, k, a1, a2, a3;
    k = 1; //k - вписываемый в эл-т матрицы символ
    a1 = 0; /* инициализация эл-та для (по порядку): старта просмотра 
    верхней строки, для начала просмотра правого столбца,  
    для обозначения конца нижней строки с учетом хода справа налево,  
    для обозначения последнего нерассмотренного эл-та левого столбца  
    с учетом хода снизу вверх */
    a2 = n - 1; /* инициализация эл-та для (по порядку): обозначения конца 
    верхней строки, для обозначения правого столбца, для обозначения  
    правого столбца, который еще не рассмотрен(т.е. который находится 
    неподсредственно левее рассмотренного правого столбца) */
    a3 = m - 1; /* инициализация эл-та для (по порядку): обозначения нижней 
    строки (во 2-м и 3-м циклах for), для обозначения начала просмотра  
    левого столбца, причем на 1 строку выше */ 
    /* ИДЕЯ: заполняем эл-ты матрицы, двигаясь по спирали по часовой  
    стрелке (рассматриваем верхнюю строку, правый столбец, нижнюю 
    строку, левый столбец и так далее) */
    while (k <= (n * m)) { 
        //рассматриваем верхнюю стр.
        for (int i = a1; i <= a2; i++) {
            x[a1][i] = k;
            k++;
        }
        //рассматриваем правый стб.
        if (k <= (n * m)) {
            for (int i = a1 + 1; i <= a3; i++) {
                x[i][a2] = k;
                k++;
            }
        } 
        //рассматриваем нижнюю стр.
        if (k <= (n * m)) {
            for (int i = (a2 - 1); i >= a1; i--) {
                x[a3][i] = k;
                k++;
            }
        } 
        //рассматриваем левый стб.
        if (k <= (n * m)) {
            for (int i = (a3 - 1); i >= (a1 + 1); i--) {
                x[i][a1] = k;
                k++;
            }
        } 
        /* обновляем эл-ты a1, a2, a3 для рассмотрения нового, более 
        "маленького" круга эл-тов матрицы */ 
        a1++; 
        a2--; 
        a3--;
    }
    
    printf("Получившаяся матрица:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("\t%d", x[i][j]);
        }
        printf("\n");
    }
    return 0;
}
