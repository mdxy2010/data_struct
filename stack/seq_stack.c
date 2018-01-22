#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 20

struct seq_stack {
	int data[MAX_SIZE];
	int top;
};

int get_stack_top(struct seq_stack *stack)
{
	return stack->top;
}

bool stack_is_empty(struct seq_stack *stack)
{
	if (stack->top == -1)
		return true;
	return false;
}

bool stack_is_full(struct seq_stack * stack)
{
	if (stack->top >= MAX_SIZE)
		return true;
	return false;
}

void dump_stack(struct seq_stack *stack)
{
	int i;
	int tmp_top;

	if (stack == NULL) {
		printf("invalid argument! please check!\n");
		return;
	}

	if (stack_is_empty(stack)) {
		printf("the stack is empty, nothing to dump\n");
		return;
	}

	tmp_top = get_stack_top(stack);
	printf("tmp_top = %d\n", tmp_top);
	for (i = 0; i <= tmp_top; i++) {
		printf("stack[%d] = %d\n", i,stack->data[i]);
	}
}

struct seq_stack *init_stack(void)
{
	struct seq_stack *seq_stack = (struct seq_stack *)(malloc(sizeof(struct seq_stack)));
	if (seq_stack == NULL){
		printf("alloc stack space failed\n");
		return NULL;
	}

	seq_stack->top = -1;
	return seq_stack;
}

int create_stack(struct seq_stack *stack, int stack_size)
{
	int ret = 0,i;
	if (stack_size < 0 || stack == NULL) {
		ret = -1;
		printf("invalid argument! please check!\n");
		return ret;
	}
	
	for (i = 0; i < stack_size; i++) {
		stack->top++;
		stack->data[stack->top] = i;
	}

	return 0;
}

int stack_push(struct seq_stack * stack, int data)
{
	int ret = 0;
	if (stack == NULL) {
		ret = -1;
		printf("invalid argument! please check!\n");
		return ret;
	}

	if (stack_is_full(stack)) {
		ret = -1;
		printf("This stack already full!\n");
		return ret;
	}

	stack->top++;
	stack->data[stack->top] = data;
	return ret;
}

int stack_pop(struct seq_stack *stack, int *data)
{
	int ret = 0;

	if (data == NULL || stack == NULL) {
		printf("invalid argument! please check!\n");
		ret = -1;
		return ret;
	}

	if (stack_is_empty(stack)) {
		ret = -1;
		printf("This stack is empty!\n");
		return ret;
	}

	*data = stack->data[stack->top];
	stack->top--;

	return ret;
}

void stack_free(struct seq_stack *stack)
{
	free(stack);
}

int main(int argc, const char *argv[])
{
	int ret;
	int ret_val = 0;
	
	struct seq_stack *stack = NULL;
	stack = init_stack();
	create_stack(stack, 10);
	printf("==================== After create stack dump stack: =======================\n");
	dump_stack(stack);

	stack_push(stack, 20);
	stack_push(stack, 99);
	printf("==================== After push stack dump stack:   =======================\n");
	dump_stack(stack);

	stack_pop(stack, &ret_val);
	printf("==================== After pop stack dump stack:   =======================\n");
	printf("the pop stack data is %d\n", ret_val);
	dump_stack(stack);
	free(stack);
	
	return 0;
}
