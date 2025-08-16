#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXROWS 2
#define MAXCOLS 12
#define DICE rand() % 6


void Dice(int *roll);
void Side(int Player, char *Side);
void colorFG(int nColor);
void Board(int table[][MAXCOLS], int control[][MAXCOLS], int captured[], char player[], int bearedOff[]);
void Gameplay (int table[][MAXCOLS], int control[][MAXCOLS], int captured[], char player[], int bearedOff[]);
void addOneToTheBar(int bar[2], int player);
void moveThisChecker(int arr[][12], int row, int col, int diceroll, int player, int bar[2], int control[][12], int bearedOff[2]);
void barLevel(int arr[][12], int control[][12], int row, int col, int diceroll, int bearedOff[2]);
int homeBoardBareOffGreen(int arr[][12], int control[][12]);
int homeBoardBareOffRed(int arr[][12], int control[][12]);
int barMoveOnly(int bar[2], int player);
int playerWinner(int bearedOff[2]);

int main()
{
        
    int table[MAXROWS][MAXCOLS] = {{5,0,0,0,3,0,5,0,0,0,0,2}, 
                                  {5,0,0,0,3,0,5,0,0,0,0,2}};
    int control[MAXROWS][MAXCOLS] = {{-1,0,0,0,1,0,1,0,0,0,0,-1}, 
                                    {1,0,0,0,-1,0,-1,0,0,0,0,1}};  
      
    int captured[2] = {0,0};
    int bearedOff[2] = {0,0};
    char player[100]; 

    srand(time(NULL));
    Gameplay (table, control, captured, player, bearedOff);
    Board(table, control, captured, player, bearedOff);
    if (playerWinner(bearedOff) == -1) printf("\n\t\t[Player 1 Wins!]\n\n");
    else if (playerWinner(bearedOff) == 1) printf("\n\t\t[Player 2 Wins!]\n\n");
    printf("---------------------------------------------\n");
    
    return 0;
}

void Board(int table[][MAXCOLS], int control[][MAXCOLS], int captured[], char player[], int bearedOff[])
{
    int i, j;

    colorFG(86);//Lightgreen
    printf("CCPROG Machine Project | Term 1 AY 2022-2023\n");
    printf("Authors:\n");
    printf("Jose Mari Del Castillo\n");
    printf("Francisco Emmanuel Dumas\n");
    colorFG(1);//darkred
    printf("\n|-[Backgammon]-|\n");
    colorFG(15);//white
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
            if (control[i][j] == 1) colorFG(160);
            else if (control[i][j] == -1)colorFG(28);
            else colorFG(15);
            printf("[%s]", player);
            colorFG(15);
            if (j == 5) printf("|_|");
            }

        printf("|");
    }
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    for (i = 0; i < MAXROWS; i++){

        for (j = 0; j < MAXCOLS; j++){
            printf("|");
            if (control[i][j] == 1) colorFG(160);
            else if (control[i][j] == -1)colorFG(28);
            else colorFG(15);
            printf("[%d]", table[i][j]);
            colorFG(15);
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
            if (control[i][j] == 1) colorFG(160);//red
            else if (control[i][j] == -1)colorFG(28);//green
            else colorFG(15);
            printf("[%s]", player);
            colorFG(15);
            if (j == 5) printf("|_|");
            }

        printf("|");
    }
    printf("\n");
    printf("----------------------------------------------------");
        colorFG(1);
    printf("\n|-[Captured]-|\n");
        colorFG(28);
    printf("Player 1");
        colorFG(15);
    printf(":[");
    if (captured [0] == 0) printf("FREE");
        colorFG(28);
        
    for (i = 0; i < captured [0]; i++) printf(" / ");
        colorFG(15);
    printf("]\n");
        colorFG(160);
    printf("Player 2");
        colorFG(15);
    printf(":[");

    if (captured [1] == 0) printf("FREE");
        colorFG(160);
    for (i = 0; i < captured [1]; i++) printf(" / ");
    colorFG(15);
    printf("]\n");
    //---------------------------------------------------------
    printf("---------------------------------------------\n");
        colorFG(1);
    printf("|-[ESCAPED]-|\n");
        colorFG(28);
    printf("Player 1");
        colorFG(15);
    printf(":[");
    
    if (bearedOff [0] == 0) printf("HELD");
        colorFG(28);
    for (i = 0; i < bearedOff[1]; i++) printf(" / ");
        colorFG(15);
    printf("]");
    
    if (homeBoardBareOffGreen(table,control) == 1) printf(" Bear Off!\n");
    else printf("\n");
        colorFG(160);
    printf("Player 2");
        colorFG(15);
    printf(":[");

    if (bearedOff [1] == 0) printf("HELD");
        colorFG(160);
    for (i = 0; i < bearedOff [0]; i++) printf(" / ");
        colorFG(15);
    printf("]");
    
    if (homeBoardBareOffRed(table,control) == 1) printf(" Bear Off!\n");
    else printf("\n");
    printf("---------------------------------------------\n");
}

