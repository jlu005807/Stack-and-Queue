#pragma once
#include<iostream>



template<class T>

class Stack_Seq
{
public:	
	int capcity;
	T* base;
	T* top;

	Stack_Seq(int capcity=1):capcity(capcity)
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

		this->top = this->base;

		T* p = other.base;

		for (p; p != other.top; p++)
		{
			*(this->top++) = *p;
		}

		return *this;
	}


	bool InitStack_from_Stack(const Stack_Seq<T>& other)
	{
		this->capcity = other.capcity;

		this->base = new T[this->capcity];//��������

		if (!base)
		{
			throw std::exception();
		}

		
	}

	void InitStack_from_array(T a[],int n)
	{
		this->capcity = n + 10;//��������

		this->base = new T[this->capcity];

		if (!base)
		{
			throw std::exception();
		}

		this->top = this->base;

		for (int i = 0; i < n; i++)
		{
			*(top++) = a[i];
		}
	}

	bool InitStack(int capcity)
	{
		this->base = new T[this->capcity];
		if (!base)
		{
			exit(OVERFLOW);
		}
		this->top = base;
		
		return true;
	}

	void DestroyStack()
	{
		this->capcity = 0;
		delete[]base;

	}

	void ClearStack()
	{
		this->top = this->base;
	}

	bool IsEmpty()const
	{
		if (this->top == this->base)
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
		if (this->top - this->base == this->capcity)return true;
		else return false;
	}

	int StackLength()const
	{
		return (top - base);
	}

	T& GetTop()
	{
		if (!IsEmpty())
		{
			return *(top-1);
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
			*(this->top++) = e;
			return true;
		}
	}

	bool Pop(T* e = nullptr)
	{
		if (IsEmpty())return false;
		else
		{
			if(e)
			{
				e = &GetTop();
			}
			top--;
			return true;
		}

	}
	template<class K>
	friend std::ostream& operator<<(std::ostream& out, const Stack_Seq<K>& other);
};


template<class K>
std::ostream& operator<<(std::ostream& out, const Stack_Seq<K>& other)
{
	if (other.base==other.top)
	{
		out << "Stack is empty" << std::endl;
		return out;
	}
	K* p = other.top-1;

	for (p; p != other.base; p--)
	{
		out << *p<<" ";
	}

	out << *p<<std::endl;

	return out;
}