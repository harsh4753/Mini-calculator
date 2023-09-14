#include<stdio.h>
#include<stdlib.h>
#include "stack.h"
#include "list.h"

void operator_stack_init(operator_stack *s){
    s -> top = -1;
}

int operator_empty(operator_stack s){
    if(s.top == -1)
        return 1;
    else
        return 0;
}

int operator_full(operator_stack s){
    if(s.top == max - 1)
        return 1;
    else
        return 0;
}

void operator_push(operator_stack *s, char ch){
    if(operator_full(*s))
        return;
    else{
        (s -> top)++;
        s -> op[s -> top] = ch;
        return;
    }
}

char operator_pop(operator_stack *s){
    if(operator_empty(*s))
        return 0;
    else{
        char ch = s -> op[s -> top];
        (s -> top)--;
        return ch;
    }
}

char operator_peek(operator_stack s){
    return s.op[s.top];
}

void operand_stack_init(operand_stack *s){
    s -> top = -1;
}

int operand_empty(operand_stack s){
    if(s.top == -1){
        return 1;
    }
    else
        return 0;
}

int operand_full(operand_stack s){
    if(s.top == max - 1)
        return 1;
    else
        return 0;
}

void operand_push(operand_stack *s, list *l){
    if(operand_full(*s))
        return;
    else{
        (s -> top)++;
        s -> l[s -> top] = l;
        return;
    }
}

list* operand_pop(operand_stack *s){
    list *p = (list*)malloc(sizeof(list));
    if(operand_empty(*s))
        return 0;
    else{
        p = s -> l[s -> top];
        (s->top)--;
        return p;
    }
}

list* operand_peek(operand_stack s){
    return s.l[s.top];
}


