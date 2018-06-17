OC是动态消息系统，所以不可能有真正的‘私有方法/私有实例’。但是我们最好还是将不需要公开的写在'class-continuation分类'中.

class-continuation分类写在 .m 文件中

最常见到的集中状况是：

- 覆写‘只读’为‘可读写’
- 私有方法/属性声明在此
- 不想被知道的协议也可写在‘class-continuation’中