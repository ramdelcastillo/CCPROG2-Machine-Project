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

int main(){

int i, j, roll1 = 0, roll2 = 0;
int table[MAXROWS][MAXCOLS] = {{5,0,0,0,3,0,5,0,0,0,0,2}, {5,0,0,0,3,0,5,0,0,0,0,2}};
int control[MAXROWS][MAXCOLS] = {{1,0,0,0,-1,0,-1,0,0,0,0,1}, {-1,0,0,0,1,0,1,0,0,0,0,-1}}; // 1 = Player 1 / -1 = Player 2 
int captured[2] = {0,0};
char player[100]; 

srand(time(NULL));

printf("CCPROG Machine Project | Term 1 AY 2022-2023\n\n");
printf("Authors:\n");
printf("Jose Mari Del Castillo\n");
printf("Francisco Emmanuel Dumas\n");
printf("\n|-[Backgammon]-|\n");


//Table
Board(table, control, captured, player);

printf("\nPress ENTER to Roll");
scanf("%*[^\n]");
getchar();

printf("-Dice-\n");
Dice(&roll1);
Dice(&roll2);
printf("Dice 1: [%d]\n", roll1);
printf("Dice 2: [%d]", roll2);

    return 0;
}

void Board(int table[][MAXCOLS], int control[][MAXCOLS], int captured[], char player[])
{
    int i, j;

    printf("----------------------------------------------------\n");
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
