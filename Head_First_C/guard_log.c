#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 函数返回一个字符串，包含当前文本和时间
char* now()
{
  time_t t;
  time (&t);
  return asctime(localtime (&t));
}

int main(int argc, char const *argv[]) {
  char comment[80];
  char cmd[120];
  // 把文本保存在comment 数组中
  fgets(comment, 80, stdin);
  // sprintf 把字符写到字符串中
  sprintf(cmd, "echo '%s %s' >> reports.log", comment, now());
  // cmd 会写入reports.log
  system(cmd);
  return 0;
}

// system 简化了程序
