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
#include <unistd.h>

#define MAX 4
#define INPUTSZ 100
#define FILENAME ".mm"

/*Check user's input*/
void validation(char *input, char *number, int *val, int *pRepeat);
/*Compare user's input to answer*/
void checkChoice(char *usrInput, char const *rNum, int *guesses, int *win);
/*Generate randum number*/
void genRandNum(int const MAXNUM, char *rNum, int *pRepeat);
/*Parse CLI arguements*/
void argParse(int const argc, char *argv[], int *pRepeat);

int main(int argc, char *argv[])
{
    char randNum[MAX], *input = NULL, guess[MAX];
    int guesses = 0, winner = 0, valid = 0, repeat = 0;
    double totalTime = 0;
    FILE *pFile;
    size_t size;
    time_t begin, end;

    argParse(argc, argv, &repeat);

    pFile = fopen(FILENAME, "r");

    if(NULL != pFile)
    {
        if (getline(&input, &size, pFile) != -1)
        {
            input[strlen(input)-1] = 0;
            validation(input, randNum, &valid, &repeat);
        }
        fclose(pFile);
    }

    if (valid || !(NULL !=pFile))
    {
        genRandNum(10, randNum, &repeat);
    }

    while(!winner)
    {
        begin = time(NULL);

        printf("Guess a number: ");

        if(getline(&input, &size, stdin) != -1)
        {
            input[strlen(input)-1] = 0;
            validation(input, guess, &valid, &repeat);
        }

        switch(valid)
        {
            case 0:
            {
                checkChoice(guess, randNum, &guesses, &winner);
                end = time(NULL);
                totalTime += difftime(end, begin);
                break;
            }
            case 3:
            {
                printf("Repeating digits. No no.\n");
                break;
            }
            default:
            {
                printf("Not valid input. Must be 4 digits only.\n");
            }
        }
    }

    printf("Average time per guess %.2f seconds\n", totalTime / guesses);

    return 0;
}

void validation(char *input, char *number, int *val, int *pRepeat)
{
    /*Check user input*/

    int s = strlen(input);
    *val = 0;

    if (s == 4)
    {
        for (int i = 0; i < s; i++)
        {
            if ('0' <= input[i] && '9' >= input[i])
            {
                number[i] = input[i];
            }
            else
            {
                *val = 5;
                break;
            }
        }
    }
    else if (4 < s)
    {
        *val = 1;
    }
    else if (4 > s)
    {
        *val = 2;
    }

    if (!(*val) && !(*pRepeat))
    {
        for (int i = 0; i < MAX; i++)
        {
            for (int j = i + 1; j < MAX; j++)
            {
                if (number[i] == number[j])
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
    else
    {
        printf("No matches...\n");
    }

    if (4 == red)
    {
        printf("Winner, took %d guess(es).\n", *guesses);
        *win = 1;
    }
}

void genRandNum(int const MAXNUM, char *rNum, int *pRepeat)
{
    /*Generate a random 4 digit number 1111 - 9999*/

    int randN, num[MAX], totalNum = 0;
    srand(time(NULL));

    while (totalNum < MAX)
    {
        randN = (rand() % MAXNUM);
        num[totalNum] = randN;
        totalNum++;

        if (!(*pRepeat))
        {
            for (int i = 0; i < totalNum - 1; i++)
            {
                if (randN == num[i])
                {
                    totalNum--;
                    break;
                }
            }
        }
    }
    
    sprintf(rNum, "%d%d%d%d", num[0], num[1], num[2], num[3]);
}

void argParse(int const argc, char *argv[], int *pRepeat)
{
    int opt;
    opterr = 0;

    while ((opt = getopt(argc, argv, "rh")) != -1)
    {
        switch (opt)
        {
            case 'r':
            {   
                *pRepeat = 1;
                break;
            }
            case 'h':
            {
                printf("-r: allow repeating digits\n");
                exit(0);
            }
            case '?':
            default:
            {
                fprintf(stderr, "Unknown option %c -- use -h\n", optopt);
            }
        }
    }

    for (int index = optind; index < argc; index++)
    {
        printf ("Non-option argument %s\n", argv[index]);
        exit(1);
    }
      
}
