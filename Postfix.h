#pragma once
#include"Stack_Seq.h"
#include<climits>
#include<functional>


class Postfix//后缀表达式
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


	bool is_correct(std::string expression)//简略判断表达式是否正确
	{
		Stack_Seq<char> backet_left(expression.size());//存放左括号

		int num_size = 0;
		int operator_size = 0;//操作数和运算符的数量
		bool prior_num = false;
		bool prior_oper = false;
		bool prior_backet_left = false;//前面字符的标识
		bool prior_backet_right = false;
		for (int i = 0; i < expression.size(); i++)
		{
			if (isdigit(expression[i])&& !prior_num)//为数字并且不连续
			{
				prior_num = true;
			    prior_oper = false;
				prior_backet_left = false;
				prior_backet_right = false;

				num_size++;
			}
			else if(expression[i]=='('&& !prior_backet_right&& !prior_num)//为左括号压入栈并且前面的符号不可以为右括号和操作数
			{
				backet_left.Push(expression[i]);
				prior_num = false;
				prior_oper = false;
				prior_backet_left =true ;
				prior_backet_right = false;
			}
			else if (expression[i] == ')')//为右括号判断
			{
				if (backet_left.IsEmpty())return false;//无匹配的左括号
				else backet_left.Pop();//弹出匹配的左括号
				prior_num = false;
				prior_oper = false;
				prior_backet_left = false;
				prior_backet_right = true;
			}
			else if (precedence(expression[i])&& !prior_oper&& !prior_backet_left)//为运算符并且前面的符号不可以为左括号和运算符
			{
				prior_num = false;
				prior_oper = true;
				prior_backet_left = false;
				prior_backet_right = false;

				operator_size++;
			}
			else//又非法的连续两字符（如两个操作数，两个运算符，左括号加运算符，右括号加左括号
			{
				return false;
			}
		}
		//循环后判断
		if (!backet_left.IsEmpty() || num_size - operator_size != 1)return false;

		return true;

	}



	int precedence(char c)//转换优先级，默认只有加减乘除和幂运算
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


	int Transform_infix_to_postfix_and_calculate(std::string expression, Stack_Seq<std::string>& postfix)//默认表达式只有正整数(10以内并且只有'（）')
	{
		Stack_Seq<std::string> operators(expression.size());
		Stack_Seq<std::string> rpostfix(expression.size());//反序的后缀表达式
		Stack_Seq<int> calculates(expression.size());//中途计算
		for (int i = 0; i < expression.size(); i++)
		{
			if (expression[i] == ' ')
			{
				continue;//空格忽略
			}
			else if (std::isdigit(expression[i]))//如果是操作数直接压入逆后缀表达式
			{
				rpostfix.Push(std::string(1, expression[i]));
				calculates.Push((expression[i]-'0'));
			}
			else if (expression[i] == '(')
			{
				operators.Push(std::string(1, expression[i]));
			}
			else if (expression[i] == ')')//遇到')'
			{
				while (operators.GetTop() != "(")
				{
					rpostfix.Push(operators.Pop());
				}
				operators.Pop();//将括号内的运算符压入逆后缀表达式，并删除'('
			}
			else if(precedence(expression[i]))//为运算符
			{
				if (operators.IsEmpty() || operators.GetTop() == "(")
				{
					operators.Push(std::string(1, expression[i]));//为空或者有'('未匹配时将运算符压入
				}
				else
				{
					std::string prior = operators.GetTop();
					if (precedence(prior[0]) >= precedence(expression[i]))//遇到优先级小于等于栈顶运算符的运算符，出栈并压入逆后缀表达式同时将此次运算符压入
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
						operators.Push(std::string(1, expression[i]));//当前运算符优先级大于栈顶运算符
					}
				}
			}

		}

		//将运算栈所有元素移入逆后缀表达式
		while (!operators.IsEmpty())
		{
			std::string prior = operators.GetTop();
			rpostfix.Push(operators.Pop());

			int right, left;
			left = calculates.Pop();
			right = calculates.Pop();
			calculates.Push(calculate(right, left, prior[0]));
		}

		//将逆后缀表达式所有元素翻转移入后缀表达式
		postfix.ClearStack();
		while (!rpostfix.IsEmpty())
		{
			postfix.Push(rpostfix.Pop());
		}

		//记录结果
		int v = calculates.Pop();
		return v;
	}

};
