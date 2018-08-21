#include <stdio.h>
// 为了使用 exec() 函数，需要unistd
#include <unistd.h>
// 为了使用 errno变量
#include <errno.h>
// 为了使用strerror()函数
#include <string.h>

int main(int argc, char const *argv[]) {
  if (execl("/sbin/ifconfig", "sbin/ifconfig", NULL) == - 1)
  // 使用execl 因为我们有路径， sbin/ifconfig 在 Linux or Mac上
    if (execlp("ipconfig", "ipconfig", NULL) == -1) {
      // 使用 execlp 会根据 PATH 查找 ipconfig 命令
      // 如果返回值是 -1， 则打印错误
      fprintf(stderr, "Cannot run ipconfig %s",strerror(errno));
      return 1;
    }

  return 0;
}
