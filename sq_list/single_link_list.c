#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct link_list {
	struct link_list *next;
};

struct sg_link_list {
	struct link_list *head;
	int data;
	int link_list_length;
};

/*insert element to link list*/
struct sg_link_list *sg_link_list_inserted(struct sg_link_list *head,
	struct sg_link_list *new)
{
	if (NULL == head || NULL == new) {
		
	}
	return NULL;
}

/*deleted  element from link list*/
struct sg_link_list *sg_link_list_deleted(struct sg_link_list *ll, int data)
{
	return NULL;
}

bool link_list_is_full(struct sg_link_list *ll)
{
	return 1;
}

bool link_list_is_empty(struct sg_link_list *ll)
{
	return 1;
}


/*init link list*/
struct sg_link_list_type * init_single_list(void)
{
	struct sg_link_list *link_list = 
		(struct sg_link_list*)malloc(sizeof(struct sg_link_list));
	link_list->head = NULL;
	link_list->data = 0;
	link_list->link_list_length = 0;

	return link_list;
}

int main(int argc, const char *argv[])
{
	
	return 0;
}
