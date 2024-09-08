#pragma once
#include"Stack_Seq.h"


template<class T>
class Queue_Stack
{
public:
	Stack_Seq<T>* S1;
	Stack_Seq<T>* S2;

	Queue_Stack(int min_capcity)
	{

	}

	~Queue_Stack()
	{

	}

	bool InitQueue(int min_capcity)
	{
		S1 = new Stack_Seq(min_capcity);

		S2 = new Stack_Seq(min_capcity);

		return true;
	}

	void DestroyQueue()
	{
		delete S1;
		delete S2;
		S1 = nullptr;
		S2 = nullptr;
	}

	void ClearQueue()
	{
		S1->ClearStack();
		S2->ClearStack();
	}

	bool QueueEmpty()
	{
		if (S1->IsEmpty() && S2->IsEmpty())
		{
			return true;
		}

		else return false;
	}

	bool QueueFull()
	{
		if (S1->IsFull() && (!S2->IsEmpty()))
		{
			return true;
		}
		else if (!S1->IsFull() || S2->IsEmpty())
		{
			return false;
		}
	}

	int QueueLength()
	{
		return S1->StackLength() + S2->StackLength();
	}

	T& GetHead()
	{
		if (QueueEmpty())
		{
			throw std::exception();
		}

		if (S2->IsEmpty())
		{
			T* e;

			while (!S1->IsEmpty())
			{
				S1->Pop(e);
				S2->Push(&e);
			}

			e = nullptr;
		}


		return S2->GetTop()

	}

	bool EnQueue(T e)
	{
		if (QueueFull())
		{
			std::cout << "Queue is Full" << std::endl;
			return false;
		}
		else if (S1->IsFull())
		{
			T* e;

			while (!S1->IsEmpty())
			{
				S1->Pop(e);
				S2->Push(&e);
			}

			e = nullptr;
		}
		
		S1->Push(e);
		return true;

	}

	bool DeQueue(T* e = nullptr)
	{
		if (QueueEmpty())
		{
			std::cout << "Queue is empty" << std::endl;
			return false;
		}
		else if (S2->IsEmpty())
		{
			T* e;

			while (!S1->IsEmpty())
			{
				S1->Pop(e);
				S2->Push(&e);
			}

			e = nullptr;
		}

		S2->Pop(e);
		
	}


};