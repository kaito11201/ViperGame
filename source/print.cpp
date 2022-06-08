#include "header/print.h"

Print::Print(const int width, const int height)
    : _width(width)
    , _height(height)
{}

void Print::setColor(int color)
// 文字色の指定を行う関数
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
// 文字色と背景色の指定を行う関数
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
// フィールドの描画を行う関数
{
    // 外周(上)
    setColor(YELLOW, YELLOW);
    setCursorPos(0, 1);
    for (int x = 0; x < _width; x++) {
        cout << " ";
    }

    // 外周(左右)
    for (int y = 2; y < _height - 2; y++) {
        // 左
        setCursorPos(0, y);
        cout << " ";

        // 右
        setCursorPos(_width - 1, y);
        cout << " ";
    }

    // 外周(下)
    setCursorPos(0, _height - 2);
    for (int x = 0; x < _width; x++) {
        cout << " ";
    }

    // フィールド部分
    setColor(YELLOW, BLACK);
    for (int y = 0; y < _height - 4; y++) {
        setCursorPos(1, y + 2);
        for (int x = 0; x < _width - 2; x++) {
            cout << " ";
        }
    }

    // 制限時間とヘビの長さの部分
    setCursorPos(0, 0);
    for (int x = 0; x < _width; x++) {
        cout << " ";
    }

    // 勝利メッセージ部分
    setCursorPos(0, _height - 1);
    for (int x = 0; x < _width; x++) {
        cout << " ";
    }

    // トライメッセージ部分
    setCursorPos(0, _height);
    for (int x = 0; x < _width; x++) {
        cout << " ";
    }
}

void Print::snakeLength(int length1, int length2, int color1, int color2)
// ヘビの長さを描画する関数
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
// 制限時間を描画する関数
{
    setColor(WHITE);
    setCursorPos(_width / 2 - 2, 0);
    cout.width(3);
    cout << limitTime;
}

void Print::foods(const vector<location>& foods)
// エサを描画する関数
{
    setColor(GREEN);
    for (int i = 0; i < (int)foods.size(); i++) {
        setCursorPos(foods[i].first, foods[i].second);
        cout << "*";
    }
}

void Print::snake(const deque<location>& snake, int color)
// ヘビを描画する関数
{
    // 胴体の描画
    setColor(color);
    for (int i = 1; i < (int)snake.size(); i++) {
        setCursorPos(snake[i].first, snake[i].second);
        cout << "o";

    }

    // 頭の描画
    setCursorPos(snake[0].first, snake[0].second);
    cout << "x";
}

void Print::poisons(const vector<location>& poisons, int color)
// 毒を描画する関数
{
    setColor(color);
    for (int i = 0; i < (int)poisons.size(); i++) {
        setCursorPos(poisons[i].first, poisons[i].second);
        cout << 'X';
    }
}

void Print::rule()
// ルールを描画する関数
{

    // 段数
    int y = 0;

    // タイトル
    setColor(WHITE);
    setCursorPos(_width + 1, ++y);
    cout << "[Viper Game]";

    // 勝利条件
    setCursorPos(_width + 1, ++++y);
    cout << "Win conditions";

    setCursorPos(_width + 1, ++y);
    cout << "- Make your length 20 by eating food(*)";

    setCursorPos(_width + 1, ++y);
    cout << "- Longer than opponent after time limit";

    // 負け条件
    setCursorPos(_width + 1, ++++y);
    cout << "Lose conditions";

    setCursorPos(_width + 1, ++y);
    cout << "- Collide";
    setCursorPos(_width + 5, ++y);
    cout << "with Opponent (xoo)";
    setCursorPos(_width + 5, ++y);
    cout << "with Opponent poison (X)";
    setCursorPos(_width + 5, ++y);
    cout << "with Wall (■)";
    setCursorPos(_width + 5, ++y);
    cout << "with Myself (oo)";

    // 操作方法
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