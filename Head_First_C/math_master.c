#include <stdio.h>
#include <stdlib.h>
// exec
#include <unistd.h>
// time
#include <time.h>
#include <string.h>

#include <errno.h>
#include <signal.h>

int score = 0;

void end_game(int sig) {
  printf("\n Final score: %i\n", score);
  exit(0);
}

int catch_signal(int sig, void (*handler)(int))
{
  struct sigaction action;
  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  return sigaction(sig, &action, NULL);
}

void times_up(int sig) {
  puts("\nTIME'S UP!");
  // 这个还是会调用end_game 
  raise(SIGINT);
}

void error(char *msg)
{
  fprintf(stderr, "%s %s\n",msg, strerror(errno));
  exit(1);
}

int main(int argc, char const *argv[]) {
  // 会抓两个信号
  catch_signal(SIGALRM, times_up);
  catch_signal(SIGINT, end_game);
  srandom(time(0));
  while (1) {
    int a = random() % 11;
    int b = random() % 11;
    char txt[4];
    alarm(5);
    printf("\nWhat is %i times %i? ",a , b);
    fgets(txt, 4, stdin);
    int answer = atoi(txt);
    if (answer == a * b)
      score++;
    else
      printf("\nWrong! Score: %i",score );
  }
  return 0;
}
