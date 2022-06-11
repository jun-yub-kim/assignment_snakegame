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
int Fruit_time = 0;
int key_count = 0;
int Poison_time = 0;
bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, poisonX, poisonY, score;
int tailX[100], tailY[100];
int nTail;
char recent = 'm';
int gate1X, gate1Y, gate2X, gate2Y; // gate x y 좌표
int exitX, exitY;                   // exit 좌표
int gateTime = 0;
enum eDirecton
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};             // left,right,up,down 이라는 키를 정의하기 위한 구문
eDirecton dir; // 이 구문을 dir라는 변수로 하나 만들었다.

char map[20][40] = {
    '2', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '2',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '1', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '1',
    '2', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '2' };

void gate(int x1, int y1, int x2, int y2)
{ // gate 좌표 생성
    map[y1][x1] = '1';
    map[y2][x2] = '1';
    srand((unsigned)time(NULL));
    while (1)
    {
        gate1X = (rand() % width); //랜덤으로 gate1의 x,y좌표 설정
        gate1Y = (rand() % height);
        if (map[gate1Y][gate1X] == '1')
        {                              //난수가 wall이 될때까지 실행함
            map[gate1Y][gate1X] = '3'; // wall이면 gate로 변경
            break;
        }
    }
    srand((unsigned)time(NULL));
    while (1)
    {
        gate2X = (rand() % width); //랜덤으로 gate2의 x,y좌표 설정
        gate2Y = (rand() % height);
        if (map[gate2Y][gate2X] == '1')
        {
            map[gate2Y][gate2X] = '3';
            break;
        }
    }
}

void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;                       //뱀의 머리 X좌표
    y = height / 2;                      //뱀의 머리 Y좌표
    fruitX = 1 + (rand() % (width - 2)); // Fruit의 X좌표가 width를 넘어버리면 안되기 때문에 % width를 해줌, 밑부분도 마찬가지
    fruitY = 1 + (rand() % (height - 2));
    poisonX = 1 + (rand() % (width - 2)); // Fruit과 마찬가지로 점수를 깎아먹는 아이템 생성
    poisonY = 1 + (rand() % (height - 2));
    // 이 부분에, Fruit 생성이 3초가 넘으면, 새로운 Fruit 생성해야됨
    score = 0;
    gate(1, 0, 1, 0);
}
void Draw() // 입력 , 방향키쪽으로 전진하는 구문같은거 없음. 그냥 미리 판을 짜두기 위한 함수일 뿐
{
    system("cls"); // 이 구문이 없으면, 계속계속해서 콘솔화면에 스네이크 게임 창이 생성됨

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == y && j == x)
            {
                cout << "0";
            }
            else if (i == fruitY && j == fruitX)
                cout << "F"; // 맵에 랜덤하게 Fruit 생성함
            else if (i == poisonY && j == poisonX)
                cout << "P"; // 맵에 랜덤하게 Fruit 생성함
            else if (i == gate1Y && j == gate1X)
                cout << "G";
            else if (i == gate2Y && j == gate2X)
                cout << "G";
            else
            {
                bool print = false; // print라는 bool 함수 선언, 이후 이를 false로 초기화
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << map[i][j];
            }
        }
        cout << endl;
    }

    cout << "X";
    cout << endl;
    cout << " Score:" << score << endl;
}

void Input()
{
    if (_kbhit())
    {
        int key = _getch();
        if (key == 224 || key == 0)
        {
            key_count++;
            if (key_count < 2)
            {
                nTail = nTail + 3;
            }
            key = _getch();
            if (key == 72 && recent != 's')
            {
                dir = UP;
                recent = 'w';
            }
            if (key == 75 && recent != 'd')
            {
                dir = LEFT;
                recent = 'a';
            }
            if (key == 77 && recent != 'a')
            {
                dir = RIGHT;
                recent = 'd';
            }
            if (key == 80 && recent != 'w')
            {
                dir = DOWN;
                recent = 's';
            }
        }
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

    if (map[y][x] == 49)
    { //벽을 치면 죽는 구문 (수정됨)
        gameOver = true;
    }

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y) // 머리가 꼬리를 먹으면 죽는 구문
            gameOver = true;

    if (key_count > 2)
    { //꼬리가 3개 미만이면 죽는 구문
        if (nTail < 3)
        {
            gameOver = true;
        }
    }

    if (x == fruitX && y == fruitY) // 머리가 Fruit을 먹는 구문
    {
        srand(time(0));
        score += 10;
        fruitX = 1 + (rand() % (width - 2));
        fruitY = 1 + (rand() % (height - 2));
        nTail++;
        Fruit_time = 0; // 머리가 Fruit을 먹은 후엔, Fruit 리스폰 시간 0으로 초기화 함
    }
    else if (Fruit_time > 35)
    { // 과일이 생성된 후 5초 이후면 Fruit 의 위치가 변경됨
        Fruit_time = 0;
        fruitX = 1 + (rand() % (width - 2));
        fruitY = 1 + (rand() % (height - 2));
    }

    if (x == poisonX && y == poisonY) // 머리가 Poison을 먹는 구문
    {
        srand(time(0));
        score -= 10;
        poisonX = 1 + (rand() % (width - 2));
        poisonY = 1 + (rand() % (height - 2));
        nTail--;
        Poison_time = 0;
    }

    else if (Poison_time > 35)
    { // 과일이 생성된 후 5초 이후면 Fruit 의 위치가 변경됨
        Poison_time = 0;
        poisonX = 1 + (rand() % (width - 2));
        poisonY = 1 + (rand() % (height - 2));
    }

    if (x == gate1X && y == gate1Y)
    {
        exitX = gate2X;
        exitY = gate2Y;

        if (exitX == 0)
        {
            x = exitX + 1;
            y = exitY;
            dir = RIGHT;
        }
        else if (exitX == 39)
        {
            x = exitX - 1;
            y = exitY;
            dir = LEFT;
        }
        else if (exitY == 0)
        {
            x = exitX;
            y = exitY + 1;
            dir = DOWN;
        }
        else if (exitY == 19)
        {
            x = exitX;
            y = exitY - 1;
            dir = UP;
        }
    }
    else if (x == gate2X && y == gate2Y)
    {
        exitX = gate1X;
        exitY = gate1Y;

        if (exitX == 0)
        {
            x = exitX + 1;
            y = exitY;
            dir = RIGHT;
        }
        else if (exitX == 39)
        {
            x = exitX - 1;
            y = exitY;
            dir = LEFT;
        }
        else if (exitY == 0)
        {
            x = exitX;
            y = exitY + 1;
            dir = DOWN;
        }
        else if (exitY == 19)
        {
            x = exitX;
            y = exitY - 1;
            dir = UP;
        }
    }

    if (gateTime > 70)
    { // gate가 생성된 후 10초 이후면 gate의 위치가 변경됨
        gate(gate1X, gate1Y, gate2X, gate2Y);
        gateTime = 0;
    }
}
int main()
{
    system("MODE con cols=50 lines=30"); // 콘솔 창 크기 지정해주는 구문
    Setup();
    while (!gameOver) // 게임오버가 되지 않는 한, 다음 함수들을 차례대로 실행한다.
    {
        Draw();
        Input();
        Logic();
        Sleep(100); // 지연율, 50이면 더 어렵고, 200이면 더 쉬워진다
        Fruit_time++;
        Poison_time++;
        gateTime++;
    }
    return 0;
}
