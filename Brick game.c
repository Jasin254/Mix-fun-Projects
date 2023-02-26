#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define PADDLE_LENGTH 10
#define PADDLE_HEIGHT 1
#define BALL_SIZE 1
#define BRICK_ROWS 5
#define BRICK_COLS 10
#define BRICK_WIDTH 7
#define BRICK_HEIGHT 3

int bricks[BRICK_ROWS][BRICK_COLS];
int paddle_x, ball_x, ball_y;
int ball_dx, ball_dy, ball_speed;

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void drawBrick(int x, int y) {
    int i, j;
    for (i = 0; i < BRICK_HEIGHT; i++) {
        gotoxy(x, y + i);
        for (j = 0; j < BRICK_WIDTH; j++) {
            printf("*");
        }
    }
}

void drawBricks() {
    int i, j;
    for (i = 0; i < BRICK_ROWS; i++) {
        for (j = 0; j < BRICK_COLS; j++) {
            if (bricks[i][j] == 1) {
                drawBrick(j * BRICK_WIDTH, i * BRICK_HEIGHT);
            }
        }
    }
}

void initBricks() {
    int i, j;
    for (i = 0; i < BRICK_ROWS; i++) {
        for (j = 0; j < BRICK_COLS; j++) {
            bricks[i][j] = 1;
        }
    }
}

void drawPaddle() {
    int i;
    for (i = 0; i < PADDLE_LENGTH; i++) {
        gotoxy(paddle_x + i, SCREEN_HEIGHT - 1);
        printf("=");
    }
}

void erasePaddle() {
    int i;
    for (i = 0; i < PADDLE_LENGTH; i++) {
        gotoxy(paddle_x + i, SCREEN_HEIGHT - 1);
        printf(" ");
    }
}

void movePaddle() {
    if (_kbhit()) {
        char ch = _getch();
        erasePaddle();
        if (ch == 'a' && paddle_x > 0) {
            paddle_x--;
        }
        if (ch == 'd' && paddle_x < SCREEN_WIDTH - PADDLE_LENGTH) {
            paddle_x++;
        }
        drawPaddle();
    }
}

void drawBall() {
    gotoxy(ball_x, ball_y);
    printf("O");
}

void eraseBall() {
    gotoxy(ball_x, ball_y);
    printf(" ");
}

void resetBall() {
    ball_x = SCREEN_WIDTH / 2;
    ball_y = SCREEN_HEIGHT - 2;
    ball_dx = 1;
    ball_dy = -1;
    ball_speed = 10;
}

void moveBall() {
    eraseBall();
    ball_x += ball_dx;
    ball_y += ball_dy;
    if (ball_x <= 0 || ball_x >= SCREEN_WIDTH - BALL_SIZE) {
        ball_dx = -ball_dx;
    }
    if (ball_y <= 0) {
        ball_dy = -ball_dy;
    }
    if (ball_y >= SCREEN_HEIGHT - PADDLE_HEIGHT - BALL_SIZE && ball_x >= paddle_x && ball_x < paddle_x + PADDLE_LENGTH) {
        ball_dy = -ball_dy;
    }
    drawBall();
}

int checkCollision() {
int i, j;
for (i = 0; i < BRICK_ROWS; i++) {
for (j = 0; j < BRICK_COLS; j++) {
if (bricks[i][j] == 1) {
int brick_x = j * BRICK_WIDTH;
int brick_y = i * BRICK_HEIGHT;
if (ball_x >= brick_x && ball_x < brick_x + BRICK_WIDTH && ball_y >= brick_y && ball_y < brick_y + BRICK_HEIGHT) {
bricks[i][j] = 0;
return 1;
}
}
}
}
return 0;
}

void drawGameOver() {
gotoxy(SCREEN_WIDTH / 2 - 5, SCREEN_HEIGHT / 2);
printf("GAME OVER");
}

void drawWin() {
gotoxy(SCREEN_WIDTH / 2 - 3, SCREEN_HEIGHT / 2);
printf("YOU WIN");
}

int main() {
paddle_x = SCREEN_WIDTH / 2 - PADDLE_LENGTH / 2;
resetBall();
initBricks();
while (1) {
    drawBricks();
    drawPaddle();
    movePaddle();
    moveBall();
    if (checkCollision()) {
        ball_dy = -ball_dy;
    }
    if (ball_y > SCREEN_HEIGHT - PADDLE_HEIGHT - BALL_SIZE) {
        drawGameOver();
        break;
    }
    int i, j, count = 0;
    for (i = 0; i < BRICK_ROWS; i++) {
        for (j = 0; j < BRICK_COLS; j++) {
            if (bricks[i][j] == 0) {
                count++;
            }
        }
    }
    if (count == BRICK_ROWS * BRICK_COLS) {
        drawWin();
        break;
    }
    Sleep(1000 / ball_speed);
}

return 0;
