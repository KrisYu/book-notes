/*
 * advice_server2.c
 * 为连接的用户随机提出建议
 * 增加了错误检查
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>



void error(char *msg)
{
  fprintf(stderr, "%s %s\n",msg, strerror(errno));
  exit(1);
}

// read in entire file as string
// https://stackoverflow.com/a/174552/3608824
char* read_file(char* filename)
{
  char* buffer;
  long length;
  FILE *f = fopen(filename, "r");

  if (f) {
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length);

    if (buffer) {
      fread(buffer, 1, length, f);
    }
    fclose(f);
  }

  return buffer;
}


int main(int argc, char const *argv[]) {

  char *advice = read_file("happy");

  // 创建socket 互联网套接字
  int listener_d = socket(PF_INET, SOCK_STREAM, 0);

  // 1. 绑定端口
  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(30000);
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(listener_d, (struct sockaddr *) &name, sizeof(name)) == -1)
    error("无法绑定端口");

  // 解决绑定延时问题
  int reuse = 1;
  if (setsockopt(listener_d, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1 )
    error("无法设置套接字的“重新使用端口”选项");

  // 2. 监听
  listen(listener_d, 10);
  puts("Waiting for connection");

  //
  while (1) {
    // 3.接收连接
    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);
    int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
    char *msg = advice;

    // 开始和客户端通信
    send(connect_d, msg, strlen(msg), 0);
    close(connect_d);
  }

  return 0;
}
