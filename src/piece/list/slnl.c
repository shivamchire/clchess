#include "slnl.h"
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

void init(list_t *l) {
	l->h = l->t = NULL;
	l->num = 0;
}
int getnum(list_t *l) {
	return l->num;
}
int isempty(list_t *l) {
	return l->num == 0;
}

int insert(list_t *l, void *data, int pos) {

	/* i node number at which we are pointing to*/
	int i = 1;
	/*ptr node at which i is pointing pre_ptr node pre to ptr*/
	node_t *ptr = l->h, *pre_ptr;
	/*condition to decide if we want to go to next node*/
	while(i < pos && ptr) {
	/*if inside while loop we are confirmed that we have to check next node*/
		i++;
		pre_ptr = ptr;
		/*for this ptr must point to node and not null*/
		ptr =  ptr->nxt;
	}
	/*two condition
	 * 1st -> we have reached node where we have to insert new node
	 * 2nd -> pos < 0 or pos > total number of node + 1
	 */
	if(i == pos) {
		node_t *tmp = (node_t *)malloc(sizeof(node_t));
		l->num++;
		tmp->data = data;
		/*if insert at 1/end and list is empty*/
		if(pos == 1 && !(l->h)) {
			l->h = l->t = tmp;
			tmp->nxt = NULL;
		}
		/*if insert at 1 and list is not empty*/
		else if(pos == 1) {
			tmp->nxt = l->h;
			l->h = tmp;
		}
		/*if insert in middle or at end*/
		else {
			tmp->nxt = pre_ptr->nxt;
			if(!(pre_ptr->nxt)) {
				l->t = tmp;
			}
			pre_ptr->nxt = tmp;
		}
		return 0;
	}
	return INT_MAX;
}

void *see(list_t *l, int pos) {
	int i = 1;
	node_t *ptr = l->h;
	void *c = NULL;
	if(ptr) {
		/*check whether we need to move forward and nxt node is not null*/
		while(i < pos && ptr->nxt) {
			/*we need to go to nxt node*/
			i++;
			ptr = ptr->nxt;
		}
		/*
		 * if node which is need to be seen exist
		 */
		if(i == pos) {
			c = ptr->data;
		}
	}
	return c;

}

void *remov(list_t *l, int pos) {

	/*stores pointer of piece which is to be removed*/
	void *c = NULL;
	/*
	 * ptr traverses through entire list till it reach node which is to be
	 * removed or there is no node at pos
	 * pre_ptr stores address of node which is just before node pointed by
	 * ptr
	 */
	node_t *ptr = l->h, *pre_ptr;
	/*i stores number of node at which ptr point to */
	int i = 1;
	/*
	 * if list is not empty then only remove is possible
	 */
	if(ptr) {
		/*check whether we need to move forward and nxt node is not null*/
		while(i < pos && ptr->nxt) {
			/*we need to go to nxt node*/
			i++;
			pre_ptr = ptr;
			ptr = ptr->nxt;
		}
		/*
		 * if node which is need to be remove exist
		 */
		if(i == pos) {
			l->num--;
			/*
			 * list has only one element
			 */
			if(pos == 1 && !(ptr->nxt)) {
				c = ptr->data;
				free(ptr);
				l->h = l->t = NULL;
			}
			/*
			 * first node is to be removed
			 */
			else if(pos == 1) {
				c = ptr->data;
				l->h = ptr->nxt;
				free(ptr);
			}
			/*
			 * last node is to be removed
			 */
			else if(!(ptr->nxt)) {
				l->t = pre_ptr;
				pre_ptr->nxt = NULL;
				c = ptr->data;
				free(ptr);
			}
			/*
			 * middle node is to removed
			 */
			else {
				pre_ptr->nxt = ptr->nxt;
				c = ptr->data;
				free(ptr);
			}
		}
	}
	return c;
}
//void reverse(list_t *l) {
//	int i = 0, j = 0;
//	node_t *ptr = l->h;
//	char **arr = (char **)malloc(sizeof(char*) * 50);
//	char *tmp;
//	while(ptr) {
//		arr[i] = ptr->data;
//		i++;
//		if(i % 50 == 0) {
//			arr = (char **)realloc(arr, sizeof(char *) * ((i/50) + 1) * 50);
//		}
//		ptr = ptr->nxt;
//	}
//	i--;
//	while(j <= i/2) {
//		tmp = arr[j];
//		arr[j] = arr[i - j];
//		arr[i - j] = tmp;
//		j++;
//	}
//	j = 0;
//	ptr = l->h;
//	while(ptr) {
//		ptr->data = arr[j];
//		j++;
//		ptr = ptr->nxt;
//	}
//	free(arr);
//}
int search(list_t *l, void *data) {
	node_t *p = l->h;
	int i = 1, j = 0;
	while(p) {
		if(p->data == data) {
			j = i;
			break;
		}
		i++;
		p = p->nxt;
	}
	return j;
}

void destroy(list_t *l) {
	node_t *ptr = l->h, *tmp;

	while(ptr) {
		tmp = ptr->nxt;
		free(ptr);
		ptr = tmp;
	}
	l->h = l->t = NULL;
	l->num = 0;
}
