#pragma once
#include <stack>

class Part
{
public:
	Part(double data = 0, int operation_code = 0)
	{
		this->data = data; // само число
		this->operation_code = operation_code; // + - / * ^
		this->priority = 0; // приоритет 
		this->next = nullptr;
		this->previous = nullptr;
	};
	//~Part();

	double data;
	size_t operation_code; 
	size_t priority;
	Part* previous;
	Part* next;

};

class Expression
{
public:
	
	Expression();
	~Expression();

	std::stack <Part*> stack;

	void push_back(Part* newPart);
	void push_front(Part* newPart);
	void pop_back();//
	void to_prefixForm();
	double result();
	double operation_result(Part * operation, Part* first, Part* second);
	
	void print_to_console();
	void clear();
	bool isEmpty();
	
	// проверка ввода и парсер
	void check_and_input(char* input);

	int read_expression(char* input);
	int read_beg(char* input);
	int read_cont(char* input);
	int read_binar(char* input);
	int read_unar(char* input);
	int read_num(char* input);
	int read_digit(char* input, char* buf, size_t &index);



	
	Part* head;
	Part* tail;
};

