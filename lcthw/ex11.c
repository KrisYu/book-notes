#include <stdio.h>

int main(int argc, char *argv[])
{
  int i = 0;

  // go through each string in argv
  while (i < argc) {
    printf("arg %d : %s\n",i ,argv[i]);
    i++;
  }


  // let's make our own array of strings
  char *states[] = {
    "California", "Oregon",
    "Washington", "Texas"
  };

  int num_states = 4;
  i = 0;

  while (i < num_states) {
    printf("state %d: %s\n",i ,states[i] );
    i++;
  }

  return 0;
}
