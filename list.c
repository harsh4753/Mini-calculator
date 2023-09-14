#include<stdio.h>
#include<stdlib.h>
#include "list.h"
void list_init(list* l){
    l -> head = NULL;
    l -> dec = 0;
    return;
}

int length(list l){    //gives the length of a list
    int len = 0;
    node *p = l.head;

    if(p == NULL){
        return 0;
    }
    while(p != NULL){
        len++;
        p = p -> next;
    }
    return len;
}

void insert(list* l, int pos, int d){
    node *newnode, *temp;
    int len, i;

    temp = l -> head;
    newnode = (node*)malloc(sizeof(node));
    len = length(*l);

    if(newnode == NULL)
        return;

    if(pos < 0 || pos > len)
        return;

    newnode -> dig = d;
    newnode -> next = NULL;

    if(pos == 0){
        if(l -> head == NULL){
            l -> head = newnode;
        }
        else{
            newnode -> next = l -> head;
            l -> head = newnode;
        }
        return;
    }
    else if(pos == len){
        while(temp -> next != NULL){
            temp = temp -> next;
        }
        temp -> next = newnode;
        return;
    }
    else{
        for(i = 0; i < pos - 1; i++){
            temp = temp -> next;
        }
        newnode -> next = temp -> next;
        temp -> next = newnode;
        return;
    }
}

void append(list* l, int x){

    node *nn, *p;
    nn = (node*)malloc(sizeof(node));

    if(nn){

        nn -> dig = x;
        nn -> next = NULL;
    }
    else return;

    if (l -> head == NULL) {
        l -> head = nn;
        return;
    }

    p = l -> head;
    while(p -> next){
        p = p -> next;
    }
    p -> next = nn;
    p -> next-> next = NULL;
    return;
}

int display(list l, int pos){
    fflush(stdin);
    int i;
    node* p = l.head;
    int len = length(l);

    if(pos < 0 || pos > len){
        return 0;
    }
    for(i = 0; i < pos; i++){
        p = p -> next;
    }
    return p -> dig;
}

void reverse(list* l){
    node* prev = NULL;
    node* current = l -> head;
    node* next;

    while(current != NULL){
        next = current -> next;
        current -> next = prev;
        prev = current;
        current = next;
    }
    l -> head = prev;
}

int iszero(list *l){
	int i, flag = 1;
	for(i = 0; i < length(*l); i++) {
		if(display(*l, i) != 0)
			flag = 0;
	}
	return flag;
}

int compare(list *l1, list *l2){
    int len1 = length(*l1);
    int len2 = length(*l2);
	if(l1 -> dec > l2 -> dec){
		int i;
		int y = l1 -> dec - l2 -> dec;
		for(i = 0; i < y; i++) {
			append(l2, 0);
			(l2 -> dec)++;
		}
	}
	else if(l2 -> dec > l1 -> dec){
		int i;
		int y = (l2 -> dec - l1 -> dec);
		for(i = 0; i < y; i++) {
			append(l1, 0);
			(l1 -> dec)++;
		}
	}
	int a = (len1 - len2);
	if(a > 0){
		int i = 0;
		while(i < a) {
			insert(l2, 0, 0);
			i++;
		}
	}
	else if(a < 0) {
		int i = 0;
		a = -a;
		while(i < a) {
			insert(l1, 0, 0);
			i++;
		}
	}
		int i;
		for(i = 1; i <= len1; i++) {
			if(display(*l1, i - 1) > display(*l2, i - 1))
				return 1;
			else if(display(*l1, i - 1) < display(*l2, i - 1))
				return -1;
		}
		return 0;
}

int remove_zero(list *l){
    int i = 0;
	node* p;
	int len = length(*l);
	int decimal = l -> dec;
	while(i < len - (l -> dec)){
        if(l -> head -> dig != 0){
            break;
        }
        else{
            p = l -> head;
            l -> head = p -> next;
            free(p);
        }
        i++;
	}
	i = 0;
	reverse(l);
	while(i < decimal - 2){
        if(l -> head -> dig != 0){
            break;
        }
        else{
            p = l -> head;
            l -> head = p -> next;
            free(p);
            (l -> dec)--;
        }
        i++;
	}
	reverse(l);
    return 0;
}

list* addition(list *l1, list *l2){
    list* res;
    res = (list*)malloc(sizeof(list));
    list_init(res);
    int dig = 0;
    int carry = 0;
    int len1, len2;

    int p = length(*l1);
    int q = length(*l2);
    if(l1 -> dec > l2 -> dec){
        int i;
        int j = ((l1 -> dec) - (l2 -> dec));

        for(i = 0; i < j; i++){
            insert(l2, q, 0);
            (l2 -> dec)++;
            q++;
        }
    }
    else if(l1 -> dec < l2 -> dec){
        int i;
        int j = ((l2 -> dec) - (l1 -> dec));

        for(i = 0; i < j; i++){
            insert(l1, p, 0);
            (l1 -> dec)++;
            p++;
        }
    }
    len1 = length(*l1);
    len2 = length(*l2);

    while(len1 != 0 || len2 != 0){
        if(len1 == 0){
            dig = display(*l2, len2 - 1) + carry;
            insert(res, 0, dig);
            len2--;
            carry = 0;
        }
        else if(len2 == 0){
            dig = display(*l1, len1 - 1) + carry;
            insert(res, 0, dig);
            len1--;
            carry = 0;
        }
        else{
            dig = display(*l1, len1 - 1) + display(*l2, len2 - 1) + carry;
            carry = dig / 10;
            dig = dig % 10;
            insert(res, 0, dig);
            len1--;
            len2--;
        }
    }
    if(carry != 0)
        insert(res, 0, carry);

    res -> dec = l1 -> dec;
    return res;
}

