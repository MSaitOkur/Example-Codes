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

int rolldice()
{
    return (rand() % 6 + 1) + (rand() % 6 + 1);
}

int new_rules(int first_dice_sum)
{
    for (;;)
    {
        int new_dices = rolldice();

        if (new_dices == first_dice_sum)
            return 1;
        else if (new_dices == 7)
            return 0;
    }

    return 0;
}

int game(void)
{
    int dice_sum = rolldice();

    switch (dice_sum)
    {
    case 7:
    case 11:
        return 1;
    case 2:
    case 3:
    case 12:
        return 0;
    default:
        return new_rules(dice_sum);
    }

    return 0;
}

int main()
{
    randomize();

    size_t win_cnt = 0;
    size_t num_of_games = rand() % 1000000 + 1;
    for (size_t i = 0; i < num_of_games; ++i)
        win_cnt += game();

    fprintf(stdout, "win number of %zu games: %zu\n",
            (size_t)num_of_games, win_cnt);
    fprintf(stdout, "percentage of winning chance %.4f%%\n", (double)win_cnt / num_of_games);
}