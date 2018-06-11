### 静态绑定 static binding


编译器就能决定运行时所应调用的函数：

```
#include <stdio.h>

void printHello() {
  printf("Hello, world!\n");
}


void printGoodBye() {
  printf("Goodbye, world!\n");
}


void doTheThing(int type) {
  if (type == 0) {
    printHello();
  } else {
    printGoodBye();
  }

}

int main(int argc, char const *argv[]) {
  doTheThing(0);
  return 0;
}

```


###  动态绑定

所需调用的函数运行期才能确定：

```
#include <stdio.h>


void printHello() {
  printf("Hello, world!\n");
}


void printGoodBye() {
  printf("Goodbye, world!\n");
}


void doTheThing(int type) {
  void (*fnc)();
  // function pointer 
  if (type == 0) {
    fnc = printHello;
  } else {
    fnc = printGoodBye;
  }
  fnc();
}

int main(int argc, char const *argv[]) {
  doTheThing(1);
  return 0;
}
```

所以C是可以fake dynamic binding的。



在OC中，再底层，所有方法都是普通的C语言函数，应该调用哪个方法完全于运行期决定，甚至可以在程序运行时改变。



```
id returnValue = [someObject messageName: parameter];
```

实际上运行时是：

函数 objc_msgSend(id self, SEL cmd, ...) 

这是一个参数可变函数，最终的...是parameters.


```
id returnValue = objc_msgSend(someObject,
								   @selector(messageName:),
								   parameter);
```				



objc_msgSend 会在 list of methods 中找方法列表，如果无法找到，就会朝上查找，直到找到合适的方法再跳转。这个函数将会开始跟我们经常见面。


EOC第11： 理解objc-msgSend的作用

 