void Gameplay (int table[][MAXCOLS], int control[][MAXCOLS], int captured[], char player[], int bearedOff[])
{
    int round = 1, GameOver = 0, diceroll, row, col, moves = 0, choice, TotalM = 0, i;
    int roll[4] = {0, 0, 0, 0};
    do
    {
        //Table
        Board(table, control, captured, player, bearedOff);
        printf("Round [%d] | ",round);
            colorFG(160);
        printf("Player [2 | R]\n");
            colorFG(15);
        printf("\nPress ENTER to Roll");
        scanf("%*[^\n]");
        getchar();

        Dice(&roll[0]);
        Dice(&roll[1]);
        system("cls");
        if (roll[0] == roll[1])
        {
            moves = 4;
            roll[2] = roll[0];
            roll[3] = roll[0];
        }
        else moves = 2;
        TotalM = moves;
            do
            {
                do
                {
                    Board(table, control, captured, player, bearedOff);
                    printf("Round [%d] | ",round);
                        colorFG(160);
                    printf("Player [2 | R]\n");
                        colorFG(15);
                    printf("-Dice-\n");
                    for (i = 0; i < TotalM; i++)
                    { 
                        if (roll[i] != 0)printf("Dice %d: [%d]\n", i, roll[i]);
                    }

                    printf("\nMoves:  [%d]\n", moves);

                    printf("\nWhat die do you want to use?\n->");
                    scanf("%d", &choice);
                    system("cls");

                } while ((TotalM == 2 && (roll[choice] == 0 || choice >= 3 || choice < 0)) || (TotalM == 4 && (roll[choice] == 0 || choice >= 5 || choice < 0)));

                if (choice == 0) diceroll = roll[0];
                    else if (choice == 1) diceroll = roll[1];
                    else if (choice == 2) diceroll = roll[2];
                    else if (choice == 3) diceroll = roll[3];

                if(barMoveOnly(captured, 1) == 1)
                {
                    do 
                    {    
                        Board(table, control, captured, player, bearedOff);
                        printf("Round [%d] | ",round);
                            colorFG(160);
                        printf("Player [2 | R]\n");
                            colorFG(15);
                        printf("-Dice-\n");
                        printf("Dice %d: [%d]\n", choice, roll[choice]);

                        printf("\n-Move-\n");
                        printf("What piece would you like to move?\n");
                        printf("Row-> ");
                        scanf("%d", &row);
                        printf("Col-> ");
                        scanf("%d", &col);
                        system("cls");
                    } while ((control[row][col] != 1 && (table[0][col + diceroll] >= 2 || table[1][col - diceroll] >= 2)) || ((control[row][col] != 1 && (row >= 3 || row < 0)) || (col >= 12 || col < 0)));
                }
                Board(table, control, captured, player, bearedOff);
                printf("Round [%d] | ",round);
                    colorFG(160);
                printf("Player [2 | R]\n");
                    colorFG(15);

                printf("\nPress ENTER to END turn");
                scanf("%*[^\n]");
                getchar();
                printf("\n");
                system("cls");
                moveThisChecker(table, row, col, diceroll, 1, captured, control, bearedOff); 

                roll[choice] = 0;
                moves--;
            } while (moves != 0);
            GameOver = playerWinner(bearedOff);
        //----------------------------------------------------------
            //Table
            if (GameOver == 0)
            {
                Board(table, control, captured, player, bearedOff);
                printf("Round [%d] | ",round);
                    colorFG(28);
                printf("Player [1 | G]\n");
                    colorFG(15);
                printf("\nPress ENTER to Roll");
                scanf("%*[^\n]");
                getchar();

                Dice(&roll[0]);
                Dice(&roll[1]);
                roll[2] = 0;
                roll[3] = 0;
                system("cls");
                if (roll[0] == roll[1])
                {
                    moves = 4;
                    roll[2] = roll[0];
                    roll[3] = roll[0];
                }
                else moves = 2;
                TotalM = moves;
                do
                {
                    do
                    {
                        Board(table, control, captured, player, bearedOff);
                        printf("Round [%d] | ",round);
                            colorFG(28);
                        printf("Player [1 | G]\n");
                            colorFG(15);
                        printf("-Dice-\n");
                        for (i = 0; i < TotalM; i++)
                        { 
                            if (roll[i] != 0)printf("Dice %d: [%d]\n", i, roll[i]);
                        }

                        printf("\nMoves:  [%d]\n", moves);

                        printf("\nWhat die do you want to use?\n->");
                        scanf("%d", &choice);
                        system("cls");

                    } while ((TotalM == 2 && (roll[choice] == 0 || choice >= 3 || choice < 0)) || (TotalM == 4 && (roll[choice] == 0 || choice >= 5 || choice < 0)));

                    if (choice == 0) diceroll = roll[0];
                        else if (choice == 1) diceroll = roll[1];
                        else if (choice == 2) diceroll = roll[2];
                        else if (choice == 3) diceroll = roll[3];

                    if (barMoveOnly(captured, -1) == 1)
                    {
                        do
                        {   
                            Board(table, control, captured, player, bearedOff);
                            printf("Round [%d] | ",round);
                                colorFG(28);
                            printf("Player [1 | G]\n");
                                colorFG(15);
                            printf("-Dice-\n");
                            printf("Dice %d: [%d]\n", choice, roll[choice]);

                            printf("\n-Move-\n");
                            printf("What piece would you like to move?\n");
                            printf("Row-> ");
                            scanf("%d", &row);
                            printf("Col-> ");
                            scanf("%d", &col);
                            system("cls");
                        } while ((control[row][col] != -1 && (table[0][col + diceroll] >= 2 || table[1][col - diceroll] >= 2)) || ((control[row][col] != -1 && (row >= 3 || row < 0)) || (col >= 12 || col < 0)));
                    }
                    
                    Board(table, control, captured, player, bearedOff);
                    printf("Round [%d] | ",round);
                        colorFG(28);
                    printf("Player [1 | G]\n");
                        colorFG(15);

                    printf("\nPress ENTER to END turn");
                        scanf("%*[^\n]");
                    
                    getchar();
                    printf("\n");
                    system("cls");
                    
                    moveThisChecker(table, row, col, diceroll, -1, captured, control, bearedOff); 

                    roll[choice] = 0;
                    moves--;
                } while (moves != 0);
            round++;
            GameOver = playerWinner(bearedOff);
        }
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
        strcpy(Side, "G");
        break;
    
    case 0:
        strcpy(Side, "-");
        break;

    case 1:
        strcpy(Side, "R");
        break;
    
    default:
        break;
    }
}

