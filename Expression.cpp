#include "Expression.h"
#include <exception>
#include <iomanip>
#include <iostream>
#include <stack>
#include <math.h>


#define pi 3.14159265358979323846
#define e 2.71828182845904523536
using namespace std;

int pos;
// 1 - степень
// 2 - деление
// 3 - умножение
// 4 - сложение
// 5 - вычитание
// 6 - cos
// 7 - sin
// 8 - tg
// 9 - ctg
// 10 - ln
// 11 - lg
// 12 - sqrt
//13 - abs

//error code 0: empty list
Expression::Expression()
{
	this->head = nullptr;
	this->tail = nullptr;
}

Expression::~Expression()
{
}

void Expression::push_back(Part* newPart)
{
	if (head == nullptr)
		head = newPart;
	else
	{
		tail->next = newPart;
		newPart->previous = tail;
	}
	tail = newPart;
}

void Expression::push_front(Part* newPart)
{
	if (tail == nullptr)
		tail = newPart;
	else
	{
		head->previous = newPart;
		newPart->next = head;
	}
	head = newPart;
}

void Expression::pop_back()
{
	if (head!=nullptr )
		if (head != tail)
		{
			Part *new_tail;
			new_tail = tail->previous;
			tail->next = nullptr;
			tail->previous = nullptr;
			delete tail;
			new_tail->next = nullptr;
			tail = new_tail;
		}
		else
		{
			delete tail;
			head = nullptr;
			tail = nullptr;
		}
}

void Expression::to_prefixForm()
{
	Expression* inPrefix = new Expression;
	Part* Elem = tail;
	while (Elem!=nullptr)
	{
		if (Elem->priority != 6)
		{
	
			if (!stack.empty())
				while (!stack.empty() && stack.top()->priority < Elem->priority && Elem->priority!=4 &&Elem->priority!=5)
				{
					inPrefix->push_front(stack.top());
					stack.pop();
				}
			stack.push(Elem);
			if (Elem->priority==4)
			{
				while (stack.top()->priority != 5)
				{
					if (stack.top()->priority != 4 && stack.top()->priority != 5)
						inPrefix->push_front(stack.top());
					stack.pop();
				}
				stack.pop();
			}
		}
		else
		{
			while (!stack.empty())
			{
				if (stack.top()->priority != 4)
					inPrefix->push_front(stack.top());
				stack.pop();
			}
		}
		Elem = Elem->previous;
	}

	//удоли

	head = inPrefix->head; 
	tail = inPrefix->tail;
	head->previous = nullptr; 
	tail->next = nullptr;
}

double Expression::result() 
{
	try
		{
		if (!stack.empty())
			while (!stack.empty())
				stack.pop();

		Part* current = tail;
		head->previous = nullptr;
		while (current != nullptr)
		{
			if (current->operation_code > 5)
			{
				Part* first = stack.top();
				stack.pop();
				Part* newPart = new Part(operation_result(current, first, nullptr));
				stack.push(newPart);
			}
			if (current->operation_code < 6 && current->operation_code != 0)
			{
				Part* first = stack.top();
				stack.pop();
				Part* second = stack.top();
				stack.pop();
				Part* newPart = new Part(operation_result(current, first, second));
				stack.push(newPart);
			}
			if (current->operation_code == 0)
				stack.push(current);
			current = current->previous;
		}
		return stack.top()->data;

		}
	catch (int error)
		{
		switch (error)
		{
			case 4: cout<<"\nВ выражении присутствует деление на ноль\n"; break;
			case 5: cout<<"\nВ выражении присутствует логарифм отицательного числа"; break;
			case 6: cout << "\nВ выражении присутствует квадратный корень отрицательного числа"; break;
		}
		throw 0;
		}
			
				
}

double Expression::operation_result(Part* operation, Part* first, Part* second)
{
	switch (operation->operation_code)
	{
	case 1: return (pow(first->data, second->data)); // 1 - степень
	case 2: 
		if(second->data!=0)
			return (first->data / second->data); // 2 - деление
		else throw 4;
	case 3: return (first->data * second->data); // 3 - умножение
	case 4: return (first->data + second->data); // 4 - сложение
	case 5: return (first->data - second->data); // 5 - вычитание
	case 6: return (cos(first->data)); // 6 - cos
	case 7: return (sin(first->data)); // 7 - sin
	case 8: return (tan(first->data)); // 8 - tg
	case 9: return (1 / tan(first->data)); // 9 - ctg
	case 10:  // 10 - ln
		if (first->data > 0)
			return (log(first->data)); // 2 - деление
		else throw 5;
	case 11:  // 11 - lg
		if (first->data > 0)
			return (log10(first->data)); // 2 - деление
		else throw 5;
	case 12: // 12 - sqrt
		if (first->data >= 0)
			return (sqrt(first->data)); // 2 - деление
		else throw 6;
	case 13: return (abs(first->data));
	}
}

