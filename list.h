#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

typedef struct node{         //each node is used for storing a digit
    int dig;
    struct node* next;
}node;

typedef struct list{
    node* head;
    int dec;   //is used for counting number of decimal digits
}list;

void list_init(list* l);
int length(list l);
void insert(list* l, int pos, int d);
void append(list *l, int num);
int display(list l, int pos);
void traverse(list l);
list* addition(list *l1, list *l2);
list* subtract(list *l1, list *l2);
list* multiply(list *l1, list *l2);
list* division(list *l1, list *l2);

#endif // LIST_H_INCLUDED
