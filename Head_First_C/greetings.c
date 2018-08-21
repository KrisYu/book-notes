#include <stdio.h>
// 需要包含 signal
#include <signal.h>
#include <stdlib.h>

// 新的信号处理器，返回void
void diediedie(int sig)  {
  puts("Goodbye cruel world...\n");
  exit(1);
}

// 注册处理器的函数
int catch_signal(int sig, void (*handler)(int))
{
  struct sigaction action;
  action.sa_handler = diediedie;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  return sigaction(sig, &action, NULL);
}

int main(int argc, char const *argv[]) {
  // 捕捉中断信号 SIGINT, 将中断处理程序设置为 diediedie() 函数
  if (catch_signal(SIGINT, diediedie) == -1) {
    fprintf(stderr, "Can't map the handler");
    exit(2);
  }
  char name[30];
  printf("Enter your name : ");
  fgets(name, 30, stdin);
  printf("Hello %s\n",name );
  return 0;
}
