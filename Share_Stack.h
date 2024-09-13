#pragma once
#include<iostream>

#pragma once
#include<iostream>



template<class T>

class Share_Stack
{
public:
	int capcity;
	int top[2];
	T* base;

	Share_Stack(int capcity = 1) :capcity(capcity)
	{
		InitStack(capcity);
	}

	Share_Stack(T a[], int n)
	{
		InitStack_from_array(a, n);
	}

	Share_Stack(const Share_Stack<T>& other)
	{
		InitStack_from_Stack(other);
	}

	~Share_Stack()
	{
		DestroyStack();
	}

	Share_Stack<T>& operator=(const Share_Stack<T>& other)
	{
		if (this == &other)return *this;

		if (this->base != nullptr)
		{
			delete[]base;
		}


		this->capcity = other.capcity;
		this->base = new T[this->capcity];

		if (!base)
		{
			throw std::exception();
		}

		this->top[0] = -1;
		this->top[1] = this->capcity;

		while (top[0] != other.top[0])
		{
			this->top[0]++;
			this->base[top[0]] = other.base[top[0]];
		}

		while (top[1] != other.top[1])
		{
			this->top[1]--;
			this->base[top[1]] = other.base[top[1]];
		}

		return *this;
	}


	bool InitStack_from_Stack(const Share_Stack<T>& other)
	{
		this->capcity = other.capcity;

		this->base = new T[this->capcity];

		if (!base)
		{
			std::cout << "Memory allocation failed" << std::endl;
			throw std::exception();
		}

		this->top[0] = -1;
		this->top[1] = this->capcity;

		while (top[0] != other.top[0])
		{
			this->top[0]++;
			this->base[top[0]] = other.base[top[0]];
		}
		
		while (top[1] != other.top[1])
		{
			this->top[1]--;
			this->base[top[1]] = other.base[top[1]];
		}

		return 0;
	}

	void InitStack_from_array(T a[], int n)
	{
		this->capcity = n + 10;//À©´óÈÝÁ¿

		this->base = new T[this->capcity];

		if (!base)
		{
			std::cout << "Memory allocation failed" << std::endl;
			throw std::exception();
		}

		this->top[0] = -1;
		this->top[1] = this->capcity;

		for (int i = 0; i < n; i++)
		{
			this->top[0]++;
			this->base[top[0]] = a[i];
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
		this->top[0] = -1;
		this->top[1] = this->capcity;

		return true;
	}

	void DestroyStack()
	{
		this->capcity = 0;
		this->top[0] = -1;
		this->top[1] = this->capcity;

		delete[]base;
		
		base = nullptr;

	}

	void ClearStack(int i=-1)
	{
		switch (i)
		{
		case -1:
			this->top[0] = -1;
			this->top[1] = this->capcity;
			break;
		case 0:
			this->top[0] = -1;
			break;
		case 1:
			this->top[1] = this->capcity;
			break;
		default:
			break;
		}
		
	}

	bool IsEmpty(int i=-1)const
	{
		switch (i)
		{
		case -1:
		{
			if (this->top[0] == -1 && this->top[1] == this->capcity)
			{
				return true;
			}
			else
			{
				return false;
			}
			break;
		}
		case 0:
			return this->top[0] == -1;
			break;
		case 1:
			return this->top[1] == this->capcity;
			break;
		default:
			break;
		}
	}

	bool IsFull()const
	{
		if (this->top[0] + 1 == this->top[1])
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int StackSize()const
	{
		int i = this->capcity - this->top[1];
		int j = this->top[0] + 1;

		return i + j;
	}

	T& GetTop(int i=0)
	{
		if (IsEmpty(i))
		{
			std::cout << "Stack is empty" << std::endl;
			throw std::exception();
		}
		else
		{
			if (i == 0)
			{
				return this->base[top[0]];
			}
			else if(i==1)
			{
				return this->base[top[1]];
			}
		}
	}

	bool Push(T e,int i=0)

	{
		if (IsFull())
		{
			return false;
		}
		else
		{
			if (i == 0)
			{
				this->top[0]++;
				
				this->base[top[0]] = e;
			}
			else
			{
				this->top[1]--;

				this->base[top[1]] = e;
			}
		}
	}

	T Pop(int i=0)
	{
		if (IsEmpty(i))
		{
			std::cout << "Stack is empty" << std::endl;
			throw std::exception();
		}
		else
		{
			T p = GetTop(i);
			
			if (i == 0)
			{
				this->top[0]--;
			}
			else if(i==1)
			{
				this->top[1]++;
			}

			return p;
		}

	}
	template<class K>
	friend std::ostream& operator<<(std::ostream& out, const Share_Stack<K>& other);
};


template<class K>
std::ostream& operator<<(std::ostream& out, const Share_Stack<K>& other)
{
	if (other.IsEmpty())
	{
		out << "Stack is empty" << std::endl;
		return out;
	}
	if (other.IsEmpty(0))
	{
		out << "Stack_0 is empty" << std::endl;
	}
	else
	{
		out << "Stack_0:" << std::endl;
		for (int i = other.top[0]; i > 0; i--)
			out << other.base[i] << " ";
		out << other.base[0];
	}

	if (other.IsEmpty(1))
	{
		out << "Stack_1 is empty" << std::endl;
	}
	else
	{
		out << "Stack_1:" << std::endl;
		for (int i = other.top[1]; i<other.capcity-1; i++)
			out << other.base[i] << " ";
		out << other.base[other.capcity-1];
	}
}