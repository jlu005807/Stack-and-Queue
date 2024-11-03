#pragma once
#include"Queue_Seq.h"
#include<vector>

//单调队列,默认为单调增加
//「单调」指的是元素的「规律」——递增（或递减）。
//「队列」指的是元素只能从队头和队尾进行操作。

template<typename T>
class Monotone_Queue: public Queue_Seq<T>
{
	//除了入队外，其他操作一致，所以这里只是实现入队操作隐藏基类的EnQueue
	bool EnQueue(T e)
	{
		if (QueueFull())
		{
			std::cout << "Queue is full" << std::endl;
			throw std::exception();
			return false;

		}

		//暂存队列元素
		std::vector<T> temp;

		while (!this->QueueEmpty())
		{
			temp.push_back(this->DeQueue())
		}

		//现在队列为空，按照单调入队
		auto it = temp.begin();

		bool flag = false;

		while (it != temp.end())
		{
			if (*it < e||flag)
			{
				if (QueueFull())
				{
					std::cout << "Queue is full" << std::endl;
					throw std::exception();
					return false;

				}
				element[rear] = *it;
				rear = (rear + capcity + 1) % capcity;//取模循环
				size++;
				it++;
			}
			else
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
				flag = true;
			}
		}
		
	}
};
