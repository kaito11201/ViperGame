#include <iostream>
#include <time.h>

#include "header/print.h"
#include "header/food.h"
#include "header/snake.h"

using namespace std;

// �t�B�[���h�̑傫��
#define H 25
#define W 80

// �v���C���[�̐F
# define PLAYER1_COLOR RED
# define PLAYER2_COLOR BLUE

// �G�T�̍ő吔
#define MAX_FOODS 10

// �������邽�߂̃w�r�̒���
#define VICTORY_LENGTH 20

// FPS
#define FPS 10

// ��������(�b)
#define LIMIT_TIME 100

int main() {

	// �C���X�^���X��
	Print print(W, H);
	Food food(W, H, MAX_FOODS);
	Snake snake(W, H);
	Snake snake2(W, H);

	// ����������
	srand((int)time(0));

	for (;;) {

		// ��������
		int limitTime = LIMIT_TIME;

		// �Փ˔�����s���z��
		bool isCollision[2] = { false, false };

		// ����������s���z��
		bool isVictory[2] = { false, false };

		// �e�I�u�W�F�N�g�̏�����
		snake.init(5, H / 2);
		snake2.init(W - 7, H / 2);
		food.init();
		food.add(MAX_FOODS);

		// �X�^�[�g�ҋ@���
		// �e�I�u�W�F�N�g�̕`��
		print.field();
		print.foods(food.getFoods());
		print.snake(snake.getSnake(), PLAYER1_COLOR);
		print.snake(snake2.getSnake(), PLAYER2_COLOR);
		print.rule();
		print.startMessage();
		for (;;) {
			if (isKeyPressed('S'))
				break;
		}

		// �Q�[���J�n
		print.field();
		print.foods(food.getFoods());
		print.snake(snake.getSnake(), PLAYER1_COLOR);
		print.snake(snake2.getSnake(), PLAYER2_COLOR);

		for (int count = 0;; count++) {

			//	�L�[�ɂ�鑀��
			snake.controller('A', 'S', 'W', 'D', 'F', 'C');
			snake2.controller('J', 'K', 'I', 'L', 'H', 'N');

			//�@�e�I�u�W�F�N�g�𓮂���
			snake.move();
			snake2.move();
			snake.poisonMove();
			snake2.poisonMove();

			// �G�T��H�ׂ�
			vector<location> foods = food.getFoods();
			snake.eat(foods);
			snake2.eat(foods);
			food.setFoods(foods);

			// �G�T���[
			food.add();

			// �w�r�̒���
			int snakeLength1 = snake.getSnake().size();
			int snakeLength2 = snake2.getSnake().size();

			// �e�I�u�W�F�N�g�̕`��
			print.snakeLength(snakeLength1, snakeLength2, PLAYER1_COLOR, PLAYER2_COLOR);
			print.time(limitTime);
			print.foods(food.getFoods());
			print.snake(snake.getSnake(), PLAYER1_COLOR);
			print.snake(snake2.getSnake(), PLAYER2_COLOR);
			print.poisons(snake.getPoisons(), PLAYER1_COLOR);
			print.poisons(snake2.getPoisons(), PLAYER2_COLOR);

			// ��������
			isVictory[0] = (snakeLength1 >= VICTORY_LENGTH)
				|| snake2.isCollision(snake.getSnake(), snake.getPoisons());

			isVictory[1] = (snakeLength2 >= VICTORY_LENGTH)
				|| snake.isCollision(snake2.getSnake(), snake2.getPoisons());

			// �������Ԃ��߂����ꍇ
			if (limitTime <= 0) {
				isVictory[0] = snakeLength1 > snakeLength2;
				isVictory[1] = snakeLength1 < snakeLength2;
			}

			// Player1��Player2�������ɏ���
			if (isVictory[0] && isVictory[1]) {
				// �r�[�v��
				cout << (char)0x07 << (char)0x07 << (char)0x07;

				// ���b�Z�[�W
				print.judgeMessage("Draw!!");

				// �Q�[���I��
				break;
			}
			// Player1������
			else if (isVictory[0]) {

				cout << (char)0x07 << (char)0x07 << (char)0x07;

				print.judgeMessage("Player1 Win!!");

				break;
			}
			// Player2������
			else if (isVictory[1]) {

				cout << (char)0x07 << (char)0x07 << (char)0x07;

				print.judgeMessage("Player2 Win!!");

				break;
			}

			// 0.1�b���i��(fps)
			Sleep(1000 / FPS);

			// ���Ԃ����炷
			if (!(count % FPS)) limitTime--;
		}

		// �ēx�Q�[�����s�����ǂ���
		print.restartMessage();
		for (;;) {
			if (isKeyPressed('Y'))
				break;
			if (isKeyPressed('N'))
				return 0;
		}
	}
	return 0;
}