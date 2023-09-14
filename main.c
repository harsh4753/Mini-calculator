#include "list.h"
#include "stack.h"
#include "evaluation.h"
#include<stdio.h>
#include<stdlib.h>

int main(){
    char expr[1000];
    char c, operator;
    int i = 0;    
    int j = 0;    
    int count;    
    int flag;     

    list *operand1, *operand2, *res;
    list* temp[1000];

    operator_stack s1;
    operand_stack s2;
    operator_stack_init(&s1);
    operand_stack_init(&s2);

    printf("enter the expression to be evaluated : ");
    fgets(expr, 656565625, stdin);

    if(expr[0] == '*' || expr[0] == '/' || expr[0] == '*' || expr[0] == ')' || expr[0] == '^' || expr[0] == '%'){
        printf("Invalid");
    }
    while(expr[i] != '\0'){
        c = expr[i];
        flag = 0;
        if(c == '('){
            operator_push(&s1, c);
        }
        else if(is_digit(c) || c == '.'){
            count = 0;
            temp[j] = (list*)malloc(sizeof(list));
            list_init(temp[j]);

            while(is_digit(expr[i]) || expr[i] == '.'){
                if(expr[i] == '.'){
                    if(flag == 1){
                        printf("Invalid..!");
                        exit(0);
                    }
                    else{
                        flag = 1;
                    }
                }
                else{
                    append(temp[j], (int)(expr[i] - '0'));
                    if(flag == 1)
                        count++;
                }
                temp[j] -> dec = count;
                i++;
            }
            i--;
            operand_push(&s2, temp[j]);
        }
        else if(c == ')'){
            while(!operator_empty(s1) && operator_peek(s1) != '('){
                operator = operator_pop(&s1);
                operand1 = operand_pop(&s2);
                operand2 = operand_pop(&s2);
                res = operation(operand1, operand2, operator);
                operand_push(&s2, res);
            }
            if(operator_peek(s1) == '('){
                operator_pop(&s1);
            }
        }
        else if(c == '*' || c == '/' || c == '+' || c == '-' || c == '%' || c == '^'){
            if(operator_empty(s1)){
                operator_push(&s1, c);
            }
            else{
                while(!operator_empty(s1) && precedence(operator_peek(s1)) >= precedence(c)){
                    operator = operator_pop(&s1);
                    operand2 = operand_pop(&s2);
                    operand1 = operand_pop(&s2);
                    res = operation(operand1, operand2, operator);
                    operand_push(&s2, res);
                }
                operator_push(&s1, c);
            }
        }
        i++;
        j++;
    }
    while(!operator_empty(s1)){
        operator = operator_pop(&s1);
        operand2 = operand_pop(&s2);
        operand1 = operand_pop(&s2);
        res = operation(operand1, operand2, operator);
        operand_push(&s2, res);
    }
    traverse(*res);
    return 0;
}




