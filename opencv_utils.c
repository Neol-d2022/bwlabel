#include <stdlib.h>
//#include <stdio.h>

#include <opencv2/imgproc/imgproc_c.h>

unsigned int** extractUintArr(IplImage *img, unsigned int channel) {
	CvScalar val;
	CvSize s;
	unsigned int **ret;
	
	int i, j, k;
	s = cvGetSize(img);
	ret = (unsigned int **)malloc(s.height * sizeof(*ret));
	if(!ret) {
		return 0;
	}
	
	for(i = 0; i < s.height; i += 1) {
		ret[i] = (unsigned int *)malloc(s.width * sizeof(**ret));
		if(!ret) {
			for(k = 0; k < i; k += 1) {
				free(ret[k]);
			}
			free(ret);
			return 0;
		}
		
		for(j = 0; j < s.width; j += 1) {
			val = cvGet2D(img, i, j);
			ret[i][j] = val.val[channel];
			//fprintf(stderr, "(%u,%u)=%u\n", i, j, ret[i][j]);
		}
	}
	
	return ret;
}

void freeUintArr(unsigned int **arr, int height) {
	int i;
	
	for(i = 0; i < height; i += 1) {
		free(arr[i]);
	}
	free(arr);
}

unsigned int** copyUintArr(const unsigned int **srcArr, int height, int width) {
	unsigned int **ret;
	int i, j, k;
	
	ret = (unsigned int **)malloc(height * sizeof(*ret));
	if(!ret) return 0;
	
	for(i = 0; i < height; i += 1) {
		ret[i] = (unsigned int *)malloc(width * sizeof(**ret));
		if(!ret) {
			for(k = 0; k < i; k += 1) free(ret[k]);
			free(ret);
			return 0;
		}
		for(j = 0; j < width; j += 1) ret[i][j] = srcArr[i][j];
	}
	
	return ret;
}