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

namespace {
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

		~token();
	};
}


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
Token(empty);

class Parser
{
public:
	bool parseBody(token_stack*tns, token_stack*tokenout, int&vector_index);
	//bool parseParenthesis(token_stack*tns, token_stack*tokenout, int&vector_index);
	//bool parseBraces(token_stack*tns, token_stack*tokenout, int&vector_index);
	//bool parseClass(token_stack*tns, token_stack*tokenout, int&vector_index);
	//bool parseMathOperator(token_stack*tns, token_stack*tokenout, int&vector_index);
	//bool parseBoolOperator(token_stack*tns, token_stack*tokenout, int&vector_index);

	bool parse(token_stack* tokns, token_stack* tokenout, int& vector_index);
	token_stack parse(token_stack& tokens);
};

#undef token_stack

class MochaOpcodeProvider
{
public:
#define checkIndex(x, y) ((x >= y) ? 0 : x ++)
#define checkIndex1(x, y) ((x >= y) ? 0 : x)
#define checkIndex0(x) ((x <= 0) ? 0 : x - 1)
	//struct TokenStream
	//{
	//	std::vector<token> tokens;
	//	unsigned int index = 0;

	//	TokenStream(std::vector<token> ts) : tokens(ts) {}

	//	token& next()
	//	{
	//		if (tokens.size() <= index) return tokens[tokens.size() - 1];
	//		else return tokens[index++];
	//	}

	//	token& previewLast()
	//	{
	//		if ((index - 1) <= 0) return tokens[0];
	//		else if ((index - 1) >= tokens.size()) return tokens[tokens.size() - 1];
	//		return tokens[index - 1];
	//	}

	//	token& previewNext()
	//	{
	//		if (tokens.size() <= index) return tokens[tokens.size() - 1];
	//		else return tokens[index];
	//	}

	//	bool hasPrevious()
	//	{
	//		return index > 0;
	//	}

	//	bool hasNext()
	//	{
	//		return index < tokens.size();
	//	}

	//	unsigned int remaining()
	//	{
	//		return tokens.size() - index;
	//	}
	//};
	
	//struct GRAMMAR_RULE
	//{
	//	std::string name;
	//	std::vector<std::string> rules;

	//	GRAMMAR_RULE(std::string n, std::vector<std::string> r) : name(n), rules(r) {}

	//	//void parse(TokenStream& stream, std::vector<token>& tokens)
	//	//{
	//	//	using namespace std;
	//	//	int i = stream.index;

	//	//	int amt_spaces = 0;
	//	//	token* lookoutfor = 0;

	//	//	//int last____space = stream.previewLast().vector.numspaces;
	//	//	//int current_space = stream.next().vector.numspaces; 
	//	//	


	//	//	//if (rules[0] == "[WHITESPACE(>)]" && (current_space > last____space))
	//	//	//{
	//	//	//	tokens.push_back(token(stream.previewLast()));

	//	//	//	while (stream.next().vector.numspaces > last____space)
	//	//	//	{
	//	//	//		tokens.push_back(token(stream.previewLast()));
	//	//	//	}
	//	//	//}
	//	//	//else stream.index = i;
	//	//}

	//	//bool checkMatch(token& t, TokenStream& stream)
	//	//{
	//	//	using namespace std;
	//	//	int i = stream.index;

	//	//	int amt_spaces = 0;
	//	//	token* lookoutfor = 0;

	//	//	if (rules.size() > stream.remaining()) return false;

	//	//	//check if rule is special
	//	//	if ((rules[0] == "[WHITESPACE(>)]" && stream.hasPrevious()))
	//	//	{
	//	//		if (t.vector.numspaces > stream.previewLast().vector.numspaces)
	//	//		{
	//	//			t.print();
	//	//			stream.previewLast().print();
	//	//			return true;
	//	//		}
	//	//	} //otherwise check rulename matches token name
	//	//	
	//	//	if (rules[0] == t.name)
	//	//	{
	//	//	}

