/*
 * ip_client.c
 * 连接 checkip.dyndns.org 网站
 * 获得网站内容，在屏幕上显示
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

void error(char *msg)
{
  fprintf(stderr, "%s %s\n",msg, strerror(errno));
  exit(1);
}

int open_socket(char* host, char* port)
{
  struct addrinfo *res;

  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if (getaddrinfo(host, port, &hints, &res) == -1)
    error("Can't resolve the address");

  int d_sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
  if (d_sock == -1)
    error("Can't open socket");

  int c = connect(d_sock, res->ai_addr, res->ai_addrlen);

  freeaddrinfo(res);
  if (c == -1)
    error("Can't connect to socket");

  return d_sock;
}

int say(int socket, char *s)
{
  int result = send(socket, s, strlen(s), 0);

  if (result == -1)
    fprintf(stderr, "%s: %s \n","Error talking to the server", strerror(errno));

  return result;
}

int main(int argc, char const *argv[])
{
  int d_sock;

  d_sock = open_socket("checkip.dyndns.org", "80");
  char buf[255];

  sprintf(buf,"GET / HTTP/1.1\r\n");
  say(d_sock, buf);

  say(d_sock, "Host: checkip.dyndns.org\r\n\r\n");
  char rec[256];

  int bytesRcvd = recv(d_sock, rec, 255, 0);
  while (bytesRcvd) {
    if (bytesRcvd == -1)
      error("Can't read from server");

    rec[bytesRcvd] = '\0';
    printf("%s\n",rec );
    bytesRcvd = recv(d_sock, rec, 255, 0);
  }
  close(d_sock);

  return 0;
}
