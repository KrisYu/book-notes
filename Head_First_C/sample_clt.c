/*
 * sample_clt.c
 * 简单的客户端例子
 * 配合 sample_srv.c 使用
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define _INT_BUF (255)
// 端口号， 处理监听队列大小
#define _INT_PORT (8088)
// 简单的辅助操作宏
#define _IF_CODE(code) \
  if ((code) < 0) \
    perror(#code), exit(EXIT_FAILURE)

static void __print(char* buf, int len)
{
  int i = -1;
  while (++i < len)
    putchar(buf[i]);
  fflush(stdout);
}

int main(int argc, char const *argv[]) {

  int sfd;
  struct sockaddr_in saddr = { AF_INET };
  char buf[_INT_BUF + 1];
  int len;

  // 创建套接字
  _IF_CODE(sfd = socket(PF_INET, SOCK_STREAM, 0));

  // 绑定端口 bind
  saddr.sin_port = htons(_INT_PORT);
  saddr.sin_addr.s_addr = INADDR_ANY;
  _IF_CODE(connect(sfd, (struct sockaddr*)&saddr, sizeof saddr));

  // 接收信息直到结束
  while ((len = read(sfd, buf, _INT_BUF)) > 0)
    __print(buf, len);

  close(sfd);
  return 0;
}
