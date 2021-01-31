#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>

#include "./segment.h"
#include "./sleep.h"
#include "./snake.h"

// APP PROTO
void initNcurses();
void draw(struct Segment *head, int appleCount, int appleY[50], int appleX[50]);
//

int main() {
  struct Segment *head = genSegment();

  int appleRow[50];
  int appleCol[50];
  int appleCount = 48;

  initSnake(head);
  initNcurses();

  spreadApples(appleCount, appleRow, appleCol);

  while(1) {
    setSnakeDirection(head);
    slither(head, appleRow, appleCol);

    if(canSnakeEatApple(head, appleCount, appleRow, appleCol)) {
      attachSegment(head);
      slither(head, appleRow, appleCol);
    }

    draw(head, appleCount, appleRow, appleCol);
    msleep(100);
  }

  endwin();
  return 0;
}


void draw(struct Segment *head, int appleCount, int appleRow[50], int appleCol[50]) {
  struct Segment *ptr = head;
  int i,j,k;
  char snakeHead;

  clear();

  if(head->direction == 'u') {
    snakeHead = 'A';
  } else if(head->direction == 'd') {
    snakeHead = 'V';
  } else if(head->direction == 'r') {
    snakeHead = '>';
  } else if(head->direction == 'l') {
    snakeHead = '<';
  }

  mvwprintw(stdscr, head->current_y, head->current_x, "%c", snakeHead);

  while(ptr->prev != NULL) {
    ptr = ptr->prev;
    mvwprintw(stdscr, ptr->current_y, ptr->current_x, "X");
  }

  for(i=0; i <= appleCount; i++) {
    if(appleRow[i] != -1) {
      mvwprintw(stdscr, appleRow[i], appleCol[i], "0");
    }
  }

  refresh();
}


void initNcurses() {
  int row,col;

  initscr();                    /* Start curses mode                */
  cbreak();                     /* Line buffering disabled, Pass on
                                 * every thing to me                */
  keypad(stdscr, TRUE);		/* I need that nifty F1             */
  getmaxyx(stdscr, row, col);   /* get height and width of screen   */

  noecho();                     /* do not print to screen           */
  nodelay(stdscr, TRUE);        /* getch is async                   */
  curs_set(0);                  /* hide cursor                      */
  refresh();
}
