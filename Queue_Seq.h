#pragma once
#include<iostream>


template<class T>
class Queue_Seq
{
public:
	int capcity;
	int front;
	int rear;
	int size;
	T* element;
	

	Queue_Seq(int capcity=1)
	{
		InitQueue(capcity);
	}

	Queue_Seq(T a[], int n)
	{
		InitQueue_from_array(a, n);
	}

	Queue_Seq(const Queue_Seq<T>& other)
	{
		InitQueue_from_Queue(other);
	}

	~Queue_Seq()
	{
		DestroyQueue();
	}

	void InitQueue_from_Queue(const Queue_Seq<T>& other)
	{
		InitQueue(other.capcity);

		int i = other.front;

		for (int k = 0; k < other.size; k++)
		{
			this->EnQueue(other.element[i]);
			i = (i + capcity + 1) % capcity;
		}


	}

	Queue_Seq<T>& operator=(const Queue_Seq<T>& other)
	{
		delete[]element;

		if(this!=&other)
		{
			InitQueue_from_Queue(other);
		}

		return *this;
	}

	void InitQueue_from_array(T a[], int n)
	{
		//扩大容量
		InitQueue(n+1);
		for (int i = 0; i < n; i++)
		{
			EnQueue(a[i]);
		}
	}

	void InitQueue(int capcity)
	{
		this->capcity = capcity;
		size = 0;
		element = new T[this->capcity];

		if (!element)
		{
			std::cout << "Memory allocation failed" << std::endl;
			throw std::exception();
		}

		front = rear = 0;
	}

	void DestroyQueue()
	{
		delete[]element;
		element = nullptr;
		ClearQueue();
	}

	void ClearQueue()
	{
		front = rear = 0;
		size = 0;
	}

	bool QueueEmpty()const
	{
		if (size == 0)return true;
		else return false;
	}

	bool QueueFull()const
	{
		if (size == capcity)return true;
		else return false;
	}

	int QueueLength()const
	{
		return size;
	}

	T& GetHead()
	{
		if (QueueEmpty())
		{
			std::cout << "Queue is empty" << std::endl;
			throw std::exception();
		}

		return element[front];

	}

	bool EnQueue(T e)
	{
		if (QueueFull())
		{
			std::cout << "Queue is full" << std::endl;
			throw std::exception();
			return false;

		}

		element[rear] = e;
		rear = (rear + capcity + 1) % capcity;//取模循环
		size++;

	}

	T DeQueue()
	{
		if (QueueEmpty())
		{
			std::cout << "Queue is empty" << std::endl;
			throw std::exception();
		}

		T p = element[front];
		front = (front + capcity + 1) % capcity;
		size--;

	}

	template<class K>
	friend std::ostream& operator<<(std::ostream& out, const Queue_Seq<K>& other);
};

template<class K>
std::ostream& operator<<(std::ostream& out, const Queue_Seq<K>& other)
{
	if (other.QueueEmpty())
	{
		out << "Queue is empty" << std::endl;
		return out;
	}

	int i = other.front;

	for (int k = 0; k < other.size; k++)
	{
		out << other.element[i] << " ";
		i = (i + other.capcity + 1) % other.capcity;
	}

	return out;
}