list* subtract(list *l1, list *l2){
    list* res;
    res = (list*)malloc(sizeof(list));
    list_init(res);
    int borrow = 0;
    int num = 0;
    int len1, len2;

    int p = length(*l1);
    int q = length(*l2);

    if(l1 -> dec > l2 -> dec){
        int i;
        int j = ((l1 -> dec) - (l2 -> dec));

        for(i = 0; i < j; i++){
            insert(l2, q, 0);
            (l2 -> dec)++;
            q++;
        }
    }
    else if(l1 -> dec < l2 -> dec){
        int i;
        int j = ((l2 -> dec) - (l1 -> dec));

        for(i = 0; i < j; i++){
            insert(l1, p, 0);
            (l1 -> dec)++;
            p++;
        }
    }
    len1 = length(*l1);
    len2 = length(*l2);

    while(len1 != 0){
        if(len2 == 0){
            num = display(*l1, len1 - 1) - borrow;
            insert(res, 0, num);
            len1--;
        }
        else{
            num = display(*l1, len1 - 1) - display(*l2, len2 - 1) - borrow;
            if(num < 0){
                num = 10 + num;
                insert(res, 0, num);
                borrow = 1;
            }
            else{
                insert(res, 0, num);
                borrow = 0;
            }
            len1--;
            len2--;
        }
    }
    res -> dec = l1 -> dec;
    return res;
}

void traverse(list l){
    node *p = l.head;
    int i = 0;
    int flag = 0;

    int len = length(l);

    if(p == NULL){
        return;
    }
    while(p != NULL){
        if(i < len - (l.dec)){
            printf("%d", p -> dig);
        }
        if(i == len - (l.dec)){
            if(i == 0)
                printf("0.");
            else
                printf(".");
            flag = 1;     
        }
        if(flag == 1){
            printf("%d", p -> dig);
       }
        p = p -> next;
        i++;
    }
    printf("\n");
}

list* multiply(list* l1, list* l2){
    int i, x, y;
    node *p, *q, *m;
    int carry = 0;
    list *res, *temp;
    res = (list*)malloc(sizeof(list));
    temp = (list*)malloc(sizeof(list));
    list_init(res);
    list_init(temp);


    reverse(l1);
    reverse(l2);

    q = l2 -> head;

    int count = 0;
    while(q != NULL){

        x = q -> dig;
        p = l1 -> head;

        for(i = 0; i < count; i++){
            insert(temp, 0, 0);
        }

        while(p != NULL){
            y = (p -> dig) * x + carry;
            carry = y / 10;
            y = y % 10;
            insert(temp, 0, y);
            p = p -> next;
        }
        if(carry != 0){
            insert(temp, 0, carry);
            carry = 0;
        }
        //traverse(*temp);
        res = addition(temp, res);
        q = q -> next;
        m = temp -> head;
        temp -> head = NULL;
        free(m);
        count++;
    }
    reverse(l1);
    reverse(l2);

    res -> dec = l1 -> dec + l2 -> dec;
    return res;
}
list* division(list *l1, list *l2){
    if(iszero(l2)){
        printf("Invalid..!");
        return NULL;
    }
    list *res, *temp;
    res = (list*)malloc(sizeof(list));
    temp = (list*)malloc(sizeof(list));
    list_init(res);
    list_init(temp);

    int i, j, num;
    int dec1 = l1 -> dec;
    int dec2 = l2 -> dec;

    int len1 = length(*l1);
    l1 -> dec = l2 -> dec = 0;

    for(i = 0; i < len1; i++){
        num = display(*l1, i);
        append(temp, num);

        if(compare(temp, l2) < 0){
            append(res , 0);

        }
        else{
            int count = 0;
            while(1){
                temp = subtract(temp, l2);
                count++;
                if(compare(temp, l2) < 0){
                    break;
                }
            }
            append(res, count);
        }
    }
    j = 0;
    while(j < 10){
        append(temp, 0);
        int count = 0;
        while(compare(temp, l2) >= 0){
            temp = subtract(temp, l2);
            count++;
        }
        append(res, count);
        j++;
    }
    l1 -> dec = dec1;
    l2 -> dec = dec2;
	res -> dec = 10 + dec1 - dec2;
	free(temp);

	//remove_zero(l1);
	remove_zero(l2);
	remove_zero(res);

	return res;
}








