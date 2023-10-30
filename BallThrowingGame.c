#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define maxplayers 5
#define BOARD_SIZE 5
#define MAX_ROUNDS 25
#define SCORE_RANGE_MIN 1
#define SCORE_RANGE_MAX 9

struct player
{
    char name[11];
    int score;
};
typedef struct player player;

player players[maxplayers];
char board[BOARD_SIZE][BOARD_SIZE];

void initializeBoard()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            board[i][j] = 'X';
        }
    }
}

void printBoard()
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf(" %c  ", board[i][j]);
        }
        printf("\n");
    }
}

void playerDetails(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Enter Player %d Name: ", i + 1);
        scanf("%10s", players[i].name);
        players[i].score = 0;
    }
}
void scoreboard(int n)
{
    int i;
    system("cls");
    printf("SCOREBOARD\n__________________\n");
    printf("|Name      |Scores|\n|__________|______|\n");
    for (i = 0; i < n; i++)
    {
        printf("|%-10s|  %-4d|\n", players[i].name, players[i].score);
    }
    printf("|__________|______|\n\n");
    printBoard();
}
void menu()
{
    printf("********************************************************************\n");
    printf("Prepare for a thrilling game with hidden treasures behind the X marks!\n");
    printf("You and your friends will each get 25 balls to toss at the game board.\n");
    printf("But beware of the X marks - they're hiding precious points!\n");
    printf("Points revealed behind the X marks are awarded to the lucky thrower!\n");
    printf("Will you be the champion with the highest score when all balls are thrown?\n");
    printf("Get ready for some ball-tossing excitement!\n");
    printf("Press any key when you finish reading\n");
    printf("********************************************************************\n");
    _getch();
}
int main()
{
    initializeBoard();
    int numPlayers;
    char ch;
    printf("WELCOME TO BALL THROWING GAME\n");
    printf("Press 'a' to know how to play, press 'x' to ignore\n");
    scanf(" %c", &ch);
    if (ch == 'a' || ch == 'A')
        menu();
    printf("Enter how many players: ");
    scanf("%d", &numPlayers);

    if (numPlayers < 2 || numPlayers > maxplayers)
    {
        printf("Invalid number of players. Please choose between 2 and %d players.\n", maxplayers);
        return 1;
    }

    playerDetails(numPlayers);
    srand((unsigned int)time(NULL));
    scoreboard(numPlayers);
    int currentPlayer = 0;
    for (int round = 1; round <= MAX_ROUNDS; round++)
    {
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        printf("\n%s its Your turn to Throw the ball\nPress any key to throw: ", players[currentPlayer].name);
        _getch();
        if (board[x][y] == 'X')
        {
            int randomScore = rand() % (SCORE_RANGE_MAX - SCORE_RANGE_MIN + 1) + SCORE_RANGE_MIN;
            board[x][y] = randomScore + '0';
            players[currentPlayer].score += randomScore;
            scoreboard(numPlayers);
            printf("%s scores %d\n", players[currentPlayer].name, randomScore);
        }
        else
        {
            scoreboard(numPlayers);
            printf("%s dropped the ball!\n", players[currentPlayer].name);
        }

        currentPlayer = (currentPlayer + 1) % numPlayers;
    }

    printf("Game Over!\n");
    int winner = 0;
    for (int i = 1; i < numPlayers; i++)
    {
        if (players[i].score > players[winner].score)
        {
            winner = i;
        }
    }
    printf("%s wins with a score of %d!\n", players[winner].name, players[winner].score);

    return 0;
}
