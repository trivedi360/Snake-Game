#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int width = 20;
const int height = 20;

struct Point {
    int x, y;
};

enum Direction { UP, DOWN, LEFT, RIGHT };

class SnakeGame {
private:
    Point snake[100];
    Point food;
    int length;
    Direction dir;
    bool gameOver;

public:
    SnakeGame() {
        length = 1;
        snake[0].x = width / 2;
        snake[0].y = height / 2;
        food.x = rand() % width;
        food.y = rand() % height;
        dir = RIGHT;
        gameOver = false;
    }

    void Draw() {
        system("cls");
        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0)
                    cout << "#";
                if (i == snake[0].y && j == snake[0].x)
                    cout << "O";
                else if (i == food.y && j == food.x)
                    cout << "F";
                else {
                    bool print = false;
                    for (int k = 1; k < length; k++) {
                        if (snake[k].x == j && snake[k].y == i) {
                            cout << "o";
                            print = true;
                        }
                    }
                    if (!print)
                        cout << " ";
                }
                if (j == width - 1)
                    cout << "#";
            }
            cout << endl;
        }

        for (int i = 0; i < width + 2; i++)
            cout << "#";
        cout << endl;
    }

    void Input() {
        if (_kbhit()) {
            switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
            }
        }
    }

    void Logic() {
        Point prev = snake[0];
        Point prev2;
        snake[0] = prev;
        for (int i = 1; i < length; i++) {
            prev2 = snake[i];
            snake[i] = prev;
            prev = prev2;
        }

        switch (dir) {
        case LEFT:
            snake[0].x--;
            break;
        case RIGHT:
            snake[0].x++;
            break;
        case UP:
            snake[0].y--;
            break;
        case DOWN:
            snake[0].y++;
            break;
        }

        if (snake[0].x >= width || snake[0].x < 0 || snake[0].y >= height || snake[0].y < 0)
            gameOver = true;

        for (int i = 1; i < length; i++) {
            if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
                gameOver = true;
        }

        if (snake[0].x == food.x && snake[0].y == food.y) {
            length++;
            food.x = rand() % width;
            food.y = rand() % height;
        }
    }

    bool GetGameOver() {
        return gameOver;
    }
};

int main() {
    SnakeGame game;

    while (!game.GetGameOver()) {
        game.Draw();
        game.Input();
        game.Logic();
        Sleep(50); // Adjust speed
    }

    cout << "Game Over!" << endl;

    return 0;
}
