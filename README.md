mini_yuv_lib

Function:
	scale yuv420 image and convert yuv420 to jpg.

Description:
	1.scale source from libyuv.
	2.convert yuv to jpg without libjpeg, you can convert normal-image(YCbCr)
to jpg by open "UV_PARAM", convert grey-image(Y) to jpg by close "UV_PARAM".The
macro defination at yuv2jpg.h.

USAGE:
	Details see example.c. 
