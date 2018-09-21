/*
 * ikkp_server.c
 * 服务器与客户端对话
 *
 */


#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>

// 显示错误的代码
void error(char *msg)
{
  fprintf(stderr, "%s %s\n",msg, strerror(errno));
  exit(1);
}

// 创建互联网套接字
int open_listener_socket()
{
  int s = socket(PF_INET, SOCK_STREAM, 0);
  if (s == -1)
    error("Can't open socket.");

  return s;
}

void bind_to_port(int socket, int port)
{
  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(30000);
  name.sin_addr.s_addr = htonl(INADDR_ANY);
  int reuse = 1;
  if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
    error("Can't set the reuse option on the socket");
  int c = bind(socket, (struct sockaddr *)&name, sizeof(name));
  if (c == -1)
    error("Can't bind to socket");
}

// 向客户端发送字符串
int say(int socket, char *s)
{
  int result = send(socket, s, strlen(s), 0);
  if (result == -1)
    fprintf(stderr, "%s: %s \n","和客户通信时发生了错误", strerror(errno));
  return result;
}

// 用这个函数读取 \n 前的所有字符
int read_in(int socket, char *buf, int len)
{
  char *s = buf;
  int slen = len;
  int c = recv(socket, s, slen, 0);
  //循环读取字符，知道没有字符或者可读或者读到了 \n
  while ((c > 0) && s[c-1] != '\n') {
    s += c; slen -= c;
    c = recv(socket, s, slen, 0);
  }
  // 防止错误
  if (c < 0)
    return c;
  // 什么都没读到，返回一个空字符
  else if (c == 0)
    buf[0] = '\0';
  // 用\0替换\r
  else
    s[c-1] = '\0';
  return len - slen;
}

int catch_signal(int sig, void (*handler)(int))
{
  struct sigaction action;
  action.sa_handler = handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  return sigaction(sig, &action, NULL);
}

// 保存服务器的主监听套接字
int listener_d;

// 如果有人在服务器运行期间按了 Ctrl-c,
// 这个函数就会赶在程序结束前关闭套接字
void handle_shutdown(int sig)
{
  if (listener_d)
    close(listener_d);

  fprintf(stderr, "Bye!\n" );
  exit(0);
}

int main(int argc, char const *argv[]) {

  if (catch_signal(SIGINT, handle_shutdown) == -1)
    // 如果有人按了 Ctrl-c 就调用 handle_shutdown()
    error("Can't set the interrupt handler");

  // 在 30000 端口创建套接字
  listener_d = open_listener_socket();
  bind_to_port(listener_d, 30000);

  // 把队列长度设为10
  if (listen(listener_d, 10))
    error("Can't listen");

  struct sockaddr_storage client_addr;
  unsigned int address_size = sizeof(client_addr);
  puts("Waiting for connection");
  char buf[255];

  while (1) {
    int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
    if (connect_d == -1)
      error("Can't open secondary socket");

    // 向客户端发送数据
    if (say(connect_d, "Internet Knock-Knock Protocl Server\r\nVersion 1.0\r\nKnock! Knock!\r\n>") != -1) {
      // 从客户端读取数据
      read_in(connect_d, buf, sizeof(buf));
      // 检查用户的回答，如果不同则发送数据，指导它回答
      if (strncasecmp("Who's there?", buf ,12))
        // 检查用户的回答
        say(connect_d, "You should say 'Who's there?' !");
      else {
        if (say(connect_d, "Oscar\r\n>") != -1) {
          read_in(connect_d, buf, sizeof(buf));
          if (strncasecmp("Oscar who?", buf, 10))
            say(connect_d, "You should say 'Oscar who?' !\r\n");
          else
            say(connect_d, "Oscar silly question. you get a silly answer\r\n");
        }
      }
    }
    // 关闭用来对话的套接字
    close(connect_d);
  }

  return 0;
}
