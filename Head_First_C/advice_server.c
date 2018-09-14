// 为连接的用户随机提出警告

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>



int main(int argc, char const *argv[]) {

  char *advice[] = {
    "Take smaller bites\r\n",
    "Go for the tight jeans. No they do NOT make you look fat.\r\n",
    "One word: inappropriate\r\n ",
    "Just for today, be honest. Tell your boss what you *really* think \r\n",
    "You might want to rethink that haircut\r\n"
  };

  // 创建socket 互联网套接字（这翻译）
  int listener_d = socket(PF_INET, SOCK_STREAM, 0);

  // 1. 绑定端口
  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(30000);
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  int c = bind(listener_d, (struct sockaddr *) &name, sizeof(name));

  // 2. 监听
  // 这里的10是监听队列的长度
  listen(listener_d, 10);
  puts("Waiting for connection");

  //
  while (1) {
    // 3.接收连接
    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);
    int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
    char *msg = advice[rand() % 5];

    // 开始和客户端通信
    send(connect_d, msg, strlen(msg), 0);
    close(connect_d);
  }

  return 0;
}
