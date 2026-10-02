#define STKDEBUG  //TURN ON-OFF by delete/set comment

#include "stack.h"

#define debug_push(stk, val) do {stack_push(&(stk), (val)); print_stack(&(stk));} while(0)
#define debug_pop(stk) do {double term_var = 0; stack_pop(&(stk), &(term_var)); print_stack(&(stk));} while(0)

#define print_var_val(...) fprintf(...) 

void clear_buffer()  //очищает стандартный буффер ввода до \n включительно вызовами getchar()
{
	char _ = 0;
	while ((_ = (char) getchar()) != '\n' && _ != EOF){}
}

int choose_exit()
{
	fprintf(stderr, "----------------------------------------------------------------------------------------------\n");

	bool is_finish = false;

	fprintf(stdout, "Do u wanna exit ? (Y/N)");


	char choosing = fgetc(stdin);
	clear_buffer();

	if (choosing == 'Y' || choosing == 'y' ) {fprintf(stdout, "Goodbye!!\n"); exit(-1);}

	return 0;



}

int dump_stack(struct Stack* stk, enum ERRNO error)
{
	#ifdef STKDEBUG

		fprintf(stderr, "\n\nSTACK_DUMP\n----------------------------------------------------------------------------------------------\n");	

		if (error == NULL_PTR_STK) return -fprintf(stderr, "NULL PTR STACK\n");


		fprintf(stderr, "Stack <%s>[%p] created by <%s> at <%s:%d>\n{\n\t", stk->name, &stk, stk->func_name, stk->file_name, stk->line);
			fprintf(stderr, "1)size = <%zu (or signed <%lld>)>\n\t", stk->size, (ssize_t) stk->size;
			fprintf(stderr, "2)capacity = <%zu (or signed <%lld>)>\n\t", stk->capacity, (ssize_t) stk->capacity);

			if (error == NULL_PTR_STKBUF) return -fprintf(stderr, "NULL PTR on STACK BUFFER\n");
			fprintf(stderr, "3)data[%zu] = \n{\n\t", stk->capacity);

				if (error == LESS_ZERO_CAP) return -fprintf(stderr, "LESS OR ZERO CAPACITY or SIZE");
				if (error == OUT_OF_RANGE) return -fprintf(stderr, "OUT_OF_RANGE - SIZE > capacity");

				for (size_t i = 0; i < stk->size; i++)
				{
					fprintf(stderr, "* [%zu] = <%g>[%p]\n\t\t", i, (stk->data)[i], &((stk->data)[i]));
				}

				for (size_t i = stk->size; i < stk->capacity; i++)
				{
					fprintf(stderr, " [%zu] = <%g>[%p]\n\t\t", i, POISON, NULL);
				}

		fprintf(stderr, "\n");

		fprintf(stderr, "ERROR_Num = <%d>..... Error codes \n{\n", error);
			fprintf(stderr, "	NO_ERROR = 0,\n\t"
							"LESS_ZERO_CAP = -1,\n\t"
							"NULL_PTR_STK = -2,\n\t"
							"NULL_PTR_STKBUF = -3,\n\t"
							"OUT_OF_RANGE = -4,\n\t"
							"STACK_UNDERFLOW = -5,\n\t");


	#endif
}

int verificator(struct Stack* stk)
{
	printf("verificator started\n");
	if (stk == NULL) {return NULL_PTR_STK; }

	if ((ssize_t) (stk->capacity) <= 0 || (ssize_t) (stk->size) < 0) {printf("cap <= 0\n");return LESS_ZERO_CAP; }

	if (stk->data == NULL) {return NULL_PTR_STKBUF; }

	if (stk->size > stk->capacity) return OUT_OF_RANGE;

	return 0;
}

int print_stack(struct Stack* stk)
{
	putchar('[');

	for (size_t i = 0; i < stk->capacity; i++)
	{
		printf("%3g  ", stk->data[i]);
	}

	printf("]: capacity = <%zu>, size = <%zu>\n", stk->capacity, stk->size);
}

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

int main()
{
	struct Stack stk1 = {};

	stack_init(&stk1, 100);

	print_stack(&stk1);

	stk1.size = -1;

	for (double i = 0; i < 25.0; i++)
	{
		debug_push(stk1, i);
	}

	for (double i = 0; i < 25.0; i++)
	{
		debug_pop(stk1);
	}
	debug_pop(stk1);


	return 0;
}