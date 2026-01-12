#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int computer_score(string word);

int main(void)
{

    string word1 = get_string("Player 1: \n");
    string word2 = get_string("Player 2: \n");

    int score1 = computer_score(word1);
    int score2 = computer_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int computer_score(string word)
{
    int position;
    int score = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        if ((int) toupper(word[i]) >= 65 && (int) toupper(word[i]) <= 90)
        {
            position = (int) toupper(word[i]) - 65;
            score += POINTS[position];
        }
    }

    return score;
}
