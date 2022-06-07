#include "header/snake.h"

Snake::Snake(const int width, const int height)
	: _width(width)
	, _height(height)
{}

void Snake::init(int x, int y)
// �������֐�
{
	// �������W
	_pos.first = x;
	_pos.second = y;

	// ���������x�N�g��
	_vector.first = 0;
	_vector.second = 1;

	// �����w�r�̓��Ɠ���
	_snake.clear();
	_snake.push_front(location(x, y - 2));
	_snake.push_front(location(x, y - 1));
	_snake.push_front(location(x, y));

	// �ł̏�����
	_isAttacking = false;
	_poisons.clear();
}

void Snake::controller(char left, char down, char up, char right, char attackKey, char attackStopKey)
// �w�r�𑀍삷��֐�
{
	//	�����]��
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

	// �ōU��(����)
	if (isKeyPressed(attackKey) && !_isAttacking && _snake.size() > 2) {
		attack();
		_isAttacking = true;
	}

	// �ōU��(�ł��~�߂�)
	if (isKeyPressed(attackStopKey) && _isAttacking) {
		_isAttacking = false;
	}

}

void Snake::move()
// �ړ�����֐�
{
	// �i�s�����Ɉړ�
	_pos.first += _vector.first;
	_pos.second += _vector.second;
	_snake.push_front(_pos);
}

void Snake::eat(vector<location>& foods)
// �G�T��H�ׂ�֐�
{
	// �w�r�̓��̂�L�΂������肷��ϐ�
	bool isExtend = false;

	for (int i = (int)foods.size(); --i >= 0;) {

		// �G�T�̍��W�ƃw�r�̓��̍��W��������
		if (foods[i].first == _pos.first && foods[i].second == _pos.second) {

			// �G�T������
			foods.erase(foods.begin() + i);

			// �r�[�v��
			cout << (char)0x07;

			isExtend = true;
		}
	}

	// �w�r�̓��̂�L�΂�
	_addBody(isExtend);
}

void Snake::attack()
{	// �ł̍U�����s���֐�

	// ���̂�Z������
	setCursorPos(_snake.back().first, _snake.back().second);
	cout << " ";
	_snake.pop_back();

	// �ł̐i�s����
	_poisonVector.first = _vector.first;
	_poisonVector.second = _vector.second;

	// �ł̍��W
	_poisons.push_back(location(_pos.first + _poisonVector.first,
		_pos.second + _poisonVector.second));
}

void Snake::poisonMove()
// �ł��΂��֐�
{
	if (_isAttacking) {
		setCursorPos(_poisons.back().first, _poisons.back().second);
		cout << " ";

		_poisons.back().first += _poisonVector.first;
		_poisons.back().second += _poisonVector.second;

		// �ǂɏՓ�
		int x = _poisons.back().first;
		int y = _poisons.back().second;

		if (x <= 1 || x >= _width - 2 || y <= 2 || y >= _height - 3) {
			_isAttacking = false;
		}
	}

}

bool Snake::isCollision(const deque<location>& enemy, const vector<location>& enemyPoison)
// �Փ˔�����s���֐�
{
	// �w�r�̓��̍��W
	int x = _snake[0].first;
	int y = _snake[0].second;

	// �ǂɏՓ�
	if (x <= 0 || x >= _width - 1 || y <= 1 || y >= _height - 2) {
		return true;
	}

	// ���̂ɏՓ�
	for (int i = 1; i < (int)_snake.size(); i++) {
		if (_snake[i].first == x && _snake[i].second == y) {
			return true;
		}
	}

	// �G�ɏՓ�
	for (int i = 0; i < (int)enemy.size(); i++) {
		if (enemy[i].first == x && enemy[i].second == y) {
			return true;
		}
	}

	// �G�̓łɏՓ�
	for (int i = 0; i < (int)enemyPoison.size(); i++) {
		if (enemyPoison[i].first == x && enemyPoison[i].second == y) {
			return true;
		}
	}

	return false;
}

void Snake::_addBody(bool isExtend)
// �w�r�̓��̂�ǉ�����֐�
{
	if (!isExtend) {
		setCursorPos(_snake.back().first, _snake.back().second);
		cout << " ";
		_snake.pop_back();
	}
}

bool Snake::_isBody(int dx, int dy)
// �i�s���������̂����肷��֐�
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