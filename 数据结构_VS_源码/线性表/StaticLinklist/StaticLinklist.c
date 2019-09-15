#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define MAXSIZE 20
typedef struct {
	int data;
	int cur;
}Component;

void create_StaticLinklist(Component* arr);
int malloc_node(Component* arr);
void free_node(Component* arr, int k);
bool insert_StaticLinklist(Component* arr, int pos, int value);
bool delete_StaticLinklist(Component* arr, int pos, int* value);
bool is_empty(Component* arr);
bool is_full(Component* arr);
int length_StaticLinklist(Component* arr);
void sort_StaticLinklist(Component* arr);
void show_arr(const Component* arr);
int Getelem_StaticLinklist(Component* arr, int pos);

int main(void)
{
	Component arr[MAXSIZE];														//采用结构数组的方式，向函数传入它的数组名（即一个const指针）
	int value;

	create_StaticLinklist(arr);
	show_arr(arr);

	insert_StaticLinklist(arr, 3, 45);
	insert_StaticLinklist(arr, 1, 34);
	printf("After inserting:\n");
	show_arr(arr);

	printf("After deleting:\n");
	if (delete_StaticLinklist(arr, 2, &value))
		printf("You delete member %d and its value is %d.\n", 2, value);
	else
		printf("No data deleted.\n");
	show_arr(arr);

	sort_StaticLinklist(arr);
	printf("After sorting:\n");
	show_arr(arr);

	printf("The member %d is %d\n", 3, Getelem_StaticLinklist(arr, 3));

	return 0;
}

void create_StaticLinklist(Component* arr)
{
	int len;
	int i;

	printf("Enter the length of Static linked list: ");
	scanf("%d", &len);
	if ((len > MAXSIZE - 1) || len < 1)
	{
		printf("out of range!\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < MAXSIZE - 1; i++)
		arr[i].cur = i + 1;
	arr[MAXSIZE - 1].cur = 0;
	for (i = 1; i <= len; i++)
	{
		printf("Enter the value for member %d: ", i);
		scanf("%d", &arr[i].data);
	}
	arr[i - 1].cur = 0;
	arr[MAXSIZE - 1].cur = 1;
	arr[0].cur = i;

}

bool is_empty(Component* arr)
{
	if (arr[MAXSIZE - 1].cur == 0)
		return true;
	else
		return false;
}

bool is_full(Component* arr)
{
	if (arr[0].cur == 0)
		return true;
	else
		return false;
}

int malloc_node(Component* arr)
{
	int i = arr[0].cur;
	if (i)
		arr[0].cur = arr[i].cur;
	return i;
}

void free_node(Component* arr, int k)
{
	arr[k].cur = arr[0].cur;
	arr[0].cur = k;
}

bool insert_StaticLinklist(Component* arr, int pos, int value)
{
	int i, k, j;
	k = MAXSIZE - 1;
	if (pos<1 || pos>length_StaticLinklist(arr) + 1)
		return false;
	j = malloc_node(arr);
	if (j)
	{
		arr[j].data = value;
		for (i = 1; i < pos; i++)
			k = arr[k].cur;
		arr[j].cur = arr[k].cur;
		arr[k].cur = j;
		return true;
	}
	else
		return false;
}

bool delete_StaticLinklist(Component* arr, int pos, int* value)
{
	int i, k;
	k = MAXSIZE - 1;
	if (pos<1 || pos>length_StaticLinklist(arr))
		return false;

	for (i = 1; i < pos; i++)
		k = arr[k].cur;												//得到pos的前一位
	int j = arr[k].cur;
	*value = arr[j].data;
	arr[k].cur = arr[j].cur;
	free_node(arr, j);
	return true;
}

int length_StaticLinklist(Component* arr)
{
	int i = arr[MAXSIZE - 1].cur;
	int len = 0;

	while (i)
	{
		len++;
		i = arr[i].cur;
	}
	return len;
}

void sort_StaticLinklist(Component* arr)
{
	int top, seek;
	int i, j;

	for (top = 0, i = arr[MAXSIZE - 1].cur; top < length_StaticLinklist(arr) - 1; top++, i = arr[i].cur)
		for (seek = top + 1, j = arr[i].cur; seek < length_StaticLinklist(arr); seek++, j = arr[j].cur)
			if (arr[i].data > arr[j].data)
			{
				int temp = arr[i].data;
				arr[i].data = arr[j].data;
				arr[j].data = temp;
			}
}

void show_arr(const Component* arr)
{
	int i, j;
	for (j = 1, i = arr[MAXSIZE - 1].cur; j <= length_StaticLinklist(arr); j++, i = arr[i].cur)
		printf("%d ", arr[i].data);
	putchar('\n');
}

int Getelem_StaticLinklist(Component* arr, int pos)
{
	int i = MAXSIZE - 1;
	int j;

	for (j = 0; j < pos; j++)
		i = arr[i].cur;
	return arr[i].data;
}