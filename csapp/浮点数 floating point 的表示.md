# 浮点数 floating point 的表示

`V = (-1) ^s * M * 2^E`

其中：

- (-1)^s 表示符号位， s = 0，V 为正数; s = 1， V 为负数
- M 是有效数字： [1.0, 2.0)
- E 是指数位


```
| s | exp | frac |

32位
|s|    exp   | frac 
 1    8-bits   23 bits

64位
|s|    exp   | frac 
 1    11-bits   52 bits
```

根据 exp 是否全为0 又分为三种情况：

### normalized value

- exp != 00..0, exp != 11..1
- E = Exp - Bias: Bias = 2^(k-1) - 1， k 就是 exp bits 位数，对于单精度（32位），Bias 是127， 双精度是1023
- M = 1.xxx...x2, M 是只取了小数点右边的部分， 当 frac = 00..0，M = 1.0， 当 frac = 11..1， M = 2.0 - ε，这样我们就可以节约放1的那一位了


看例子一个：

15213(10) = 11101101101101(2) =  1.1101101101101(2) x 2^13

- frac 部分 ：M = 1101101101101 ， fract = 1101101101101 0000000000 （加上补的0
- exp 部分： E = 13, exp = 127 + 13 = 140 = 10001100

结果：

```
0 10001100 11011011011010000000000
```

### Denormalized value

- exp = 000..0
- E = 1 - Bias（ 而不是 E = 0(exp) - Bias），并且 M 会变成 0.xx..x
- 如果 exp = 00..0, frac = 000..0，用来代表0， 同时 +0 和 -0 是不同的
- 如果 exp = 00..0, frac != 000..0， 用来代表很接近 0 的数

### Special Values

- exp = 111..1, frac = 000..0， 代表无穷， 可以用来代表 +∞ 和 -∞
- exp = 111..1, frac != 000..0， 代表 NaN, not a number, 比如 sqrt(-1), ∞ - ∞， ∞ * 0


另： 这一篇文章也很清楚： [浮点数的二进制表示](http://www.ruanyifeng.com/blog/2010/06/ieee_floating-point_representation.html)