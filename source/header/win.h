#pragma once

#include <windows.h>

inline void setCursorPos(int x, int y)
// 文字を表示する場所を決める関数
{
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hCons, pos);
}

inline bool isKeyPressed(int key)
// 押下されたキーの判定を行う関数
{
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}