这个问题来自于so：


['Calling a method' OR 'sending a message' in Objective C](https://stackoverflow.com/questions/2852381/calling-a-method-or-sending-a-message-in-objective-c)


理论上，它们是不同的。

实际上，并非如此。

它们在Objective-C中的不同之处在于，对象可以选择不响应消息，或将消息转发到不同的对象或任何其他对象。在像C这样的语言中，函数调用实际上只是跳到内存中的某个位置并执行代码。没有涉及动态行为。

但是，在标准用例中，当您向对象发送消息时，消息表示的方法通常最终会被调用。所以大约99％的时间，发送消息将导致调用方法。因此，当我们真正的意思是“发送消息”时，我们经常说“调用方法”。实际上，它们几乎总是相同的，但它们不一定是。

前一段时间，我在这个主题上发表了哲学观点，并对此进行了博客：http://davedelong.tumblr.com/post/58428190187/an-observation-on-objective-c

编辑

要直接回答你的问题，说“调用方法”而不是“发送消息”通常没有错。但是，理解实施差异非常重要很重要。

谷歌翻译而来的答案。


===============

实际上，这个问题很值得回答：这是Effective Objective-C书中的第1条：了解Objective-C语言的起源。

使用 messaging structure的语言，运行时所执行的代码由运行环境决定；而使用函数调用 function calling的语言，则由编译器决定。

使用 messaging structure（消息结构）的语言，无论是否多态，总是再运行时才会去查找要执行的代码，实际上OC的重要工作都由 runtime component 而非便一起来完成。
