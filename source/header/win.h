#pragma once

#include <windows.h>

inline void setCursorPos(int x, int y)
// ������\������ꏊ�����߂�֐�
{
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hCons, pos);
}

inline bool isKeyPressed(int key)
// �������ꂽ�L�[�̔�����s���֐�
{
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}