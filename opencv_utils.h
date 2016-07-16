#ifndef UTILS
#define UTILS

#include <opencv2/imgproc/imgproc_c.h>

unsigned int** extractUintArr(IplImage *img, unsigned int channel);
void freeUintArr(unsigned int **arr, int height);

unsigned int** copyUintArr(const unsigned int **srcArr, int height, int width);

#endif

/**

=== extractUcharArr ===

Extract unsigned int array (2D) from an image.

Inputs
img: Data structure defined in OpenCV
channel: color space channel defined in OpenCV(Range: 0 ~ 3)

Returns unsigned int array (2D)
It MUST be freed(using freeUcharArr() ) after used.

Return null on failure.


=== freeUcharArr ===

Release unsigned int array (2D).

Inputs
arr: unsigned char int array (2D) to be freed
size: image size which represented by arr

Returns nothing


=== copyUintArr ===

Copy an unsigned int array (2D).

Inputs
srcArr: source unsigned char int array (2D) to be copied
height: height of that array
width: width of that array

Returns unsigned int array (2D)
It MUST be freed(using freeUcharArr() ) after used.

Return null on failure.
 */