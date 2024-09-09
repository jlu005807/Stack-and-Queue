#pragma once
#include<iostream>


template<class T>
class Queue_Node
{
public:
	Queue_Node()
	{
		next = nullptr;
	}

	Queue_Node(T e)
	{
		m_data = e;
		next = nullptr;
	}


	T m_data;
	Queue_Node* next;
};


template<class T>
class Queue_Link
{
public:
	Queue_Node<T>* front;
	Queue_Node<T>* rear;
	int size;

	Queue_Link()
	{
		InitQueue();
	}

	Queue_Link(T a[],int n)
	{
		InitQueue_from_array(a,n);
	}

	Queue_Link(const Queue_Link<T>& other)
	{
		InitQueue_from_Queue(other);
	}

	Queue_Link<T>& operator=(const Queue_Link<T>& other)
	{
		if (this != &other)
		{
			InitQueue_from_Queue(other);
		}

		return *this;
	}

	~Queue_Link()
	{
		DestroyQueue();
	}

	bool InitQueue()
	{
		front = new Queue_Node<T>();

		if (!front)
		{
			std::cout << "Memory allocation failed" << std::endl;
			throw std::exception();
		}

		rear = front;

		size = 0;

		return true;
	}


	void InitQueue_from_array(T a[], int n)
	{
		InitQueue();

		for (int i = 0; i < n; i++)
		{
			EnQueue(a[i]);
		}

	}

	void InitQueue_from_Queue(const Queue_Link<T>& other)
	{
		InitQueue();

		Queue_Node<T>* p = other.front->next;

		while (p != nullptr)
		{
			EnQueue(p->m_data);
			p = p->next;
		}

	}

	void DestroyQueue()
	{
		ClearQueue();
		delete front;

		front = rear = nullptr;


	}

	void ClearQueue()
	{
		Queue_Node<T>* p = front->next;

		for (int i = 0; i < size; i++)
		{
			Queue_Node<T>* v = p;
			p = p->next;
			delete v;
		}

		rear = front;

		size = 0;

	}

	bool QueueEmpty()const
	{
		if (size == 0)return true;
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

		return front->next->m_data;

	}

	bool EnQueue(T e)
	{
		Queue_Node<T>* p = new Queue_Node<T>(e);

		if (!p)
		{
			std::cout << "Memory allocation failed" << std::endl;
			throw std::exception();
		}

		rear->next = p;

		rear = p;

		size++;

		return true;

	}

	T DeQueue()
	{
		if (QueueEmpty())
		{
			std::cout << "Queue is empty" << std::endl;
			throw std::exception();
		}

		Queue_Node<T>* p = front->next;

		T e = GetHead();

		front->next = p->next;

		delete p;

		size--;

		return e;

	}
	template<class K>
	friend std::ostream& operator<<(std::ostream& out, const Queue_Link<K>& other);
};

template<class K>
std::ostream& operator<<(std::ostream& out, const Queue_Link<K>& other)
{
	if (other.QueueEmpty())
	{
		std::cout << "Queue is empty" << std::endl;
		return out;
	}

	Queue_Node<K>* p = other.front->next;

	while (p != nullptr)
	{
		out << p->m_data << " ";
		p = p->next;
	}

	out << std::endl;

	return out;
	
}