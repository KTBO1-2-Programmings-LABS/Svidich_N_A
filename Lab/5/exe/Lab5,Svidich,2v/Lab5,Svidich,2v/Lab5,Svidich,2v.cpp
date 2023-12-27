#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

#pragma warning(disable : 4996)
#define n 1000 // Константа n, для определния длины массивов

// Функция генерирования случайных чисел, запись их в массивы
void generator(int* m, int* bbl, int* shl, int* mrg) {
    for (int i = 0; i < n; i++) {
        m[i] = rand();
    }

}

// Функция вывода массива в файл
void output(int* m) {
    FILE* output = fopen("..\\input.txt", "w");

    if (output == NULL) perror("Opening file error");
    else
    {
        puts("\nRecording...");
        for (int i = 0; i < n; i++) {
            fprintf(output, "%i ", m[i]);
        }

        puts("Done\n");
    }

    fclose(output);
}

// Функция заполнения массива из данных файла
void input(int* m) {
    FILE* output = fopen("..\\input.txt", "r");

    if (output == NULL) perror("Opening file error");
    else
    {
        puts("\nReading...");

        for (int i = 0; i < n; i++) {
            fscanf(output, "%i", &m[i]);
        }

        puts("Done\n");
    }

    fclose(output);
}

// Функция вывода массива в консоль
void print(int* m) {
    for (int i = 0; i < n; i++)
        printf("%i ", m[i]);
    printf("\n");
}

// Функция вывода массивов в файл
void result(int* m, int* bbl, int* shl, int* mrg) {
    FILE* output = fopen("..\\input.txt", "w");

    if (output == NULL) perror("Opening file error");
    else
    {
        puts("\nRecording...");
        fputs("Array: \n", output);
        for (int i = 0; i < n; i++) {
            fprintf(output, "%i ", m[i]);
        }
        fputs("\nResult: \n", output);
        fputs("m[] bbl[] shl[] mrg[]\n", output);
        for (int i = 0; i < n; i++) {
            fprintf(output, "%i ", m[i]);
            fprintf(output, "%i ", bbl[i]);
            fprintf(output, "%i ", shl[i]);
            fprintf(output, "%i \n", mrg[i]);
        }

        puts("Done\n");
    }

    fclose(output);
}

// Функция сортировки пузырьком
// Сложность О (n2)
void bubble_sort(int* m) {
    int k; // Вспомогательная переменная для хранения промежуточного значения
    puts("\nBubble sorting: \n");
    // Цикл прохождения по каждому элементу массива
    for (int i = 0; i < n - 1; i++) {
        // Цикл сравнения элементов
        for (int j = n - 2; j >= i; j--) {
            // Если элемент больше следующего, вспомогательная переменная получает его значение,
            //  следующий элемент становится на его место
            // следующий индекс заполняется значением из буфера
            if (m[j] > m[j + 1]) {
                k = m[j];
                m[j] = m[j + 1];
                m[j + 1] = k;
            }
        }
    }
    print(m);
}

// Функция сортировки Шела
// Сложность O(1)
void Shel_sort(int* m) {
    puts("\nShel sorting: \n");

    int i, j, step, tmp;
    for (step = n / 2; step > 0; step /= 2) // Определение шага сортировки
        for (i = step; i < n; i++)
        {
            tmp = m[i];
            for (j = i; j >= step; j -= step)
            {
                if (tmp < m[j - step])
                    m[j] = m[j - step];
                else
                    break;
            }
            m[j] = tmp;
        }
    print(m);
}

// Функция сортировки слиянием
// Сложность O(n log2 n)
void Merge_sort(int* m) {
    puts("\nMerge sorting: \n");
    //
    int step = 1;  // Шаг разбиения последовательности
    int* temp = (int*)malloc(n * sizeof(int)); // Дополнительный массив
    while (step < n)  // Пока шаг меньше длины массива
    {
        int index = 0;    // Индекс результирующего массива
        int l = 0;      // Левая граница участка
        int h = l + step;  // Середина участка
        int r = l + step * 2;  // Правая граница участка
        do
        {
            h = h < n ? h : n;  // Сортируемый участок не выходит за границы последовательности
            r = r < n ? r : n;
            int i1 = l, i2 = h; // Индексы сравниваемых элементов
            for (; i1 < h && i2 < r; ) // Пока i1 не дошёл до середины и i2 не дошёл до конца
            {
                if (m[i1] < m[i2]) { temp[index++] = m[i1++]; } // Заполняем участок результирующей последовательности
                else { temp[index++] = m[i2++]; }
            }
            // Или i1 < m или i2 < r - только один из операторов while может выполниться
            while (i1 < h) temp[index++] = m[i1++]; // Заносим оставшиеся элементы сортируемых участков
            while (i2 < r) temp[index++] = m[i2++]; // В результирующий массив
            l += step * 2; // Перемещаемся на следующий сортируемый участок
            h += step * 2;
            r += step * 2;
        } while (l < n); // Пока левая граница сортируемого участка - в пределах последовательности
        for (int i = 0; i < n; i++) // Переносим сформированный массив обратно в a
            m[i] = temp[i];
        step *= 2; // Увеличиваем в 2 раза шаг разбиения
    }
    //
    print(m);
}


int main()
{

    int m[n], bbl[n], shl[n], mrg[n];
    // Генерация
    generator(m, bbl, shl, mrg);
    // Вывод в консоль исходного массива
    print(m);
    output(m);
    // Заполнение массивов для сортировки из файла
    input(bbl);
    input(shl);
    input(mrg);

    time_t start = time(NULL);
    bubble_sort(bbl); // Сортировка пузырьком
    printf("\nRunning bubble_sort time: %f\n", time(NULL) - start);

    start = time(NULL);
    Shel_sort(shl); // Сортировка Шелла
    printf("\nRunning Shel_sort time: %f\n", time(NULL) - start);

    start = time(NULL);
    Merge_sort(mrg); // Сортировка слиянием
    printf("\nRunning Merge_sort time: %f\n", time(NULL) - start);
  

    result(m, bbl, shl, mrg); // Вывод полученных массивов в файл

    return 0;
}