/*
    This function changes the texts color's
    @param ncolor Color Number ex:15 - White
*/
void colorFG(int nColor)
{
    printf("\x1b[38;5;%dm", nColor);
}

/*
    This function adds a checker to the bar of player 1 or player 2
    Precondition: bar[0] (player 1) and bar[1] (player 2) must be an integer
    @param bar[2]    1D integer array, serves as a container for the bar
    @param player   identifies players or non-occupied points (1 for Player 1, -1 for Player 2, 0 for non-occupied points) 
    @display    adds 1 to the respective bars   
*/
void addOneToTheBar(int bar[2], int player) //make it player for now i need the identification for the player
{
    if(player == -1) bar[1] += 1; 
    else if(player == 1) bar[0] += 1;
}



/*
    This function returns 1 if a player has no checkers in his bar, if there are checkers return 0
    Precondition: bar[0] (player 1) and bar[1] (player 2) must be an integer
    @param bar[2]    1D integer array, serves as a container for the bar
    @param player   identifies players or non-occupied points (1 for Player 1, -1 for Player 2, 0 for non-occupied points) 
    @return  
*/
int barMoveOnly(int bar[2], int player)
{
    int isAbleToMove = 0;

    if(player == -1) //GREEN
    {
        if(bar[0] == 0) isAbleToMove = 1;
    }
    else if(player == 1) //RED
    {
        if(bar[1] == 0) isAbleToMove = 1;
    }
    else isAbleToMove = 0;

    return isAbleToMove;
}

int homeBoardBareOffGreen(int arr[][12], int control[][12])
{
    int i, j, nCheckers = 0, nTotal = 0, nBareOff = 0;

    for(i = 1; i < 2; i++)
    {
        for(j = 6; j < 12; j++)
        {
            if(control[i][j] == -1) nCheckers += arr[i][j]; //GREEN
        }
    }

    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 12; j++)
        {
            if(control[i][j] == -1) nTotal += arr[i][j]; //RED
        }
    }

    if(nCheckers == nTotal) nBareOff = 1;

    return nBareOff;
}

