#include "stack.h"

int fill_poison(struct Stack* stk)
{
	for (int i = stk->size; i < stk->capacity; i++)
	{
		if (i == 0) continue;
		stk->data[i] = NAN;
	}
	return 0;
}

void debug_init(struct Stack* stk)
{
	#ifdef STKDEBUG
		stk->file_name = __FILE__;
		stk->func_name = __FUNCTION__;
		stk->time = __TIME__;
		stk->date = __DATE__;
		stk->line =  __LINE__;
	#endif
}

void canary_init(struct Stack* stk)
{
	#ifdef CANARY
		stk->start_canary = START_CAN_VAL;
		stk->end_canary = END_CAN_VAL;

		stk->data[0] = START_DATA_CAN_VAL;
		stk->data[stk->capacity + 1] = END_DATA_CAN_VAL;

		stk->data = &(stk->data[1]);
	#endif
	
}

int stack_init(struct Stack* stk, size_t capacity)
{	
	//if (verificator(stk) == NULL_PTR_STK) {fprintf(stdout, "NULL PTR STACK\n"); choose_exit();}

	//Initialisation
	stk->capacity = capacity;
	stk->size = 0;
	stk->data = (double*) malloc(sizeof(double));

	debug_init(stk);

	DEBUG_ON(printf("I CHECK_ERROR in init\n");)

	CHECK_ERROR(stk)

	stk->data = (double* ) realloc(stk->data, (capacity + 2) * sizeof(double));
	canary_init(stk);
 
	DEBUG_ON(printf("II CHECK_ERROR in init\n");)
	CHECK_ERROR(stk)

	fill_poison(stk);

	DEBUG_ON(printf("III CHECK_ERROR in init\n");)
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

		#ifdef CANARY
			stk->data[-1] = START_DATA_CAN_VAL;
			stk->data[stk->capacity] = END_DATA_CAN_VAL;
		#endif
	}

	CHECK_ERROR(stk)
	return 0;
}

int resize_down(struct Stack* stk)
{
	FUNC_START

	CHECK_ERROR(stk)

	//dump_stack(stdout, stk, 0);


	if (stk->size < stk->capacity / 8)
	{
		printf("HUY\n");
		stk->data = realloc(stk->data, ((stk->capacity > 5) ? (stk->capacity /= 2) : 5) * sizeof(double));
		#ifdef CANARY
			stk->data[-1] = START_DATA_CAN_VAL;
			stk->data[stk->capacity] = END_DATA_CAN_VAL;
		#endif
	}

	CHECK_ERROR(stk)

	FUNC_END

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
	FUNC_START

	CHECK_ERROR(stk)

	if (stk->size == 0)
	{
		fprintf(stdout, "UNDERFLOW error, u cant pop any element, cause there nothing to pop. I will pass this command\n");
		dump_stack(stdout, stk, STACK_UNDERFLOW);
		dump_stack(stderr, stk, STACK_UNDERFLOW);
		choose_exit();

		return STACK_UNDERFLOW;
	}

	stk->size--;
	*value = stk->data[stk->size];
	stk->data[stk->size] = NAN;
	resize_down(stk);
	DEBUG_ON(printf("poped val = %g\n", *value);)

	CHECK_ERROR(stk)

	FUNC_END

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

	#ifdef CANARY
		free(&(stk->data[-1]));
	#else
		free(stk->data);
	#endif

	stk->capacity = 0;
	stk->size = 0;
}