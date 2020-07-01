#include <iostream>
#include <stack>
#include <math.h>       /* pow */

using namespace std;


int prioridade(char c, char t)
{
	int pc = 0;
	int pt = 0;

	if (c == '^')
		pc = 4;
	else if (c == '*' || c == '/')
		pc = 2;
	else if (c == '+' || c == '-')
		pc = 1;
	else if (c == '(')
		pc = 4;

	if (t == '^')
		pt = 3;
	else if (t == '*' || t == '/')
		pt = 2;
	else if (t == '+' || t == '-')
		pt = 1;
	else if (t == '(')
		pt = 0;

	return (pc > pt);
}



string intopos(string expr)
{
	string saida;
	stack<char> p;
	int i = 0;
	int j = -1;
	char c, t;

	p.push('(');

	do {
		c = expr[i];
		i++;
		if (c >= '1' && c <= '9')
		{
			saida += c;
			printf("%c", c);
		}
		else if (c == '(')
		{
			p.push('(');
		}
		else if (c == ')' || c == '\0')
		{
			do
			{
				t = p.top();
				p.pop();

				if (t != '(')
				{
					saida += t;
					printf("%c", t);
				}
			} while (t != '(');
		}
		else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
		{
			while (1)
			{
				t = p.top();
				p.pop();

				if (prioridade(c, t))
				{
					p.push(t);
					p.push(c);
					break;
				}
				else
				{
					saida += t;
					printf("%c", t);
				}
			}
		}
	} while (c != '\0');

	printf("\n");

	return saida;
}

int main()
{
    // (5 * (((9 + 8) * (4 * 6)) + 7))^2
	string expr;
	cout << "Entre com a expressão: ";
	getline(cin, expr);

	string saida = intopos(expr); //5 9 8 + 4 6 * * 7 + *

	stack<int> p;
	for (size_t i = 0; i < saida.length(); i++)
	{
		char c = saida[i];

		if (c >= '1' && c <= '9')
			p.push(c - 48); // 0 representa o 48 em ASCII
		else
		{
			int a = p.top();
			p.pop();
			int b = p.top();
			p.pop();

			if (c == '+')
				p.push(a + b);
			else if (c == '-')
				p.push(a - b);
			else if (c == '*')
				p.push(a * b);
			else if (c == '/')
				p.push(a / b);
			else if (c == '^')
				p.push(pow(b, a));
		}
	}

	cout << expr + " = " + to_string(p.top()) << endl;
}
