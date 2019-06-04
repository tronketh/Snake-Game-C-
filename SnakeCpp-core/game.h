#pragma once
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <ctime> 
#include <vector>
#include <stdlib.h>

#define UP 1
#define DOWN -1
#define LEFT -2
#define RIGHT 2

void initGrid(int, int);
void drawGrid();
void drawSnake();
void drawFood();
void showScore(int,int);