int homeBoardBareOffRed(int arr[][12], int control[][12])
{
    int i, j, nCheckers = 0, nTotal = 0, nBareOff = 0;

    for(i = 0; i < 1; i++)
    {
        for(j = 6; j < 12; j++)
        {
            if(control[i][j] == 1) nCheckers += arr[i][j]; //RED
        }
    }

    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 12; j++)
        {
            if(control[i][j] == 1) nTotal += arr[i][j]; //RED
        }
    }   

    if(nCheckers == nTotal) nBareOff = 1;

    return nBareOff;
}

void barLevel(int arr[][12], int control[][12], int row, int col, int diceroll, int bearedOff[2])
{
    if(homeBoardBareOffGreen(arr, control) == 1)
    {
        if(arr[row][col] >= 1 && (col + diceroll) > 11)
        {
            bearedOff[0] += 1;
            arr[row][col] -= 1;
            if(arr[row][col] == 0) control[row][col] = 0;
        }
    }
    else if(homeBoardBareOffRed(arr, control) == 1) 
    {
        if(arr[row][col] >= 1 && (col + diceroll) > 11)
        {
            bearedOff[1] += 1;
            arr[row][col] -= 1;
            if(arr[row][col] == 0) control[row][col] = 0;
        }
    }
}

/*
    This function handles the movement rules of the checkers in the 2D Array (board)
    Precondition: all elements in arr[][12] must be an integer
    ,row can only be 0 or 1, col can only be 0 to 11, diceroll can only be 1 to 6, player can only be 1, 0, or -1
    @param arr[][12]    integer array, location of checkers
    @param row  row index of the array
    @param col  column index of the array
    @param diceroll amount of points that a checker can move
    @param player   identifies players or non-occupied points (1 for Player 1, -1 for Player 2, 0 for non-occupied points) 
    @display    moves the checkers 
*/
void moveThisChecker(int arr[][12], int row, int col, int diceroll, int player, int bar[2], int control[][12], int bearedOff[2]) //changes the amount of checkers on a point
{
    if(homeBoardBareOffGreen(arr, control) == 1 || homeBoardBareOffRed(arr, control) == 1) 
    {
        barLevel(arr, control, row, col, diceroll, bearedOff);
        //when a certain player is able to bare off
    }
    else if(player == 1 && barMoveOnly(bar, player) == 0) 
    //player 2 & has checkers in the bar
    {
        if((arr[1][12 - diceroll] >= 1 && control[1][12 - diceroll] == 1) || control[1][12 - diceroll] == 0)
        {
            bar[1] -= 1;
            arr[1][12 - diceroll] += 1;
            control[1][12 - diceroll] = 1;
        }
        else if(arr[1][12 - diceroll] == 1 && control[1][12 - diceroll] == -1)
        //capturing to the bar
        {
            bar[1] -= 1;
            control[1][12 - diceroll] = 1;
        }
    } 
    else if(player == -1 && barMoveOnly(bar, player) == 0)
    //player 1 & has checkers in the bar
    {
        if((arr[0][12 - diceroll] >= 1 && control[0][12 - diceroll] == -1) || control[0][12 - diceroll] == 0)
        {
            bar[0] -= 1;
            arr[0][12 - diceroll] += 1;
            control[0][12 - diceroll] = -1;
        }
        else if(arr[0][12 - diceroll] == 1 && control[0][12 - diceroll] == 1)
        //capturing to the bar
        {
            bar[0] -= 1;
            control[0][12 - diceroll] = -1;
        }
    }
    else if(arr[row][col] != 0 && control[row][col] == 1 && player == 1 && barMoveOnly(bar, player) == 1) 
    //board element (point) has checkers & control element is the same as player 2 number (1) 
    //& player has no checkers in the bar
    {
        if(row == 1 && (col - diceroll) >= 0) //left
        {
            if((arr[row][col - diceroll] >= 1 && control[row][col - diceroll] == 1) || control[row][col - diceroll] == 0)
            {
                arr[row][col] -= 1;
                arr[row][col - diceroll] += 1;
                if(arr[row][col] == 0) control[row][col] = 0;
                control[row][col - diceroll] = 1;
            }
            else if(arr[row][col - diceroll] == 1 && control[row][col - diceroll] == -1)
            //capturing to the bar
            {
                arr[row][col] -= 1;
                if(arr[row][col] == 0) control[row][col] = 0;
                control[row][col - diceroll] = 1; 
                addOneToTheBar(bar, player);
            } 
        }
        else if(row == 0 && (col + diceroll) < 12) //right NOTE
        {
            if((arr[row][col + diceroll] >= 1 && control[row][col + diceroll] == 1) || control[row][col + diceroll] == 0)
            {
                arr[row][col] -= 1;
                arr[row][col + diceroll] += 1;
                if(arr[row][col] == 0) control[row][col] = 0;
                control[row][col + diceroll] = 1;
            }
            else if(arr[row][col + diceroll] == 1 && control[row][col + diceroll] == -1)
            //capturing to the bar
            {
                arr[row][col] -= 1;
                if(arr[row][col] == 0) control[row][col] = 0;
                control[row][col + diceroll] = 1; 
                addOneToTheBar(bar, player);
            } 
        }
        else if(row == 1 && (col - diceroll) < 0) //excess movement
        {
            int excess = -1;
            excess -= col - diceroll;
            if((arr[row - 1][excess] >= 1 && control[row - 1][excess] == 1) || control[row - 1][excess] == 0)
            {
                arr[row][col] -= 1;
                arr[row - 1][excess] += 1;
                if(arr[row][col] == 0) control[row][col] = 0;
                control[row - 1][excess] = 1;
            }
            else if(arr[row - 1][excess] == 1 && control[row - 1][excess] == -1)
            //capturing to the bar
            {
                arr[row][col] -= 1;
                if(arr[row][col] == 0) control[row][col] = 0;
                control[row - 1][excess] = 1;
                addOneToTheBar(bar, player);
            } 
        }
    }
    else if(arr[row][col] != 0 && control[row][col] == -1 && player == -1 && barMoveOnly(bar, player) == 1)
     //board element (point) has checkers & control element is the same as player 1 number (-1) 
    //& player has no checkers in the bar
    {
        if(row == 0 && (col - diceroll) >= 0) //left
        {
            if((arr[row][col - diceroll] >= 1 && control[row][col - diceroll] == -1) || control[row][col - diceroll] == 0)
            {
                arr[row][col] -= 1;
                arr[row][col - diceroll] += 1;
                if(arr[row][col] == 0) control[row][col] = 0;
                control[row][col - diceroll] = -1;
            }
            else if(arr[row][col - diceroll] == 1 && control[row][col - diceroll] == 1)
            {
                arr[row][col] -= 1;
                if(arr[row][col] == 0) control[row][col] = 0;
                control[row][col - diceroll] = -1; 
                addOneToTheBar(bar, player);
            } 
        }
        else if(row == 1 && (col + diceroll) < 12) //right NOTE
        {
            if((arr[row][col + diceroll] >= 1 && control[row][col + diceroll] == -1) || control[row][col + diceroll] == 0)
            {
                arr[row][col] -= 1;
                arr[row][col + diceroll] += 1;
                if(arr[row][col] == 0) control[row][col] = 0;
                control[row][col + diceroll] = -1; 
            }
            else if(arr[row][col + diceroll] == 1 && control[row][col + diceroll] == 1)
            {
                arr[row][col] -= 1;
                if(arr[row][col] == 0) control[row][col] = 0;
                control[row][col + diceroll] = -1; 
                addOneToTheBar(bar, player);
            } 
        }
        else if(row == 0 && (col - diceroll) < 0) //excess movement
        {
            int excess = -1;
            excess -= col - diceroll;
            if((arr[row + 1][excess] >= 1 && control[row + 1][excess] == -1) || control[row + 1][excess] == 0)
            {
                arr[row][col] -= 1;
                arr[row + 1][excess] += 1;
               
                if(arr[row][col] == 0) control[row][col] = 0;
                control[row + 1][excess] = -1;
            }
            else if(arr[row + 1][excess] == 1 && control[row + 1][excess] == 1)
            {
                arr[row][col] -= 1;
                if(arr[row][col] == 0) control[row][col] = 0;
                control[row + 1][excess] = -1;
                addOneToTheBar(bar, player);
            } 
        }
    }
}

/*
    This function returns 1 if player 1 could bare off the his/her checkers, if not return 0
    Precondition: all elements in arr[][12] must be an integer 
    ,row can only be 0 or 1,col can only be 6 to 11
    @param arr[][12]    2D integer array, location of checkers
    @return nBareOff    
*/
int playerWinner(int bearedOff[2])
{
    if(bearedOff[0] == 15) return 1;
    else if(bearedOff[1] == 15) return -1;
}