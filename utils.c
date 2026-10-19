#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

/* keeps asking until the user types a whole number between min and max */
int getInt(const char *prompt, int min, int max)
{
    char line[100];
    int num;
    char leftover;

    while (1)
    {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            exit(0);
        }

        if (sscanf(line, "%d %c", &num, &leftover) == 1)
        {
            if (num >= min && num <= max)
            {
                return num;
            }
        }
        printf("Invalid. Enter a whole number from %d to %d.\n", min, max);
    }
}

/* same idea but for decimal numbers, the number must be min or more */
double getDouble(const char *prompt, double min)
{
    char line[100];
    double num;
    char leftover;

    while (1)
    {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            exit(0);
        }

        if (sscanf(line, "%lf %c", &num, &leftover) == 1)
        {
            if (num >= min)
            {
                return num;
            }
        }
        printf("Invalid. Enter a number that is %.2f or more.\n", min);
    }
}

/* asks for text and does not accept empty input or only spaces */
void getString(const char *prompt, char *dest, int size)
{
    char line[100];
    int i;
    int found;
    int len;

    while (1)
    {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL)
        {
            exit(0);
        }

        /* fgets keeps the newline so remove it */
        line[strcspn(line, "\n")] = '\0';

        len = strlen(line);

        /* look for at least one character that is not a space */
        found = 0;
        for (i = 0; i < len; i++)
        {
            if (line[i] != ' ')
            {
                found = 1;
            }
        }

        if (found == 0)
        {
            printf("This cannot be empty.\n");
        }
        else if (len >= size)
        {
            printf("Too long, maximum is %d characters.\n", size - 1);
        }
        else
        {
            strcpy(dest, line);
            return;
        }
    }
}
