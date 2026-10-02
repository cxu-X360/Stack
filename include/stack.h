#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>


#ifdef STKDEBUG
	#define DEBUG_ON(...) __VA_ARGS__
#else
	#define DEBUG_ON(...)
#endif



#define __VAR_NAME__(var) #var



#define INT_POISON  0xB110A
#define DBL_POISON  nan



enum ERRNO
{
	NO_ERROR = 0,
	LESS_ZERO_CAP = -1,
	NULL_PTR_STK = -2,
	NULL_PTR_STKBUF = -3,
	OUT_OF_RANGE = -4,
	STACK_UNDERFLOW = -5,
};



struct Stack
{
	DEBUG_ON(
			const char* name;

			const char* file_name;
			const char* func_name;
			const int line;
			)



	double* data;

	size_t capacity;
	size_t size;
};

#endif