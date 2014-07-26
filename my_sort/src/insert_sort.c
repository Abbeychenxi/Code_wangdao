/*************************************************************************
	> File Name: insert_sort.c
	> Author: Abbey
	> Mail:abbeychenx@gmail.com 
	> Created Time: 三  6/18 13:38:29 2014
 ************************************************************************/

void insert_sort(int a[],int low,int high)
{
	int temp;
	int i,j;
	for (i=low+1;i<=high;i++)
	{
		temp=a[i];
		j=i-1;

		while((i<=high)&&(temp<a[j]))
		{
			a[j+1]=a[j];
			j--;
		}
		a[j+1]=temp;
	}
}
