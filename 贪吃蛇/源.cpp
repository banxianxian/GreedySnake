#include<iostream>
#include<cstdlib>
#include<ctime>
#include<easyx.h>
#include<conio.h>

using namespace std;
const int KeepDirection = 10;

enum direction { eUp, eDown, eLeft, eRight };

struct node {
	int x;
	int y;
};

class Graphme {
public:
	Graphme() {
		initgraph(800, 600);
		setbkcolor(RGB(164, 225, 202));
		cleardevice();
		for (int i = 0; i <= 800; i += 40) {
			line(i, 0, i, 600);
		}
		for (int j = 0; j <= 600; j += 40) {
			line(0, j, 800, j);
		}
	}

	void setGraphme() {
		setbkcolor(RGB(164, 225, 202));
		cleardevice();
		for (int i = 0; i <= 800; i += 40) {
			line(i, 0, i, 600);
		}
		for (int j = 0; j <= 600; j += 40) {
			line(0, j, 800, j);
		}
	}
	
};


class Food;

class Snake {
public:
	
	Snake() :length(5), dx(0), dy(0) {
		for (int i = 0; i < length; i++) {
			snakenode[i].x = length - i;
			snakenode[i].y = 7;
			drawSnake();
		}
	}

	void setSnake() {
		length = 5;
		dx = 0;
		dy = 0;
		cnt = 0;
		for (int i = 0; i < length; i++) {
			snakenode[i].x = length - i;
			snakenode[i].y = 7;
			drawSnake();
		}
	}

	bool crossBoard(){
		return !(snakenode[0].x >= 0 && snakenode[0].x <= 19 && snakenode[0].y >= 0 && snakenode[0].y <= 14);
	}

	bool eatSelf() {
		for (int i = 1; i < length; i++) {
			if (snakenode[0].x == snakenode[i].x && snakenode[0].y == snakenode[i].y) {
				return true;
			}
			
		}
		return false;
	}

	void drawSnake() {
		
		int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
		setfillcolor(WHITE);
		for (int i = 0; i < length; i++) {
			x1 = snakenode[i].x * Width;
			y1 = snakenode[i].y * Width;
			x2 = x1 + Width;
			y2 = y1 + Width;
			solidrectangle(x1, y1, x2, y2);
		}
	}

	void snakeMove(int direction) {
		
		if (direction == KeepDirection && cnt == 0) {
			return;
		}
		
		for (int i = length - 1; i > 0; i--) {
			snakenode[i] = snakenode[i - 1];
		}
		struct node Temp = snakenode[0];

		if (direction == eLeft) {
			dx = -1;
			dy = 0;
			cnt++;
		}
		else if (direction == eRight) {
			dx = 1;
			dy = 0;
			cnt++;
		}
		else if (direction == eUp) {
			dy = -1;
			dx = 0;
			cnt++;
		}
		else if (direction == eDown) {
			dy = 1;
			dx = 0;
			cnt++;
		}
		
		Temp.x += dx;
		Temp.y += dy;
		snakenode[0] = Temp;

	}

	const int Width = 40;
	struct node snakenode[100];
	int length;
	int dx;
	int dy;
	static int cnt;
};

int Snake::cnt = 0;


class Food {
public:
	
	Food() {
		x = rand() % 20;
		y = rand() % 15;
		drawFood();

	}
	void setNewfood(Snake snake) {
		int k = 0;
		while (1) {
			k = 0;
			x = rand() % 20;
			y = rand() % 15;
			for (int i = 0; i < snake.length; i++) {
				if (snake.snakenode[i].x == x && snake.snakenode[y].y == y) {
					k = 1;
					break;
				}
			}

			if (k == 0) {
				break;
			}

		}
		
		drawFood();
	}

	void drawFood() {
		int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
		x1 = x * Width;
		y1 = y * Width;
		x2 = x1 + Width;
		y2 = y1 + Width;
		setfillcolor(YELLOW);
		solidrectangle(x1, y1, x2, y2);

	}
	int x;
	int y;
	const int Width = 40;
};

void eatFood(Snake &snake, Food &food) {

	if (snake.snakenode[0].x == food.x && snake.snakenode[0].y == food.y) {
		snake.length++;
		for (int i = snake.length - 1; i > 0; i--) {
			snake.snakenode[i] = snake.snakenode[i - 1];
		}
		snake.snakenode[0].x = food.x;
		snake.snakenode[0].y = food.y;
		food.setNewfood(snake);
	}

}

int main() {

	Graphme graphme;

	Snake snake;

	srand(time(0));

	Food food;
	while (1) {
		if (_kbhit() != 0) {
			
			cleardevice();
			char c;
			c = _getch();
			switch (c) {
			case 'a':
				if (snake.dx != 1) {
					snake.snakeMove(eLeft);
				}
				break;

			case 'd':
				if (snake.dx != -1) {
					snake.snakeMove(eRight);
				}
				break;

			case 's':
				if (snake.dy != -1) {
					snake.snakeMove(eDown);
				}
				break;
			case 'w':
				if (snake.dy != 1) {
					snake.snakeMove(eUp);
				}
			
				break;
			}
			
		}
		else {
			snake.snakeMove(KeepDirection);
		}

		if (snake.crossBoard()||snake.eatSelf()) {
			snake.setSnake();
		}
		else {
			eatFood(snake, food);
			graphme.setGraphme();
			food.drawFood();
			snake.drawSnake();
			Sleep(600);
		}
			
	}
	getchar();
	closegraph();

	return 0;
}