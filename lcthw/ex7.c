#include<stdio.h>

int main(int argc, char *argv[])
{
  int bugs = 100;
  double bug_rate = 1.2;
  
  printf("You have %d bugs at the imaginary rate of %f.\n", bugs, bug_rate);
  
  long universe_of_defects = 1l * 1024l * 1024l * 1024l;
  printf("The entire universe has %ld defects.\n",universe_of_defects);

  double expected_bugs = bugs * bug_rate;
  printf("You are expected to have %f bugs.\n", expected_bugs);

  double part_of_universe = expected_bugs / universe_of_defects;
  printf("This is only a %e portion of the universe.\n", part_of_universe);

  // this makes no sense, just a demo of something weird.
  char nul_byte = '\0';
  int care_percentage = bugs * nul_byte;
  printf("which means you should care %d%%.\n", care_percentage);

  return 0;
}
