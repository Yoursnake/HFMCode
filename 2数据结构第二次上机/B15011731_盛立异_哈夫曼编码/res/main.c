#include "BTree.h"
#include <stdio.h>
#include <stdlib.h>

void PrintHead();

int main(){
	int w[20] ;
	//int w[20] = {3,4,2,6,1};
	char na[20] ;
	//char na[20] = { 'A', 'B', 'C', 'D', 'E' };
	BTNode *btn;
	int i = 0;
	//int i = 5;
	char c;
	BTree HFMTree;
	char s[20];
	//char s[20] = "CABED";
	char print[200];

	char choice;

	FILE *textfile, *codefile, *codefileRead, *resultfile;/*
	fopen_s(&textfile,"textfile.txt","w");
	fopen_s(&codefile,"codefile.txt","w");
	fopen_s(&resultfile, "resultfile.txt", "w");*/

	do{
		PrintHead();
		scanf_s("%c",&choice,1);
		getchar();
		if (choice == 'X')break;
		switch (choice){
		case 'B':{
			CreateBT(&HFMTree);

			do{
				printf("请输入字符：");
				na[i] = getchar();
				printf("请输入对应的频度：");
				scanf_s("%d", &w[i]);
				getchar();
				i++;
				if (i == 20){
					printf("数组已满\n");
					break;
				}
				printf("是否继续输入（y/n）");
				c = getchar();
				getchar();
			} while (c != 'n');

			HFMTree = CreateHFMTree(na, w, i);
			printf("\n");
			break;

		}
		case 'T':{
			printf("先序遍历为：");
			PreOrder(HFMTree, Visit); printf("\n\n");
			printf("中序遍历为：");
			InOrder(HFMTree, Visit); printf("\n\n");
			break;

		}
		case 'E':{
			outputHMFTreeCode(&HFMTree);
			break;

		}
		case 'C':{
			fopen_s(&textfile, "textfile.txt", "w");
			fopen_s(&codefile, "codefile.txt", "w");
			printf("请输入需要编码的字符串：");
			scanf_s("%s", &s, _countof(s));
			getchar();

			Encode(textfile, codefile, s);

			printf("编码已保存至文件 textfile.txt 和 codefile.txt\n\n");
			fclose(textfile);
			fclose(codefile);
			break;

		}
		case 'D':{
			fopen_s(&codefile, "codefile.txt", "r");
			fopen_s(&resultfile, "resultfile.txt", "w");

			Decode(codefile, resultfile, HFMTree);

			printf("译码已保存至文件 reusltfile.txt\n\n");

			fclose(codefile);
			fclose(resultfile);
			break;
		}
		case 'P':{
			fopen_s(&textfile, "textfile.txt", "r");
			fopen_s(&codefile, "codefile.txt", "r");
			fopen_s(&resultfile, "resultfile.txt", "r");

			fscanf_s(textfile, "%s", &print, _countof(print));
			printf("textfile.txt:\n");
			printf("%s\n\n", print);

			fscanf_s(codefile, "%s", &print, _countof(print));
			printf("codefile.txt:\n");
			printf("%s\n\n", print);

			fscanf_s(resultfile, "%s", &print, _countof(print));
			printf("resultfile.txt:\n");
			printf("%s\n\n", print);


			fclose(textfile);
			fclose(resultfile);
			fclose(codefile);
		}
		}
	} while (1);

	
	

	system("pause");
	return 0;
}

void PrintHead(){
	printf("------------哈夫曼编码和系统------------\n");
	printf("----B:建树--------------------T:遍历----\n");
	printf("----E:生成编码----------------C:编码----\n");
	printf("----D:译码--------------------P:打印----\n");
	printf("---------------X:退出-------------------\n");
}