/*************************************************************************
	> File Name: bubble_sort.c
	> Author: Abbey
	> Mail:abbeychenx@gmail.com 
	> Created Time: 三  6/18 14:33:37 2014
 ************************************************************************/

void bubble_sort(int a[],int low,int high)
{
	int temp;
	for(int i=0;i<high;i++)
	{
		for(int j=0;j<=high-i-1;j++)
		{
			if(a[j]>a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
}
