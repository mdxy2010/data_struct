#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct double_list {
	struct double_list *prev;
	struct double_list *next;
	int data;
};

#define OK 1
#define ERROR 0

struct double_list *init_double_list_head(void)
{
	struct double_list *head = (struct double_list*)malloc(sizeof(struct double_list));
	
	if (head == NULL) {
		printf("malloc double_list head failed\n");
		return NULL;
	}

	head->prev = NULL;
	head->next = NULL;

	printf("Create double list head: 0x%08x OK\n", head);
	return head;
}

void free_double_list_head(struct double_list *head)
{
	printf("head = 0x%08x\n", head);
	free(head);
}

void dump_double_list(struct double_list *head)
{
	struct double_list *p;
	p = head->next;

	if (NULL == head) {
		printf("double list is null\n");
		return;
	}

	while(p) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}

/*
 * Create double list through head insert method
 * head: the double list head pointer
 * table_size: the size of the double list
 * 
 */
struct double_list* create_double_list_table_head(struct double_list *head, int table_size)
{
	struct double_list *new;
	int i;

	if (head == NULL) {
		printf("double list head is null, please alloc list head\n");
		return NULL;
	}

	for (i = 0; i < table_size; i++) {
		/* Malloc memory space for new node */
		struct double_list *new = (struct double_list*)malloc(sizeof(struct double_list));
		printf("alloc new node: 0x%08x\n", new);
		if (NULL == new) {
			printf("malloc node %d failed\n", i);
			return NULL;
		}

		/* init data for new node */
		new->data = i;

		/* link new node to head */
		new->next = head->next;
		head->next = new;
		new->prev = head;
	}

	return head;
}

/*
 * Create double list through tail insert method
 * head: the double list head pointer
 * table_size: the size of the double list
 * 
 */
struct double_list* create_double_list_table_tail(struct double_list *head, int table_size)
{
	struct double_list *new;
	int i;

	if (head == NULL) {
		printf("double list head is null, please alloc list head\n");
		return NULL;
	}

	for (i = 0; i < table_size; i++) {
		/* Malloc memory space for new node */
		struct double_list *new = (struct double_list*)malloc(sizeof(struct double_list));
		printf("alloc new node: 0x%08x\n", new);
		if (NULL == new) {
			printf("malloc node %d failed\n", i);
			return NULL;
		}

		/* init data for new node */
		new->data = i;

		/* link new node to head */
		new->prev = head;
		new->next = head->next;
		head->next = new;
		head = new;
	}

	return head;
}
int get_double_list_length(struct double_list *head)
{
	int len = 0;
	struct double_list *p = NULL;

	if (head == NULL) {
		printf("double list head is null, please alloc list head\n");
		return -1;
	}

	p = head->next;
	while (p) {
		len++;
		p = p->next;
	}
	
	return len;
}

int double_list_inserted(struct double_list *head, int pos, int node_data)
{
	struct double_list *new;
	struct double_list *p;
	struct double_list *q;
	int len = 0, j = 1;

	if (NULL == head)
		return ERROR;

	len = get_double_list_length(head);
	if (pos < 0 || pos > len) {
		printf("argument pos error\n");
		return ERROR;
	}

	/* Malloc memory space for new node */
	new = (struct double_list*)malloc(sizeof(struct double_list));
	if (NULL == new) {
		printf("malloc new node failed\n");
		return ERROR;
	}

	/* init data for new node */
	new->data = node_data;


	/*Find the pos node*/
	p = head->next;
	while (p && j < pos - 1) {
		p = p->next;
		j++;
	}

	/* the pointer q stroage the pos node */
	q = p;

	new->prev = q;
	new->next = q->next;
	q->next = new;
	q->next->prev = new;
	
	printf("Insert a new node at %d node, data is %d\n", pos, node_data);
	return OK;
}

int double_list_deleted_position(struct double_list *head, int position, int *del_val)
{
	struct double_list *p = NULL;
	struct double_list *del_node = NULL;
	int j = 1, len = 0;

	if (NULL == head || NULL == del_val)
		return ERROR;

	len = get_double_list_length(head);
	if (position < 0 || position > len) {
		printf("argument position error\n");
		return ERROR;
	}

	p = head->next;
	while(p && j < position) {
		j++;
		p = p->next;
	}

	del_node = p->next;
	*del_val = del_node->data;

	p->next = del_node->next;
	del_node->next->prev = p;
	free(del_node);

	printf("The delete node number is %d and elements is %d\n", position, *del_val);

	return OK;
}

int free_double_list(struct double_list *head)
{
	struct double_list *p = NULL;
	struct double_list *q = NULL;

	if (NULL == head)
		return false;

	// point the first node
	p = head->next;

	while(p) {
		printf("free node: 0x%08x\n", p);
		q = p->next;
		free(p);
		if (q != NULL)
			q->prev = NULL;
		p = q;
	}
	return 0;
}

int main(int argc, const char *argv[])
{
	int len, del_val;
	struct double_list *head = NULL;

	head = init_double_list_head();
#if 0
	create_double_list_table_head(head, 10);
#endif

	create_double_list_table_tail(head, 10);

	/*
	 *len = get_double_list_length(head);
	 *printf("the double_list len is %d\n", len);
	 */

	/*
	 *double_list_inserted(head, 6, 12);
	 *double_list_inserted(head, 8, 19);
	 */

#if 0
	printf("before delete elements\n");
	dump_double_list(head);
	double_list_deleted_position(head, 6, &del_val);

	printf("after delete elements\n");
	dump_double_list(head);
#endif

	len = get_double_list_length(head);
	printf("the double_list len is %d\n", len);
	free_double_list(head);

	free_double_list_head(head);
	return 0;
}
