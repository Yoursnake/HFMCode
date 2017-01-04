#include "ADT.h"

typedef Node* List;

List BuildList()
{
	Node *p, *r = NULL, *first = NULL;
	char c;
	printf("Another element?y/n");
	while ((c = getchar()) == '\n');
	while (c != 'n'){
		p = NewNode1();
		if (first != NULL)
			r->Link = p;
		else
			first = p;
		r = p;
		printf("Another element?y/n");
		while ((c = getchar()) == '\n');
	}
	return first;
}

void PrintList(List first)
{
	printf("\tThe list contains:");
	while (first != NULL){
		PrintElement(first->Element);
		first = first->Link;
	}
	printf("\n\n");
}

void Clear(List *first)
{
	Node *p = *first;
	while (*first){
		p = (*first)->Link;
		free(*first);
		*first = p;
	}
}

void SplitList(Node *first, Node **numFirst, Node **alpFirst, Node **othFirst)
{
	Node *p = first, *a = NULL, *b = NULL, *c = NULL, *q = NULL;
	//*numFirst = a; 
	//*numFirst->Link = NULL;
	//*alpFirst->Link = NULL;
	//*othFirst->Link = NULL;
	
	a = *numFirst;
	b = *alpFirst;
	c = *othFirst;

	while (p != NULL){

		if (p->Element[0] >= '0' && p->Element[0] <= '9'){
			/*if (a == NULL){
				a = p;
				*numFirst = a;
			}
			else{*/
				a->Link = p;
				a = a->Link;
			//}

		}
		else if (p->Element[0] >= 'a' && p->Element[0] <= 'z'
			|| p->Element[0] >= 'A' && p->Element[0] <= 'Z'){
			/*if (b == NULL){
				b = p;
				*alpFirst = b;
				
			}
			else{*/
				b->Link = p;
				b = b->Link;
			//}
		}
		else{
			/*if (c == NULL){
				c = p;
				*othFirst = c;
				
			}
			else{*/
				c->Link = p;
				c = c->Link;
			//}
		}
		p = p->Link;


	}
	if (a != NULL){
		a->Link = NULL;
	}if (b != NULL){
		b->Link = NULL;
	}
	if (c != NULL){
		c->Link = NULL;
	}

}

List FirstToLast(Node* p){
	if (p == NULL)
		return p;

	while (p->Link != NULL)
		p = p->Link;
	return p;
}

List ConcatList(Node* numFirst, Node* alpFirst, Node* othFirst){

	List q = numFirst, p = NULL, allfirst = NULL;

	p = FirstToLast(q);
	allfirst = numFirst;
	if (p != NULL){
		p->Link = alpFirst;
		q = p->Link;
		
	}
	else
		q = alpFirst;

	p = FirstToLast(q);
	if (p != NULL){
		p->Link = othFirst;
		q = p->Link;

		if (allfirst == NULL)
			allfirst = alpFirst;
	}
	else
		q = othFirst;

	p = FirstToLast(q);
	if (p != NULL){
		if (allfirst == NULL){
			allfirst = othFirst;
		}
	}

	return allfirst;
}

