#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


struct sg_link_list {
	struct sg_link_list *next;
	int data;
};

int link_list_inserted_tail_step(struct sg_link_list *list, int data)
{
	struct sg_link_list *new_node = NULL;
	struct sg_link_list *tail = NULL;

	tail = list;

	while(tail->next != NULL) {
		tail = tail->next;
	}
	new_node = (struct sg_link_list*)malloc(sizeof(struct sg_link_list));
	if (new_node == NULL) {
		printf("malloc new node failed\n");
		return -1;
	}

	new_node->data = data;
	new_node->next = NULL;
	tail->next = new_node;

	return 0;
}

#if 0
int link_list_inserted_tail(struct sg_link_list *list, int data)
{
	struct sg_link_list *p, *q;

	q = list;

	p = (struct sg_link_list*)malloc(sizeof(struct sg_link_list));
	p->data = data;
#if 0
	p->next = q->next;
	q->next = p;
#endif
#if 1
	q->next = p;
	q = p;
#endif

	p->next = NULL;

	return 0;
}
#endif

int link_list_inserted_head(struct sg_link_list *head, int data)
{
	struct sg_link_list *new_node = NULL;

	new_node = (struct sg_link_list*)malloc(sizeof(struct sg_link_list));
	if (new_node == NULL) {
		printf("malloc new node failed\n");
		return -1;
	}
	new_node->data = data;
	new_node->next = head->next;
	head->next = new_node;

	return 0;
}
int link_list_inserted_midle(struct sg_link_list *head, int pos, int data)
{
	int len;
	int j;
	struct sg_link_list *p;
	struct sg_link_list *q;

	len = get_link_list_length(head);
	if (pos < 0 || pos > len) {
		printf("pos not exsit in link list\n");
		return -1;
	}

	q = (struct sg_link_list*)malloc(sizeof(struct sg_link_list));
	p = head->next;
	j = 1;

	while (p && j < pos) {
		p = p->next;
		j++;
	}

	q->data = data;
	q->next = p->next;
	p->next = q;

	return 0;
}

void dump_list(struct sg_link_list *head)
{
	struct sg_link_list *p;

	if (head == NULL)
		return;
	if (head->next == NULL) {
		printf("The link list is NULL\n");
		return;
	}

	p = head->next;

	while (p) {
		printf("link list node 0x%08x: %x\n", p, p->data);
		p = p->next;
	}
	printf("\n");
}

int get_link_list_length(struct sg_link_list *head)
{
	int length = 0;
	struct sg_link_list *p;
	
	if (head == NULL) {
		printf("link list is not exsit\n");
		return length;
	}

	p = head->next;

	while(p) {
		length++;
		p = p->next;
	}

	return length;
}

int create_link_list_head(struct sg_link_list **head)
{
	*head = (struct sg_link_list *)malloc(sizeof(struct sg_link_list));
	if (*head == NULL) {
		printf("malloc link list head failed\n");
		return -1;
	}
	(*head)->next = NULL;
	return 0;
}

int create_link_list_table_head(struct sg_link_list *head, int length)
{
	int i;
	struct sg_link_list *p;

	if (length == 0) {
		printf("link list table length must > 0\n");
		return -1;
	}

	for (i = 0; i < length; i++) {
		p = (struct sg_link_list*)malloc(sizeof(struct sg_link_list));
		p->data = i;
		p->next = head->next;
		head->next = p; //the head->next point the new node forever
	}

	return 0;
}

int link_list_deleted_by_pos(struct sg_link_list *head, int pos, int *deleted_val)
{
	int ret = 0, j, len;
	struct sg_link_list *p = NULL;
	struct sg_link_list *q = NULL;

	if (head == NULL || deleted_val == NULL) {
		ret = -1;
		return ret;
	}

	len = get_link_list_length(head);

	if (pos > len || pos < 0) {
		ret = -1;
		printf("delete position overflow........\n");
		return ret;
	}

	j = 1;
	p = head->next;

	// find the prev node of the pos node
	while (p && j < pos) {
		p = p->next;
		j++;
	}
	printf("p = 0x%08x\n", p);

	if (!p || j > pos) {
		ret = -1;
		printf("deleted node do not exsit\n");
		return ret;
	}

	q = p->next; //get the delete node
	*deleted_val = p->next->data; //get the delete node data
	p->next = q->next; //p->next = p->next->next

	free(q);

	return ret;

}

int link_list_free(struct sg_link_list *head)
{

	struct sg_link_list *p = NULL;
	struct sg_link_list *q = NULL;

	p = head->next;

	while(p) {
		q = p->next;
		free(p);
		printf("free link list node:0x%08x\n", p);
		p = q;
	}
	head->next = NULL;
	return 0;
}

int link_list_get_element(struct sg_link_list *head, int element)
{
	int k, j;
	struct sg_link_list *p = NULL;

	if (head == NULL)
		return -1;

	j = 1;
	p = head->next;

	while(p) {
		if (p->data == element)
			break;
		p = p->next;
		j++;
	}

	if (!p) {
		printf("the element do not exsit in link list\n");
		return -1;
	}
	k = j;

	printf("the element: 0x%x is at %d node\n", element, k);
	return 0;
}

int create_link_list_table_tail(struct sg_link_list *head, int length)
{
	int i;
	struct sg_link_list *p;

	if (length == 0) {
		printf("link list table length must > 0\n");
		return -1;
	}

	for (i = 0; i < length; i++) {
		p = (struct sg_link_list*)malloc(sizeof(struct sg_link_list));
		p->data = i;
		head->next = p; //the head->next  point the first node forever
		head = p;
	}

	p->next = NULL;
	return 0;
}

int main(int argc, const char *argv[])
{
	int i;
	struct sg_link_list *head;
	int len, del_val;
	create_link_list_head(&head);
	create_link_list_table_tail(head, 10);

	link_list_inserted_midle(head, 5, 0x11);
	link_list_inserted_midle(head, 6, 0x22);
	//link_list_deleted_by_pos(head, 5, &del_val);
	//printf("del_val = %d\n", del_val);
	//link_list_get_element(head, 0x11);
	len = get_link_list_length(head);
	printf("before free the link list length = %d\n", len);
	link_list_free(head);
	len = get_link_list_length(head);
	printf("after free the link list length = %d\n", len);

	dump_list(head);
	return 0;
}
