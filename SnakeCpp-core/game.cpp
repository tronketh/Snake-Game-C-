#include "game.h"
int gridX, gridY;
std::vector<int> posX, posY;
short sDirection = RIGHT;
extern bool gameOver;
bool food = true;
int foodX, foodY;
int snakeLength = 1;

void unit(int, int);
void random(int& x, int& y);

void initGrid(int x, int y) {
	gridX = x;
	gridY = y;
}

void drawGrid() {
	for (int x = 0; x < gridX;x++) {
		for (int y = 0; y < gridY; y++) {
			unit(x,y);
		}
	}
	posX.push_back(gridX / 2);
	posY.push_back(gridY / 2);
}
void unit(int x,int y) {

	if (x == 0 || y == 0 || x == (gridX - 1) || y == (gridY - 1)) {
		glLineWidth(3.0);
		glColor3f(0.5, 0, 0);
	}
	else {
		glLineWidth(1.0);
		glColor3f(0.17, 0.17, 0.17);
	}

	glBegin(GL_LINE_LOOP);
	glVertex2f(x,y);
	glVertex2f(x+1,y);
	glVertex2f(x+1,y+1);
	glVertex2f(x,y+1);
	glEnd();
}

void drawSnake() {
	for (int i = snakeLength-1; i > 0; i--) {
		posX[i] = posX[i - 1];
		posY[i] = posY[i - 1];
	}
	if (sDirection == UP) {
		posY[0]++;
	}
	else if (sDirection == DOWN) {
		posY[0]--;
	}
	else if (sDirection == RIGHT) {
		posX[0]++;
	}
	else if (sDirection == LEFT) {
		posX[0]--;
	}

	for (int i = 0; i < snakeLength; i++) {
		if (i == 0){
			glColor3f(0, 0.9, 0);
			switch (sDirection) {
				case UP:
					glRectd(posX[i], posY[i], posX[i] + 1.0, posY[i] + 0.5);
					break;
				case DOWN:
					glRectd(posX[i], posY[i] + 0.5, posX[i] + 1.0, posY[i] + 1.0);
					break;
				case LEFT:
					glRectd(posX[i] + 0.5, posY[i], posX[i] + 1.0, posY[i] + 1.0);
					break;
				case RIGHT:
					glRectd(posX[i], posY[i], posX[i] + 0.5, posY[i] + 1.0);
					break;
			}
			glRectd(posX[i] + 0.25, posY[i] + 0.25, posX[i] + 0.75, posY[i] + 0.75);
		}
		else {
			glColor3f(0.9, 0.9, 0);
			glRectd(posX[i], posY[i], posX[i] + 1.0, posY[i] + 1.0);
		}
	}

	if (posX[0] == 0 || posX[0] == (gridX-1) || posY[0] == 0 || posY[0] == (gridY-1)) {
		gameOver = true;
	}
	for (int i = 1; i < snakeLength;i++) {
		if (posX[0]==posX[i] && posY[0]==posY[i]) {
			posX.erase(posX.begin()+i+1, posX.end());
			posY.erase(posY.begin()+i+1, posY.end());
			snakeLength = i+1;
			break;
		}
	}

	if (posX[0] == foodX && posY[0] == foodY) {
		food = true;
		snakeLength++;
		posX.push_back(0);
		posY.push_back(0);
	}
}

void drawFood() {
	if (food) 
		random(foodX,foodY);
	food = false;
	glColor3f(1, 0, 1);
	glRectf(foodX,foodY, foodX+1, foodY+1);
}

void random(int& x, int& y) {
	int maxX = gridX - 2;
	int maxY = gridY - 2;
	int _min = 1;
	srand(time(NULL));
	x = _min + (rand() % (1+maxX - _min));
	y = _min + (rand() % (1+maxY - _min));
}

void showScore(int x,int y) {
	glRasterPos2i(x, y);
	glColor4f(0.0f, 0.0f, 1.0f,1.0f);

	char _score[10];
	_itoa_s(snakeLength, _score, 10);
	char text[50] = "Your Score : ";
	strcat_s(text, _score);
	const unsigned char* t = reinterpret_cast<const unsigned char*>(text);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, t);
}