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
	// 描画クラス
{
public:
	Print(const int width, const int height);

	//色の指定と描画位置の指定
	void setColor(int color);
	void setColor(int frontColor, int backColor);

	//各オブジェクトの描画
	void field();
	void snakeLength(int length1, int length2, int color1, int color2);
	void time(int limitTime);
	void foods(const vector<location>& foods);
	void snake(const deque<location>& snake, int color);
	void poisons(const vector<location>& poison, int color);

	// ルールの描画
	void rule();

	// メッセージの描画
	void startMessage();
	void judgeMessage(string msg);
	void restartMessage();

private:
	// フィールドの大きさ
	const int _width;
	const int _height;
};