/*************************************************************************
	> File Name: select_sort.c
	> Author: Abbey
	> Mail:abbeychenx@gmail.com 
	> Created Time: 三  6/18 14:19:21 2014
 ************************************************************************/

void select_sort(int a[],int low,int high)
{
	int temp;
	for(int i=low;i<high+1;i++)
	{
		int j=i+1;
		while(j<=high)
		{
			if(a[i]<=a[j])
			{
				j++;
			}
			else
			{
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
				j++;
			}
		}
	}
}
