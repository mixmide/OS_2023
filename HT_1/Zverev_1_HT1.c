#include <stdio.h>

int main(void) {
    printf("Зверев Дмитрий, 210 группа, ДЗ-1, задание 1\n");
    
    printf("Введите число eps (эпсилон): ");
    double eps;
    scanf("%lf", &eps);
    
    double x = 0;
    double Xn = 1;
    double Xn_old;
    printf("Введите число: ");
    while (scanf("%lf", &x) != EOF) {
        // используем метод касательных (Ньютона)
        Xn = 1;
        do {
            Xn_old = Xn;
	        Xn = (Xn_old + x / Xn_old) / 2;
        } while (((Xn_old - Xn) >= eps) || (((Xn_old - Xn) <= -eps)));
        printf("Ответ в 4х форматах:\n");
        printf("%f\n", Xn);
        printf("%g\n", Xn);
        printf("%e\n", Xn);
        printf("%.10g\n", Xn);
        printf("Введите число (или признак конца файла): ");
    }
    
    return 0;
}
