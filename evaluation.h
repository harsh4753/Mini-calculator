#ifndef EVALUATION_H_INCLUDED
#define EVALUATION_H_INCLUDED

#include "list.h"

int is_digit(char d);
list* operation(list* operand1, list* operand2, char operator);
int precedence(char c);
list* evaluate(char *expr);


#endif // EVALUATION_H_INCLUDED
