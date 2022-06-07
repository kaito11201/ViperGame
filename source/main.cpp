#include <iostream>
#include <time.h>

#include "header/print.h"
#include "header/food.h"
#include "header/snake.h"

using namespace std;

// フィールドの大きさ
#define H 25
#define W 80

// プレイヤーの色
# define PLAYER1_COLOR RED
# define PLAYER2_COLOR BLUE

// エサの最大数
#define MAX_FOODS 10

// 勝利するためのヘビの長さ
#define VICTORY_LENGTH 20

// FPS
#define FPS 10

// 制限時間(秒)
#define LIMIT_TIME 100

int main() {

	// インスタンス化
	Print print(W, H);
	Food food(W, H, MAX_FOODS);
	Snake snake(W, H);
	Snake snake2(W, H);

	// 乱数初期化
	srand((int)time(0));

	for (;;) {

		// 制限時間
		int limitTime = LIMIT_TIME;

		// 衝突判定を行う配列
		bool isCollision[2] = { false, false };

		// 勝利判定を行う配列
		bool isVictory[2] = { false, false };

		// 各オブジェクトの初期化
		snake.init(5, H / 2);
		snake2.init(W - 7, H / 2);
		food.init();
		food.add(MAX_FOODS);

		// スタート待機画面
		// 各オブジェクトの描画
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

		// ゲーム開始
		print.field();
		print.foods(food.getFoods());
		print.snake(snake.getSnake(), PLAYER1_COLOR);
		print.snake(snake2.getSnake(), PLAYER2_COLOR);

		for (int count = 0;; count++) {

			//	キーによる操作
			snake.controller('A', 'S', 'W', 'D', 'F', 'C');
			snake2.controller('J', 'K', 'I', 'L', 'H', 'N');

			//　各オブジェクトを動かす
			snake.move();
			snake2.move();
			snake.poisonMove();
			snake2.poisonMove();

			// エサを食べる
			vector<location> foods = food.getFoods();
			snake.eat(foods);
			snake2.eat(foods);
			food.setFoods(foods);

			// エサを補充
			food.add();

			// ヘビの長さ
			int snakeLength1 = snake.getSnake().size();
			int snakeLength2 = snake2.getSnake().size();

			// 各オブジェクトの描画
			print.snakeLength(snakeLength1, snakeLength2, PLAYER1_COLOR, PLAYER2_COLOR);
			print.time(limitTime);
			print.foods(food.getFoods());
			print.snake(snake.getSnake(), PLAYER1_COLOR);
			print.snake(snake2.getSnake(), PLAYER2_COLOR);
			print.poisons(snake.getPoisons(), PLAYER1_COLOR);
			print.poisons(snake2.getPoisons(), PLAYER2_COLOR);

			// 勝利判定
			isVictory[0] = (snakeLength1 >= VICTORY_LENGTH)
				|| snake2.isCollision(snake.getSnake(), snake.getPoisons());

			isVictory[1] = (snakeLength2 >= VICTORY_LENGTH)
				|| snake.isCollision(snake2.getSnake(), snake2.getPoisons());

			// 制限時間が過ぎた場合
			if (limitTime <= 0) {
				isVictory[0] = snakeLength1 > snakeLength2;
				isVictory[1] = snakeLength1 < snakeLength2;
			}

			// Player1とPlayer2が同時に勝利
			if (isVictory[0] && isVictory[1]) {
				// ビープ音
				cout << (char)0x07 << (char)0x07 << (char)0x07;

				// メッセージ
				print.judgeMessage("Draw!!");

				// ゲーム終了
				break;
			}
			// Player1が勝利
			else if (isVictory[0]) {

				cout << (char)0x07 << (char)0x07 << (char)0x07;

				print.judgeMessage("Player1 Win!!");

				break;
			}
			// Player2が勝利
			else if (isVictory[1]) {

				cout << (char)0x07 << (char)0x07 << (char)0x07;

				print.judgeMessage("Player2 Win!!");

				break;
			}

			// 0.1秒ずつ進む(fps)
			Sleep(1000 / FPS);

			// 時間を減らす
			if (!(count % FPS)) limitTime--;
		}

		// 再度ゲームを行うかどうか
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