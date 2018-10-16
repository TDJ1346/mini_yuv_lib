#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "yuv2jpg.h"
#include "scale.h"

#define SRC_WIDTH 1280
#define SRC_HEIGHT 720
#define DST_WIDTH 128
#define DST_HEIGHT 72

int scale_yuv(unsigned char *srcY, unsigned char *srcU, unsigned char *srcV)
{
	size_t dLen; 
	unsigned char *dstAll, *dstY, *dstU, *dstV;
	//unsigned char *srcY, *srcU, *srcV;
	FILE *dstFile;
	
	//printf("srcAll = %p\n", srcAll);
	
	/*srcY = (unsigned char *)malloc(SRC_WIDTH * SRC_HEIGHT);
	if (srcY == NULL) {
		printf("srcY malloc error!\n");
		return -1;
	}

	srcU = (unsigned char *)malloc(SRC_WIDTH * SRC_HEIGHT / 4);
	if (srcU == NULL) {
		printf("srcU malloc error!\n");
		return -1;
	}

	srcV = (unsigned char *)malloc(SRC_WIDTH * SRC_HEIGHT / 4);
	if (srcV == NULL) {
		printf("srcV malloc error!\n");
		return -1;
	}*/

	dstAll = (unsigned char *)malloc(DST_WIDTH * DST_HEIGHT * 3/2);
	if (dstAll == NULL) {
		printf("dstAll malloc error!\n");
		return -1;
	}

	dstY = (unsigned char *)malloc(DST_WIDTH * DST_HEIGHT);
	if (dstY == NULL) {
		printf("dstY malloc error!\n");
		return -1;
	}

	dstU = (unsigned char *)malloc(DST_WIDTH * DST_HEIGHT / 4);
	if (dstU == NULL) {
		printf("dstU malloc error!\n");
		return -1;
	}

	dstV = (unsigned char *)malloc(DST_WIDTH * DST_HEIGHT / 4);
	if (dstV == NULL) {
		printf("dstV malloc error!\n");
		return -1;
	}

	/*memcpy(srcY, srcAll, SRC_WIDTH * SRC_HEIGHT);	
	memcpy(srcU, srcAll + SRC_WIDTH * SRC_HEIGHT, SRC_WIDTH * SRC_HEIGHT / 4);	
	memcpy(srcV, srcAll + SRC_WIDTH * SRC_HEIGHT * 5/4, SRC_WIDTH * SRC_HEIGHT / 4);*/
	//printf("----------6---------\n");
	Scale(srcY,
	//	srcAll + SRC_WIDTH * SRC_HEIGHT,
	//	srcAll + SRC_WIDTH * SRC_HEIGHT * 5/4,
		srcU,
		srcV,
		SRC_WIDTH,
		SRC_WIDTH / 2,
		SRC_WIDTH / 2,
		SRC_WIDTH,
		SRC_HEIGHT,
		//dstAll,
		//dstAll + DST_WIDTH * DST_HEIGHT,
		//dstAll + DST_WIDTH * DST_HEIGHT * (5/4),
		dstY,
		dstU,
		dstV,
		DST_WIDTH,
		DST_WIDTH / 2,
		DST_WIDTH / 2,
		DST_WIDTH,
		DST_HEIGHT,
		1);
		
	memcpy(dstAll, dstY, DST_WIDTH * DST_HEIGHT);
	memcpy(dstAll + DST_WIDTH * DST_HEIGHT, dstU, DST_WIDTH * DST_HEIGHT / 4);
	memcpy(dstAll + DST_WIDTH * DST_HEIGHT * 5/4, dstV, DST_WIDTH * DST_HEIGHT / 4);

	//printf("----------7---------\n");
	dstFile = fopen("128_72.yuv", "wb");
	if (dstFile == NULL) {
		printf("128_72.yuv open error!\n");
		return -1;
	}
	
	dLen = fwrite(dstAll, DST_WIDTH * DST_HEIGHT * 3/2, 1, dstFile);
	if (dLen < 0) {
		printf("128_72.yuv write data error!\n");
		return -1;	
	}

	free(dstAll);	
	free(dstY);
	free(dstU);
	free(dstV);
	fclose(dstFile);	
	
	return 0;
}

