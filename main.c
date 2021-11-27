#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define PLAYER1 'X'
#define PLAYER2 'O'

char ** create_board(size_t size)
{
    char ** board = (char **)malloc(size * sizeof(char *));

    for (size_t i = 0; i < size; i++)
        board[i] = (char *)malloc(size * sizeof(char));
    

    for (size_t i = 0; i < size; i++)
    {
        for(size_t j = 0; j < size; j++)
            board[i][j] = ' ';
    }
    
    
    return board;
}

void print_line(size_t size)
{
    printf("-----");
    for (size_t i = 0; i < size-1; i++)
        printf("----");

    printf("\n");
}

void print_board(char ** board, size_t size)
{
    for (size_t i = 0; i < 3; i++)
    {
        print_line(size);
        for (size_t j = 0; j < size; j++)
        {
            if (j == size-1)
                printf("| %c |\n", board[i][j]);
            else
                printf("| %c ", board[i][j]);     
        }  
    }
    print_line(size);
}

void update_board(char ** board, size_t size, char player)
{
    unsigned int row, col;
    printf("Input <row, column> :\n>> ");
    scanf("%d%d", &row, &col);

    board[row-1][col-1] = player;
    print_board(board, size);
}

int main()
{
    size_t size = 3;
    char ** board = create_board(size);
    print_board(board, size);

    update_board(board, size, PLAYER1);

    return 0;
}