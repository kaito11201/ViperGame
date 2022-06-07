#include "header/food.h"

Food::Food(const int width, const int height, const int max)
	: _width(width)
	, _height(height)
	, _maxFoods(max)
{}

void Food::init()
// �������֐�
{
	// �G�T�̏ꏊ���i�[����z��̗v�f��S�č폜
	_foods.clear();
}

void Food::add(int n)
// �G�T��n�t�B�[���h�ɒǉ�����֐�
{
	if ((int)_foods.size() < _maxFoods) {
		for (int i = 0; i < n; i++) {

			// �ꏊ�̑I��(�����_��)
			int x = rand() % (_width - 2) + 1;
			int y = rand() % (_height - 4) + 2;

			// �G�T�ǉ�
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