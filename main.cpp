#include"Stack_Seq.h"
#include"Stack_Link.h"
#include"Share_Stack.h"

int main()
{
	//À≥–Ú’ª
	/*int a[9] = { 1,2,3,4,5,6,7,8,9 };

	Stack_Seq<int> one(a, 9);

	std::cout <<one;

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

	system("pause");*/

	//¡¥±Ì’ª
	/*int a[9] = { 1,2,3,4,5,6,7,8,9 };

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

	system("Pause");*/


	//π≤œÌ’ª
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