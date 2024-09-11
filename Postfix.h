#pragma once
#include"Stack_Seq.h"
#include<climits>
#include<functional>


class Postfix//��׺���ʽ
{
public:
	int result;
	Stack_Seq<std::string> postfix;
	std::string expression;


	Postfix():postfix(50),result(INT16_MIN),expression()
	{

	}

	Postfix(std::string expression):postfix(expression.size()), result(INT16_MIN),expression(expression)
	{
		if (!is_correct(expression))
		{
			std::cout << "Invalid expression" << std::endl;
			throw std::exception();
		}
		else
		{
			result = Transform_infix_to_postfix_and_calculate(this->expression, postfix);
		}
	}


	bool is_correct(std::string expression)//�����жϱ��ʽ�Ƿ���ȷ
	{
		Stack_Seq<char> backet_left(expression.size());//���������

		int num_size = 0;
		int operator_size = 0;//�������������������
		bool prior_num = false;
		bool prior_oper = false;
		bool prior_backet_left = false;//ǰ���ַ��ı�ʶ
		bool prior_backet_right = false;
		for (int i = 0; i < expression.size(); i++)
		{
			if (isdigit(expression[i])&& !prior_num)//Ϊ���ֲ��Ҳ�����
			{
				prior_num = true;
			    prior_oper = false;
				prior_backet_left = false;
				prior_backet_right = false;

				num_size++;
			}
			else if(expression[i]=='('&& !prior_backet_right&& !prior_num)//Ϊ������ѹ��ջ����ǰ��ķ��Ų�����Ϊ�����źͲ�����
			{
				backet_left.Push(expression[i]);
				prior_num = false;
				prior_oper = false;
				prior_backet_left =true ;
				prior_backet_right = false;
			}
			else if (expression[i] == ')')//Ϊ�������ж�
			{
				if (backet_left.IsEmpty())return false;//��ƥ���������
				else backet_left.Pop();//����ƥ���������
				prior_num = false;
				prior_oper = false;
				prior_backet_left = false;
				prior_backet_right = true;
			}
			else if (precedence(expression[i])&& !prior_oper&& !prior_backet_left)//Ϊ���������ǰ��ķ��Ų�����Ϊ�����ź������
			{
				prior_num = false;
				prior_oper = true;
				prior_backet_left = false;
				prior_backet_right = false;

				operator_size++;
			}
			else//�ַǷ����������ַ���������������������������������ż�������������ż�������
			{
				return false;
			}
		}
		//ѭ�����ж�
		if (!backet_left.IsEmpty() || num_size - operator_size != 1)return false;

		return true;

	}



	int precedence(char c)//ת�����ȼ���Ĭ��ֻ�мӼ��˳���������
	{
		if (c == '+' || c == '-')return 1;
		else if (c == '/' || c == '*' || c == '%')return 2;
		else if (c == '^')return 3;
		else return int(false);
	}

	int calculate(int right, int left, char oper)
	{
		switch (oper)
		{
		case '+':
			return right + left;
		case '-':
			return right - left;
		case '*':
			return right * left;
		case '/':
			return right / left;
		case '%':
			return right % left;
		case '^':
			return pow(right, left);
		default:
			break;
		}
	}


	int Transform_infix_to_postfix_and_calculate(std::string expression, Stack_Seq<std::string>& postfix)//Ĭ�ϱ��ʽֻ��������(10���ڲ���ֻ��'����')
	{
		Stack_Seq<std::string> operators(expression.size());
		Stack_Seq<std::string> rpostfix(expression.size());//����ĺ�׺���ʽ
		Stack_Seq<int> calculates(expression.size());//��;����
		for (int i = 0; i < expression.size(); i++)
		{
			if (expression[i] == ' ')
			{
				continue;//�ո����
			}
			else if (std::isdigit(expression[i]))//����ǲ�����ֱ��ѹ�����׺���ʽ
			{
				rpostfix.Push(std::string(1, expression[i]));
				calculates.Push((expression[i]-'0'));
			}
			else if (expression[i] == '(')
			{
				operators.Push(std::string(1, expression[i]));
			}
			else if (expression[i] == ')')//����')'
			{
				while (operators.GetTop() != "(")
				{
					rpostfix.Push(operators.Pop());
				}
				operators.Pop();//�������ڵ������ѹ�����׺���ʽ����ɾ��'('
			}
			else if(precedence(expression[i]))//Ϊ�����
			{
				if (operators.IsEmpty() || operators.GetTop() == "(")
				{
					operators.Push(std::string(1, expression[i]));//Ϊ�ջ�����'('δƥ��ʱ�������ѹ��
				}
				else
				{
					std::string prior = operators.GetTop();
					if (precedence(prior[0]) >= precedence(expression[i]))//�������ȼ�С�ڵ���ջ������������������ջ��ѹ�����׺���ʽͬʱ���˴������ѹ��
					{
						int right, left;
						left = calculates.Pop();
						right = calculates.Pop();
						calculates.Push(calculate(right, left, prior[0]));


						rpostfix.Push(operators.Pop());
						operators.Push(std::string(1, expression[i]));
					}
					else
					{
						operators.Push(std::string(1, expression[i]));//��ǰ��������ȼ�����ջ�������
					}
				}
			}

		}

		//������ջ����Ԫ���������׺���ʽ
		while (!operators.IsEmpty())
		{
			std::string prior = operators.GetTop();
			rpostfix.Push(operators.Pop());

			int right, left;
			left = calculates.Pop();
			right = calculates.Pop();
			calculates.Push(calculate(right, left, prior[0]));
		}

		//�����׺���ʽ����Ԫ�ط�ת�����׺���ʽ
		postfix.ClearStack();
		while (!rpostfix.IsEmpty())
		{
			postfix.Push(rpostfix.Pop());
		}

		//��¼���
		int v = calculates.Pop();
		return v;
	}

};
