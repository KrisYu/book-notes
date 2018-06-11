#include <stdio.h>

int main(){
  __block  int val = 0;
  void (^blk)(void) = ^{ val = 1; };

  blk();

  printf("val = %d\n", val);
  return 0;
}
