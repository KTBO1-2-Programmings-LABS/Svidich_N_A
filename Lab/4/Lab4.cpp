#include <iostream>
#include <stdio.h>

// Функция для выборки необходимых слов из одного файла и записи их в другой с объявлением передаваемых параметров
void transfers(FILE* out, FILE* in) {
    // Объявление вспомогательных переменных: массив для чтения строк из файла и указатель на строки
    char arr[256];
    char* p;
    // Проверка на корректность открытия файла
    if (out == NULL) perror("Ошибка открытия файла");
    else
    {
        printf("Reading file...\n");
        // Цикл, инициализирующий начало чтение файла до его конца
        while (!feof(out))
        {
            // Цикл получения и обработки строк 
            while ( (p = fgets(arr, 256, out)) != NULL) {
                // Цикл перебора символов в строке
                for (p; (*p) != '\0'; (p++)) {
                    // Проверка слова на начальную гласную букву
                    if (
                        ((*p) == 'a' || (*p) == 'e' || (*p) == 'i' || (*p) == 'o' || (*p) == 'u' || (*p) == 'y' ||
                            (*p) == 'A' || (*p) == 'E' || (*p) == 'I' || (*p) == 'O' || (*p) == 'U' || (*p) == 'Y')
                        && ( (*(p - 1)) == ' ' )
                        ) {
                        printf("\nWord was founded! Its: ");
                        // Цикл для вывода слова, начинающегося на гласную
                        for (int j = 0; (*(p + j)) != ' '; j++) {
                            printf("%c", *(p + j));
                            fputc(*(p + j), in);
                            // Разделение слов при выводе
                            if (*(p + j + 1) == ' ') {
                                fputc(' ', in);
                            }
                            // Прекращение цикла вывода слова, если был выведен последний символ последнего слова
                            if (*(p + j + 1) == '\0') {
                                printf("\n");
                                break;
                            }
                        }

                    }

                }

            }
        }
    }

}

int main()
{
    // Объявление переменных для хранения адресов файлов
    char address_out[256] = "..\\out.txt"; 
    char address_in[256] = "..\\in.txt";

    char ok;
    // Условная проверка на правильность адреса хранения файлов
    printf("Directory of files is ..\\Lab4Var2,Svidich,Ktbo1-2 . Right? Enter Y or N: ");
    scanf("%c", &ok);

    if (ok == 'n' || ok == 'N') {

        /*printf("Enter address of file with a text :");
        gets(address_out);
        printf("\nThe address where you need to enter the words: ");
        gets(address_in);*/
       
    }
    printf(address_out);
    printf(address_in);

    // Объявление переменных-указателей на файлы
    FILE* out = fopen(address_out, "r");
    FILE* in = fopen(address_in, "w");
    // Использование функции с параметрами, передающими ссылки на файлы
    transfers(out, in);
    // Программное закрытие используемых файлов для освобождения памяти
    fclose(out);
    fclose(in);

    printf("\nDone! You can check files.\n");

    return 0;
}