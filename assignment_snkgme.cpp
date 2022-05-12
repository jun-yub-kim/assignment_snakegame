#include <iostream>

#include <conio.h>
/*

방향키 입력에 따라 방향전환을 하는 구문을 만들어 주기 위해선 conio 함수와 windows.h 가 선언되어야 한다.
또한, getch 함수 , kbhit 함수가 사용된다.



conio.h : 입력이 있었는지, 없었는지 판단하는 함수
coni.h내에선 kbhit이라는 함수가 존재한다. 이는 버퍼에 값이 있으면 1, 없으면 0을 리턴하는데.
한마디로 입력이 있었는지, 없었는지 판단하는 함수이다.
getch()함수도 존재한다. 이는 버퍼에 있는 값을 꺼내오는 역할을 한다.
kbhit ==1  -> getch()  이런 식으로 사용하면 될 것 같다.
출처 : https://monny.tistory.com/5

*/


#include <windows.h>
/*
system("cls")와 sleep()함수를 사용하기 위한 헤더파일
cls : 게임오버시 출력하는 것 일듯
sleep : 지연시간 설정하는 함수
즉, 난이도가 올라간다면, sleep함수를 타이트하게 하여, 난이도를 어렵게 해야 함
*/
#include <time.h> /*
먹이 랜덤으로 스폰하기 위한 헤더파일
*/
using namespace std;
bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
char recent = 'm';
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN }; // left,right,up,down 이라는 키를 정의하기 위한 구문
eDirecton dir; // 이 구문을 dir라는 변수로 하나 만들었다.
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width; // X좌표가 width를 넘어버리면 안되기 때문에 % width를 해줌, 밑부분돔 ㅏ찬가지
    fruitY = rand() % height;
    score = 0;
}
void Draw() // 입력 , 방향키쪽으로 전진하는 구문같은거 없음. 그냥 미리 판을 짜두기 위한 함수일 뿐
{
    system("cls"); // 이 구문이 없으면, 계속계속해서 콘솔화면에 스네이크 게임 창이 생성됨
    cout << endl;
    cout << " "; // 맨 위에 표시되는 빈 공간
    for (int i = 0; i < width + 2; i++)
        cout << "-"; // 위쪽벽위쪽벽위쪽벽위쪽벽위쪽벽위쪽벽위쪽벽위쪽벽위쪽벽위쪽벽위쪽벽위쪽벽위쪽벽위쪽벽위쪽벽위쪽벽위쪽벽위쪽벽
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "ㅣ"; // 왼쪽벽왼쪽벽왼쪽벽왼쪽벽왼쪽벽왼쪽벽왼쪽벽왼쪽벽왼쪽벽왼쪽벽왼쪽벽왼쪽벽왼쪽벽왼쪽벽왼쪽벽왼쪽벽
            if (i == y && j == x)
                cout << "O"; // 맵의 가운데에 뱀 머리 설정
            else if (i == fruitY && j == fruitX)
                cout << "F"; // 맵에 랜덤하게 Fruit 생성함
            else
            {
                bool print = false; //print라는 bool 함수 선언, 이후 이를 false로 초기화
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "ㅣ"; // 오른쪽벽오른쪽벽오른쪽벽오른쪽벽오른쪽벽오른쪽벽오른쪽벽오른쪽벽오른쪽벽오른쪽벽오른쪽벽오른쪽벽오른쪽벽
        }
        cout << endl;
    }

    cout << " ";
    for (int i = 0; i < width + 2; i++)
        cout << "-"; // 아래쪽벽아래쪽벽아래쪽벽아래쪽벽아래쪽벽아래쪽벽아래쪽벽아래쪽벽아래쪽벽아래쪽벽아래쪽벽아래쪽벽아래쪽벽아래쪽벽아래쪽벽
    cout << endl;
    cout << " Score:" << score << endl;
}
void Input()
{
    if (_kbhit())
    {
        int key = _getch();
        if (key == 224 || key == 0) {
            key = _getch();
            if (key == 72 && recent != 's') {
                dir = UP;
                recent = 'w';
            }
            if (key == 75 && recent != 'd') {
                dir = LEFT;
                recent = 'a';
            }
            if (key == 77 && recent != 'a') {
                dir = RIGHT;
                recent = 'd';
            }
            if (key == 80 && recent != 'w') {
                dir = DOWN;
                recent = 's';
            }


            /*switch (key) {
            case 72:
                dir = UP;
                recent = 'w';
                break;
            case 75 :
                dir = LEFT;
                recent = 'a';
                break;
            case 77 :
                dir = RIGHT;
                recent = 'd';
                break;
            case 80 :
                dir = DOWN;
                recent = 's';
                break;
            default:
                break;
            }*/
        }
        /*switch (_getch())
        {


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
        default:
            break;
        }*/
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
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
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x > width || x < 0 || y > height || y < 0)
        gameOver = true;
    //if (x >= width) x = 0; else if (x < 0) x = width - 1;
    //if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY)
    {
        srand(time(0)); // Random seed value for rand based on time
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}
int main()
{
    system("MODE con cols=50 lines=30");
    Setup();
    while (!gameOver) // 게임오버가 되지 않는 한, 다음 함수들을 차례대로 실행한다.
    {
        Draw();
        Input();
        Logic();
        Sleep(100); //sleep(10);
    }
    return 0;
}