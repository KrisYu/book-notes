
- (instancetype)initWithTitle:(NSString *)title image:(UIImage *)image selectedImage:(UIImage *)selectedImage;

Description	

Creates and returns a new item with the specified title, unselected image, and selected image.

If no selectedImage is provided, image is used as both the unselected and selected image.

By default, the actual unselected and selected images are automatically created from the alpha values in the source images. To prevent system coloring, provide images with UIImageRenderingModeAlwaysOriginal.

这里提到了 system coloring 是指的会自动调整颜色，然而我测试并没有肉眼可见太大区别|||