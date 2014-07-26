/*************************************************************************
	> File Name: main.c
	> Author: Abbey
	> Mail:abbeychenx@gmail.com 
	> Created Time: 三  6/18 14:45:59 2014
 ************************************************************************/

#include<stdio.h>
#include "func.h"


int main()
{
	int a[5];
	int i=0;
	while (scanf("%d",&a[i])!=EOF)
	{
		i++;
	}

	quick_sort(a,0,4);
	for(int i=0;i<5;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
	insert_sort(a,0,4);
	for(int i=0;i<5;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
	select_sort(a,0,4);
	for(int i=0;i<5;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
	bubble_sort(a,0,4);
	for(int i=0;i<5;i++)
	{
		printf("%d ",a[i]);
	}
	printf("\n");

	return 0;
}

