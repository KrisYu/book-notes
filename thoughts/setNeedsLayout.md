- setNeedsLayout will layout subviews


	Call this method on your application’s main thread when you want to adjust the layout of a view’s subviews.

- setNeedsDisplay will call for a redraw of your view (drawRect:, etc).

	You can use this method or the setNeedsDisplayInRect: to notify the system that your view’s contents need to be redrawn.
	
	
	
	Layout is not about drawing. Layout is about positioning/sizing subviews. But yes, both delay to the next runloop cycle. So calling one multiple times in a row will only result in one relayout/redraw