#include<stdio.h>
#include<stdlib.h>
#include "list.h"
#include "stack.h"
#include "evaluation.h"

int is_digit(char d){
    if(d >= 48 && d <= 57)
        return 1;
    else
        return 0;
}

list* operation(list* operand1, list* operand2, char operator){
    list* res;

    switch(operator){
        case '+':
            res = addition(operand1, operand2);
            break;
        case '-':
            res = subtract(operand1, operand2);
            break;
        case '*':
            res = multiply(operand1, operand2);
            break;
        case '/':
            res = division(operand1, operand2);
            break;
    }
    return res;
}

int precedence(char c){
    if(c == '+')
        return 10;
    else if(c == '-')
        return 10;
    else if(c == '*')
        return 20;
    else if(c == '/')
        return 20;
    else if(c == '%')
        return 20;
    else if(c == '^')
        return 30;
    else if(c == '(')
        return 5;
    return 0;
}

