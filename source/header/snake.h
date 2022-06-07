#pragma once

#include <iostream>
#include <deque>
#include <vector>

#include "win.h"

using namespace std;

typedef pair<int, int> location;

class Snake
	// �w�r�N���X
{
public:
	Snake(const int width, const int height);

	// �������֐�
	void init(int x, int y);

	// �w�r�𑀍삷��֐�
	void controller(char left, char down, char up, char right, char attackKey, char attackStopKey);

	// �ړ�����֐�
	void move();

	// �G�T��H�ׂ�֐�
	void eat(vector<location>& foods);

	//	�ł̍U��������֐�
	void attack();

	// �ł��΂��֐�
	void poisonMove();

	// �Փ˔�����s���֐�
	bool isCollision(const deque<location>& enemy, const vector<location>& enemyPoison);


	// �����o�ϐ��̎󂯓n�����s���֐�
	deque<location> getSnake();
	void setVector(int dx, int dy);
	location getPos();
	void setPos(int x, int y);
	vector<location> getPoisons();

private:
	// �t�B�[���h�̑傫��
	const int _width;
	const int _height;

	// �w�r�̓�,���̂̍��W��ۑ�����z��
	deque<location> _snake;

	// �w�r�̍��W
	location _pos;

	// �w�r�̐i�s����
	location _vector;

	// �Œ肳�ꂽ�ł̍��W��ۑ�����z��
	vector<location> _poisons;

	// �ł̐i�s����
	location _poisonVector;

	// �ł𔭎˂��Ă�r�������肷��ϐ�
	bool _isAttacking;

	// �i�s�悪�w�r�̓��̂����肷��֐�
	bool _isBody(int dx, int dy);

	// �w�r�̓��̂�ǉ�����֐�
	void _addBody(bool isExtend);

};