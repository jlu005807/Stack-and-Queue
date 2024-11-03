#pragma once
#include"Stack_Seq.h"
#include<vector>

//利用Stack_Seq实现单调栈
//单调栈即满足单调性的栈结构，此实现单调递增栈

template<class T>
class Monotone_Stack : public Stack_Seq<T>
{
public:
	//除了压栈外，其他操作一致，所以这里只是实现压栈操作隐藏基类的Push
	bool Push(T e)
	{
		//栈已满
		if (IsFull())
		{
			return false;
		}

		//临时存放栈内元素
		std::vector<T> temp;

		while (this->IsEmpty() && this->GetTop() > e)
		{
			temp.push_back(this->Pop());
		}

		//此时栈空或者栈顶元素已经小于e;
		this->base[top++] = e;

		//重新放回栈中
		while (!temp.empty())
		{
			T p = temp.back();
			temp.pop_back();
			
			//判断栈满？
			if (!IsFull())
			{
				this->base[top++] = p;
			}
		}


		
	}
};