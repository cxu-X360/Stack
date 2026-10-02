#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define STKDEBUG

#ifdef STKDEBUG
	#define DEBUG_ON(...) __VA_ARGS__
#else
	#define DEBUG_ON(...)
#endif

#define DEBUG_FIELDS 	DEBUG_ON(     \
			const char* name;     \
								      \
			const char* file_name;    \
			const char* func_name;    \
			unsigned int line;  \
			const char* time;         \
			const char* date;         \
			) 

#define DEBUG_PARAMS DEBUG_ON(         \
			,const char* name      \
			                           \
			, const char* file_name    \
			, const char* func_name    \
			, unsigned int line  \
			, const char* time         \
			, const char* date         \
			)



#define VAR_NAME(var) #var



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

	DEBUG_FIELDS

	double* data;

	size_t capacity;
	size_t size;
};

#endif