void Expression::print_to_console() 
{
	Part* current_elem = head;
	while (current_elem != nullptr)
	{
		if (current_elem->operation_code > 0)
			switch (current_elem->operation_code)
			{
			case 1: std::cout << "^"; break; // 1 - степень
			case 2: std::cout << "/"; break; // 2 - деление
			case 3: std::cout << "*"; break; // 3 - умножение
			case 4: std::cout << "+"; break; // 4 - сложение
			case 5: std::cout << "-"; break; // 5 - вычитание
			case 6: std::cout << "cos"; break; // 6 - cos
			case 7: std::cout << "sin"; break; // 7 - sin
			case 8: std::cout << "tg"; break; // 8 - tg
			case 9: std::cout << "ctg"; break; // 9 - ctg
			case 10: std::cout << "ln"; break; // 10 - ln
			case 11: std::cout << "log"; break; // 11 - lg
			case 12: std::cout << "sqrt"; break; // 12 - sqrt
			case 13: std::cout << "abs"; break;
			}
		else if (current_elem->data == e)
			std::cout << "e";
		else if (current_elem->data == pi)
			std::cout << "pi";
		else
			std::cout << current_elem->data;
		std::cout << " ";
		current_elem = current_elem->next;
	}
	if (head == nullptr)
		std::cout << "Empty input";
}


bool Expression::isEmpty()
{
	if (head == nullptr)
		return true;
	return false;
}

/*****************************************************************************/
/*******************************ВВОД******************************************/
/*****************************************************************************/

void Expression::check_and_input(char* input)
{
	char* expression = new char[500];
	size_t index = 0;
	for (size_t i = 0; input[i] != '\0'; i++)
	{
		if (input[i] != ' ')
		{
			expression[index] = input[i];
			index++;
		}
	}
	pos = 0;
	expression[index] = '\0';
	system("cls");
	cout << "Выражение без пробелов:\n";
	for (size_t i = 0; expression[i] != '\0'; i++)
	{
		
		cout<<	expression[i];
	
	}
	cout << endl;
	try
	{
		read_expression(expression);
		
	}
	catch (int error)
	{
		for (size_t i = pos; i > 0; i--)
			cout << " ";
		cout << '^';
		switch (error)
		{
		case 2: cout << "\nНет открывающей скобки"; break;
		case 3: cout << "\nНет закрывающей скобки"; break;
		case 1: cout << "\nНекорректный символ"; break;
		}
		throw 0;
	}
	
	Part* End = new Part;
	End->priority = 6;
	push_front(End);

}

int Expression::read_expression(char* input) 
{
	read_beg(input);
	read_cont(input);
	return pos;
}

int Expression::read_beg(char * input)
{
	Part* newElem1 = new Part();
	Part* newElem2 = new Part();
	newElem1->priority = 4;
	newElem2->priority = 5;

	switch (input[pos])
	{
	case '(':
		pos+=1;
		push_back(newElem1);
		read_expression(input);
		if (input[pos] == ')')
		{
			pos += 1;
			push_back(newElem2);
		}
		else
			throw 3; //закрывающая скобка отсутствует
		break;


	case 'l': case 's': case 't': case 'c': case 'a':
		read_unar(input);
		if (input[pos] != '(')
			throw 2; //нет открывающей скобки
		else pos+=1;

		push_back(newElem1);
		read_expression(input);

		if (input[pos] == ')')
		{
			pos += 1;
			push_back(newElem2);
		}
		else
			throw 3; //закрывающая скобка отсутствует
		break;


	case'-': case'1': case'2': case'3': case'4': case'5': case'6': case'7': case'8':
	case'9': case'0': case'e': case'p':
		read_num(input);
		break;
	case '\0': throw 0;
	default: throw 1; // недопустимый символ
	}
	return pos;
}

int Expression::read_cont(char * input)
{
	switch (input[pos])
	{
	case'+': case'-': case'/': case'^': case'*':
		read_binar(input);
		read_expression(input);
		break;
	case '\0': case ')': break;
	default: throw 1;
	}
	return pos;
}

