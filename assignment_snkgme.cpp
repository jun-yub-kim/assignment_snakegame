#include <iostream>

#include <conio.h>
/*

����Ű �Է¿� ���� ������ȯ�� �ϴ� ������ ����� �ֱ� ���ؼ� conio �Լ��� windows.h �� ����Ǿ�� �Ѵ�.
����, getch �Լ� , kbhit �Լ��� ���ȴ�.



conio.h : �Է��� �־�����, �������� �Ǵ��ϴ� �Լ�
coni.h������ kbhit�̶�� �Լ��� �����Ѵ�. �̴� ���ۿ� ���� ������ 1, ������ 0�� �����ϴµ�.
�Ѹ���� �Է��� �־�����, �������� �Ǵ��ϴ� �Լ��̴�.
getch()�Լ��� �����Ѵ�. �̴� ���ۿ� �ִ� ���� �������� ������ �Ѵ�.
kbhit ==1  -> getch()  �̷� ������ ����ϸ� �� �� ����.
��ó : https://monny.tistory.com/5

*/


#include <windows.h>
/*
system("cls")�� sleep()�Լ��� ����ϱ� ���� �������
cls : ���ӿ����� ����ϴ� �� �ϵ�
sleep : �����ð� �����ϴ� �Լ�
��, ���̵��� �ö󰣴ٸ�, sleep�Լ��� Ÿ��Ʈ�ϰ� �Ͽ�, ���̵��� ��ư� �ؾ� ��
*/
#include <time.h> /*
���� �������� �����ϱ� ���� �������
*/
using namespace std;
bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
char recent = 'm';
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN }; // left,right,up,down �̶�� Ű�� �����ϱ� ���� ����
eDirecton dir; // �� ������ dir��� ������ �ϳ� �������.
void Setup()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width; // X��ǥ�� width�� �Ѿ������ �ȵǱ� ������ % width�� ����, �غκе� ��������
    fruitY = rand() % height;
    score = 0;
}
void Draw() // �Է� , ����Ű������ �����ϴ� ���������� ����. �׳� �̸� ���� ¥�α� ���� �Լ��� ��
{
    system("cls"); // �� ������ ������, ��Ӱ���ؼ� �ܼ�ȭ�鿡 ������ũ ���� â�� ������
    cout << endl;
    cout << " "; // �� ���� ǥ�õǴ� �� ����
    for (int i = 0; i < width + 2; i++)
        cout << "-"; // ���ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ�
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "��"; // ���ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ����ʺ�
            if (i == y && j == x)
                cout << "O"; // ���� ����� �� �Ӹ� ����
            else if (i == fruitY && j == fruitX)
                cout << "F"; // �ʿ� �����ϰ� Fruit ������
            else
            {
                bool print = false; //print��� bool �Լ� ����, ���� �̸� false�� �ʱ�ȭ
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
                cout << "��"; // �����ʺ������ʺ������ʺ������ʺ������ʺ������ʺ������ʺ������ʺ������ʺ������ʺ������ʺ������ʺ������ʺ�
        }
        cout << endl;
    }

    cout << " ";
    for (int i = 0; i < width + 2; i++)
        cout << "-"; // �Ʒ��ʺ��Ʒ��ʺ��Ʒ��ʺ��Ʒ��ʺ��Ʒ��ʺ��Ʒ��ʺ��Ʒ��ʺ��Ʒ��ʺ��Ʒ��ʺ��Ʒ��ʺ��Ʒ��ʺ��Ʒ��ʺ��Ʒ��ʺ��Ʒ��ʺ��Ʒ��ʺ�
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
    while (!gameOver) // ���ӿ����� ���� �ʴ� ��, ���� �Լ����� ���ʴ�� �����Ѵ�.
    {
        Draw();
        Input();
        Logic();
        Sleep(100); //sleep(10);
    }
    return 0;
}