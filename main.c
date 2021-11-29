#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define PLAYER1 'X'
#define PLAYER2 'O'

#define INFINITY __INT_MAX__
#define MAX_DEPTH 8


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
        while (1)
        {
            printf("Input <row, column> :\n>> ");
            scanf("%d%d", &row, &col);
            if ((row <= size || col <= size) && (col >= 0 || row >= 0))
            {
                if (board[row-1][col-1] == ' ')
                {
                    board[row-1][col-1] = player;
                    break;
                }
                printf("Cell not Empty!\n");
            }
            else
                printf("Invalid Move! Please try again!\n");
        }

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

void play_with_friend(char ** board, size_t size, char * players)
{
    while (1)
    {
        char current_player = players[0];
        printf("Player %c turn!\n", current_player);
        update_board(board, size, current_player, NULL);

        if (check_won(board, current_player, size))
        {
            printf("Player %c won!\n", current_player);
            break;
        }
        switch_player(players);

        if (is_board_full(board, size))
        {
            printf("Board is full\n");
            break;
        }
    }
}

void empty_board(char ** board, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
            board[i][j] = ' ';
        
    }
}

int check_winner(char ** board, size_t size, char computer, char human)
{
    bool curr_player = check_won(board, computer, size);
    bool opponent = check_won(board, human, size);

    if (curr_player)
        return 1;

    if(opponent)
        return -1;

    return 0;    
}

int max(int a, int b)
{
    if(a > b)
        return a;
    return b;
}

int min(int a, int b)
{
    if(a < b)
        return a;
    return b;
}

int minimax(char ** board, size_t size, bool maximizer, int depth, int alpha, int beta, char computer, char human)
{
    int result = check_winner(board, size, computer, human);
    if(depth <= 0)
        return result;

    if (maximizer)
    {
        int max_eval = -INFINITY;
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = computer;
                    int eval = minimax(board, size, false, depth - 1, alpha, beta, computer, human);
                    board[i][j] = ' ';
                    max_eval = max(max_eval, eval);

                    alpha = max(alpha, eval);
                    if(beta <= alpha)
                        return max_eval;
                }
                
            }
        }
        
        return max_eval;
    }
    else if (!maximizer)
    {
        int min_eval = INFINITY;
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                if (board[i][j] == ' ')
                {
                    board[i][j] = computer;
                    int eval = minimax(board, size, true, depth - 1, alpha, beta, computer, human);
                    board[i][j] = ' ';
                    min_eval = min(min_eval, eval);

                    beta = min(beta, eval);
                    if(beta <= alpha)
                        return min_eval;
                }
                
            }
        }
        
        return min_eval;
    }
    
    
}

void play_with_computer(char ** board, size_t size, char * players, int * ai_moves)
{
    bool has_picked = false;
    while (1)
    {
        char human;
        while (!has_picked)
        {
            printf("Choose your player!\n");
            printf("1 - %c\n", PLAYER1);
            printf("2 - %c\n", PLAYER2);

            int choice;
            printf(">> ");
            scanf(" %d", &choice);

            if (choice == 1)
            {
                human = PLAYER1;
                has_picked = true;
                print_board(board, size);
                break;
            }
            else if (choice == 2)
            {
                human = PLAYER2;
                has_picked = true;
                print_board(board, size);
                break;
            }
            else
                printf("Invalid choice\n");
        }

        char current_player = players[0];
        printf("Player %c turn!\n", current_player);
        
        if (current_player == human)
            update_board(board, size, current_player, NULL);
        else
        {
            int best_score = -INFINITY;
            for (size_t i = 0; i < size; i++)
            {
                for (size_t j = 0; j < size; j++)
                {
                    if (board[i][j] == ' ')
                    {
                        board[i][j] = current_player;
                        int score = minimax(board, size, false, MAX_DEPTH, -INFINITY, INFINITY, current_player, human);
                        board[i][j] = ' ';

                        if (best_score < score)
                        {
                            best_score = score;
                            ai_moves[0] = i;
                            ai_moves[1] = j;
                        }
                        
                    }
                    
                }
                
            }
            update_board(board, size, current_player, ai_moves);
        }

        if (check_won(board, current_player, size))
        {
            printf("Player %c won!\n", current_player);
            break;
        }
        switch_player(players);

        if (is_board_full(board, size))
        {
            printf("Board is full\n");
            break;
        }
    }
    
}

int main()
{
    size_t size = 3;
    char ** board = create_board(size);
    int ai_move[2];
    char players[2] = {PLAYER1, PLAYER2};
    char winner;
    
    //print_board(board, size);

    int choice;
    while (1)
    {
        printf("TIC-TAC-TOE\n");
        printf("1. Play with friend\n");
        printf("2. Play with computer\n");
        printf("3. Exit\n");
        printf(">> ");
        scanf(" %d", &choice);

        switch (choice)
        {
        case 1:
            print_board(board, size);
            play_with_friend(board, size, players);
            empty_board(board, size);
            break;
        
        case 2:
            play_with_computer(board, size, players, ai_move);
            empty_board(board, size);
            break;
    
        case 3:
            break;

        default:
            printf("Invalid Choice!\n");
            break;
        }

        if (choice == 3)
            break;
        
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