int yuv_to_jpg(unsigned char *srcY, unsigned char *srcU, unsigned char *srcV)
{
	FILE *jpgFile;
	size_t jLen;
	unsigned char *jData;
	
	jData = (unsigned char *)malloc(SRC_WIDTH * SRC_HEIGHT);
	if (jData == NULL) {
		printf("jData malloc error!\n");
		return -1;
	}
	
	YUV2Jpg(srcY,
		srcU,
		srcV,
		SRC_WIDTH,
		SRC_HEIGHT,
		100,
		SRC_WIDTH,
		jData,
		&jLen);

	jpgFile = fopen("1280_720.jpg", "wb");
	if (jpgFile == NULL) {
		printf("1280_720.jpg open error!\n");
		return -1;
	}
	
	jLen = fwrite(jData, jLen, 1, jpgFile);
	if (jLen < 0) {
		printf("1280_720.jpg write error!\n");
		return -1;
	}

	free(jData);
	fclose(jpgFile);

	return 0;
}
 
int main()
{
	FILE *srcFile;
	size_t sLen;
	int ret; 
	unsigned char *srcAll, *srcY, *srcU, *srcV;
	
	//printf("----------0---------\n");
	srcAll = (unsigned char *)malloc(SRC_HEIGHT * SRC_WIDTH * 3/2);
	if (srcAll == NULL) {
		printf("srcAll malloc error!\n");
		return -1;
	}
	
	srcY = (unsigned char *)malloc(SRC_WIDTH * SRC_HEIGHT);
	if (srcY == NULL) {
		printf("srcY malloc error!\n");
		return -1;
	}

	srcU = (unsigned char *)malloc(SRC_WIDTH * SRC_HEIGHT / 4);
	if (srcU == NULL) {
		printf("srcU malloc error!\n");
		return -1;
	}

	srcV = (unsigned char *)malloc(SRC_WIDTH * SRC_HEIGHT / 4);
	if (srcV == NULL) {
		printf("srcV malloc error!\n");
		return -1;
	}
	
	//printf("----------1---------\n");
	srcFile = fopen("1280_720.yuv", "rb"); 
	if (srcFile == NULL) {
		printf("1280_720.yuv open error!\n");
		return -1;
	}
	//printf("----------2---------\n");
	
	sLen = fread(srcAll, SRC_HEIGHT * SRC_WIDTH * 3/2, 1, srcFile);
	if (sLen < 0) {
		printf("1280_720.yuv read data error!\n");
		return -1;
	}
	
	memcpy(srcY, srcAll, SRC_WIDTH * SRC_HEIGHT);	
	memcpy(srcU, srcAll + SRC_WIDTH * SRC_HEIGHT, SRC_WIDTH * SRC_HEIGHT / 4);	
	memcpy(srcV, srcAll + SRC_WIDTH * SRC_HEIGHT * 5/4, SRC_WIDTH * SRC_HEIGHT / 4);	
	
	//printf("222---srcAll = %p\n", srcAll);
	//printf("----------3---------\n");
	ret = scale_yuv(srcY, srcU, srcV);
	if (ret < 0) {
		printf("scale yuv error!\n");
		return -1;
	}
	//printf("----------4---------\n");
	
	ret = yuv_to_jpg(srcY, srcU, srcV);	
	if (ret < 0) {
		printf("convert jpg error!\n");
		return -1;
	}
	//printf("----------5---------\n");
	
	free(srcV);
	free(srcU);
	free(srcY);
	free(srcAll);
	fclose(srcFile);

	return 0;
}
