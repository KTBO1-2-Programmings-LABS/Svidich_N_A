#include <string.h>
#include <cstdio>
#pragma warning(disable:4996)

#define MAX_SIZE 256
#define INPUT_FN "..\\input.txt"
#define OUTPUT_FN "..\\output.txt"

// Стек и id последнего элемента
char stack[MAX_SIZE];
int peek = 0;

// Добавить элемент в стек
void push(const char с)
{
    if (peek >= MAX_SIZE)
        printf("Stack overflow\n");
    else
    {
        stack[peek] = с;
        peek++;
    }
}

// Удалить элемент из стека
char pop()
{
    if (peek == 0)
    {
        return -1;
    }
    peek--;
    return stack[peek];

}

// Значение приоритета операции
int operation(char c)
{
    switch (c)
    {
    case '(':
        return 0;
    case ')':
        return 1;
    case '+': case '|': case '-':
        return 2;
    case '*': case '&': case '/': case '^':
        return 3;
    default:
        return -1;
    }
}


int main() {

    FILE* input = fopen(INPUT_FN, "r");
    FILE* output = fopen(OUTPUT_FN, "w");

    if (input == NULL || output == NULL) {
            printf("Files error\n");
            return -1;
        }

    char line[MAX_SIZE], result[MAX_SIZE];
    int id = 0;       
   
    while (fgets(line, MAX_SIZE, input) != NULL) {

        // Перебор строки-выражения по символам
        for (int i = 0; i < strlen(line); ++i)
        {
            // Если знак - операнд, перебираем строку в поиске более приоритетных значений операндов. Если цифра - запись в буфер
            if (line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/' || line[i] == '|' || line[i] == '&')
            {
                
                while (peek != 0 && stack[peek - 1] >= operation(line[i]))
                {
                    result[id++] = pop();
                }
                push(line[i]);

            }
            else if (line[i] == '(')
            {
                push(line[i]);
            }
            else if (line[i] == ')')
            {
                // Пока не дойдём до скобки, добавляем символы в стек
                while (peek != 0 && stack[peek - 1] != '(')
                {
                    result[id++] = pop();
                }
                pop();
            }
            else if (line[i] != '\n' && line[i] != ' ')
            {
                result[id++] = line[i];

            }
        }

        result[id++] = '\0';

        printf("%s\n", result);
        fputs(result, output);

    }

    fclose(input);
    fclose(output);

    printf("\nDone\n");

    return 0;
}