#include <stdlib.h>

#include "segment.h"


void attachSegment(struct Segment *head) {
  struct Segment *ptr = head;
  struct Segment *tail = genSegment();

  while(ptr->prev != NULL) {
    ptr = ptr->prev;
  }

  ptr->prev = tail;
}

struct Segment* genSegment(void) {
  struct Segment *ptr = (struct Segment*) malloc(sizeof(struct Segment));
  return ptr;
}
