#include "game.h"

#define COLUMNS 40
#define ROWS 40
#define FPS 10
#define SCOREAREA 40

extern short sDirection;
bool gameOver = false;
extern int snakeLength;

void init();
void display_callback();
void reshape_callback(int, int);
void timer_callback(int);
void keyboard_callback(int, int, int);

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(136, 70);
	glutInitWindowSize(500, 500+SCOREAREA);
	glutCreateWindow("Snake Game");
	glutDisplayFunc(display_callback);
	glutReshapeFunc(reshape_callback);
	glutTimerFunc(0, timer_callback, 0);
	glutSpecialFunc(keyboard_callback);
	init();
	glutMainLoop();
	return 0;
}

void init() {
	glClearColor(0, 0, 0, 1);
	initGrid(COLUMNS, ROWS);
}

void display_callback() {
	glClear(GL_COLOR_BUFFER_BIT);
	drawGrid();
	drawSnake();
	drawFood();
	showScore(COLUMNS/2.5,ROWS+1);
	glutSwapBuffers();
	if (gameOver) {
		char _score[10];
		_itoa_s(snakeLength, _score, 10);
		char text[50] = "Your Score : ";
		strcat_s(text, _score);
		MessageBoxA(0, text, "Game Over", 0);
		exit(0);
	}
}

void reshape_callback(int width, int height) {
	glViewport(0, 0, (GLsizei)width, (GLsizei)(height));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, COLUMNS, 0, ROWS+(SCOREAREA*40.0/height), -1, 1);
	glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int) {
	glutPostRedisplay();
	glutTimerFunc((1000 / FPS), timer_callback, 0);
}

void keyboard_callback(int key, int, int) {
	switch (key) {
	case GLUT_KEY_UP:
		if (sDirection != DOWN) {
			sDirection = UP;
		}
		break;
	case GLUT_KEY_DOWN:
		if (sDirection != UP) {
			sDirection = DOWN;
		}
		break;
	case GLUT_KEY_LEFT:
		if (sDirection != RIGHT) {
			sDirection = LEFT;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (sDirection != LEFT) {
			sDirection = RIGHT;
		}
		break;
	}
}