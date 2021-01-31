#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

extern void initSnake(struct Segment *head);
extern void spreadApples(int count, int appleY[50], int appleX[50]);
extern void setSnakeDirection(struct Segment *head);
extern void slither(struct Segment *head, int appleY[50], int appleX[50]);
extern bool canSnakeEatApple(struct Segment *head, int appleCount, int appleRow[50], int appleCol[50]);
#endif
