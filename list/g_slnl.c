#include "g_slnl.h"

void init(list_t *l, size_t size) {
	l->h = l->t = NULL;
	l->size = size;
}
/*
void printl(list_t *l) {

	node_t *ptr = l->h;
	while(ptr) {
		printf("%s ", ptr->data);
		ptr = ptr->nxt;
	}
	printf("\n");
}
*/

int insert(list_t *l, void *data_ar, size_t pos) {

	/* i node number at which we are pointing to*/
	size_t i = 1, len = l->size;
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
		void *data = malloc(len);
		tmp->data = data;
		memcpy(data, data_ar, len);
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

void *see(list_t *l, size_t pos) {
	size_t i = 1;
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

/*
 * user must free the memory at char pointer return by this function
 * also check if return is NULL if yes then there is no node at pos
 */
void *remov(list_t *l, size_t pos) {

	/*stores pointer of data which is to be removed*/
	void *c = NULL;
	/*
	 * ptr traverses through entire list till it reach node which is to be
	 * removed or there is no node at pos
	 * pre_ptr stores address of node which is just before node pointed by
	 * ptr
	 */
	node_t *ptr = l->h, *pre_ptr;
	/*i stores number of node at which ptr point to */
	size_t i = 1;
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
void sort(list_t *l, int compar(const void **a, const void **b)) {

	size_t i = 0;
	node_t *ptr = l->h;
	void **arr = (void **)malloc(sizeof(void*) * BUFF);
	//store all pointers to data in an array
	while(ptr) {
		arr[i] = ptr->data;
		i++;
		if(i % BUFF == 0) {
			arr = (void **)realloc(arr, sizeof(void *) * ((i/BUFF) + 1) * BUFF);
		}
		ptr = ptr->nxt;
	}
	//sort data according to some compar function
	qsort(arr, i, sizeof(void *), compar);
	ptr = l->h;
	i = 0;
	//restore all pointers to data to there node
	while(ptr) {
		ptr->data = arr[i];
		i++;
		ptr = ptr->nxt;
	}
	free(arr);
}

void reverse(list_t *l) {
	int i = 0, j = 0;
	node_t *ptr = l->h;
	void **arr = (void **)malloc(sizeof(void*) * BUFF);
	void *tmp;
	while(ptr) {
		arr[i] = ptr->data;
		i++;
		if(i % BUFF == 0) {
			arr = (void **)realloc(arr, sizeof(void *) * ((i/BUFF) + 1) * BUFF);
		}
		ptr = ptr->nxt;
	}
	i--;
	while(j <= i/2) {
		tmp = arr[j];
		arr[j] = arr[i - j];
		arr[i - j] = tmp;
		j++;
	}
	j = 0;
	ptr = l->h;
	while(ptr) {
		ptr->data = arr[j];
		j++;
		ptr = ptr->nxt;
	}
	free(arr);
}
void destroy(list_t *l) {
	node_t *ptr = l->h, *tmp;

	while(ptr) {
		free(ptr->data);
		tmp = ptr->nxt;
		free(ptr);
		ptr = tmp;
	}
}
