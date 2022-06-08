#include "header/print.h"

Print::Print(const int width, const int height)
    : _width(width)
    , _height(height)
{}

void Print::setColor(int color)
// �����F�̎w����s���֐�
{
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD attr = 0;
    if (color & INTENSITY)
        attr |= FOREGROUND_INTENSITY;
    if (color & RED_MASK)
        attr |= FOREGROUND_RED;
    if (color & GREEN_MASK)
        attr |= FOREGROUND_GREEN;
    if (color & BLUE_MASK)
        attr |= FOREGROUND_BLUE;
    SetConsoleTextAttribute(hCons, attr);
}

void Print::setColor(int frontColor, int backColor)
// �����F�Ɣw�i�F�̎w����s���֐�
{
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
    WORD attr = 0;

    if (frontColor & INTENSITY)
        attr |= FOREGROUND_INTENSITY;
    if (frontColor & RED_MASK)
        attr |= FOREGROUND_RED;
    if (frontColor & GREEN_MASK)
        attr |= FOREGROUND_GREEN;
    if (frontColor & BLUE_MASK)
        attr |= FOREGROUND_BLUE;

    if (backColor & INTENSITY)
        attr |= BACKGROUND_INTENSITY;
    if (backColor & RED_MASK)
        attr |= BACKGROUND_RED;
    if (backColor & GREEN_MASK)
        attr |= BACKGROUND_GREEN;
    if (backColor & BLUE_MASK)
        attr |= BACKGROUND_BLUE;
    SetConsoleTextAttribute(hCons, attr);
}

void Print::field()
// �t�B�[���h�̕`����s���֐�
{
    // �O��(��)
    setColor(YELLOW, YELLOW);
    setCursorPos(0, 1);
    for (int x = 0; x < _width; x++) {
        cout << " ";
    }

    // �O��(���E)
    for (int y = 2; y < _height - 2; y++) {
        // ��
        setCursorPos(0, y);
        cout << " ";

        // �E
        setCursorPos(_width - 1, y);
        cout << " ";
    }

    // �O��(��)
    setCursorPos(0, _height - 2);
    for (int x = 0; x < _width; x++) {
        cout << " ";
    }

    // �t�B�[���h����
    setColor(YELLOW, BLACK);
    for (int y = 0; y < _height - 4; y++) {
        setCursorPos(1, y + 2);
        for (int x = 0; x < _width - 2; x++) {
            cout << " ";
        }
    }

    // �������Ԃƃw�r�̒����̕���
    setCursorPos(0, 0);
    for (int x = 0; x < _width; x++) {
        cout << " ";
    }

    // �������b�Z�[�W����
    setCursorPos(0, _height - 1);
    for (int x = 0; x < _width; x++) {
        cout << " ";
    }

    // �g���C���b�Z�[�W����
    setCursorPos(0, _height);
    for (int x = 0; x < _width; x++) {
        cout << " ";
    }
}

void Print::snakeLength(int length1, int length2, int color1, int color2)
// �w�r�̒�����`�悷��֐�
{
    // player1
    setColor(color1);
    setCursorPos(0, 0);
    cout << "Length:";
    cout.width(2);
    cout << length1;

    // player2
    setColor(color2);
    setCursorPos(_width - 9, 0);
    cout << "Length:";
    cout.width(2);
    cout << length2;
}

void Print::time(int limitTime)
// �������Ԃ�`�悷��֐�
{
    setColor(WHITE);
    setCursorPos(_width / 2 - 2, 0);
    cout.width(3);
    cout << limitTime;
}

void Print::foods(const vector<location>& foods)
// �G�T��`�悷��֐�
{
    setColor(GREEN);
    for (int i = 0; i < (int)foods.size(); i++) {
        setCursorPos(foods[i].first, foods[i].second);
        cout << "*";
    }
}

void Print::snake(const deque<location>& snake, int color)
// �w�r��`�悷��֐�
{
    // ���̂̕`��
    setColor(color);
    for (int i = 1; i < (int)snake.size(); i++) {
        setCursorPos(snake[i].first, snake[i].second);
        cout << "o";

    }

    // ���̕`��
    setCursorPos(snake[0].first, snake[0].second);
    cout << "x";
}

void Print::poisons(const vector<location>& poisons, int color)
// �ł�`�悷��֐�
{
    setColor(color);
    for (int i = 0; i < (int)poisons.size(); i++) {
        setCursorPos(poisons[i].first, poisons[i].second);
        cout << 'X';
    }
}

void Print::rule()
// ���[����`�悷��֐�
{

    // �i��
    int y = 0;

    // �^�C�g��
    setColor(WHITE);
    setCursorPos(_width + 1, ++y);
    cout << "[Viper Game]";

    // ��������
    setCursorPos(_width + 1, ++++y);
    cout << "Win conditions";

    setCursorPos(_width + 1, ++y);
    cout << "- Make your length 20 by eating food(*)";

    setCursorPos(_width + 1, ++y);
    cout << "- Longer than opponent after time limit";

    // ��������
    setCursorPos(_width + 1, ++++y);
    cout << "Lose conditions";

    setCursorPos(_width + 1, ++y);
    cout << "- Collide";
    setCursorPos(_width + 5, ++y);
    cout << "with Opponent (xoo)";
    setCursorPos(_width + 5, ++y);
    cout << "with Opponent poison (X)";
    setCursorPos(_width + 5, ++y);
    cout << "with Wall (��)";
    setCursorPos(_width + 5, ++y);
    cout << "with Myself (oo)";

    // ������@
    setCursorPos(_width + 1, ++++y);
    cout << "Control";

    setCursorPos(_width + 1, ++y);
    cout << "- Player1";
    setCursorPos(_width + 2, ++y);
    cout << "- Move: Up[W] Down[S] Left[A] Right[D]";
    setCursorPos(_width + 2, ++y);
    cout << "- Poison: Fire[F] Stop[C]";

    setCursorPos(_width + 1, ++++y);
    cout << "- Player2";
    setCursorPos(_width + 2, ++y);
    cout << "- Move: Up[I] Down[K] Left[J] Right[L]";
    setCursorPos(_width + 2, ++y);
    cout << "- Poison: Fire[H] Stop[N]";
}

void Print::startMessage()
{
    setColor(WHITE);
    setCursorPos(_width / 2 - 13, _height / 2);
    cout << "Press [S] and [K] to start!!";
}

void Print::judgeMessage(string msg)
{
    setColor(WHITE);
    setCursorPos(0, _height - 1);
    cout << msg;
}

void Print::restartMessage()
{
    setColor(WHITE);
    setCursorPos(0, _height);
    cout << "try again ?(Y/N)";
}