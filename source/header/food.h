#pragma once

#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> location;

class Food
	// エサクラス
{
public:
	Food(const int width, const int height, const int max);

	// 初期化関数
	void init();

	// n個のエサをフィールドに追加する関数
	void add(int n = 1);

	// メンバ変数の受け渡しを行う関数
	vector<location> getFoods();
	void setFoods(vector<location>& foods);

private:
	// フィールドの大きさ
	const int _width;
	const int _height;

	// エサの最大数
	const int _maxFoods;

	// エサの場所を保存する配列
	vector<location> _foods;
};