#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXROWS 2
#define MAXCOLS 12
#define DICE rand() % 6


void Dice(int *roll);
void Side(int Player, char *Side);
void Board(int table[][MAXCOLS], int control[][MAXCOLS], int captured[], char player[]);
void Gameplay (int table[][MAXCOLS], int control[][MAXCOLS], int captured[], char player[]);
int PointOccupancy(int arr[][MAXCOLS], int row, int col);
void addOneToTheBar(int arr[2], int player);
void changeCheckerAmount(int arr[][MAXCOLS], int row, int column, int diceroll, int player, int bar[2]);

int main()
{

int i, j, roll1 = 0, roll2 = 0, GameOver = 0, round = 1, diceroll, row, col;
int table[MAXROWS][MAXCOLS] = {{5,0,0,0,3,0,5,0,0,0,0,2}, {5,0,0,0,3,0,5,0,0,0,0,2}};
int control[MAXROWS][MAXCOLS] = {{-1,0,0,0,1,0,1,0,0,0,0,-1}, {1,0,0,0,-1,0,-1,0,0,0,0,1}}; // 1 = Player 1 / -1 = Player 2 
int captured[2] = {0,0};
char player[100]; 

srand(time(NULL));

    Gameplay (table, control, captured, player);
    
     return 0;
}

