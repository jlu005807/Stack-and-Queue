#pragma once
#include<iostream>



template<class T>

class Stack_Seq
{
public:	
	int capcity;//ÈÝÁ¿
	T* base;//´æ·ÅÔªËØ
	int top;//Õ»¶¥Ö¸Õë
	int size;

	Stack_Seq(int capcity=50):capcity(capcity)
	{
		InitStack(capcity);
	}

	Stack_Seq(T a[],int n)
	{
		InitStack_from_array(a, n);
	}

	Stack_Seq(const Stack_Seq<T>& other)
	{
		InitStack_from_Stack(other);
	}

	~Stack_Seq()
	{
		DestroyStack();
	}

	Stack_Seq<T>& operator=(const Stack_Seq<T>& other)
	{
		if (this == &other)return *this;

		if(this->base!=nullptr)
		{
			delete[]base;
		}

		this->capcity = other.capcity;

		this->base = new T[this->capcity];

		if (!base)
		{
			throw std::exception();
		}

		top = 0;

		for (int i = 0; i < other.size; i++)
		{
			this->base[top++] = other.base[i];
		}

		return *this;
	}


	bool InitStack_from_Stack(const Stack_Seq<T>& other)
	{
		this->capcity = other.capcity;

		this->base = new T[this->capcity];//À©´óÈÝÁ¿

		if (!base)
		{
			std::cout << "Memory allocation failed" << std::endl;
			throw std::exception();
		}

		this->top = this->base;

		top = 0;

		for (int i = 0; i < other.size; i++)
		{
			this->base[top++] = other.base[i];
		}

		return true;
	}

	void InitStack_from_array(T a[],int n)
	{
		this->capcity = n + 10;//À©´óÈÝÁ¿

		this->base = new T[this->capcity];

		if (!base)
		{
			std::cout << "Memory allocation failed" << std::endl;
			throw std::exception();
		}

		for (int i = 0; i < n; i++)
		{
			base[top++] = a[i];
		}
	}

	bool InitStack(int capcity)
	{
		this->base = new T[this->capcity];
		if (!base)
		{
			std::cout << "Memory allocation failed" << std::endl;
			throw std::exception();
		}
		
		top = 0;

		return true;
	}

	void DestroyStack()
	{
		this->capcity = 0;
		delete[]base;
		base = nullptr;
		top = 0;
	}

	void ClearStack()
	{
		//Âß¼­É¾³ý
		top = 0;
		size = 0;
	}

	bool IsEmpty()const
	{
		if (top==0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool IsFull()const
	{
		if (top==capcity)return true;
		else return false;
	}

	int StackLength()const
	{
		return top;
	}

	T& GetTop()
	{
		if (!IsEmpty())
		{
			return base[top-1];
		}
	}

	bool Push(T e)
	{
		if (IsFull())
		{
			return false;
		}
		else
		{
			base[top++] = e;
			return true;
		}
	}

	T Pop()
	{
		if (IsEmpty())
		{
			std::cout << "Stack is empty" << std::endl;
			throw std::exception();
		}
		else
		{
			T e = GetTop();

			top--;

			return e;
		}

	}
	template<class K>
	friend std::ostream& operator<<(std::ostream& out, const Stack_Seq<K>& other);
};


template<class K>
std::ostream& operator<<(std::ostream& out, const Stack_Seq<K>& other)
{
	if (other.top==0)
	{
		out << "Stack is empty" << std::endl;
		return out;
	}

	for (int i = other.top - 1; i > 0; i--)
	{
		out << other.base[i] << " ";
	}

	out << other.base[0];

	return out;
}