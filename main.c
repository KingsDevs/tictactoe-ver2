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


void update_board(char ** board, size_t size, char player, int * ai_move)
{      
    if(ai_move == NULL)
    {
        unsigned int row, col;
        printf("Input <row, column> :\n>> ");
        scanf("%d%d", &row, &col);
        board[row-1][col-1] = player;
    }
    else
    {
       board[ai_move[0]][ai_move[1]] = player;
    }
    print_board(board, size);
}

bool check_won(char ** board, char player, size_t size)
{
    short int score = 0;
    //horizontal
    for (size_t i = 0; i < size; i++)
    {
        score = 0;
        if (board[i][0] == player)
        {
            score++;
            for (size_t j = 1; j < size; j++)
            {
                if (board[i][j] == player)
                    score++;
            }
            if (score == size)
                return true;
        }
    }

    //vertical
    for (size_t i = 0; i < size; i++)
    {
        score = 0;
        for (size_t j = 0; j < size; j++)
        {
            if (board[j][i] == player)
                score++;
        }
        if (score == size)
            return true;
        
    }
    
    //front slash
    
    
    for (size_t i = 0; i < size; i++)
    {
        if (board[i][i] == player)
            score++;
    }

    if (score == size)
        return true;


    
    return false;
}
int main()
{
    size_t size = 3;
    char ** board = create_board(size);
    print_board(board, size);

    update_board(board, size, PLAYER1, NULL);
    update_board(board, size, PLAYER1, NULL);
    update_board(board, size, PLAYER1, NULL);

    printf("%d", check_won(board, PLAYER1, size));
    

    return 0;
}