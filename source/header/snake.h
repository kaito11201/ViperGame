#pragma once

#include <iostream>
#include <deque>
#include <vector>

#include "win.h"

using namespace std;

typedef pair<int, int> location;

class Snake
	// ヘビクラス
{
public:
	Snake(const int width, const int height);

	// 初期化関数
	void init(int x, int y);

	// ヘビを操作する関数
	void controller(char left, char down, char up, char right, char attackKey, char attackStopKey);

	// 移動する関数
	void move();

	// エサを食べる関数
	void eat(vector<location>& foods);

	//	毒の攻撃をする関数
	void attack();

	// 毒を飛ばす関数
	void poisonMove();

	// 衝突判定を行う関数
	bool isCollision(const deque<location>& enemy, const vector<location>& enemyPoison);


	// メンバ変数の受け渡しを行う関数
	deque<location> getSnake();
	void setVector(int dx, int dy);
	location getPos();
	void setPos(int x, int y);
	vector<location> getPoisons();

private:
	// フィールドの大きさ
	const int _width;
	const int _height;

	// ヘビの頭,胴体の座標を保存する配列
	deque<location> _snake;

	// ヘビの座標
	location _pos;

	// ヘビの進行方向
	location _vector;

	// 固定された毒の座標を保存する配列
	vector<location> _poisons;

	// 毒の進行方向
	location _poisonVector;

	// 毒を発射してる途中か判定する変数
	bool _isAttacking;

	// 進行先がヘビの胴体か判定する関数
	bool _isBody(int dx, int dy);

	// ヘビの胴体を追加する関数
	void _addBody(bool isExtend);

};