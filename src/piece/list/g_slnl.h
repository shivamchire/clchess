#ifndef G_SLNL_H
#define G_SLNL_H
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#define BUFF 50

typedef struct node {
	void *data;
	struct node *nxt;
}node_t;

typedef struct list {
	node_t *h, *t;
	size_t size;
	size_t num;
}list_t;

void init(list_t *l, size_t size);
int getnum(list_t *l);
int isempty(list_t *l);
//void printl(list_t *l);
int insert(list_t *l, void *data, size_t pos);
void *see(list_t *l, size_t pos);
void *remov(list_t *l, size_t pos);
int search(list_t *l, void *d, int ifequal(void *a, void *b));
//void sort(list_t *l, int compar(const void **, const void **));
//void reverse(list_t *l);
void destroy(list_t *l);
#endif //#ifndef G_SLNL_H
