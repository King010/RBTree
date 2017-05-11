#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include"RBTree.h"
using namespace std;



int main()
{
	RBTree<int, int>brt;
	int a[10] = { 8, 7, 9, 15, 6, 10, 14, 13, 5, 16 };
	for (int i = 0; i < 10; i++)
	{
		brt.Insert(a[i],i);
	}
	brt.InOrder();
	brt.CheckRBTree();
	system("pause");
	return 0;
}
