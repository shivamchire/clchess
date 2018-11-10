typedef struct node {
	void *data;
	struct node *nxt;
}node_t;

typedef struct list {
	node_t *h, *t;
	int num;
}list_t;
void init(list_t *l);
int isempty(list_t *l);
int insert(list_t *l, void *data, int pos);
void *see(list_t *l, int pos);
void *remov(list_t *l, int pos);
int search(list_t *l, void *data);
int getnum(list_t *l);
void destroy(list_t *l);
