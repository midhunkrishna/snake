#ifndef SEGMENT_H_INCLUDED
#define SEGMENT_H_INCLUDED

extern struct Segment {
  int current_y;
  int current_x;

  int next_y;
  int next_x;

  char direction;
  struct Segment *prev;
};

extern void attachSegment(struct Segment *head);
extern struct Segment* genSegment(void);

#endif
