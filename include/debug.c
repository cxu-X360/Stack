#include "stack.h"

void clear_buffer()  //очищает стандартный буффер ввода до \n включительно вызовами getchar()
{
	char _ = 0;
	while ((_ = (char) getchar()) != '\n' && _ != EOF){}
}

int choose_exit()
{
	fprintf(stderr, "\n}\n----------------------------------------------------------------------------------------------\n\n\n\n");
	fprintf(stdout, "\n}\n----------------------------------------------------------------------------------------------\n\n\n\n");


	bool is_finish = false;

	fprintf(stdout, "Do u wanna exit ? (y/N)\n");

	char choosing = fgetc(stdin);
	clear_buffer();

	if (choosing == 'Y' || choosing == 'y' ) {fprintf(stdout, "Goodbye!!\n"); exit(-1);}

	return 0;
}

int dump_stack(FILE* stream, struct Stack* stk, enum ERRNO error)
{
	#ifdef STKDEBUG

		fprintf(stream, "\n\nSTACK_DUMP\n----------------------------------------------------------------------------------------------\n");	

			fprintf(stream, "ERROR_Num = <%d>..... Error codes \n{\n", error);
			fprintf(stream, "	NO_ERROR = 0,\n\t"
							"LESS_ZERO_CAP_OR_SIZE = -1,\n\t"
							"NULL_PTR_STK = -2,\n\t"
							"NULL_PTR_STKBUF = -3,\n\t"
							"OUT_OF_RANGE = -4,\n\t"
							"STACK_UNDERFLOW = -5,\n\t"
							"CANARY_PROTECT = -6, \n}\n");

		if (error == NULL_PTR_STK) return -fprintf(stream, "NULL PTR STACK\n");


		fprintf(stream, "[%s:%s] Stack <%s>[%p] created by <%s> at <%s:%d>\n{\n\t", stk->date, stk->time, stk->name, &stk, stk->func_name, stk->file_name, stk->line);
			fprintf(stream, "size = <%zu (or signed <%lld>)>\n\t", stk->size, (ssize_t) stk->size);
			fprintf(stream, "capacity = <%zu (or signed <%lld>)>\n\t", stk->capacity, (ssize_t) stk->capacity);

			#ifdef CANARY
				fprintf(stream, "start_canary = <0x%x>", (long long int) stk->start_canary);
				if (stk->start_canary == START_CAN_VAL) fprintf(stream, " - correct\n\t");
				else fprintf(stream, " - INCORRECT\n\t");

				fprintf(stream, "end_canary = <0x%x>", (long long int) stk->end_canary);
				if (stk->end_canary == END_CAN_VAL) fprintf(stream, " - correct\n\t");
				else fprintf(stream, " - INCORRECT\n\t");
			#endif

			if (error == NULL_PTR_STKBUF) return -fprintf(stream, "NULL PTR on STACK BUFFER\n");
			fprintf(stream, "data[%zu] = \n{\n\t", stk->capacity);

				if (error == LESS_ZERO_CAP_OR_SIZE) return -fprintf(stream, "LESS OR ZERO CAPACITY or SIZE");
				if (error == OUT_OF_RANGE) return -fprintf(stream, "OUT_OF_RANGE - SIZE > capacity");

				#ifdef CANARY
					fprintf(stream, "start_data_canary = <0x%x>", (long long int) stk->data[-1]);
					if (stk->data[-1] == START_DATA_CAN_VAL) fprintf(stream, " - correct\n\t");
					else fprintf(stream, " - INCORRECT\n\t");
				#endif

				for (size_t i = 0; i < stk->size; i++)
				{
					fprintf(stream, "* [%zu] = <%g>[%p]\n\t\t", i, (stk->data)[i], &((stk->data)[i]));
				}

				for (size_t i = stk->size; i < stk->capacity; i++)
				{
					fprintf(stream, " [%zu] = <%g>[%p]\n\t\t", i, DBL_POISON, NULL);
				}


				#ifdef CANARY
					fprintf(stream, "end_data_canary = <0x%x>", (long long int) stk->data[stk->capacity]);
					if (stk->data[stk->capacity] == END_DATA_CAN_VAL) fprintf(stream, " - correct\n\t");
					else fprintf(stream, " - INCORRECT\n\t");
				#endif

		fprintf(stream, "}\n");
	#endif
}

int verificator(struct Stack* stk)
{
	DEBUG_ON(printf("verificator started\n"));
	if (stk == NULL) {fprintf(stdout, "stk null pltr\n"); return NULL_PTR_STK;}

	if ((ssize_t) (stk->capacity) <= 0 || (ssize_t) (stk->size) < 0) {fprintf(stdout, "cap <= 0\n");return LESS_ZERO_CAP_OR_SIZE; }

	if (stk->data == NULL) {fprintf(stdout, "stk_buf null pltr\n"); return NULL_PTR_STKBUF;}

	if (stk->size > stk->capacity){fprintf(stdout, "stk_buf null pltr\n"); return OUT_OF_RANGE;}

	#ifdef CANARY

		if (stk->start_canary != START_CAN_VAL || stk->end_canary != END_CAN_VAL) {fprintf(stdout, "Canaries a crying, help them ;(\n"); return WRONG_CANARIES;}
		if (stk->data[-1] != START_DATA_CAN_VAL || stk->data[stk->capacity] != END_DATA_CAN_VAL) {fprintf(stdout, "Data Canaries fuck of\n"); return WRONG_CANARIES;}

	#endif

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