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
		InitQueue(min_capcity);
	}

	Queue_Stack(T a[], int n)
	{
		InitQueue_from_array(a, n);
	}

	Queue_Stack(const Queue_Stack<T>& other)
	{
		InitQueue_from_Queue(other);
	}

	~Queue_Stack()
	{
		DestroyQueue();
	}

	Queue_Stack& operator=(const Queue_Stack& other)
	{
		if (this == &other)return *this;

		delete S1;
		delete S2;

		InitQueue_from_Queue(other);
	}


	bool InitQueue_from_Queue(const Queue_Stack<T>& other)
	{
		S1 = new Stack_Seq<T>(*(other.S1));
		S2 = new Stack_Seq<T>(*(other.S2));

		if ((!S1) || (!S2))
		{
			throw std::exception();
			return false;
		}

		return true;
	}

	bool InitQueue_from_array(T a[], int n)
	{
		S1 = new Stack_Seq<T>(n);
		S2 = new Stack_Seq<T>(n);

		if ((!S1) || (!S2))
		{
			throw std::exception();
			return false;
		}

		for (int i = 0; i < n; i++)
		{
			S1->Push(a[i]);
		}

		return true;
	}

	bool InitQueue(int min_capcity)
	{
		S1 = new Stack_Seq<T>(min_capcity);//À©´ó

		S2 = new Stack_Seq<T>(min_capcity);

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

	void Transform()
	{
		while (!S1->IsEmpty())
		{
			T p = S1->Pop();
			S2->Push(p);
		}
	}

	bool QueueEmpty()const
	{
		if (S1->IsEmpty() && S2->IsEmpty())
		{
			return true;
		}

		else return false;
	}

	bool QueueFull() const
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

	int QueueLength() const
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
			Transform();
		}


		return S2->GetTop();

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
			Transform();
		}
		
		S1->Push(e);
		return true;

	}

	T DeQueue()
	{
		if (QueueEmpty())
		{
			std::cout << "Queue is empty" << std::endl;
			throw std::exception();
		}
		else if (S2->IsEmpty())
		{
			Transform();
		}
		T p=S2->Pop();
		return p;
	}


	template<class K>
	friend std::ostream& operator<<(std::ostream& out, const Queue_Stack<K>& other);

};


template<class K>
std::ostream& operator<<(std::ostream& out, const Queue_Stack<K>& other)
{
	if (other.QueueEmpty())
	{
		out << "Queue is empty" << std::endl;
		return out;
	}

	if (!other.S2->IsEmpty())
	{
		K* p = other.S2->top - 1;

		for (p; p != other.S2->base; p--)
		{
			out << *p << " ";
		}

		out << *p <<" ";

		p = nullptr;
	}

	K* p = other.S1->base;

	for (p; p != other.S1->top - 1; p++)
	{
		out << *p << " ";
	}

	out << *p << std::endl;

	return out;

}