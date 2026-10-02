#ifndef PROTOTYPES_H
#define PROTOTYPES_H 
	#include "stack.h" 
	


	#define CHECK_ERROR(stk) if(enum ERRNO error = verificator(stk)) {dump_stack(stk, error); choose_exit();} 

	void clear_buffer();

	//Debuging

	int choose_exit();
	int dump_stack(struct Stack* stk, enum ERRNO error);
	int verificator(struct Stack* stk);
	int print_stack(struct Stack* stk);


	//Stack manage

	int fill_poison(struct Stack* stk);

	int stack_init(struct Stack* stk, size_t capacity);

	int resize_up(struct Stack* stk);
	int resize_down(struct Stack* stk);

	int stack_push(struct Stack* stk, double value);
	int stack_pop(struct Stack* stk, double* value);

	int stack_destroy(struct Stack* stk);


#endif