#include "header/food.h"

Food::Food(const int width, const int height, const int max)
	: _width(width)
	, _height(height)
	, _maxFoods(max)
{}

void Food::init()
// 初期化関数
{
	// エサの場所を格納する配列の要素を全て削除
	_foods.clear();
}

void Food::add(int n)
// エサをn個フィールドに追加する関数
{
	if ((int)_foods.size() < _maxFoods) {
		for (int i = 0; i < n; i++) {

			// 場所の選択(ランダム)
			int x = rand() % (_width - 2) + 1;
			int y = rand() % (_height - 4) + 2;

			// エサ追加
			_foods.push_back(location(x, y));
		}
	}
}

vector<location> Food::getFoods()
{
	return _foods;
}

void Food::setFoods(vector<location>& foods)
{
	_foods = foods;
}