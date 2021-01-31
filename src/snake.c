#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "./segment.h"

void initSnake(struct Segment *head) {
  head->current_y = 0;
  head->current_x = 0;
  head->direction = 'r';
}

void spreadApples(int count, int appleRow[50], int appleCol[50]) {
  time_t t;
  srand((unsigned) time(&t));
  int col, row, i;

  getmaxyx(stdscr, row, col);

  for(i = 0; i<= count; i++) {
    int newCol = rand() % (col + 1);
    int newRow = rand() % (row + 1);

    appleRow[i] = newRow;
    appleCol[i] = newCol;
  }
}

void setSnakeDirection(struct Segment *head) {
  int dir = getch(); /* Works inside loop, due to set nodelay(stdscr, TRUE);*/

  if(dir==KEY_UP) {
    head->direction = 'u';
  } else if(dir==KEY_DOWN) {
    head->direction = 'd';
  } else if(dir==KEY_LEFT) {
    head->direction = 'l';
  } else if(dir==KEY_RIGHT) {
    head->direction = 'r';
  }
}

void slither(struct Segment *head, int appleY[50], int appleX[50]) {
  char dir = head->direction;
  int next_y = head->current_y;
  int next_x = head->current_x;

  switch(dir) {
  case 'u':
    next_y = head->current_y - 1;
    break;

  case 'd':
    next_y = head->current_y + 1;
    break;

  case 'l':
    next_x = head->current_x - 1;
    break;

  case 'r':
    next_x = head->current_x + 1;
    break;
  }

  head->next_x = next_x;
  head->next_y = next_y;

  // printw("%d, %d", head->current_y, head->current_x);

  struct Segment *ptr = head;
  struct Segment *i;
  // struct Segment *prev = NULL;

  while(ptr->prev !=NULL) {
    i = ptr->prev;
    i->next_x = ptr->current_x;
    i->next_y = ptr->current_y;
    ptr = i;
  }

  struct Segment *ptrs = head;

  head->current_x = head->next_x;
  head->current_y = head->next_y;

  while(ptrs->prev != NULL) {
    ptrs = ptrs->prev;
    ptrs->current_x = ptrs->next_x;
    ptrs->current_y = ptrs->next_y;
  }
}

bool canSnakeEatApple(struct Segment *head, int appleCount, int appleRow[50], int appleCol[50]) {
  int i,j;

  for(i=0; i<=appleCount; i++){
    if(appleRow[i]==head->current_y) {
      if(appleCol[i]==head->current_x) {
        appleCol[i] = -1;
        appleRow[i] = -1;
        return true;
      }
    }
  }

  return false;
}
