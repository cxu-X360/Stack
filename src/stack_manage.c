#include "..\include\prototypes.h"
#include "..\include\stack.h"

int fill_poison(struct Stack* stk)
{

	for (int i = stk->size; i < stk->capacity; i++)
	{
		stk->data[i] = NAN;
	}

	return 0;
}

int stack_init(struct Stack* stk, size_t capacity)
{	
	//Initialisation
	stk->capacity = capacity;
	stk->size = 0;

	#ifdef STKDEBUG

		stk->file_name = __FILE__;
		stk->func_name = __FUNCTION__;

		stk->time = __TIME__;
		stk->date = __DATE__;


		stk->line =  __LINE__;

	#endif

	printf("I CHECK_ERROR in init\n");
	CHECK_ERROR(stk)

	stk->data = (double* ) calloc(capacity, sizeof(double));
 
	printf("II CHECK_ERROR in init\n");
	CHECK_ERROR(stk)

	fill_poison(stk);


	printf("III CHECK_ERROR in init\n");
	CHECK_ERROR(stk)

	return 0;
}

int resize_up(struct Stack* stk)
{
	CHECK_ERROR(stk);

	if (stk->size > stk->capacity) return OUT_OF_RANGE;

	if (stk->size == stk->capacity) 
	{
		stk->data = realloc(stk->data, (stk->capacity *= 2) * sizeof(double));
		fill_poison(stk);
	}

	CHECK_ERROR(stk)
	

	return 0;
}

int resize_down(struct Stack* stk)
{
	CHECK_ERROR(stk)

	if (stk->size <= stk->capacity / 4)
	{
		stk->data = realloc(stk->data, ((stk->capacity > 5) ? (stk->capacity /= 2) : 5) * sizeof(double));
	}

	CHECK_ERROR(stk)

	return 0;
}


int stack_push(struct Stack* stk, double value)
{
	CHECK_ERROR(stk)

	resize_up(stk);

	stk->data[stk->size]= value;

	(stk->size)++;

	CHECK_ERROR(stk)

	return 0;
}

int stack_pop(struct Stack* stk, double* value)
{
	CHECK_ERROR(stk)

	if (stk->size == 0)
	{
		fprintf(stderr, "UNDERFLOW error, u cant pop any element, cause there nothing to pop. I will pass this command\n");
		return STACK_UNDERFLOW;
	}

	stk->size--;

	*value = stk->data[stk->size];

	resize_down(stk);

	fill_poison(stk);

	printf("poped val = %g\n", *value);

	CHECK_ERROR(stk)

	return 0;
}

int stack_destroy(struct Stack* stk)
{
	CHECK_ERROR(stk)

	#ifdef STKDEBUG

		stk->file_name = "";
		stk->func_name = "";

		stk->time = "";
		stk->date = "";


		stk->line = 0;



	#endif

	free(stk->data);

	stk->capacity = 0;
	stk->size = 0;
}