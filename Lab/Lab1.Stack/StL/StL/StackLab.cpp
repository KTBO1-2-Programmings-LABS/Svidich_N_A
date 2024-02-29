#include <cstdio>
#include <string.h>
#pragma warning(disable:4996)

#define MAX_SIZE 256
#define INPUT_FN "..\\input.txt"
#define OUTPUT_FN "..\\output.txt"

// Ñòåê è id ïîñëåäíåãî ýëåìåíòà
char stack[MAX_SIZE];
int peek = 0;

// Äîáàâèòü ýëåìåíò â ñòåê
void push(const char c)
{
    if (peek >= MAX_SIZE) printf("Stack overflow\n");
    else
    {
        stack[peek] = c;
        peek++;
    }
}

// Óäàëèòü ýëåìåíò èç ñòåêà
char pop()
{
    if (peek == 0)
    {
        return -1;
    }
    peek--;
    return stack[peek];

}

// Çíà÷åíèå ïðèîðèòåòà îïåðàöèè
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
    unsigned int id = 0;       
   
    while (fgets(line, MAX_SIZE, input) != NULL) {

        // Ïåðåáîð ñòðîêè-âûðàæåíèÿ ïî ñèìâîëàì
        for (int i = 0; i < strlen(line); ++i)
        {
            // Åñëè çíàê - îïåðàíä, ïåðåáèðàåì ñòðîêó â ïîèñêå áîëåå ïðèîðèòåòíûõ çíà÷åíèé îïåðàíäîâ. Åñëè öèôðà - çàïèñü â áóôåð
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
                // Ïîêà íå äîéä¸ì äî ñêîáêè, äîáàâëÿåì ñèìâîëû â ñòåê
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
