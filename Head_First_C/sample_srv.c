/*
 * sample_srv.c
 * 简单的服务器例子
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define _STR_HEOO "Hello World!\n"
#define _INT_PORT (8088)
#define _INT_LIS (10)

#define _IF_CODE(code) \
  if ((code) < 0) \
    perror(#code), exit(EXIT_FAILURE)

int main(int argc, char const *argv[]) {

  int sfd;
  struct sockaddr_in saddr;

  // 创建套接字
  _IF_CODE(sfd = socket(AF_INET, SOCK_STREAM, 0));

  // 绑定端口 bind
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(_INT_PORT);
  saddr.sin_addr.s_addr = INADDR_ANY;
  memset(&saddr.sin_zero, 0, sizeof(saddr.sin_zero));
  _IF_CODE(bind(sfd, (struct sockaddr *)&saddr, sizeof saddr));

  // 监听 listen
  _IF_CODE(listen(sfd, _INT_LIS));

  // 下面就是采用单进程处理客户端链接请求
  for (;;) {
    int cfd, fd;
    // 接受 accept
    struct sockaddr_in caddr;
    socklen_t clen = sizeof caddr;
    _IF_CODE(cfd = accept(sfd, (struct sockaddr*)&caddr, &clen));
    printf("got connection from %s.\n",inet_ntoa(caddr.sin_addr));

    // 开启多进程
    _IF_CODE(fd = fork()); // 存在文件描述符没清除，严谨的代码，让更愿意的人写吧

    if (fd == 0) { // 子进程处理
      close(sfd);
      write(cfd, _STR_HEOO, strlen(_STR_HEOO));
      close(cfd);
      exit(EXIT_SUCCESS);
    }

    // 父进程原先逻辑
    close(cfd);

    // 为子进程收尸|||
    while(waitpid(-1, NULL, WNOHANG) > 0)
      usleep(1000);
  }

  close(sfd);
  return 0;
}
