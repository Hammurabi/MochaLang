#ifndef MOCHA_H
#define MOCHA_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <map>

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
	std::vector<token*> tokens;
	int precedence;

	filevector  vector;

	void print(std::string pre = "");

	std::string spacing(int i);

	void debug(int spcing = 0);

	token();
	~token();
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

//namespace MochaRuntimeEnvironment
//{
//	template<typename T> struct Buffer
//	{
//		T* mBuffer;
//		unsigned long index;
//		unsigned long size;
//
//		void allocate(unsigned long size)
//		{
//			mBuffer = malloc(sizeof(T) * size);
//			index = 0;
//			this->size = size;
//		}
//
//		void reset()
//		{
//			index = 0;
//		}
//
//		unsigned long remaining()
//		{
//			return size - index;
//		}
//
//		void push(T t)
//		{
//			mBuffer[index++] = t;
//		}
//
//		T get()
//		{
//			return mBuffer[index++];
//		}
//	};
//
//	struct Stack
//	{
//		enum { CHAR, UCHAR, SHORT, USHORT, INT, UINT, LONG, ULONG, OBJECT, POINTER, SMARTPOINTER };
//		std::vector<unsigned char> main;
//		std::vector<unsigned int>  indx;
//		std::vector<unsigned char> typs;
//		unsigned int index;
//
//		void push_char(char c)
//		{
//			main.push_back(c);
//			indx.push_back(1);
//			typs.push_back(CHAR);
//			index++;
//		}
//
//		void push_uchar(unsigned char c)
//		{
//			main.push_back(c);
//			indx.push_back(1);
//			typs.push_back(UCHAR);
//			index++;
//		}
//
//		void push_short(short c)
//		{
//			main.push_back((&c)[0]);
//			main.push_back((&c)[1]);
//			indx.push_back(2);
//			typs.push_back(UCHAR);
//			index++;
//		}
//
//		void push_ushort(unsigned short c)
//		{
//			main.push_back((&c)[0]);
//			main.push_back((&c)[1]);
//			indx.push_back(2);
//			typs.push_back(UCHAR);
//			index++;
//		}
//
//		void push_int(int c)
//		{
//			main.push_back((&c)[0]);
//			main.push_back((&c)[1]);
//			main.push_back((&c)[2]);
//			main.push_back((&c)[3]);
//			indx.push_back(4);
//			typs.push_back(UCHAR);
//			index++;
//		}
//
//		void push_uint(unsigned int c)
//		{
//			main.push_back((&c)[0]);
//			main.push_back((&c)[1]);
//			main.push_back((&c)[2]);
//			main.push_back((&c)[3]);
//			indx.push_back(4);
//			typs.push_back(UCHAR);
//			index++;
//		}
//
//		void push(long c)
//		{
//			main.push_back((&c)[0]);
//			main.push_back((&c)[1]);
//			main.push_back((&c)[2]);
//			main.push_back((&c)[3]);
//			main.push_back((&c)[4]);
//			main.push_back((&c)[5]);
//			main.push_back((&c)[6]);
//			main.push_back((&c)[7]);
//			indx.push_back(8);
//			typs.push_back(UCHAR);
//			index++;
//		}
//
//		void push(unsigned long c)
//		{
//			main.push_back((&c)[0]);
//			main.push_back((&c)[1]);
//			main.push_back((&c)[2]);
//			main.push_back((&c)[3]);
//			main.push_back((&c)[4]);
//			main.push_back((&c)[5]);
//			main.push_back((&c)[6]);
//			main.push_back((&c)[7]);
//			indx.push_back(8);
//			typs.push_back(UCHAR);
//			index++;
//		}
//	};
//
//	struct alu
//	{
//		void add_d(Stack& stack)
//		{
//		}
//	};
//
//	void addition(Stack& stack)
//	{
//	}
//
//	void multiply(Stack& stack)
//	{
//	}
//
//	void run(Buffer<unsigned short> buffer)
//	{
//		Stack stack;
//
//		while (buffer.remaining() > 0)
//		{
//			unsigned short bytecode_i = buffer.get();
//
//			switch (bytecode_i)
//			{
//			case ADD: addition(stack);
//			case SUB: addition(stack);
//			case DIV: addition(stack);
//			case MUL: multiply(stack);
//			case MOD: addition(stack);
//
//			default:
//				break;
//			}
//		}
//	}
//}

#define token_stack std::vector<token*>
#define remaining_ (tokens.size() - vector_index)
#define previewP   (vector_index > 0 ? vector_index - 1 : 0)
#define previewN   (vector_index < (tokens.size() - 1) ? vector_index + 1 : tokens.size() - 1)
#define Token(x) token* x = new token()

class Parser
{
public:
	bool parseBody(token_stack*tns, token_stack*tokenout, int&vector_index);
	bool parseAssertion(token_stack*tns, token_stack*tokenout, int&vector_index);
	//bool parseParenthesis(token_stack*tns, token_stack*tokenout, int&vector_index);
	//bool parseBraces(token_stack*tns, token_stack*tokenout, int&vector_index);
	//bool parseClass(token_stack*tns, token_stack*tokenout, int&vector_index);
	//bool parseMathOperator(token_stack*tns, token_stack*tokenout, int&vector_index);
	//bool parseBoolOperator(token_stack*tns, token_stack*tokenout, int&vector_index);

	bool parse(token_stack* tokns, token_stack* tokenout, int& vector_index);
	token_stack parse(token_stack& tokens);
};

#undef token_stack

class MochaLexer
{
public:
#define checkIndex(x, y) ((x >= y) ? 0 : x ++)
#define checkIndex1(x, y) ((x >= y) ? 0 : x)
#define checkIndex0(x) ((x <= 0) ? 0 : x - 1)

	std::map<std::string, std::string>				specials;
	std::vector<std::string>						keywords;
	std::map<std::string, std::string>				types;
	std::map<std::string, int>						precedence;

	bool hasNext(const std::string string, int index);

	char getNext(const std::string string, int index);

	bool isSpecial(const std::string str, std::vector<token*>& tokens, const int line, const int offset, const int spaces);

	bool isKeyword(const std::string str, std::vector<token*>& tokens);

	std::string typeof(std::string& str);

	std::string chartypeof(std::string& c);

	int getprecedence(std::string& c);

	void loop(std::vector<token*>& tokens, std::string& program, std::string& builder, int& i, int& offset, int& spaces, int& line, bool& countspaces, bool& isIdentifier);

	std::vector<token*> lex(std::string program, std::map<std::string, std::string> lexmap);

	void compile(std::string program);

	std::string loadText(std::string location);

	std::string loadSpecials(std::string location);

	std::string loadKeywords(std::string location);

	std::string loadPrecedence(std::string location);

	std::string loadncheck(std::string& s, std::ifstream& f);
};

#endif !MOCHA_H