/*************************************************************************
	> File Name: quick_sort.c
	> Author: Abbey
	> Mail:abbeychenx@gmail.com 
	> Created Time: 三  6/18 12:57:07 2014
 ************************************************************************/

void quick_sort(int a[],int low ,int high)
{
	int i=low;
	int j=high;
	int temp=a[i];

	if(low < high)
	{
		while(i<j)
		{
			while((a[j]>=temp)&&(i<j))
			{
				j--;
			}
			a[i]=a[j];
			while((a[i]<=temp)&&(i<j))
			{
				i++;
			}
			a[j]=a[i];
		}
		a[i]=temp;
		quick_sort(a,low,i-1);
		quick_sort(a,j+1,high);
	}
	else
	{
		return;
	}
}
