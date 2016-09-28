#include <iostream>
#include <stack>
#include <string>


enum pr
{
	s1 = 0, // скобка '('
	s2 = 5, // скобка ')'
	sum = 1, // сложение
	min = 1, // вычитание
	mul = 2, // умножение
	dif = 2, // деление
	step = 4 // возведение в степень
};

int oper1(std::stack<int> &st1, std::stack<char> &st2); // если встретился символ ниже или того же приоритета
void oper2(std::stack<int> &st1, std::stack<char> &st2); // если встретилась ')'
int pri(char o); // выдает приоитет
void proverka(std::string &s); // основная функция

int main()
{
	std::string s;
	while (true)
	{
		std::cout << "write your example : " << std::endl;
		std::cin >> s;
		proverka(s);
		system("pause");
	}
	return 0;
}

int pri(char o)
{
	switch (o)
	{
	case ('+'): { return sum; break; }
	case ('-'): { return min; break; }
	case ('*'): { return mul; break; }
	case ('/'): { return dif; break; }
	case ('('): { return s1; break; }
	case (')'): { return s2; break; }
	case('^'): { return step; break; }

	default: { std::cout << " 4e za symbol?" << std::endl; return -1; }
	}
}
void proverka(std::string &s)
{
	std::stack<int> st1;
	std::stack<char> st2;
	std::string n = "";
	int p = 0;
	for (size_t i = 0; i < s.size(); ++i)
	{
		if (isdigit(s[i]))
			n += s[i];
		else
		{
			if (n.size() > 0)
			{
				st1.push(stoi(n));
				n = "";
			}
			if (s[i] == '(')
			{
				st2.push(s[i]);
				p = 0;
			}
			else
				if (s[i] == ')')
				{
					oper2(st1, st2);
					if (st2.empty())
						p = 0;
					else
						p = pri(st2.top());
				}
				else
					if (pri(s[i]) > p)
					{
						st2.push(s[i]);
						p = pri(st2.top());
					}
					else
					{
						while (pri(st2.top()) >= pri(s[i]))
						{
							oper1(st1, st2);
							if (st2.empty())
								break;
						}
						st2.push(s[i]);
					}
		}
		if (i == s.size() - 1)
		{
			if (n.size() > 0)
                st1.push(stoi(n));
			while (!st2.empty())
				oper1(st1, st2);
		}
	}
	std::cout << st1.top() << std::endl;
}



int oper1(std::stack<int> &st1, std::stack<char> &st2)
{
	int a1 = 0, a2 = 0;
	char z;
	a1 = st1.top();
	st1.pop();
	a2 = st1.top();
	st1.pop();
	z = st2.top();
	st2.pop();
	switch (z)
	{
	case ('+'): { st1.push(a1 + a2); return sum; break; }
	case ('-'): { st1.push(a2 - a1); return min; break; }
	case ('*'): { st1.push(a1 * a2); return mul; break; }
	case ('/'): { st1.push(a2 / a1); return dif; break; }
	case ('^'): { st1.push(pow(a2,a1)); return step; break; }
	case ('('): { st2.push('('); return s1; break; }
	default: return -1;
	}
}
void oper2(std::stack<int> &st1, std::stack<char> &st2)
{
	while (st2.top() != '(')
		oper1(st1, st2);
	st2.pop();
}