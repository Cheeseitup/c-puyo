#include <stdio.h>
#include <stdlib.h>
#define WIDTH 6
#define HEIGHT 12
#define COLOR_COUNT 4
#define MAGIC_OFFSET 16
#define MIN_POP 4

void print_board(char* board){
    for (int r = 0; r < HEIGHT; r++) {
        for (int c = 0; c < WIDTH; c++) {
            printf("%c ", board[r*WIDTH + c]);
        }
        printf("\n");
    }
}

int flood(char* board, int i, char color, int action){
    if(board[i] != color){
        return 0;
    }
    if(action == 0){
        board[i] = '_';
    }else{
        board[i] += action;
    }
    int count = 1;
    if(i >= WIDTH){
        count += flood(board, i - WIDTH, color, action);
    }
    if(i < WIDTH*HEIGHT - WIDTH){
        count += flood(board, i + WIDTH, color, action);
    }
    if(i%WIDTH >= 1){
        count += flood(board, i - 1, color, action);
    }
    if(i%WIDTH < WIDTH - 1){
        count += flood(board, i + 1, color, action);
    }
    return count;
}

void pop_groups(char* board){
    for (int i = 0; i < WIDTH*HEIGHT; i++) {
        if(board[i] != '_'){
            int out = flood(board, i, board[i], MAGIC_OFFSET);
            if(out >= MIN_POP){
                printf("Popping a group of %d\n", out);
                print_board(board);
                flood(board, i, board[i], 0);
            }else{
                printf("Not popping a group of %d\n", out);
                print_board(board);
                flood(board, i, board[i], -MAGIC_OFFSET);
            }
        }
    }
}

void gravitate(char* board){
    for (int c = 0; c < WIDTH; c++) {
        int stable = 1;
        for (int r = HEIGHT-1; r >= 0; --r) {
            if(stable){
                if(board[r*WIDTH + c] == '_'){
                    stable = 0;
                }
            }else{
                if(board[r*WIDTH + c] != '_'){
                    for (int rn = HEIGHT-1; rn > 0; --rn) {
                        if(board[rn*WIDTH + c] == '_'){
                            board[rn*WIDTH + c] = board[r*WIDTH + c];
                            board[r*WIDTH + c] = '_';
                            break;
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    srand(12);
    char board[WIDTH*HEIGHT];
    for (int i = 0; i < WIDTH*HEIGHT/2; i++) {
        board[i] = '_';
    }
    for (int i = WIDTH*HEIGHT/2; i < WIDTH*HEIGHT; i++) {
        board[i] = '1' + rand()%COLOR_COUNT;
    }
    printf("Init:\n");
    print_board(board);
    pop_groups(board);
    printf("Popped:\n");
    print_board(board);
    gravitate(board);
    printf("Gravity:\n");
    print_board(board);
    return 0;
}
