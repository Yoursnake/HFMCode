#define Swap(a,b,c) ((c)=(a),(a)=(b),(b)=(c))
#define BOOL int
#define TRUE 1
#define FALSE 0
#define MaxSize 100000
#define T int

typedef struct list{
	T Elements[MaxSize];
	int Size, MaxList;
}List;

void InsertSort(List *list){
	int i, j;
	T x;
	for (i = 1; i<list->Size; i++){
		x = list->Elements[i];
		for (j = i - 1; j >= 0 && x<list->Elements[j]; j--){
			list->Elements[j + 1] = list->Elements[j];
		}
		list->Elements[j + 1] = x;
	}
}

void BubbleSort(List *list){
	int i = list->Size - 1;
	int j;
	T temp;
	BOOL sorted = FALSE;
	while (i>0 && !sorted){
		sorted = TRUE;
		for (j = 0; j<i; j++){
			if (list->Elements[j] > list->Elements[j + 1])
				Swap(list->Elements[j], list->Elements[j + 1], temp);
			sorted = FALSE;
		}
		i--;
	}
}


void BubbleSort1(List *list){
	int i = list->Size - 1;
	int j, last;
	T temp;
	while (i>0){
		last = 0;
		for (j = 0; j<i; j++){
			if (list->Elements[j] > list->Elements[j + 1]){
				Swap(list->Elements[j], list->Elements[j + 1], temp);
				last = j;
			}
		}
		i = last;
	}
}

void SelectSort(List *list){
	int i, j, index;
	T temp;
	for (i = 0; i<list->Size - 1; i++){
		index = i;
		for (j = i + 1; j<list->Size; j++){
			if (list->Elements[index]>list->Elements[j])
				index = j;
		}
		Swap(list->Elements[i], list->Elements[index], temp);
	}
}

int Partition(List *list, int left, int right){
	int i = left, j = right + 1;
	T temp;
	T pivot = list->Elements[left];
	do{
		do i++; while (list->Elements[i]<pivot);
		do j--; while (list->Elements[j]>pivot);
		if (i<j) Swap(list->Elements[i], list->Elements[j], temp);
	} while (i<j);
	Swap(list->Elements[left], list->Elements[j], temp);
	return j;
}

void QSort(List *list, int left, int right){
	int k;
	if (left<right){
		k = Partition(list, left, right);
		QSort(list, left, k - 1);
		QSort(list, k + 1, right);
	}
}

void QuickSort(List *list){
	QSort(list, 0, list->Size - 1);
}

void ISort(List *list, int left, int right){
	int k;
	if (right - left + 1 < 10){
		int i, j;
		T x;
		for (i = left + 1; i <= right; i++){
			x = list->Elements[i];
			for (j = i - 1; j >= 0 && x<list->Elements[j]; j--){
				list->Elements[j + 1] = list->Elements[j];
			}
			list->Elements[j + 1] = x;
		}
	}
	else{
		k = Partition(list, left, right);
		QSort(list, left, k - 1);
		QSort(list, k + 1, right);
	}
}

void ImprovedSort(List *list){
	ISort(list, 0, list->Size - 1);
}

