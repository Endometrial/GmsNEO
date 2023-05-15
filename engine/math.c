
#include <engine/math.h>

// I like when variadic functions show the typing of values
// so im adding val. if you dont like it get fucked lolz.
float* math_fvector_create(int length, float val, ...) {
	float* vector;
	va_list values;
	vector = malloc(length * sizeof(float));

	vector[0] = val;
	va_start(values, val); // val refers to the argument not value of val
	for (unsigned int i=1; i<length; i++) {
		// parameters are promoted when typing is not known at call
		// char -> int
		// float -> double etc...
		// fuck this took ages to find out about
		vector[i] = va_arg(values, double);
	}
	va_end(values);

	return vector;
}

float* math_fmatrix_create(int columns, int rows, float val, ...) {
	float* matrix;
	va_list values;
	malloc(columns * rows * sizeof(float));

	matrix[0] = val;
	va_start(values, val);
	for (unsigned int i=1; i<(columns * rows); i++) {
		matrix[i] = va_arg(values, double);
	}
	va_end(values);

	return matrix;
}

void math_free(float* construct) {
	free(construct);
}