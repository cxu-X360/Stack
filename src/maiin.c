#define STKDEBUG  //TURN ON-OFF by delete/set comment

#include "..\include\prototypes.h"
#include "..\include\stack.h"

#define debug_push(stk, val) do {stack_push(&(stk), (val)); print_stack(&(stk));} while(0)
#define debug_pop(stk) do {double term_var = 0; stack_pop(&(stk), &(term_var)); print_stack(&(stk));} while(0)


int main()
{
	struct Stack stk1 = {};

	#ifdef STKDEBUG
		stk1.name = VAR_NAME(stk1);
	#endif

	stack_init(&stk1, 100);

	print_stack(&stk1);


	for (double i = 0; i < 25.0; i++)
	{
		debug_push(stk1, i);
	}

	for (double i = 0; i < 25.0; i++)
	{
		debug_pop(stk1);
	}
	debug_pop(stk1);

	stack_destroy(&stk1);

	print_stack(&stk1);

	return 0;
}