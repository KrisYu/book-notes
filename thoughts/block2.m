#include <stdio.h>

int main(){
  int val = 0;
  void (^blk)(void) = ^{ val = 1 };

  blk();
  
  printf("val = %d\n", val);
  return 0;
}
