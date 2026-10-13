#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define STKDEBUG
#define CANARY

#ifdef STKDEBUG
	#define DEBUG_ON(...) __VA_ARGS__
#else
	#define DEBUG_ON(...) ;
#endif

#ifdef CANARY
	#define CANARY_ON(...) __VA_ARGS__
#else
	#define CANARY_ON(...) ;
#endif

#define DEBUG_FIELDS 	DEBUG_ON(     \
			const char* name;         \
								      \
			const char* file_name;    \
			const char* func_name;    \
			unsigned int line;        \
			const char* time;         \
			const char* date;         \
			) 

#define DEBUG_PARAMS DEBUG_ON(         \
			,const char* name          \
			                           \
			, const char* file_name    \
			, const char* func_name    \
			, unsigned int line        \
			, const char* time         \
			, const char* date         \
			)

#define START_CAN_VAL (double) 0xC00C01D
#define END_CAN_VAL (double) 0xC418
#define START_DATA_CAN_VAL (double) 0xAC00C01D
#define END_DATA_CAN_VAL (double) 0xAC418

#define VAR_NAME(var) #var

#define INT_POISON  0xB110A
#define DBL_POISON  nan

#define FUNC_START DEBUG_ON(printf("%s started\n", __FUNCTION__);)
#define FUNC_END DEBUG_ON(printf("%s ended\n", __FUNCTION__);)



enum ERRNO
{
	NO_ERROR = 0,
	LESS_ZERO_CAP_OR_SIZE = -1,
	NULL_PTR_STK = -2,
	NULL_PTR_STKBUF = -3,
	OUT_OF_RANGE = -4,
	STACK_UNDERFLOW = -5,	
	WRONG_CANARIES = -6,
};

struct Stack
{
	CANARY_ON (double start_canary;)

	DEBUG_FIELDS

	double* data;
	double* raw_data;

	size_t capacity;
	size_t size;

	CANARY_ON (double end_canary;)
};

#include "prototypes.h"

#endif