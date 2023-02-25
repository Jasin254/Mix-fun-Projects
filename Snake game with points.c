#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20

int score = 0;

typedef struct {
    int x;
    int y;
} point;

point snake[100];
int length = 5;
int direction = 0;
point fruit;

void setup() {
    srand(time(NULL));
    snake[0].x = WIDTH/2;
    snake[0].y = HEIGHT/2;
    for(int i=1; i<length; i++) {
        snake[i].x = snake[i-1].x + 1;
        snake[i].y = snake[i-1].y;
    }
    fruit.x = rand() % WIDTH;
    fruit.y = rand() % HEIGHT;
}

void draw() {
    system("cls");
    for(int y=0; y<HEIGHT; y++) {
        for(int x=0; x<WIDTH; x++) {
            if(x == fruit.x && y == fruit.y) {
                printf("F");
            } else if(x == snake[0].x && y == snake[0].y) {
                printf("O");
            } else {
                int print = 0;
                for(int i=1; i<length; i++) {
                    if(x == snake[i].x && y == snake[i].y) {
                        printf("o");
                        print = 1;
                        break;
                    }
                }
                if(!print) {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void input() {
    if(_kbhit()) {
        switch(_getch()) {
            case 'a':
                if(direction != 2) {
                    direction = 1;
                }
                break;
            case 'd':
                if(direction != 1) {
                    direction = 2;
                }
                break;
            case 'w':
                if(direction != 4) {
                    direction = 3;
                }
                break;
            case 's':
                if(direction != 3) {
                    direction = 4;
                }
                break;
        }
    }
}

void logic() {
    point prev = snake[0];
    point prev2;
    snake[0].y--;
    if(snake[0].y < 0) {
        snake[0].y = HEIGHT-1;
    }
    for(int i=1; i<length; i++) {
        prev2 = snake[i];
        snake[i] = prev;
        prev = prev2;
    }
    switch(direction) {
        case 1:
            snake[0].x--;
            if(snake[0].x < 0) {
                snake[0].x = WIDTH-1;
            }
            break;
        case 2:
            snake[0].x++;
            if(snake[0].x >= WIDTH) {
                snake[0].x = 0;
            }
            break;
        case 3:
            snake[0].y--;
            if(snake[0].y < 0) {
                snake[0].y = HEIGHT-1;
            }
            break;
        case 4:
            snake[0].y++;
            if(snake[0].y >= HEIGHT) {
                snake[0].y = 0;
            }
            break;
    }
    if(snake[0].x == fruit.x && snake[0].y == fruit.y) {
        length++;
        score++;
        fruit.x = rand() % WIDTH
