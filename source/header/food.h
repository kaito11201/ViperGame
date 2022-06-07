#pragma once

#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> location;

class Food
	// �G�T�N���X
{
public:
	Food(const int width, const int height, const int max);

	// �������֐�
	void init();

	// n�̃G�T���t�B�[���h�ɒǉ�����֐�
	void add(int n = 1);

	// �����o�ϐ��̎󂯓n�����s���֐�
	vector<location> getFoods();
	void setFoods(vector<location>& foods);

private:
	// �t�B�[���h�̑傫��
	const int _width;
	const int _height;

	// �G�T�̍ő吔
	const int _maxFoods;

	// �G�T�̏ꏊ��ۑ�����z��
	vector<location> _foods;
};