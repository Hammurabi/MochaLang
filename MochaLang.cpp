// MochaLang.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stack>
#include <vector>

struct filevector
{
	unsigned int line;
	unsigned int offset;
	/*
		The number of spaces before this vector
	*/
	unsigned int numspaces;
};

struct token {
	std::string name;
	std::string value;
	
	filevector  vector;
};


// char
// uchar
// short
// ushort
// int
// uint
// long
// ulong
// float
// double
// pointer

#define PUSH_CHAR 0
#define PUSH_UCHR 1
#define PUSH_SHRT 2
#define PUSH_USHT 3
#define PUSH_INTR 4
#define PUSH_UINT 5
#define PUSH_LONG 6
#define PUSH_ULNG 7
#define PUSH_UPTR 8
#define PUSH_UOBJ 9

#define POP 10
#define PRT 11

#define ADD 12
#define MUL 13
#define SUB 14
#define DIV 15
#define MOD 16

#define MRK 17
#define GTO 18

#define IF      19
#define ELSEIF  20
#define ELSE    21
#define WHILE   22

#define CAST_CHAR 23
#define CAST_UCHR 24
#define CAST_SHRT 25
#define CAST_USHT 26
#define CAST_INTR 27
#define CAST_UINT 28
#define CAST_LONG 29
#define CAST_ULNG 30
#define CAST_UPTR 31
#define CAST_UOBJ 32

#define LOAD_CHAR 33
#define LOAD_UCHR 34
#define LOAD_SHRT 35
#define LOAD_USHT 36
#define LOAD_INTR 37
#define LOAD_UINT 38
#define LOAD_LONG 39
#define LOAD_ULNG 40
#define LOAD_UPTR 41
#define LOAD_UOBJ 42

#define MOD_CHAR 43
#define MOD_UCHR 44
#define MOD_SHRT 45
#define MOD_USHT 46
#define MOD_INTR 47
#define MOD_UINT 48
#define MOD_LONG 49
#define MOD_ULNG 50
#define MOD_UPTR 51
#define MOD_UOBJ 52

//#define CLASS 256
//#define FUNCTION 258
//#define CHAR 257
//#define CHARU 257
//#define INT 257
//#define INT 257
//#define INT 257
//#define INT 257
//#define INT 257
//#define INT 257

template<typename T> struct Buffer
{
	T* mBuffer;
	unsigned long index;
	unsigned long size;

	void allocate(unsigned long size)
	{
		mBuffer = malloc(sizeof(T) * size);
		index = 0;
		this->size = size;
	}

	void reset()
	{
		index = 0;
	}

	unsigned long remaining()
	{
		return size - index;
	}

	void push(T t)
	{
		mBuffer[index++] = t;
	}

	T get()
	{
		return mBuffer[index++];
	}
};

struct Stack
{
	enum { CHAR, UCHAR, SHORT, USHORT, INT, UINT, LONG, ULONG, OBJECT, POINTER, SMARTPOINTER };
	std::vector<unsigned char> main;
	std::vector<unsigned int>  indx;
	std::vector<unsigned char> typs;
	unsigned int index;

	void push_char(char c)
	{
		main.push_back(c);
		indx.push_back(1);
		typs.push_back(CHAR);
		index++;
	}

	void push_uchar(unsigned char c)
	{
		main.push_back(c);
		indx.push_back(1);
		typs.push_back(UCHAR);
		index++;
	}

	void push_short(short c)
	{
		main.push_back((&c)[0]);
		main.push_back((&c)[1]);
		indx.push_back(2);
		typs.push_back(UCHAR);
		index++;
	}

	void push_ushort(unsigned short c)
	{
		main.push_back((&c)[0]);
		main.push_back((&c)[1]);
		indx.push_back(2);
		typs.push_back(UCHAR);
		index++;
	}

	void push_int(int c)
	{
		main.push_back((&c)[0]);
		main.push_back((&c)[1]);
		main.push_back((&c)[2]);
		main.push_back((&c)[3]);
		indx.push_back(4);
		typs.push_back(UCHAR);
		index++;
	}

	void push_uint(unsigned int c)
	{
		main.push_back((&c)[0]);
		main.push_back((&c)[1]);
		main.push_back((&c)[2]);
		main.push_back((&c)[3]);
		indx.push_back(4);
		typs.push_back(UCHAR);
		index++;
	}

	void push(long c)
	{
		main.push_back((&c)[0]);
		main.push_back((&c)[1]);
		main.push_back((&c)[2]);
		main.push_back((&c)[3]);
		main.push_back((&c)[4]);
		main.push_back((&c)[5]);
		main.push_back((&c)[6]);
		main.push_back((&c)[7]);
		indx.push_back(8);
		typs.push_back(UCHAR);
		index++;
	}