int Expression::read_binar(char * input)
{
	Part* newElem = new Part();
	switch (input[pos])
	{
	case '^': 
		newElem->operation_code=1;
		newElem->priority = 1;
		push_back(newElem);
		pos++;
		break;
	case '/':
		newElem->operation_code = 2;
		newElem->priority = 2;
		push_back(newElem);
		pos++;
		break; 
	case '*':
		newElem->operation_code = 3;
		newElem->priority = 2;
		push_back(newElem);
			pos++;
			break; 
	case '+':
		newElem->operation_code = 4;
		newElem->priority = 3;
		push_back(newElem);
		pos++;
		break;
	case '-':
		newElem->operation_code = 5;
		newElem->priority = 3;
		push_back(newElem);
		pos+=1;
		break;
	}
	return pos;
}

int Expression::read_unar(char * input)
{
	Part* newElem1 = new Part();
	switch (input[pos])
	{
	case 'l':
		pos+=1;
		if (input[pos] == 'n')
		{
			pos+=1;
			newElem1->operation_code = 10;
			push_back(newElem1);
			break;
		}
		else if (input[pos] == 'o')
		{
			pos+=1;
			if (input[pos] == 'g')
			{
				pos+=1;
				newElem1->operation_code = 11;
				push_back(newElem1);
				break;
			}
			else throw 1;
		}
		else throw 1;
	case 'c':
		pos++;
		if (input[pos] == 'o')
		{
			pos+=1;
			if (input[pos] == 's') 
			{
				pos+=1;
				newElem1->operation_code = 6;
				push_back(newElem1);
				break;
			}
			else throw 1;
		}
		else if (input[pos] == 't')
		{
			pos+=1;
			if (input[pos] == 'g')
			{
				pos+=1;
				newElem1->operation_code = 9;
				push_back(newElem1);
				break;
			}
			else throw 1;
		}
		else throw 1;
	case 't': 
		pos++;
		if (input[pos] == 'g')
		{
			pos+=1;
			newElem1->operation_code = 8;
			push_back(newElem1);
			break;
		}
		else throw 1;

	case 'a':
		pos++;
		if (input[pos] == 'b')
		{
			pos += 1;
			if (input[pos] == 's')
			{
				pos += 1;
				newElem1->operation_code = 13;
				push_back(newElem1);
				break;
			}
			else throw 1;
		}
		else throw 1;

	case 's':
		pos+=1;
		if (input[pos] == 'q')
		{
			pos+=1;
			if (input[pos] == 'r')
			{
				pos += 1;
				if (input[pos] == 't')
				{
					pos++;
					newElem1->operation_code = 12;
					push_back(newElem1);
					break;
				}
			}
			else throw 1;
		}
		else if (input[pos] == 'i')
		{
			pos++;
			if (input[pos] == 'n')
			{
				pos += 1;
				newElem1->operation_code = 7;
				push_back(newElem1);
				break;
			}
			else throw 1;

		}
		else throw 1;

	}
	return pos;
}

int Expression::read_num(char * input)
{
	Part* newElem = new Part();
	char* buf = new char[100];
	size_t index = 0;
	switch (input[pos])
	{
	case'-': 
		if (input[pos + 1] == 'e')
		{
			pos += 2;
			newElem->data = -e;
			push_back(newElem);
			break;
		}
		if (input[pos + 1] == 'p')
		 if(input[pos+2]=='i')
		 {
			pos += 3;
			newElem->data = -pi;
			push_back(newElem);
			break;
		}
		else throw 1;
		else
		{
			buf[index] = '-'; index++;
			pos+=1;
		}
	case'1': case'2': case'3': case'4': case'5': 
	case'6': case'7': case'8': case'9': 

		
		read_digit(input, buf, index);
		if (input[pos] == '.')
		{
			buf[index] = ','; index++;
			pos += 1;
			read_digit(input, buf, index);
		}		

		buf[index] = '\0';
		newElem->data = atof(buf);
		push_back(newElem);
		break;
	
	case'0': 
		
		buf[index] = '0';
		index++; pos+=1;
		if (input[pos] == '.')
		{
			buf[index] = ','; index++;
			pos+=1;
			read_digit(input, buf, index);
		}
		buf[index] = '\0';
		newElem->data = atof(buf);
		push_back(newElem);
		break;

	case'e': 
		pos+=1;
		newElem->data = e;
		push_back(newElem);
		break;
	case'p':
		if (input[pos + 1] == 'i')
		{
			pos += 2;
			newElem->data = pi;
			push_back(newElem);
			break;
		}
		else throw 1;
	}
	return pos;
}

int Expression::read_digit(char * input, char * buf, size_t &index)
{
	while (input[pos] >= '0' && input[pos] <= '9')
	{
		buf[index] = input[pos];
		pos+=1;
		index++;
	}
	return pos;
}
