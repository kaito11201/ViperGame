#pragma once

#include <iostream>
#include <windows.h>
#include <vector>
#include <deque>
#include <string>

#include "win.h"
#include "color.h"

using namespace std;

typedef pair<int, int> location;

class Print
	// �`��N���X
{
public:
	Print(const int width, const int height);

	//�F�̎w��ƕ`��ʒu�̎w��
	void setColor(int color);
	void setColor(int frontColor, int backColor);

	//�e�I�u�W�F�N�g�̕`��
	void field();
	void snakeLength(int length1, int length2, int color1, int color2);
	void time(int limitTime);
	void foods(const vector<location>& foods);
	void snake(const deque<location>& snake, int color);
	void poisons(const vector<location>& poison, int color);

	// ���[���̕`��
	void rule();

	// ���b�Z�[�W�̕`��
	void startMessage();
	void judgeMessage(string msg);
	void restartMessage();

private:
	// �t�B�[���h�̑傫��
	const int _width;
	const int _height;
};