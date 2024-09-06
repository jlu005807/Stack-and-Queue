#pragma once
#include<iostream>

#pragma once
#include<iostream>



template<class T>
class Stack_Node
{
public:
	T m_data;
	Stack_Node* next;
};

template<class T>
class Stack_Link
{
public:
	Stack_Node<T>* top;
	int size = 0;

public:

	Stack_Link()
	{
		InitStack();
	}

	Stack_Link(T a[], int n)
	{
		InitStack_from_array(a, n);
	}

	Stack_Link(const Stack_Link& other)
	{
		InitStack_from_Link(other);
	}

	~Stack_Link()
	{
		ClearStack();
	}

	void InitStack()
	{
		this->top=nullptr;
		this->size = 0;
	}

	void InitStack_from_array(T a[], int n)
	{
		this->size = n;

		for (int i = 0; i < this->size; i++)
		{
			Stack_Node<T>* p = new Stack_Node<T>();

			if (!p)
			{
				throw std::exception();
			}

			p->m_data = a[i];
			p->next = this->top;//头插法
			this->top = p;
		}
	}

	void InitStack_from_Link(const Stack_Link& other)
	{
		this->size = other.size;

		Stack_Node<T>* p = other.top;

		this->top = new Stack_Node<T>();
		this->top->m_data = p->m_data;
		p = p->next;


		//工作指针
		Stack_Node<T>* ptr = this->top;

		for (int i = 1; i < this->size; i++)
		{
			Stack_Node<T>* new_node = new Stack_Node<T>();
			new_node->m_data = p->m_data;
			//后插法
			ptr->next = new_node;
			ptr = new_node;
			//后移
			p = p->next;
		}
	}

	Stack_Link& operator=(const Stack_Link& other)
	{
		if (this == &other)return *this;

		if (this->size != 0)
		{
			ClearStack();
		}

		InitStack_from_Link(other);
	}


	void ClearStack()
	{
		for (int i = 0; i < this->size; i++)
		{
			Stack_Node<T>* p = this->top;
			this->top = this->top->next;
			delete p;
		}
		this->size = 0;
	}

	bool IsEmpty()const
	{
		if (this->size==0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	int StackLength()
	{
		return this->size;
	}

	T& GetTop()
	{
		return this->top->m_data;
	}

	void Push(T data)
	{
		Stack_Node<T>* p = new Stack_Node<T>();
		
		if (!p)
		{
			throw std::exception();
		}

		p->m_data = data;
		p->next = this->top;//头插法
		this->top = p;
		this->size++;//大小加一
	}

	void Pop(T* e = nullptr)
	{
		if (IsEmpty())
		{
			throw std::exception();
		}
		else
		{
			if (e != nullptr)
			{
				e = &GetTop();
			}
			//后移Top
			Stack_Node<T>* p = this->top;
			this->top = this->top->next;
			//删除
			delete p;
			this->size--;

		}
	}

	template<class K>
	friend std::ostream& operator<<(std::ostream& out, const Stack_Seq<K>& other);
};

template<class K>
std::ostream& operator<<(std::ostream& out, const Stack_Link<K>& other)
{
	if (other.size == 0)
	{
		out << "Stack is empty" << std::endl;
		return out;
	}
	else
	{

		//工作指针
		Stack_Node<K>* ptr = other.top;

		for (int i = 0; i < other.size-1; i++)
		{
			out << ptr->m_data << " ";
			ptr = ptr->next;
		}

		out << ptr->m_data << std::endl;

		return out;

	}
}