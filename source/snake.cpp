#include "header/snake.h"

Snake::Snake(const int width, const int height)
	: _width(width)
	, _height(height)
{}

void Snake::init(int x, int y)
// 初期化関数
{
	// 初期座標
	_pos.first = x;
	_pos.second = y;

	// 初期方向ベクトル
	_vector.first = 0;
	_vector.second = 1;

	// 初期ヘビの頭と胴体
	_snake.clear();
	_snake.push_front(location(x, y - 2));
	_snake.push_front(location(x, y - 1));
	_snake.push_front(location(x, y));

	// 毒の初期化
	_isAttacking = false;
	_poisons.clear();
}

void Snake::controller(char left, char down, char up, char right, char attackKey, char attackStopKey)
// ヘビを操作する関数
{
	//	方向転換
	if (isKeyPressed(left) && _isBody(-1, 0)) {
		_vector = location(-1, 0);
	}
	else if (isKeyPressed(down) && _isBody(0, 1)) {
		_vector = location(0, 1);
	}
	else if (isKeyPressed(up) && _isBody(0, -1)) {
		_vector = location(0, -1);
	}
	else if (isKeyPressed(right) && _isBody(1, 0)) {
		_vector = location(1, 0);
	}

	// 毒攻撃(発射)
	if (isKeyPressed(attackKey) && !_isAttacking && _snake.size() > 2) {
		attack();
		_isAttacking = true;
	}

	// 毒攻撃(毒を止める)
	if (isKeyPressed(attackStopKey) && _isAttacking) {
		_isAttacking = false;
	}

}

void Snake::move()
// 移動する関数
{
	// 進行方向に移動
	_pos.first += _vector.first;
	_pos.second += _vector.second;
	_snake.push_front(_pos);
}

void Snake::eat(vector<location>& foods)
// エサを食べる関数
{
	// ヘビの胴体を伸ばすか判定する変数
	bool isExtend = false;

	for (int i = (int)foods.size(); --i >= 0;) {

		// エサの座標とヘビの頭の座標が等しい
		if (foods[i].first == _pos.first && foods[i].second == _pos.second) {

			// エサを消去
			foods.erase(foods.begin() + i);

			// ビープ音
			cout << (char)0x07;

			isExtend = true;
		}
	}

	// ヘビの胴体を伸ばす
	_addBody(isExtend);
}

void Snake::attack()
{	// 毒の攻撃を行う関数

	// 胴体を短くする
	setCursorPos(_snake.back().first, _snake.back().second);
	cout << " ";
	_snake.pop_back();

	// 毒の進行方向
	_poisonVector.first = _vector.first;
	_poisonVector.second = _vector.second;

	// 毒の座標
	_poisons.push_back(location(_pos.first + _poisonVector.first,
		_pos.second + _poisonVector.second));
}

void Snake::poisonMove()
// 毒を飛ばす関数
{
	if (_isAttacking) {
		setCursorPos(_poisons.back().first, _poisons.back().second);
		cout << " ";

		_poisons.back().first += _poisonVector.first;
		_poisons.back().second += _poisonVector.second;

		// 壁に衝突
		int x = _poisons.back().first;
		int y = _poisons.back().second;

		if (x <= 1 || x >= _width - 2 || y <= 2 || y >= _height - 3) {
			_isAttacking = false;
		}
	}

}

bool Snake::isCollision(const deque<location>& enemy, const vector<location>& enemyPoison)
// 衝突判定を行う関数
{
	// ヘビの頭の座標
	int x = _snake[0].first;
	int y = _snake[0].second;

	// 壁に衝突
	if (x <= 0 || x >= _width - 1 || y <= 1 || y >= _height - 2) {
		return true;
	}

	// 胴体に衝突
	for (int i = 1; i < (int)_snake.size(); i++) {
		if (_snake[i].first == x && _snake[i].second == y) {
			return true;
		}
	}

	// 敵に衝突
	for (int i = 0; i < (int)enemy.size(); i++) {
		if (enemy[i].first == x && enemy[i].second == y) {
			return true;
		}
	}

	// 敵の毒に衝突
	for (int i = 0; i < (int)enemyPoison.size(); i++) {
		if (enemyPoison[i].first == x && enemyPoison[i].second == y) {
			return true;
		}
	}

	return false;
}

void Snake::_addBody(bool isExtend)
// ヘビの胴体を追加する関数
{
	if (!isExtend) {
		setCursorPos(_snake.back().first, _snake.back().second);
		cout << " ";
		_snake.pop_back();
	}
}

bool Snake::_isBody(int dx, int dy)
// 進行方向が胴体か判定する関数
{
	return _snake[0].first + dx != _snake[1].first || _snake[0].second + dy != _snake[1].second;
}

deque<location> Snake::getSnake()
{
	return _snake;
}

void Snake::setVector(int dx, int dy)
{
	_vector.first = dx;
	_vector.second = dy;
}

location Snake::getPos()
{
	return _pos;
}

void Snake::setPos(int x, int y)
{
	_pos.first = x;
	_pos.second = y;
}

vector<location> Snake::getPoisons()
{
	return _poisons;
}