	//	//	stream.index = i;

	//	//	//for (int i = 0; i < rules.size(); i++)
	//	//	//{
	//	//	//	token t = stream.next();
	//	//	//	token last = stream.previewLast();

	//	//	//	//SPECIAL TOKEN ACCESS
	//	//	//	if (rules[i].at(0) == '*')
	//	//	//	{
	//	//	//		lookoutfor = &stream.previewNext();
	//	//	//	} else if (rules[i].at(0) == '[')
	//	//	//	{
	//	//	//		if (rules[i] == "[WHITESPACE(>)]")
	//	//	//		{
	//	//	//			if (!(t.vector.numspaces > last.vector.numspaces)) return false;
	//	//	//		}else if (rules[i] == "[WHITESPACE(<)]")
	//	//	//		{
	//	//	//			if (!(t.vector.numspaces < last.vector.numspaces)) return false;
	//	//	//		} else if (rules[i] == "[WHITESPACE(>=)]")
	//	//	//		{
	//	//	//			if (!(t.vector.numspaces >= last.vector.numspaces)) return false;
	//	//	//		}
	//	//	//		else if (rules[i] == "[WHITESPACE(<=)]")
	//	//	//		{
	//	//	//			if (!(t.vector.numspaces <= last.vector.numspaces)) return false;
	//	//	//		}
	//	//	//		else if (rules[i] == "[endl]")
	//	//	//		{
	//	//	//			//This part will never be used hopefully.
	//	//	//		}
	//	//	//	}
	//	//	//	else if (t.name != rules[i])
	//	//	//	{
	//	//	//		if (lookoutfor)
	//	//	//		{

	//	//	//		}
	//	//	//		else
	//	//	//		{
	//	//	//			stream.index = i;
	//	//	//			return false;
	//	//	//		}
	//	//	//	}
	//	//	//}

	//	//	return false;
	//	//}
	//};

	//static std::vector<GRAMMAR_RULE> grammar;
	//std::vector<void(*)()>				  grammar_;

	static std::map<std::string, std::string>				specials;
	static std::vector<std::string>							keywords;
	static std::map<std::string, std::string>				types;
	static std::map<std::string, int>						precedence;

	//std::string keywords[] = {"for", "while", "class", "struct", "goto", "mark", "" };

	static bool hasNext(const std::string string, int index);

	static char getNext(const std::string string, int index);

	static bool isSpecial(const std::string str, std::vector<token*>& tokens, const int line, const int offset, const int spaces);

	static bool isKeyword(const std::string str, std::vector<token*>& tokens);

	static std::string typeof(std::string& str);

	static std::string chartypeof(std::string& c);

	static int getprecedence(std::string& c);

	static void loop(std::vector<token*>& tokens, std::string& program, std::string& builder, int& i, int& offset, int& spaces, int& line, bool& countspaces, bool& isIdentifier);

	static std::vector<token*> lex(std::string program, std::map<std::string, std::string> lexmap);

	static void compile(std::string program);

	static std::string loadText(std::string location);

	static std::string loadSpecials(std::string location);

	static std::string loadKeywords(std::string location);

	static std::string loadPrecedence(std::string location);

	static std::string loadncheck(std::string& s, std::ifstream& f);

	//static void loadGrammarFile(std::string location)
	//{
	//	using namespace std;
	//	ifstream file;

	//	file.open(location.c_str());
	//	if (!file.is_open())
	//		return;

	//	string arg;
	//	string name;
	//	string version;

	//	file >> version;

	//	while (file.good())
	//	{
	//		vector<string> grammar_rule;
	//		file >> name;

	//		while (loadncheck(arg, file) != "[stop]")
	//		{
	//			grammar_rule.push_back(arg);
	//		}

	//		//GRAMMAR_RULE rule(name, grammar_rule);
	//		//grammar.push_back(rule);
	//	}
	//}
}

#endif !MOCHA_H