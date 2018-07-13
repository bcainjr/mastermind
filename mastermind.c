/*
* TDQC5
* Bruce Cain
*
* Write a program the lets the user play Mastermind.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define MAX 4
#define INPUTSZ 100

/*Check user's input*/
void usrInValidation(char *usrInput, int *val);
/*Flush out excess stdin buffer*/
void clean_stdin(void);
/*Compare user's input to answer*/
void checkChoice(char *usrInput, char const *rNum, int *guesses, int *win);
/*Generate randum number*/
void genRandNum(int const MAXNUM, char *rNum);

int main(void)
{
    char randNum[MAX] = "0000", usrInput[INPUTSZ];
    int guesses = 0, winner = 0, valid;

    genRandNum(10, randNum);
    printf("random %s\n", randNum);

    while(!winner)
    {
        printf("Guess a number: ");
        usrInValidation(usrInput, &valid);

        switch(valid)
        {
            case 0:
            {
                checkChoice(usrInput, randNum, &guesses, &winner);
                break;
            }
            case 1:
            {
                printf("Too many digits or non digit found.\n");
                break;
            }
            case 2:
            {
                printf("Too few digits or non digit found.\n");
                break;
            }
            default:
            {
                printf("Not valid input. Try again.\n");
            }
        }
    }

    return 0;
}

void usrInValidation(char *usrInput, int *val)
{
    /*Check user input*/

    int s = 0;
    char c = 0;

    *val = 0;

    while ((c = getchar()) != '\n')
    {
        if (isdigit(c))
        {
            usrInput[s++] = c;
        }
        
        if (6 < s || isalpha(c))
        {
            /* Too many digits and must flush out buffer
            * to prevent unwanted output.
            */
            clean_stdin();
            break;
        }
    }

    if (4 < s)
    {
        *val = 1;
    }
    else if (4 > s)
    {
        *val = 2;
    }
    else if (4 == s)
    {
        for (int i = 0; i < MAX; i++)
        {
            for (int j = i + 1; j < MAX; j++)
            {
                if (usrInput[i] == usrInput[j])
                {
                    *val = 3;
                    break;
                }
            }

            if (0 != *val)
            {
                break;
            }
        }
    }
}

void clean_stdin(void)
{
    /*Flush out buffer*/

    int c = getchar();
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void checkChoice(char *usrInput, char const *rNum, int *guesses, int *win)
{
    /*Determine how many red or white numbers guessed*/

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
            if (rNum[i] == usrInput[j])
            {
                white++;
                break;
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

void genRandNum(int const MAXNUM, char *rNum)
{
    /*Generate a random 4 digit number 1111 - 9999*/

    int randN, num[MAX], totalNum = 0;
    srand(time(NULL));

    while (totalNum < MAX)
    {
        randN = (rand() % MAXNUM);
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
