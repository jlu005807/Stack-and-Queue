#pragma once
#include"Stack_Seq.h"
#include<vector>

//����Stack_Seqʵ�ֵ���ջ
//����ջ�����㵥���Ե�ջ�ṹ����ʵ�ֵ�������ջ

template<class T>
class Monotone_Stack : public Stack_Seq<T>
{
public:
	//����ѹջ�⣬��������һ�£���������ֻ��ʵ��ѹջ�������ػ����Push
	bool Push(T e)
	{
		//ջ����
		if (IsFull())
		{
			return false;
		}

		//��ʱ���ջ��Ԫ��
		std::vector<T> temp;

		while (this->IsEmpty() && this->GetTop() > e)
		{
			temp.push_back(this->Pop());
		}

		//��ʱջ�ջ���ջ��Ԫ���Ѿ�С��e;
		this->base[top++] = e;

		//���·Ż�ջ��
		while (!temp.empty())
		{
			T p = temp.back();
			temp.pop_back();
			
			//�ж�ջ����
			if (!IsFull())
			{
				this->base[top++] = p;
			}
		}


		
	}
};