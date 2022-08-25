#include "DogeLib/Includes.h"
#include <stdio.h>

int main(void) {
  printf("hello world\n");
  init();
  while (1) {
    const uint T = frameStart();
    frameEnd(T);
  }
  return 0;
}
