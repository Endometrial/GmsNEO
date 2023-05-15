#ifndef MATH_H
#define MATH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

float* math_fvector_create(int length, float val, ...);
float* math_fmatrix_create(int columns, int rows, float val, ...);
void math_free(float* vector);

#endif