	void push(unsigned long c)
	{
		main.push_back((&c)[0]);
		main.push_back((&c)[1]);
		main.push_back((&c)[2]);
		main.push_back((&c)[3]);
		main.push_back((&c)[4]);
		main.push_back((&c)[5]);
		main.push_back((&c)[6]);
		main.push_back((&c)[7]);
		indx.push_back(8);
		typs.push_back(UCHAR);
		index++;
	}
};

struct alu
{
	void add_d(Stack& stack)
	{
	}
};

void addition(Stack& stack)
{
}

void run(Buffer<unsigned short> buffer)
{
	Stack stack;

	while (buffer.remaining() > 0)
	{
		unsigned short bytecode_i = buffer.get();

		switch (bytecode_i)
		{
		case ADD: addition(stack);
		case SUB: addition(stack);
		case DIV: addition(stack);
		case MUL: addition(stack);
		case MOD: addition(stack);

		default:
			break;
		}
	}
}

namespace MochaRuntimeEnvironment
{
}

#include <fstream>
#include <cstdlib>

#include <map>

namespace MochaOpcodeProvider
{
	char SPECIAL[] = {
		'\\',
		'.',
		'+',
		'-',
		'*',
		'/',
		'-',
	};

	bool hasNext(std::string string, int index)
	{
		return string.size() > (index + 1);
	}

	char getNext(std::string string, int index)
	{
		return string.at(index + 1);
	}

	bool isSpecial(std::string str, std::vector<token>& tokens)
	{
		if (str == "->")
		{
		}
		else if (str == "..")
		{
		}
		else if (str == "<<")
		{
		}
		else if (str == ">>")
		{
		}
		else if (str == "++")
		{
		}
		else if (str == "--")
		{
		}
		else if (str == "**")
		{
		}
		else if (str == "//")
		{
		}

		return false;
	}

	bool isKeyword(std::string str, std::vector<token>& tokens)
	{
	}

	std::string typeof(std::string str)
	{
		for (int i = 0; i < str.length(); i++) if (isalpha(str.at(i))) return "identifier";

		return "integer";
	}

	std::vector<token> lex(std::string program, std::map<std::string, std::string> lexmap)
	{
		std::vector<token> tokens;
		std::string        builder;

#define N (hasNext(program, i) ? getNext(program, i) : '\0')
#define L (hasNext(program, i) ? (getNext(program, i) + "") : "")
#define C program.at(i)

		int line = 0;
		int offset = 0;
		int spaces = 0;

		bool isIdentifier = false;
		bool isNumber = false;

		for (int i = 0; i < program.size(); i++)
		{
			if (C == '\n')
			{
				line++;
				offset = 1;
			}
			else if (C == ' ') spaces++;

			std::string n = L;

			std::string cn("" + C + n);

			if (isSpecial(cn, tokens))
			{
				i++;
				offset += 2;
			}
			else
			{
				if (isIdentifier && (C == '_' || C == '$' || isalnum(C))) builder.append(C + "");
				else if (isIdentifier)
				{
					isIdentifier = false;

					token t;
					t.name = "identifier";
					t.value = std::string(builder);
					t.vector.line = line;
					t.vector.numspaces = 0;
					t.vector.offset = spaces;
					tokens.push_back(t);
				}


				else if (!isIdentifier && (C == '_' || C == '$' || isalnum(C)))
				{
					builder.append(C + "");
					isIdentifier = true;
				}
				//else if (!isNumber && ( (!isalpha(C) && isalnum(C)) || C == '_'))
				//{
				//	builder.append(C + "");
				//	isNumber = true;
				//}
				//else if ((!isalpha(C) && isalnum(C)) && isNumber)
				//{
				//	builder.append(C + "");
				//}
				//else if (!(!isalpha(C) && isalnum(C)) && isNumber)
				//{

				//}
				else {
					token t;
					t.name = "";
					t.value = C;
					t.vector.line = line;
					t.vector.numspaces = 0;
					t.vector.offset = spaces;
					tokens.push_back(t);
				}

				offset++;
			}
		}

#undef N
#undef L
#undef C

		return tokens;
	}

	void compile(std::string program)
	{
	}

	std::string loadText(std::string location)
	{
		std::string string("");
		std::string stline("");
		std::ifstream file;

		file.open(location.c_str());
		if (!file.is_open())
			return "";

		while (!file.eof())
		{
			getline(file, stline);

			int index = stline.find("//");
			if (index == -1) index = stline.length() - 1;
			string.append(stline.substr(0, index) + '\n');
		}

		return string;
	}
}

int main()
{
	std::cout << MochaOpcodeProvider::loadText(".\\lang\\sample.ma");

	while (true) {}

	return 0;
}