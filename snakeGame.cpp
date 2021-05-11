#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

// global variables_________
bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;
// _________________________

// Main 4 functions every time creating a game:> setup draw input logic

void Setup()
{
    // Game Startup
    gameOver = false;
    dir = STOP;

    x = width / 2;
    y = height / 2;

    fruitX = rand() % width;
    fruitY = rand() % height;

    score = 0;
}

void Draw()
{
    system("cls");

    for (int i = 0; i < width; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                cout << "#";
            }
            else if (j == width - 1)
            {
                cout << "#";
            }
            else if (i == y && j == x)
            {
                cout << "O";
            }
            else if (i == fruitY && j == fruitX)
            {
                cout << "f";
            }
            else
            {
                bool print = false;
                for (int k=0; k< nTail; k++){
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width; i++)
        cout << "#";

    cout << endl;
    cout << "SCORE:" << score << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            if(dir == RIGHT){
                break;
            }
            else{
                dir = LEFT;
            }
            break;
        case 's':
            if (dir == UP){
                break;
            }
            else{
                dir = DOWN;
            }
            break;
        case 'd':
            if(dir == LEFT){
                break;
            }
            else{
                dir = RIGHT;
            }
            break;
        case 'w':
            if(dir == DOWN){
                break;
            }
            else{
                dir = UP;
            }
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    int prev2X, prev2Y;
    
    int prevX = tailX[0];
    int prevY = tailY[0];

    tailX[0] = x;
    tailY[0] = y;
    
    for (int i =1; i<nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];

        tailX[i] = prevX;
        tailY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case DOWN:
        y++;
        break;
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    default:
        break;
    }

    if (x < 0 || x > width || y < 0 || y > height)
    {
        gameOver = true;
    }

    for (int i=0; i<nTail; i++){
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
        }
    }

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(10);
    }
    return 0;
}

// Thank you https://www.youtube.com/watch?v=E_-lMZDi7Uw for amazing tutorial