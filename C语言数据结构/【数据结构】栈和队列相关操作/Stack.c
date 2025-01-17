#include "Stack.h"

//初始化
void StackInit(Stack* pStack)
{
	assert(pStack);
	
	pStack->top = 0;
	pStack->data = (DataType*)malloc(sizeof(DataType)*3);
	assert(pStack->data);

	pStack->capacity = 3;

}
//销毁
void StackDestory(Stack* pStack)
{
	assert(pStack);

	free(pStack->data);
	pStack->data = NULL;
	pStack->capacity = 0;
	pStack->top = 0; 
}

//入栈
void StackPush(Stack* pStack, DataType x)
{
	assert(pStack);
	if (pStack->top == pStack->capacity)
	{
		DataType* tmp = NULL;				    
		tmp = (DataType*)realloc(pStack->data, sizeof(DataType)*(pStack->capacity + 3));
		assert(tmp);
		pStack->data = tmp;
		pStack->capacity += 3;

	}
	pStack->data[pStack->top++] = x;

}
//出栈
void StackPop(Stack* pStack)
{
	//assert(pStack);
	assert(pStack->data);
	assert(pStack->top > 0);
	pStack->top--;
}
//取栈顶元素
DataType StackTop(Stack* pStack)
{
	//assert(pStack);
	assert((pStack->data)&&(pStack->top > 0));
	return pStack->data[pStack->top - 1];
}
//判空
int StackEmpty(Stack* pStack)
{
	assert(pStack);
	return pStack->top == 0;
}
//栈的大小
int StackSize(Stack* pStack)
{
	assert(pStack);
	return pStack->top;
}


 //测试
void testStack()
{
	Stack s;
	StackInit(&s);
	StackPush(&s, 1);
	StackPush(&s, 2);
	StackPush(&s, 3);
	StackPush(&s, 4);

	printf("栈的大小：%d\n",StackSize(&s));
	printf("栈顶元素：%d\n", StackTop(&s));

	while(!StackEmpty(&s))
	{
		printf("%d ", StackTop(&s));
		StackPop(&s);
	}
	printf("\n");
	StackDestory(&s);
}