void Board(int table[][MAXCOLS], int control[][MAXCOLS], int captured[], char player[])
{
    int i, j;

    printf("CCPROG Machine Project | Term 1 AY 2022-2023\n\n");
            printf("Authors:\n");
            printf("Jose Mari Del Castillo\n");
            printf("Francisco Emmanuel Dumas\n");
            printf("\n|-[Backgammon]-|\n");

    printf("----------------------------------------------------\n");
    for (i = 0; i < MAXROWS/2; i++){

        for (j = 0; j < MAXCOLS; j++){
            printf("|");
            printf(" %d ", j);
            if (j == 5) printf("|_|");
            }

        printf("|");
    }
    printf("\n");
    for (i = 0; i < MAXROWS/2; i++){

        for (j = 0; j < MAXCOLS; j++){
            printf("|");
            printf(" V ");
            if (j == 5) printf("|_|");
            }

        printf("|");
    }
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
     for (i = 0; i < MAXROWS/2; i++){

        for (j = 0; j < MAXCOLS; j++){
            Side(control[i][j], player);
            printf("|");
            printf("[%s]", player);
            if (j == 5) printf("|_|");
            }

        printf("|");
    }
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    for (i = 0; i < MAXROWS; i++){

        for (j = 0; j < MAXCOLS; j++){
            printf("|");
            printf("[%d]", table[i][j]);
            if (j == 5) printf("|-|");
            }

        printf("|");
        printf(" < | %d |",i);
        printf("\n");
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    for (i = 1; i < MAXROWS; i++){

        for (j = 0; j < MAXCOLS; j++){
            Side(control[i][j], player);
            printf("|");
            printf("[%s]", player);
            if (j == 5) printf("|_|");
            }

        printf("|");
    }
    printf("\n");
    printf("----------------------------------------------------");
    printf("\n|-[Captured]-|\n");
    printf("Player 1:[");
    if (captured [0] == 0) printf("FREE");
    for (i = 0; i < captured [0]; i++) printf(" / ");
    printf("]\n");
    printf("Player 2:[");
    if (captured [1] == 0) printf("FREE");
    for (i = 0; i < captured [1]; i++) printf(" / ");
    printf("]\n");
    printf("---------------------------------------------\n");
  
}

void Gameplay (int table[][MAXCOLS], int control[][MAXCOLS], int captured[], char player[])
{
    int round = 1, GameOver = 0, diceroll, row, col, roll1, roll2;
        do
        {
            //Table
            Board(table, control, captured, player);
            printf("Round [%d] | Player [1 | B]\n",round);
            printf("\nPress ENTER to Roll");
            scanf("%*[^\n]");
            getchar();

            printf("-Dice-\n");
            Dice(&roll1);
            Dice(&roll2);
            printf("Dice 1: [%d]\n", roll1);
            printf("Dice 2: [%d]\n", roll2);
            diceroll = roll1 + roll2;

            printf("\n-Move-\n");
            printf("What piece would you like to move?\n");
            printf("Row ->");
            scanf("%d", &row);
            printf("Col ->");
            scanf("%d", &col);

            printf("\nPress ENTER to END turn");
            scanf("%*[^\n]");
            getchar();
            printf("\n");
            system("cls");
            changeCheckerAmount(table, row, col, diceroll, 1, captured); 
        //----------------------------------------------------------
            Board(table, control, captured, player);
            printf("Round [%d] | Player [2 | W]\n",round);
            printf("\nPress ENTER to Roll");
            scanf("%*[^\n]");
            getchar();

            printf("-Dice-\n");
            Dice(&roll1);
            Dice(&roll2);
            printf("Dice 1: [%d]\n", roll1);
            printf("Dice 2: [%d]\n", roll2);
            diceroll = roll1 + roll2;

            printf("\n-Move-\n");
            printf("What piece would you like to move?\n");
            printf("Row ->");
            scanf("%d", &row);
            printf("Col ->");
            scanf("%d", &col);

            printf("\nPress ENTER to END turn");
            scanf("%*[^\n]");
            getchar();
            changeCheckerAmount(table, row, col, diceroll, -1, captured); 

            system("cls");
            round++;
        } while (GameOver == 0);

}

void Dice(int *roll)
{
    int i;

    for (i = 0; i < 5; i++){
            *roll = DICE;
        }

    switch (*roll)
    {
    case 0:
        *roll = 1;
        break;

    case 1:
        *roll = 2;
        break;

    case 2:
        *roll = 3;
        break;

    case 3:
        *roll = 4;
        break;

    case 4:
        *roll = 5;
        break;

    case 5:
    *roll = 6;
        break;
    }
}

void Side(int Player, char *Side)
{
    switch (Player)
    {
    case -1:
        strcpy(Side, "B");
        break;
    
    case 0:
        strcpy(Side, "-");
        break;

    case 1:
        strcpy(Side, "W");
        break;
    
    default:
        break;
    }
}

int PointOccupancy(int arr[][12], int row, int col) //gets the amount of checkers on a point
{
    int nOccupancy = 0;

    nOccupancy = arr[row][col];

    return nOccupancy;
}

void addOneToTheBar(int bar[2], int player) //make it player for now i need the identification for the player
{
    if(player == -1) bar[0] += 1;
    else if(player == 1) bar[1] += 1;
}

void changeCheckerAmount(int arr[][12], int row, int col, int diceroll, int player, int bar[2]) //changes the amount of checkers on a point
{
    if(PointOccupancy(arr, row, col) != 0 && player == -1)
    {
        int excess = -1;
        excess -= col - diceroll;
        if(row == 1 && (col - diceroll) > 0)
        {
            if(PointOccupancy(arr, row, col) >= 1) arr[row][col] -= 1;
            if(PointOccupancy(arr, row, col - diceroll) == 1 /*&& player == 1*/) 
            {
                addOneToTheBar(bar, player);
                 //change piece to -1
            }
            else if(PointOccupancy(arr, row, col - diceroll) != 1) arr[row][col - diceroll] += 1;
        }
        else if(row == 0)
        {
            if(PointOccupancy(arr, row, col) >= 1) arr[row][col] -= 1;
            if(PointOccupancy(arr, row, col + diceroll) == 1) 
            {
                addOneToTheBar(bar, player);
                //change piece to -1
            }
            else if(PointOccupancy(arr, row, col + diceroll) != 1) arr[row][col + diceroll] += 1;
        }
        else if(row == 1 && (col - diceroll) < 0)
        {
            if(PointOccupancy(arr, row, col) >= 1) arr[row][col] -= 1;
            if(PointOccupancy(arr, row - 1, excess) == 1) 
            {
                addOneToTheBar(bar, player);
                //change piece to -1
            }
            else if(PointOccupancy(arr, row - 1, excess) != 1) arr[row - 1][excess] += 1;
        }
    } 
    else if(PointOccupancy(arr, row, col) != 0 && player == 1)
    {
        int excess = -1;
        excess -= col - diceroll;
        if(row == 0 && (col - diceroll) > 0)
        {
            if(PointOccupancy(arr, row, col) >= 1) arr[row][col] -= 1;
            if(PointOccupancy(arr, row, col - diceroll) == 1 /*&& player == 1*/) 
            {
                addOneToTheBar(bar, player);
                 //change piece to 1
            }
            else if(PointOccupancy(arr, row, col - diceroll) != 1) arr[row][col - diceroll] += 1;
        }
        else if(row == 1)
        {
            if(PointOccupancy(arr, row, col) >= 1) arr[row][col] -= 1;
            if(PointOccupancy(arr, row, col + diceroll) == 1) 
            {
                addOneToTheBar(bar, player);
                //change piece to 1
            }
            else if(PointOccupancy(arr, row, col + diceroll) != 1) arr[row][col + diceroll] += 1;
        }
        else if(row == 0 && (col - diceroll) < 0)
        {
            if(PointOccupancy(arr, row, col) >= 1) arr[row][col] -= 1;
            if(PointOccupancy(arr, row + 1, excess) == 1) 
            {
                addOneToTheBar(bar, player);
                //change piece to 1
            }
            else if(PointOccupancy(arr, row + 1, excess) != 1) arr[row + 1][excess] += 1;
        }
    }
}
