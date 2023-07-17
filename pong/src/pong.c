#include <stdio.h>
int weidth_field = 80;  // ширина поля X
int height_field = 25;  // высота поля Y
int raketka_left, raketka_leftCenter, raketka_left1, raketka_left2;  // координаты левой ракетки
int raketka_right, raketka_rightCenter, raketka_right1, raketka_right2;  // координаты правой ракетки
int exit_game = 0;
char raketka = '|';
char ball = '@';
int ballX, ballY, directionBallX, directionBallY;  // координаты и нравление мяча
int score_left = 0;  // счёт левого игрока
int score_right = 0;  // счёт правого игрока
char key;
int raketki(int a, int b);
int ballXY(int a, int b);
int keys(int a);
int draw_frame(int a, int b);
int main(void) {
    raketki(height_field, weidth_field);
    ballXY(weidth_field, height_field);
    printf("\033c");
    while (score_left < 21 && score_right < 21 && exit_game < 1) {
        keys(key);
        if (ballX == raketka_right - 1 && (ballY == raketka_rightCenter ||
                    ballY == raketka_right1 || ballY == raketka_right2)) {  // проверка по оси X
            directionBallX *= -1;
            printf("\a");  // звук удара
        } else if (ballX == raketka_left + 1 && (ballY == raketka_leftCenter ||
                    ballY == raketka_left1 || ballY == raketka_left2)) {  // проверка по оси X
            directionBallX *= -1;
            printf("\a");
        } else if (ballX ==  weidth_field + 1) {  // реализация потери шарика у правого игрока
            score_left++;
            ballX = weidth_field / 2;
            ballY = height_field / 2 + 1;
            directionBallY = 1;
        } else if (ballX == 0) {  // реализация потери шарика у правого игрока
            score_right++;
            ballX = weidth_field / 2;
            ballY = height_field / 2 + 1;
            directionBallY = -1;
        }
        if (ballY == 1 || ballY == height_field)  // Проверка по оси Y
            directionBallY *= -1;
        printf("                                     P O N G\n");
        printf("                        Левый игрок: %.2d | Правый игрок %.2d\n", score_left, score_right);
        for (int y = 0; y <= height_field + 1; y++) {  // высота + рамка
            for (int x = 0; x <= weidth_field + 1; x++) {  // ширина + рамка
                draw_frame(x, y);
            }
        }
        printf("\n");
        printf("A - Z                         - Клавиши управления -                         K - M\n");
        printf("\n");
        printf("Для победы наберит 21 очко.    Для выхода из программы нажмите q :-)\n");
        printf("\n");
        printf("                                - GOOD LUCK !!!! -                                \n");
        scanf("%c", &key);
        ballX += directionBallX;
        ballY += directionBallY;
        printf("\033c");
    }
    if (score_right == 21) {
        printf("\033c");
        printf("Игрок справа победил\n");
        return 0;
    } else if (score_left == 21) {
        printf("\033c");
        printf("Игрок слева победил\n");
        return 0;
    } else if (exit_game == 0) {
        printf("\033c");
        return 0;
    }
}
int raketki(int a, int b) {  // принимаем высоту поля и ширину
    raketka_left = 2;
    raketka_right = b - 1;
    raketka_rightCenter = a / 2 + 1;
    raketka_right1 = raketka_rightCenter - 1;
    raketka_right2 = raketka_rightCenter + 1;
    raketka_leftCenter = a / 2 + 1;
    raketka_left1 = raketka_leftCenter - 1;
    raketka_left2 = raketka_leftCenter + 1;
    return 0;
}
int ballXY(int a, int b) {
    ballX = a / 2;
    ballY = b / 2 + 1;
    directionBallX = -1;
    directionBallY = 1;
    return 0;
}
int keys(int a) {
    if (a == 97 && raketka_left1 != 1) {  // движение левой вниз
        raketka_leftCenter--;
        raketka_left2 = raketka_leftCenter + 1;
        raketka_left1 = raketka_leftCenter - 1;
    } else if (a == 122 && raketka_left2 != height_field) {
        raketka_leftCenter++;
        raketka_left2 = raketka_leftCenter + 1;
        raketka_left1 = raketka_leftCenter - 1;
    } else if (a == 107 && raketka_right1 != 1) {
        raketka_rightCenter--;
        raketka_right2 = raketka_rightCenter + 1;
        raketka_right1 = raketka_rightCenter - 1;
    } else if (a == 109 && raketka_right2 != height_field) {
        raketka_rightCenter++;
        raketka_right2 = raketka_rightCenter + 1;
        raketka_right1 = raketka_rightCenter - 1;
    } else if (a == 113) {  // выход по q
        exit_game = 1;
    } else {
        return 0;
    }
    return 0;
}
int draw_frame(int a, int b) {
    if (b == 0 || b == height_field + 1) {
        if (a == weidth_field + 1)
            printf("#\n");
        else
            printf("#");
    } else {
        if (a == 0)
        printf("#");
        else if (a == weidth_field +1 )
            printf("#\n");
        else if (raketka_left == a && (raketka_left2 == b || raketka_left1 == b || raketka_leftCenter == b))
            printf("\033[1;32m%c\033[0m", raketka);
        else if (raketka_right == a && (raketka_right2 == b ||
        raketka_right1 == b || raketka_rightCenter == b))
            printf("\033[1;34m%c\033[0m", raketka);
        else if (a == ballX && b == ballY)
            printf("\033[1;33m%c\033[0m", ball);
        else if (a == (weidth_field/2))
            printf("|");
        else
            printf(" ");
    }
    return 0;
}
