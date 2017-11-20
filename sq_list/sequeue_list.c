#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define LIST_SIZE 10

struct sq_list {
	int data[LIST_SIZE];
	int list_length;
};

struct sq_list* init_sq_list(void);
int insert_sq_list(struct sq_list *sq_list, int data, int pos);
int sq_list_deleted(struct sq_list *sq_list, int element);
int sq_list_lookup(struct sq_list *sq_list, int element);
void dump_sq_list(struct sq_list *list);
bool sq_list_is_full(struct sq_list *list);
bool sq_list_is_empty(struct sq_list *list);

struct sq_list* init_sq_list(void)
{
	int i;

	struct sq_list *sq_list = (struct sq_list*)malloc(sizeof(struct sq_list));
	if (NULL == sq_list) {
		printf("alloc sq_list failed\n");
		return NULL;
	}

	memset(sq_list->data, 0x0, sizeof(sq_list->data));
	sq_list->list_length = 0;
	
	for (i = 0; i < 5 ; i++) {
		sq_list->data[i] = i;
		sq_list->list_length++;
	}

	return sq_list;
}

int insert_sq_list(struct sq_list *sq_list, int data, int pos)
{
	int ret;
	int i;
	
#ifdef DBEUG
	printf("%s: before inserted list_length = %d\n", __func__, sq_list->list_length);
#endif
	if (sq_list == NULL || pos < 0 || pos > LIST_SIZE) {
		printf("inserted pos overflow\n");
		return -1;
	}

	if (sq_list_is_full(sq_list)) {
		printf("sequeue list is full, no space inserted\n");
		return -1;
	}
	
	if (pos <= sq_list->list_length) {
		for (i = sq_list->list_length - 1; i >= pos - 1; i--) {
			sq_list->data[i + 1] = sq_list->data[i];
		}
	}
	sq_list->data[pos - 1] = data;
	sq_list->list_length ++;

#ifdef DBEUG
	printf("%s: after inserted list_length = %d\n", __func__, sq_list->list_length);
#endif
	return 0;
}

int sq_list_deleted_pos(struct sq_list *list, int pos, int *element)
{
	int k;

	if (pos < 0 || pos > list->list_length ||
		list == NULL || element == NULL) {
		printf("invalid argument\n");
		return -1;
	}

	if (sq_list_is_empty(list)) {
		printf("The list is empty\n");
		return -1;
	}
	
	*element = list->data[pos -1];
	if (pos < list->list_length) {
		for (k = pos -1; k < list->list_length - 1; k++) {
			list->data[k] = list->data[k+1];
		}
	}
	list->list_length --;
	return 0;
}

int sq_list_deleted(struct sq_list *sq_list, int element)
{
	int i = 0;
	int deleted_pos;

	if (sq_list == NULL) {
		printf("element is not exsit\n");
		return -1;
	}
	
	if (sq_list_is_empty(sq_list)) {
		printf("The list is empty\n");
		return -1;
	}
	
	printf("before deleted element %d\n", element);
	dump_sq_list(sq_list);
	for (i = 0; i <= sq_list->list_length - 1; i++)
	{
		if (sq_list->data[i] == element) {
			deleted_pos = i;
			if (deleted_pos == sq_list->list_length - 1) {
				sq_list->list_length --;
				break;
			}

			while (deleted_pos < sq_list->list_length - 1)
			{
				sq_list->data[deleted_pos] = sq_list->data[deleted_pos + 1];
				deleted_pos ++;
			}
			sq_list->list_length --;
			break;
		}
#ifdef DEBUG
		printf("i = %d\n", i);
#endif
	}
	printf("after deleted element %d\n", element);
	dump_sq_list(sq_list);
	return 0;
}

int sq_list_lookup(struct sq_list *sq_list, int element)
{	
	int i;
	if (sq_list == NULL || element < 0)
		return -1;

	for (i = 0; i < sq_list->list_length; i++) {
		if (element == sq_list->data[i]) {
			printf("element:%d is local at list %d\n", element, i);
			return 0;
		}
	}

	printf("element:%d is not exsit at list \n", element);
	return -1;
}

void dump_sq_list(struct sq_list *list)
{
	int i;
	printf("************* START DUMP LIST  ****************\n");
	//printf("************* list length = %d ****************\n", list->list_length);
	if (list->list_length == 0) {
		printf("list is null\n");
		return ;
	}

	for (i = 0; i < list->list_length; i++)
		printf("%d ", list->data[i]);
	printf("\n");
	printf("************* END   DUMP LIST  ****************\n");
}

bool sq_list_is_full(struct sq_list *list)
{
	if (list->list_length == LIST_SIZE)
		return 1;
	return 0;
}

bool sq_list_is_empty(struct sq_list *list)
{
	if (list->list_length == 0)
		return 1;
	return 0;
	
}
int sq_list_clear(struct sq_list *list)
{
	int i;
	if (list == NULL)
		return -1;

	for (i = 0; i < list->list_length; i++) {
		list->data[i] = 0;
	}

	list->list_length = 0;
	return 0;
}

int main(int argc, const char *argv[])
{
	struct sq_list *sq_list = NULL;
	int ret_val = 0;

	sq_list = init_sq_list();
	printf("sq_list = %p\n", sq_list);
	//dump_sq_list(sq_list);
	//insert_sq_list(sq_list, 100, 2);
	//dump_sq_list(sq_list);
	//insert_sq_list(sq_list, 100, 3);
	dump_sq_list(sq_list);
	sq_list_deleted_pos(sq_list, 2, &ret_val);
	printf("ret_val = %d\n", ret_val);
	sq_list_clear(sq_list);
	dump_sq_list(sq_list);
	
	free(sq_list);
	
	return 0;
}
