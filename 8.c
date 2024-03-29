#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

// Функция для определения положительности, отрицательности или нуля
int bolishe_menchi(int );
int bolishe_menchi(int number) {
    if (number > 0) {
        return 0;  // Положительное число
    } else if (number < 0) {
        return 1;  // Отрицательное число
    } else {
        return 2;  // Ноль
    }
}

// Функция для возведения в квадрат отрицательных чисел в массиве
int cvadrat(int[], int);
int cvadrat(int array[], int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] < 0) {
            array[i] = (int)pow(array[i], 2);  // Преобразование результата к целому типу
        }
    }
}

// Функция для подсчета чисел в матрице, близких к среднему арифметическому каждой строки
int blizkii_chisla(int[1000][1000],int,int);
int blizkii_chisla(int matrix[1000][1000], int rows, int cols) {
    double porog = 1;  // Порог близких чисел
    int chet;
    int totalChet = 0;
    for (int i = 0; i < rows; i++) {
        chet = 0;
        double colSum = 0;
        // Суммируем элементы столбца
        for (int j = 0; j < cols; j++) {
            colSum += matrix[i][j];
        }
        // Среднее арифметическое
        double cred = colSum / cols;
        // fabs возвращает модуль, игнорируя минусы, подсчет чисел близких к среднему арифметическому
        for (int j = 0; j < cols; j++) {
            if (fabs(matrix[i][j] - cred) < porog) {
                chet++;
            }
        }
        totalChet += chet;
    }
    return totalChet;
}

// Функция для создания второго массива с элементами, удовлетворяющими критерию
int* dinamick_massiv(int[1000],int,int,int*);
int* dinamick_massiv(int mainarray[1000], int size, int n, int* resultSize) {
    int j = 0;

    // Создание динамического массива
    int* dinamickarray;
    dinamickarray = (int*)malloc(size * sizeof(int));

    // Отбор чисел по критерию из главного массива в динамический
    for (int i = 0; i < size; i++) {
        if (mainarray[i] > n) {
            dinamickarray[j] = mainarray[i];
            ++j;
        }
    }
    // Устанавливаем размер результата
    *resultSize = j;

    return dinamickarray;
}


int plus(float,float);
int plus(float a,float b){
    return a+b;
}

int minus(float,float);
int minus(float a,float b){
    return a-b;
}

int ymnog(float,float);
int ymnog(float a,float b){
    return a*b;
}

int deli(float,float);
int deli(float a,float b){
    return a/b;
}

// Главная функция
int main() {
    int (*bolishe_menchiC)(int) = bolishe_menchi;
    int (*cvadratC)(int[], int) = cvadrat;
    int (*blizkii_chislaC)(int[1000][1000],int,int) = blizkii_chisla;
    int* (*dinamick_massivC)(int[1000],int,int,int*) = dinamick_massiv;
    int (*kalkylator[4])(float,float) = {plus,minus,ymnog,deli};
    while (true) {
        // Меню выбора функции
        printf("Введите номер функции 1, 2 (для массива), 0 (для выхода): ");
        int b;
        scanf("%d", &b);

        // Обработка выбора
        if (b == 0) {
            printf("Программа завершена.\n");
            break;
        } else if (b == 1) {
            // Проверка положительности, отрицательности или нуля введенного числа
            int c;
            printf("Введите число для проверки на положительность или отрицательность: ");
            scanf("%d", &c);

            if (c != 1) {
                while (getchar() != '\n');
                continue;
            }

            int result = bolishe_menchiC(c);
            if (result == 0) {
                printf("Число %d является положительным.\n", c);
            } else if (result == 1) {
                printf("Число %d является отрицательным.\n", c);
            } else if (result == 2) {
                printf("Число %d является нулем.\n", c);
            }

        } else if (b == 2) {
            // Изменение массива, вывод измененного массива
            int c;
            printf("Введите размер массива: ");
            int chet;
            scanf("%d", &chet);
            int mainarray[1000];

            printf("Введите значения массива: ");
            for (int i = 0; i < chet; i++) {
                scanf("%d", &mainarray[i]);
                if (mainarray[i] != 1) {
                    while (getchar() != '\n');
                    continue;
                }
            }

            cvadratC(mainarray, chet);
            printf("Измененный массив:\n");
            for (int i = 0; i < chet; i++) {
                printf("Элемент %d: %d\n", i, mainarray[i]);
            }
        } else if (b == 3) {
            // Подсчет чисел в матрице, близких к среднему арифметическому
            int rows, cols;
            printf("Введите количество строк: ");
            scanf("%d", &rows);
            printf("Введите количество столбцов: ");
            scanf("%d", &cols);
            // Создание матрицы
            int matrix[rows][cols];
            printf("Введите элементы матрицы:\n");
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    scanf("%d", &matrix[i][j]);
                    if (matrix[i][j] != 1) {
                        while (getchar() != '\n');
                        continue;
                    }
                }
            }
            int result = blizkii_chislaC(matrix, rows, cols);
            printf("Общее количество чисел близких к среднему арифметическому в матрице: %d\n", result);

        } else if (b == 4) {
            // Создание второго массива, удовлетворяющего критерию
            int size;
            printf("Введите размер массива: ");
            scanf("%d", &size);
            int mainarray[size];
            printf("Заполните массив:\n");

            // Заполнение главного массива
            for (int i = 0; i < size; i++) {
                scanf("%d", &mainarray[i]);
            }

            int resultSize;
            // Вводим критерии
            printf("Введите критерии заполнения второго массива: ");
            int n;
            scanf("%d", &n);
            // Вызываем функцию для создания второго массива
            int* result = dinamick_massivC(mainarray, size, n, &resultSize);

            // Выводим результат в main
            printf("Второй массив с элементами, удовлетворяющими критерию:\n");
            for (int i = 0; i < resultSize; i++) {
                printf("%d ", result[i]);
            }

            // Освобождаем память
            free(result);
        } else if (b==5){
            float a;
            float b;
            int c;
            printf("Введите первое число");
            scanf("%f",&a);
             printf("Введите второе число");
            scanf("%f",&b);
            printf("Выберите действие если 1 прибавь,2 вычесть, 3 умнож, 4 дели");
            scanf("%d",&c);
            float resultt;
            if (c >= 1 && c <= 4) {
                resultt = kalkylator[c - 1](a, b);

                printf("Ваш ответ: %f\n", resultt);
            } else {
                printf("Некорректный выбор действия.\n");
            }


        }
        
    }

    return 0;
}