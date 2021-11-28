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
    
    score = 0;
    for (size_t i = 0; i < size; i++)
    {
        if (board[i][i] == player)
            score++;
    }

    if (score == size)
        return true;

    score = 0;
    int curr_ind = size - 1;
    for (size_t i = 0; i < size; i++)
    {
        if (board[curr_ind][i] == player)
            score++;

        curr_ind--;        
    }
    if (score == size)
        return true;
    
    return false;
}

bool is_board_full(char ** board, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
       for (size_t j = 0; j < size; j++)
       {
           if(board[i][j] == ' ')
                return false;
       }
       
    }
    
    return true;
}

void switch_player(char * players)
{
    char temp = players[0];
    players[0] = players[1];
    players[1] = temp;
}

int main()
{
    size_t size = 3;
    char ** board = create_board(size);
    int ai_move[2];
    char players[2] = {PLAYER1, PLAYER2};
    char winner;
    
    print_board(board, size);


    while (1)
    {
        char current_player = players[0];
        update_board(board, size, current_player, NULL);

        if (check_won(board, current_player, size))
        {
            printf("Player %c won!", current_player);
            break;
        }
        switch_player(players);

        if (is_board_full(board, size))
        {
            printf("Board is full\n");
            break;
        }
    }
    

    // update_board(board, size, PLAYER1, NULL);
    // update_board(board, size, PLAYER1, NULL);
    // update_board(board, size, PLAYER1, NULL);

    // update_board(board, size, PLAYER1, NULL);
    // update_board(board, size, PLAYER1, NULL);
    // update_board(board, size, PLAYER1, NULL);

    // update_board(board, size, PLAYER1, NULL);
    // update_board(board, size, PLAYER1, NULL);
    // update_board(board, size, PLAYER1, NULL);


    // printf("%d", check_won(board, PLAYER1, size));
    // printf("%d", is_board_full(board, size));
    // for (size_t i = 0; i < size; i++)
    // {
    //     printf("%c ", board[i][i]);
    // }
    
    

    return 0;
}