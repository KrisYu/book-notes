[理解UIScrollView](https://objccn.io/issue-3-2/)

> 现在，回想一下，每个视图都有一个 bounds 和 frame。当布局一个界面时，我们需要处理视图的 frame。这允许我们放置并设置视图的大小。视图的 frame 和 bounds 的大小通常是一样的（虽然可以被 transforms 改变），但是他们的 origin 经常是不同的。弄懂这两个工作原理是理解 UIScrollView 的关键。


> The geometry of each view is defined by its frame and bounds properties. The frame property defines the origin and dimensions of the view in the coordinate system of its superview. The bounds property defines the internal dimensions of the view as it sees them and is used almost exclusively in custom drawing code. The center property provides a convenient way to reposition a view without changing its frame or bounds properties directly.

frame是在父级视图中的位置，bounds是其本身维度。


UIScrollView 用这个公式：

```
CompositedPosition.x = View.frame.origin.x - Superview.bounds.origin.x;

CompositedPosition.y = View.frame.origin.y - Superview.bounds.origin.y;
```

当我们移动时，改变Superview.bounds.origin.x。

> 现在，巧妙的是通过改变这个紫色视图的 bounds，它每一个单独的子视图都被移动了。事实上，这正是 scroll view 工作的原理。当你设置它的 contentOffset 属性时它改变 scroll view.bounds 的 origin。事实上，contentOffset 甚至不是实际存在的。代码看起来像这样：

```
- (void)setContentOffset:(CGPoint)offset
{
    CGRect bounds = [self bounds];
    bounds.origin = offset;
    [self setBounds:bounds];
}
```

>  content size 设置为比 bounds 大的时候，用户就可以滚动视图了。你可以认为 scroll view 的 bounds 为可滚动区域上的一个窗口

> 当你想要使用 UIRefreshControl 实现拉动刷新时发生了什么？你不能在 table view 的可滚动区域内放置 UIRefreshControl，否则，table view 将会允许用户通过 refresh control 中途停止滚动，并且将 refresh control 的顶部弹回到视图的顶部。因此，你必须将 refresh control 放在可滚动区域上方。这将允许首先将 content offset 弹回第一行，而不是 refresh control。

- Content Size 是可滚动区域
- Content Inset 可以调整可滚动区域
