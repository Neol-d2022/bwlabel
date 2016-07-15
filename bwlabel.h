#ifndef BWLABEL
#define BWLABEL

void bwlabel(unsigned int **arr2D, unsigned int rows, unsigned int cols, unsigned int *numLabels);

#endif

/**

=== bwlabel ===

Label connected components

Inputs
arr2D: unsigned int array (2D) of an image
rows: number of rows in that array (height)
cols: number of column in that array (width)

Outputs
numLabels: (Optional) returns the number of connected components

After each call, arr2D is modified.

 */