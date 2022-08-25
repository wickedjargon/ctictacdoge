#include "DogeLib/Includes.h"
#include "DogeLib/Text.h"
#include <stdio.h>

int main(void) {

  int w = 4;
  int* x = &w;
  *x = 10;
  printf("%p \n%i\n", (void *) x, *x);
  printf("%i\n", w);
  init();
  while (1) {
    const uint T = frameStart();
    setTextSize(16);
    setTextColor(WHITE);
    drawTextCenteredCoord("hello world", getWindowMid());
    frameEnd(T);
  }
  return 0;
}
