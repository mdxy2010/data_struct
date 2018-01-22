#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct link_stack_node {
	int data;
	struct link_stack_node *next;
};

struct link_stack {
	struct link_stack_node *top;
	struct link_stack_node *bootm;
};

struct link_stack* init_link_list(void)
{
	struct link_stack *ll_stack = NULL;

	ll_stack = (struct link_stack *)malloc(sizeof(struct link_stack));
	if (!ll_stack) {
		printf("malloc memory for link_stack failed\n");
		return NULL;
	}

	ll_stack->top = ll_stack->bootm = (struct link_stack_node*)malloc(sizeof(struct link_stack_node));

	ll_stack->bootm = ll_stack->top;
	ll_stack->top->next = NULL;
	return ll_stack;
}

int link_stack_is_empty(struct link_stack *stack)
{
	if (stack->top == stack->bootm)
		return 1;
	return 0;
}


int link_stack_push(struct link_stack *stack, int data)
{
	int ret = 0;
	struct link_stack_node *new = NULL;
	new = (struct link_stack_node*)malloc(sizeof(struct link_stack_node));
	printf("alloc: 0x%08x\n", new);
	if (new) {
		new->data = data;
		new->next = stack->top;
		stack->top = new;
	} else {
		printf("malloc link_stack_node failed\n");
		ret = -1;
	}

	return ret;

}

struct link_stack_node* get_stack_top(struct link_stack *stack)
{
	return stack->top;	
}

int link_stack_pop(struct link_stack *stack, int *data)
{
	int ret = 0;
	struct link_stack_node *top = NULL;

	if (stack == NULL || data == NULL) {
		ret = -1;
		printf("Invalid argument,please check!\n");
		return ret;
	}

	if (link_stack_is_empty(stack)) {
		ret = -1;
		printf("This stack is empty\n");
		return ret;
	}

	top = get_stack_top(stack);
	*data = top->data;
	printf("pop data:%d\n", *data);
	stack->top = stack->top->next;
	free(top);
	top = NULL;

	return ret;
}
void clear_link_stack(struct link_stack *stack)
{
	struct link_stack_node *p;
	struct link_stack_node *tmp;

	while(stack->top != stack->bootm) {
		tmp = stack->top;
		printf("free:0x%08x\n", tmp);
		stack->top = stack->top->next;
		free(tmp);
	}
}

void dump_link_list_stack(struct link_stack *stack)
{
	struct link_stack_node *p;

	p = stack->top;
	if (p == stack->bootm) {
		printf("The list is empty, nothing to be done!\n");
		return;
	}

	while(p != stack->bootm) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

int main(int argc, const char *argv[])
{
	struct link_stack *ll_stack = NULL;
	int i;
	int data=0xff;

	printf("==================== init    stack =====================\n");
	ll_stack = init_link_list();

	printf("==================== create  stack =====================\n");
	for (i = 0; i < 10; i++) {
		link_stack_push(ll_stack, i);
	}
	dump_link_list_stack(ll_stack);

	printf("==================== pop stack =====================\n");
	link_stack_pop(ll_stack, &data);
	
	printf("==================== clear stack =====================\n");
	clear_link_stack(ll_stack);

	dump_link_list_stack(ll_stack);
	free(ll_stack);
	
	return 0;
}
