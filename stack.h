#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include"list.h"
#define max 500


typedef struct operator_stack{
    int top;
    char op[max];
}operator_stack;

typedef struct operand_stack{
    int top;
    list *l[max];
}operand_stack;

void operator_push(operator_stack *s, char num);
char operator_pop(operator_stack *s);
int operator_empty(operator_stack s);
int operator_full(operator_stack s);
void operator_stack_init(operator_stack *s);
char operator_peek(operator_stack s);

void operand_push(operand_stack *s, list *l);
list* operand_pop(operand_stack *s);
int operand_empty(operand_stack s);
int operand_full(operand_stack s);
void operand_stack_init(operand_stack *s);
list* operand_peek(operand_stack s);


#endif // STACK_H_INCLUDED
