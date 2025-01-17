
#include "Sort.h"



//插入排序
//1.直接插入排序
void InsertSort(int* arr, int n)
{
	assert(arr);
	int i = 0;
	for (i = 0; i < n - 1; ++i)
	{
		int end = i;
		int temp = arr[end + 1];
		while (end >= 0 && temp < arr[end])
		{
			arr[end + 1] = arr[end];
			--end;
		}
		arr[end + 1] = temp;

	}


}
//2.希尔排序
void ShellSort(int* arr, int n)
{
	//1.预排序（接近有序）gap越小越有序，但是比较次数越多越接近插入排序（gap等于1插入排序）
	//2.插入排序
	assert(arr);
	int gap = n;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		int i = 0;
		for (i = 0; i < n - gap; ++i)
		{
			int end = i;
			int tmp = arr[end + gap];
			while (end >= 0 && tmp < arr[end])
			{
				arr[end + gap] = arr[end];
				end -= gap;
			}
			arr[end + gap] = tmp;
		}
	}

}



//选择排序
//1.选择排序,本只能一次选一个，此处优化一次选两个
void Swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;

}
void SelectSort(int* arr, int n)
{
	assert(arr);
	int begin = 0;
	int end = n - 1;

	int max = begin;
	int min = begin;

	while (begin < end)
	{
		int i = 0;
		for (i = begin; i <= end; ++i)
		{
			if (arr[i] < arr[min])
				min = i;
			if (arr[i] > arr[max])
				max = i;
		}

		if (min != begin)
		{
			Swap(&arr[min], &arr[begin]);
		}
		if (max == min)
		{
			max = min;
		}
		if (max != end)
		{
			Swap(&arr[max], &arr[end]);
		}

		end--;
		begin++;

	}

}
//2.堆排序(升序建大堆)

