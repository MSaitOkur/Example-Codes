/*
 * Dice Game
 * Player uses two dices.
 * Sum of dices are:
 *  7,11    --> win
 *  2,3,12  --> lose
 *  4,5,6,7,8,9,10 --> Throw dices again.
 *      if new sum == last sum --> win
 *      if new sum == 7 --> lose
 *      of new sum other than last sum and 7 --> throw again
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define randomize() srand((unsigned int)time(NULL))

void clear_input_buffer(void)
{
    int ch;
    while ((ch = getchar()) != EOF && ch != '\n')
        ;
}

int main()
{
    randomize();

    while (1)
    {
        fprintf(stdout, "Do you want to play (y)(n): ");
        int c = getchar();

        if (c == 'n' || c == 'N')
            break;
        else if (c == 'y' || c == 'Y')
        {
            system("clear");
            clear_input_buffer();
        }
        else
        {
            clear_input_buffer();

            while (1)
            {
                fprintf(stdout, "Wrong input! Do you want to play (y)(n): ");
                c = getchar();
                if (c == 'y' || c == 'Y' || c == 'n' || c == 'N')
                {
                    clear_input_buffer();
                    break;
                }
                else
                    clear_input_buffer();
            }

            if (c == 'n' || c == 'N')
                break;

            system("clear");
        }

        int dice1 = rand() % 6 + 1, dice2 = rand() % 6 + 1;
        int first_sum = dice1 + dice2;

        if (first_sum == 7 || first_sum == 11)
            fprintf(stdout, "Sum: [%d], Win!\n", first_sum);
        else if (first_sum == 2 || first_sum == 3 || first_sum == 12)
            fprintf(stdout, "Sum: [%d], Lose!\n", first_sum);
        else
        {
            fprintf(stdout, "Sum: [%d], Again!\n", first_sum);
            for (;;)
            {
                dice1 = rand() % 6 + 1;
                dice2 = rand() % 6 + 1;
                int new_sum = dice1 + dice2;

                if (new_sum == 7)
                {
                    fprintf(stdout, "Sum: [%d], Lose!\n", new_sum);
                    break;
                }
                else if (new_sum == first_sum)
                {
                    fprintf(stdout, "Sum: [%d], Win!\n", new_sum);
                    break;
                }
                else
                    fprintf(stdout, "Sum: [%d], Again\n", new_sum);
            }
        }
    }
}