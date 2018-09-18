/*
 * getip.c
 * 输入网站地址，输出其ip地址等相关信息
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
  struct hostent* ht;
  char** pptr;
  int type;

  if (argc != 2) {
    fprintf(stderr, "usage: ./getip [address]\n");
    exit(EXIT_FAILURE);
  }

  // 用 ht/gethostbyname 来取得 struct hostent
  // 如果失败报错
  if (!(ht = gethostbyname(argv[1]))) {
    // 注意这里使用的是 herror, 因为 errno 没有使用
    herror("main gethostbyname error");
    exit(EXIT_FAILURE);
  }

  // 打印所有信息
  printf("Host name is: %s\n", ht->h_name);
  // 打印所有的主机地址
  for (pptr = ht->h_aliases; (*pptr) ; ++pptr)
    printf("   alias of host: %s\n",(*pptr) );
  printf("Host addrtype is: %d\n", type = ht->h_addrtype );
  printf("Host length is: %d\n",ht->h_length);

  if (type == AF_INET || type == AF_INET6) {
    char ip[32];
    for (pptr = ht->h_addr_list; (*pptr) ; ++pptr) {

      inet_ntop(type, *pptr, ip, sizeof ip);
      printf("   address: %s\n",ip);
    }
  }
  return 0;
}
