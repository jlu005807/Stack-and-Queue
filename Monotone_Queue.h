#pragma once
#include"Queue_Seq.h"
#include<vector>

//��������,Ĭ��Ϊ��������
//��������ָ����Ԫ�صġ����ɡ�������������ݼ�����
//�����С�ָ����Ԫ��ֻ�ܴӶ�ͷ�Ͷ�β���в�����

template<typename T>
class Monotone_Queue: public Queue_Seq<T>
{
	//��������⣬��������һ�£���������ֻ��ʵ����Ӳ������ػ����EnQueue
	bool EnQueue(T e)
	{
		if (QueueFull())
		{
			std::cout << "Queue is full" << std::endl;
			throw std::exception();
			return false;

		}

		//�ݴ����Ԫ��
		std::vector<T> temp;

		while (!this->QueueEmpty())
		{
			temp.push_back(this->DeQueue())
		}

		//���ڶ���Ϊ�գ����յ������
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
				rear = (rear + capcity + 1) % capcity;//ȡģѭ��
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
				rear = (rear + capcity + 1) % capcity;//ȡģѭ��
				size++;
				flag = true;
			}
		}
		
	}
};
