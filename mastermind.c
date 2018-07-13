/*
* TDQC5
* Bruce Cain
*
* Write a program the lets the user play Mastermind.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 4

void genRandNum(int const MINNUM, int const MAXNUM, char *rNum);
void checkChoice(char *usrInput, char const *rNum, int *guesses, int *win);

int main(void)
{
    char randNum[MAX] = "0000", usrInput[MAX];
    int guesses = 0, winner = 0;

    genRandNum(1, 9, randNum);
    printf("random %s\n", randNum);

    while(!winner)
    {
        printf("Guess a number: ");
        fgets(usrInput, MAX+2, stdin);
        checkChoice(usrInput, randNum, &guesses, &winner);
    }

    return 0;
}

void checkChoice(char *usrInput, char const *rNum, int *guesses, int *win)
{
    /*Validate user input*/
    
    int white = 0, red = 0;
    
    (*guesses)++;

    /*Count red matches*/
    for (int i = 0; i < MAX; i++)
    {
        if (usrInput[i] == rNum[i])
        {
            red++;
        }
    }

    /*Count white matches*/
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if (usrInput[i] == rNum[j])
            {
                white++;
            }
        }
    }

    if (red && (white - red))
    {
        printf("%d red, %d white\n", red, (white - red));
    }
    else if (red)
    {
        printf("%d red\n", red);
    }
    else if (white - red)
    {
        printf("%d white\n", (white - red));
    }

    if (4 == red)
    {
        printf("Winner, took %d guess(es).\n", *guesses);
        *win = 1;
    }
}

void genRandNum(int const MINNUM, int const MAXNUM, char *rNum)
{
    /*Generate a random 4 digit number 1111 - 9999*/

    int randN, num[MAX], totalNum = 0;
    srand(time(NULL));

    while (totalNum < MAX)
    {
        randN = (rand() % (MAXNUM - MINNUM)) + MINNUM;
        num[totalNum] = randN;
        totalNum++;

        for (int i = 0; i < totalNum - 1; i++)
        {
            if (randN == num[i])
            {
                totalNum--;
                break;
            }
        }
    }
    
    sprintf(rNum, "%d%d%d%d", num[0], num[1], num[2], num[3]);
}
