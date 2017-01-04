#include "Operation.h"

void main()
{
	List lst = (List)malloc(sizeof(Node));
	List numList = (List)malloc(sizeof(Node));
	List alpList = (List)malloc(sizeof(Node));
	List othList = (List)malloc(sizeof(Node));
	List allFirst = (List)malloc(sizeof(Node));
	lst = BuildList();
	PrintList(lst);
	SplitList(lst, &numList, &alpList, &othList);
	//numList1 = *numList;
	//numList = lst;
	printf("Number List is :\n");
	PrintList(numList);
	printf("Alphabet List is :\n");
	PrintList(alpList);
	printf("Other List is :\n");
	PrintList(othList);

	allFirst = ConcatList(numList, alpList, othList);
	printf("Concat List is :\n");
	PrintList(allFirst);
	system("pause");
	return;
}