#include "..\include\prototypes.h"
#include "..\include\stack.h"

void clear_buffer()  //очищает стандартный буффер ввода до \n включительно вызовами getchar()
{
	char _ = 0;
	while ((_ = (char) getchar()) != '\n' && _ != EOF){}
}

int choose_exit()
{
	fprintf(stderr, "----------------------------------------------------------------------------------------------\n");

	bool is_finish = false;

	fprintf(stdout, "Do u wanna exit ? (y/N)\n");


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


		fprintf(stderr, "[%s:%s] Stack <%s>[%p] created by <%s> at <%s:%d>\n{\n\t", stk->date, stk->time, stk->name, &stk, stk->func_name, stk->file_name, stk->line);
			fprintf(stderr, "1)size = <%zu (or signed <%lld>)>\n\t", stk->size, (ssize_t) stk->size);
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
					fprintf(stderr, " [%zu] = <%g>[%p]\n\t\t", i, DBL_POISON, NULL);
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
	DEBUG_ON(printf("verificator started\n"));
	if (stk == NULL) {fprintf(stderr, "stk null pltr\n"); return NULL_PTR_STK; }

	if ((ssize_t) (stk->capacity) <= 0 || (ssize_t) (stk->size) < 0) {printf("cap <= 0\n");return LESS_ZERO_CAP; }

	if (stk->data == NULL) {fprintf(stderr, "stk_buf null pltr\n"); return NULL_PTR_STKBUF;}

	if (stk->size > stk->capacity){fprintf(stderr, "stk_buf null pltr\n"); return OUT_OF_RANGE;}

	DEBUG_ON(printf("verificator correct\n"));
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