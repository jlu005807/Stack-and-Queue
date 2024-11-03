#include"Stack_Seq.h"
#include"Stack_Link.h"
#include"Share_Stack.h"
#include"Queue_Stack.h"
#include"Queue_Seq.h"
#include"Queue_Link.h"
#include"Postfix.h"
#include<string>
#include<cctype>

//顺序栈
void TestStack_Seq()
{
	int a[9] = { 1,2,3,4,5,6,7,8,9 };

	Stack_Seq<int> one(a, 9);

	std::cout << one;

	system("Pause");

	Stack_Seq<int> two = one;

	two.Pop();

	two.Push(7);

	two.ClearStack();

	two = one;

	two.Pop();

	two.Push(7);

	two.Push(66);

	std::cout << two;

	system("pause");
}

//链表栈
void TestStack_Link()
{
	int a[9] = { 1,2,3,4,5,6,7,8,9 };

	Stack_Link<int> one(a, 9);

	one.Pop();

	one.Push(55);

	std::cout << one;

	system("Pause");

	Stack_Link<int> two(one);

	two.Pop();

	two.Push(22);

	two.ClearStack();

	std::cout << two;

	system("Pause");

	two = one;

	std::cout << two;

	system("Pause");

}

//共享栈
void TestShare_Stack()
{
	int a[9] = { 1,2,3,4,5,6,7,8,9 };

	Share_Stack<int> one(a, 9);

	one.Pop(0);

	one.Push(55, 1);

	one.ClearStack(1);

	std::cout << one;

	system("Pause");

	Share_Stack<int> two(one);

	one.Push(44, 1);

	std::cout << two;

	system("pause");

	two = one;

	std::cout << two;

	system("Pause");
}

//模拟队列
void TestQueue_Stack()
{
	int a[9] = { 1,2,3,4,5,6,7,8,9 };

	Queue_Stack<int> one(a, 9);

	one.DeQueue();

	one.EnQueue(55);

	std::cout << one;

	system("pause");

	Queue_Stack<int> two = one;

	std::cout << two;

	system("pause");

	one.EnQueue(44);

	std::cout << one;

	system("pause");

	two = one;

	std::cout << two;

	system("pause");
}

//顺序队列
void TestQueue_Seq()
{
	int a[9] = { 1,2,3,4,5,6,7,8,9 };

	Queue_Seq<int> one(a, 9);

	one.DeQueue();

	one.EnQueue(55);

	std::cout << one;

	system("pause");

	Queue_Seq<int> two = one;

	std::cout << two;

	one.DeQueue();

	std::cout << one;

	system("Pause");

	two = one;

	std::cout << two;

	system("Pause");
}

//链表队列
void TestQueue_Link()
{
	int a[9] = { 1,2,3,4,5,6,7,8,9 };

	Queue_Link<int> one(a, 9);

	one.DeQueue();

	one.EnQueue(11);

	std::cout << one;

	system("pause");

	Queue_Link<int> two = one;

	std::cout << two;

	one.DeQueue();

	std::cout << one;

	system("Pause");

	two = one;

	std::cout << two;

	system("Pause");
}

//表达式栈
void TestPostfix()
{
	std::string s;

	std::cin >> s;

	Postfix one(s);


	std::cout << one.postfix << " = " << one.result << std::endl;

	system("pause");
}

int main()
{
	TestStack_Seq();

	TestStack_Link();

	TestShare_Stack();

	TestQueue_Stack();

	TestQueue_Seq();

	TestQueue_Link();

	TestPostfix();
	
}