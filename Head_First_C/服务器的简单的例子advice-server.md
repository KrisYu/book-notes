# BLAB： 服务器连接网络四部曲

blab - bind, listen, accept, begin 

首先创建数据流- 套接字：

```
#include <sys/socket.h>

int listener_d = socket(PF_INET, SOCK_STREAM, 0);
//listener_d 套接字描述符
// 协议号填0
if (listener_d == -1)
  error("无法打开套接字"); // 上一章的 error() 函数
```

- 绑定端口 bind

```
#include <arpa/inet.h>

...
struct sockaddr_in name;
name.sin_family = PF_INET;
name.sin_port = (in_port_t)htons(30000);
name.sin_addr.s_addr = htonl(INADDR_ANY);
// 创建一个表示 ‘互联网30000端口’ 的套接字名
int c = bind(listener_d, (struct sockaddr *) &name, sizeof(name));
if (c == -1)
  error("无法绑定端口");
```


- 监听 listen


```
if (listen(listener_d, 10) == -1)
  error("无法监听");
  
// 10 表示监听队列长度为 10
```

- 接收连接 accept

绑定端口，设置监听队列，现在需要的就是等待。 服务器一直都在等待客户端，accept()系统调用会一直等待，直到有客户端链接服务器，它会返回*第二个套接字描述符*，然后就可以用它通信


```
struct sockaddr_storage client_addr;
// client_addr 将保存连接客户端的详细信息
unsigned int address_size = sizeof(client_addr);
int connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);
if (connect_d == -1)
  error("无法打开副套接字");
```

之所以accept需要创建一个新的套接字描述符是因为原本的那个还需要继续监听端口，可能会有新的进入队列。

这里可以值得注意的是在这个例子里我们用的是 struct sockaddr_storage client_addr，而不是之前见过的 struct sockaddr 或者 struct sockaddr_in.



谷歌一下：



> struct sockaddr_storage` is designed to fit in both a `struct sockaddr_in` and `struct sockaddr_in6`

> You don't create your own `struct sockaddr`, you usually create a `struct sockaddr_in` or a `struct sockaddr_in6` depending on what IP version you're using. In order to avoid trying to know what IP version you will be using, you can use a `struct sockaddr_storage` which can hold either. This will in turn be typecasted to `struct sockaddr` by the connect(), bind(), etc functions and accessed that way.

[Reasoning behind C sockets sockaddr and sockaddr_storage](https://stackoverflow.com/questions/16010622/reasoning-behind-c-sockets-sockaddr-and-sockaddr-storage) 




- 开始通信 begin


看完整的文件例子：


```
/*
 * advice_server.c
 * 为连接的用户随机提出建议
 */

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

  // 创建socket 互联网套接字
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

    // 4.开始和客户端通信
    send(connect_d, msg, strlen(msg), 0);
    close(connect_d);
  }

  return 0;
}
```

运行

``` 
> gcc advice_server.c -o advice_server
> ./advice_server
```

然后需要打开一个新的服务台


```
> telnet 127.0.0.1 30000
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
Take smaller bites
Connection closed by foreign host.
```

我们在本机运行，所以需要 127.0.0.1 作为IP.

当然，也可以配合局域网内两台电脑一起测试，也是一样的效果。 

这是一个特别简单的例子，里面缺少错误处理，并且一旦我们telnet连接之后就会关闭。但这已经写出了一个一般的 socket 编程的大概。

值得注意的还包括：

- 两个套接字，两个 struct sockaddr_in， 一个 name 和一个 client_addr
- 对于第一个设置好绑定用的是  `bind(listener_d, (struct sockaddr *) &name, sizeof(name));`
- 第二个设置之时最后一个参数： `unsigned int address_size = sizeof(client_addr); ` 然后 `connect_d = accept(listener_d, (struct sockaddr *)&client_addr, &address_size);` 并不是像第一个那样参数随意，而是用的reference
- 给客户端发送数据用的： `send(connect_d, msg, strlen(msg), 0);`
- 发送完成我们即刻关闭
- 整个程序用到的函数包括： socket, bind, listen, accept, send, close


所以 ASCII 版本的 star wars 究其本质，用的就是这样的原理吧：

```
// get star wars in your Terminal
telnet towel.blinkenlights.n
```

[advice-server2.c](advice_server2.c) 基本上跟 [advice-server.c](advice_server.c) 一致，就增加了一点错误处理，同时解决了绑定端口的延时处理。