void AdjustDown(int *arr, int size, int i)
{
	assert(arr);
	int parent = i;
	int child = i * 2 + 1;

	while (child < size)
	{
		if (child + 1 < size&&arr[child] < arr[child + 1])
			child++;
		if (arr[child] > arr[parent])
		{
			Swap(&arr[child], &arr[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}

}
void HeapSort(int* arr, int n)
{
	assert(arr);

	int i = 0;
	for (i = (n - 2) / 2; i >= 0; --i)
	{
		AdjustDown(arr, n, i);
	}

	int end = n - 1;
	while (end > 0)
	{
		Swap(arr + 0, arr + end);

		AdjustDown(arr, end, 0);
		--end;

	}
}


//交换排序
//1.冒泡排序

void BubbleSort(int* arr, int n)
{
	int flag = 0;
	int begin = 0;
	int end = n - 1;
	while (end > 0)
	{
		for (int i = 1; i <= end; ++i)
		{
			if (arr[i]<arr[i - 1])
			{
				Swap(arr + i, arr + i - 1);
				flag = 1;
			}
		}
		if (0 == flag)
			break;
		--end;
	}

}


//2.快速排序
//方法一：
int PartSort1(int* arr, int begin, int end)
{
	assert(arr);
	int key = arr[end];
	int index = end;
	while (begin < end)
	{
		while (begin<end&&arr[begin] <= key)
		{
			begin++;
		}
		while (begin<end&&arr[end] >= key)
		{
			end--;
		}
		if (begin<end)
			Swap(&arr[begin], &arr[end]);
	}
	Swap(&arr[begin], &arr[index]);
	return begin;

}
//方法二： 挖坑法
int PartSort2(int* arr, int begin, int end)
{
	assert(arr);

	int key = arr[end];
	while (begin < end)
	{
		while (begin < end&&arr[begin] <= key)
		{
			++begin;

		}
		arr[end] = arr[begin];
		while (begin<end&&arr[end] >= key)
		{
			--end;
		}
		arr[begin] = arr[end];

	}
	arr[begin] = key;
	return begin;

}
//方法三：左右指针法
int PartSort3(int* arr, int begin, int end)
{
	assert(arr);
	int key = arr[end];

	int pCur = begin;
	int pPre = begin - 1;
	while (pCur < end)
	{
		if (arr[pCur] <= key&&++pPre != pCur)
		{
			Swap(arr + pCur, arr + pPre);
		}

		++pCur;

	}
	Swap(&arr[++pPre], &arr[end]);
	return pPre;

}

//递归
void QuickSort(int* arr, int begin, int end)
{
	assert(arr);
	if (begin < end)
	{
		int ret = PartSort2(arr, begin, end);
		QuickSort(arr, begin, ret - 1);
		QuickSort(arr, ret + 1, end);

	}
}
//优化一：三数取中法
//这里的优化主要针对选择基准元素的优化。在选择基准的时候，
//当时最坏场景的时候，左边是最小，右边是最大，
//我们可以先根据最小和最大元素的下标确定中间的元素下标，然后在和要选择的基准元素交换位置；
//如果是最优场景，三数取中也可以优化，三个数中取一个中间值，必然要比随机选择基准好一些。
int GetMiddle(int* arr, int begin, int end)
{
	assert(arr);
	int mid = begin + ((end - begin) >> 1);
	if (arr[begin]<arr[mid])
	{
		if (arr[mid]<arr[end])
			return mid;
		else
		{
			if (arr[begin]>arr[end])
				return begin;
			else
				return end;
		}
	}
	else
	{
		if (arr[end]>arr[begin])
			return begin;
		else
		{
			if (arr[mid]>arr[end])
				return mid;
			else
				return end;
		}
	}
}

int ParrtSort1(int* arr, int begin, int end)
{
	assert(arr);
	int index = GetMiddle(arr, begin, end);
	Swap(arr + index, arr + end);

	int key = arr[end];
	int index = end;
	while (begin<end)
	{
		while (begin < end&&arr[begin] <= key)
		{
			begin++;
		}
		while (begin < end&&arr[end] >= key)
		{
			end--;
		}
		if (begin<end)
			Swap(arr+end,arr+begin);

	}
	Swap(arr+end,arr+begin);
	return begin;
}
//优化二：小区间优化（把底层递归用排序算法替换）
//快排对n较大的待排序列排序是很快的，但是对于n较小的序列时间复杂度和之间插入排序是差不多的，
//而且快排的递归算法还存在函数调用和返回的开销，
//所以我们可以考虑将快排递归算法的底层递归用直接插入排序给替换掉。
void QuickSort(int* arr, int begin, int end)
{
	assert(arr);
	if (end >= begin)
		return;
	if (end - begin + 1 < 10)
		InsertSort(arr, end - begin + 1);
	int ret = PartSort2(arr, begin, end);
	QuickSort(arr, begin, ret - 1);
	QuickSort(arr, ret + 1, end);

}

//非递归
/*void QuickSort(int* arr, int left, int right)
{
	assert(arr);

	stack<int> s;
	s.push(left);
	s.push(right);

	if (!s.empty())
	{
		int end = s.top();
		s.pop();
		int begin = s.top();
		s.pop();

		int ret = PartSort(arr, begin, end);

		if (begin<ret - 1)
		{
			s.push(begin);
			s.push(ret - 1);

		}
		if (end>ret + 1)
		{
			s.push(ret + 1);
			s.push(end);
		}

	}
}  */

//归并排序
void Merge(int* arr, int begin1, int end1, int begin2, int end2, int*tmp)
{
	assert(arr&&tmp);
	int index = begin1;
	int start = begin1;
	int ret = end2 - begin1;

	while (begin1 < end1&&begin2 < end2)
	{
		if (arr[begin1] < arr[begin2])
			tmp[index++] = arr[begin1++];
		else
			tmp[index++] = arr[begin2++];

	}

	while (begin1 < end1)
		tmp[index++] = arr[begin1++];
	while (begin2 < end2)
		tmp[index++] = arr[begin2++];
	memcpy(arr + start, tmp + start, sizeof(int)*(ret + 1));
}
void _MergeSort(int* arr, int begin, int end, int* tmp)
{
	assert(arr&&tmp);

	if (begin >= end) return;

	int mid = begin + ((end - begin) >> 1);

	_MergeSort(arr, begin, mid, tmp);
	_MergeSort(arr, mid + 1, end, tmp);

	Merge(arr, begin, mid, mid + 1, end, tmp);

}
void MergeSort(int* arr, int n)
{
	assert(arr);

	int* tmp = (int*)malloc((sizeof(int))*n);
	assert(tmp);
	_MergeSort(arr, 0, n - 1, tmp);

	free(tmp);
	tmp = NULL;
}



void Print(int* arr, int n)
{
	assert(arr);
	int i = 0;
	for (i = 0; i < n; ++i)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");
}

//计数排序
void CountSort(int* arr, int n)
{
	assert(arr);
	int min = arr[0];
	int max = arr[0];
	for (int i = 0; i < n; i++)
	{
		if (arr[i]>max)
			max = arr[i];
		if (arr[i] < min)
			min = arr[i];
	}
	int count = 0;
	count = max - min + 1;

	int* tmp = (int*)malloc(count*sizeof(int));
	assert(tmp);
	memset(tmp, 0, count*sizeof(int));
	for (int i = 0; i < n; i++)
	{
		tmp[arr[i]-min]++;
	}
	int index = 0;
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < tmp[i]; j++)
		{
			arr[index++] = i + min;
		}
	}
}
