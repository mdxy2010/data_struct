#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


struct sg_link_list {
	struct sg_link_list *next;
	int data;
};

int _link_list_inserted_tail(struct sg_link_list *list, int data)
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

int link_list_inserted_tail(struct sg_link_list *list, int data)
{
	struct sg_link_list *new_node = NULL;
	struct sg_link_list *tail = NULL;
	struct sg_link_list *head = NULL;

	head = tail = list;

	new_node = (struct sg_link_list*)malloc(sizeof(struct sg_link_list));
	if (new_node == NULL) {
		printf("malloc new node failed\n");
		return -1;
	}

	new_node->data = data;
	tail->next = new_node;
	new_node->next = NULL;
	tail = new_node;
	list = head;

	return 0;
}

int link_list_inserted_head(struct sg_link_list *list, int data)
{
	struct sg_link_list *new_node = NULL;

	new_node = (struct sg_link_list*)malloc(sizeof(struct sg_link_list));
	if (new_node == NULL) {
		printf("malloc new node failed\n");
		return -1;
	}
	new_node->data = data;
	new_node->next = list->next;
	list->next = new_node;

	return 0;
}

void dump_list(struct sg_link_list *list)
{
	struct sg_link_list *p;

	if (list == NULL)
		return;
	p = list->next;

	while (p) {
		printf("0x%x ", p->data);
		p = p->next;
	}
	printf("\n");
}

int get_link_list_length(struct sg_link_list *list)
{
	int length = 0;
	struct sg_link_list *p;
	
	if (list == NULL) {
		printf("link list is not exsit\n");
		return length;
	}

	p = list->next;

	while(p) {
		length++;
		p = p->next;
	}

	return length;
}

void dump_list_tail(struct sg_link_list *list)
{
	struct sg_link_list *p;
	int len;

	len = get_link_list_length(list);
	p = p - sizeof(struct sg_link_list) * len;
	if (list == NULL)
		return;
	p = list->next;

	while (p) {
		printf("0x%x ", p->data);
		p = p->next;
	}
	printf("\n");
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

int create_link_list_table(struct sg_link_list *list, int length)
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
		p->next = list->next;
		list->next = p;
	}
	return 0;
}

int main(int argc, const char *argv[])
{
	int i;
	struct sg_link_list *list;
	int len;
	
	create_link_list_head(&list);

	for (i = 0; i < 10; i++) {
		link_list_inserted_tail(list, i);
	}
	/*
	create_link_list_table(list, 10);

	link_list_inserted_head(list, 0xaa);
	link_list_inserted_head(list, 0x3a);
	link_list_inserted_head(list, 0x7a);
	*/
	//link_list_inserted_tail(list, 0x88);
	//link_list_inserted_tail(list, 0x66);
	len = get_link_list_length(list);
	printf("the link list length = %d\n", len);

	dump_list(list);
	return 0;
}
