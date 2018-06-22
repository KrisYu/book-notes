TabBar下面的tab 按钮点击 highlight 和 不highlight的时候有不同的效果，发现是`- (instancetype)initWithTitle:(NSString *)title image:(UIImage *)image selectedImage:(UIImage *)selectedImage;` 这个函数的功劳，这样默认 image 和 selectedImage 不一样。

如果发现跟预想的不太一样，那么可能是rendering的原因，我们可以调整：
`- (UIImage *)imageWithRenderingMode:(UIImageRenderingMode)renderingMode;` 可能需要把 renderingMode 设定为 UIImageRenderingModeAlwaysOriginal. 这样rendering的图片就不会被调整。
