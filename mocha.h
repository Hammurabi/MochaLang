#pragma once
#ifndef MOCHA_H
#define MOCHA_H

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
	std::vector<token> tokens;
	int precedence;

	filevector  vector;

	void print()
	{
		std::cout << "TOKEN: " << name << " " << value << " l:" << vector.line << " o:" << vector.offset << " s" << vector.numspaces << std::endl;
	}
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
#define checkIndex(x, y) ((x >= y) ? 0 : x ++)
#define checkIndex0(x) ((x <= 0) ? 0 : x - 1)
	struct TokenStream
	{
		std::vector<token> tokens;
		unsigned int index;

		TokenStream(std::vector<token> ts) : tokens(ts) {}

		token& next()
		{
			return tokens[checkIndex(index, tokens.size())];
		}

		token& previewLast()
		{
			return tokens[checkIndex0(index)];
		}

		unsigned int remaining()
		{
			return tokens.size() - index;
		}
	};
	
	struct GRAMMAR_RULE
	{
		std::string name;
		std::vector<std::string> rules;

		GRAMMAR_RULE(std::string n, std::vector<std::string> r) : name(n), rules(r) {}

		bool checkMatch(TokenStream stream)
		{
			int i = stream.index;

			for (int i = 0; i < rules.size(); i++)
			{
				token t = stream.next();
				token last = stream.previewLast();

				//SPECIAL TOKEN ACCESS
				if (rules[i].at(0) == '[')
				{
					if (rules[i] == "[WHITESPACE(>)]")
					{
						if (!(last.vector.numspaces < t.vector.numspaces)) return false;
					}else if (rules[i] == "[WHITESPACE(<)]")
					{
					} else if (rules[i] == "[WHITESPACE(>=)]")
					{
					}
					else if (rules[i] == "[WHITESPACE(<=)]")
					{
					}
				}
				else if (t.name != rules[i])
				{
					stream.index = i;
					return false;
				}
			}



			return true;
		}
	};

	std::vector<GRAMMAR_RULE> grammar;
	//std::vector<void(*)()>				  grammar_;

	char SPECIAL[] = {
		'\\',
		'.',
		'+',
		'-',
		'*',
		'/',
		'-',
	};

	std::map<std::string, std::string>				specials;
	std::vector<std::string>						keywords;
	std::map<std::string, std::string>              types;
	std::map<std::string, int>						precedence;

	//std::string keywords[] = {"for", "while", "class", "struct", "goto", "mark", "" };

	bool hasNext(const std::string string, int index)
	{
		return string.size() > (index + 1);
	}

	char getNext(const std::string string, int index)
	{
		return string.at(index + 1);
	}

	bool isSpecial(const std::string str, std::vector<token>& tokens, const int line, const int offset, const int spaces)
	{
		if (specials.find(str) != specials.end())
		{
			token t;
			t.name = specials[str];
			t.value = str;
			t.vector.line = line;
			t.vector.numspaces = spaces;
			t.vector.offset = offset;
			tokens.push_back(t);
			return true;
		}

		return false;
	}

	bool isKeyword(const std::string str, std::vector<token>& tokens)
	{
		for (int i = 0; i < keywords.size(); i++)
			if (str == keywords[i]) return true;

		return false;
	}

	std::string typeof(std::string& str)
	{
		if (isalpha(str.at(0))) return "IDENTIFIER";
		for (int i = 0; i < str.length(); i++) if (isalpha(str.at(i))) return "IDENTIFIER";

		std::string number;
		for (int i = 0; i < str.length(); i++) if (!isalpha(str.at(i)) && isalnum(str.at(i))) number += str.at(i);
		str = number;

		return "NUMBER";
	}

	std::string chartypeof(std::string& c)
	{
		//if (c == '(') return "OPEN_PARENTHESIS";
		//else if (c == ')') return "CLOSED_PARENTHESIS";
		//else if (c == '[') return "OPEN_BRACKET";
		//else if (c == ']') return "CLOSED_BRACKET";
		//else if (c == '*') return "MULTIPLICATION";
		//else if (c == '&') return "AND";
		//else if (c == '^') return "XOR";
		//else if (c == '$') return "DOLLARSIGN";
		//else if (c == '/') return "DIVISION";
		//else if (c == '.') return "DOT";
		//else if (c == ':') return "COLON";
		//else if (c == ';') return "SEMI_COLON";
		//else if (c == '+') return "ADDITION";
		//else if (c == '-') return "SUBTRACTION";
		//else if (c == '=') return "ASSIGN";
		//else if (c == '@') return "AT";
		//else if (c == '!') return "NOT";
		//else if (c == '~') return "ACCENT";
		//else if (c == '#') return "HASH";
		//else if (c == ',') return "COMMA";
		//else if (c == '?') return "QUESTION_MARK";
		//else if (c == '}') return "OPEN_CURLY";
		//else if (c == '{') return "CLOSE_CURLY";
		//else if (c == '|') return "OR";

		for (auto const& key : types)
			if (key.first == c) return key.second;
			//std::cout << key.first << " " << c << std::endl;

		return "";
	}

	int getprecedence(std::string& c)
	{
		for (auto const& key : precedence)
			if (key.first == c) return key.second;

		return 0;
	}

	void loop(std::vector<token>& tokens, std::string& program, std::string& builder, int& i, int& offset, int& spaces, int& line, bool& countspaces, bool& isIdentifier)
	{
		using namespace std;

		char C = program.at(i);

		if (C == '\n')
		{
			if (isIdentifier)
			{
				isIdentifier = false;

				token t;

				t.name = std::string(typeof(builder));
				t.value = std::string(builder.c_str());

				t.vector.line = line;
				t.vector.numspaces = spaces;
				t.vector.offset = offset;

				tokens.push_back(t);

				builder = "";
			}

			line++;
			offset = 1;
			spaces = 0;
			countspaces = true;
			return;
		}
		else if (C == ' ') {
			if (countspaces)
				spaces++;
			if (isIdentifier)
			{
				isIdentifier = false;

				token t;

				t.name = std::string(typeof(builder));
				t.value = std::string(builder.c_str());

				t.vector.line = line;
				t.vector.numspaces = spaces;
				t.vector.offset = offset;

				tokens.push_back(t);

				builder = "";
			}
			return;
		}
		else if (C == '\0')
		{
			isIdentifier = false;

			token t;

			t.name = std::string(typeof(builder));
			t.value = std::string(builder.c_str());

			t.vector.line = line;
			t.vector.numspaces = spaces;
			t.vector.offset = offset;

			tokens.push_back(t);

			builder = "";
		}
		else if (C == '\t') spaces += 4;
		else
			countspaces = false;

		char L = (hasNext(program, i) ? program.at(i + 1) : '\0');

		std::string cn = "";
		cn = program.at(i);
		cn = cn + L;

		if (program.at(i) != '\s' && program.at(i) != '\t' && program.at(i) != '\n')
			countspaces = false;

		if (isSpecial(cn, tokens, line, offset, spaces))
		{
			offset += 2;
			i++;
			countspaces = false;
			return;
		}
		else
		{
			if (isIdentifier && (C == '_' || C == '$' || isalnum(C)))
			{
				builder = builder + program.at(i);
			}
			else if (isIdentifier)
			{
				isIdentifier = false;

				token t;

				t.name = std::string(typeof(builder));
				t.value = std::string(builder.c_str());

				t.vector.line = line;
				t.vector.numspaces = spaces;
				t.vector.offset = offset;

				tokens.push_back(t);

				builder = "";
			}
			else if (!isIdentifier && (C == '_' || C == '$' || isalnum(C)))
			{
				builder = program.at(i);// +"");
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
			if (C != ' ' && C != '\n' && C != '\t' && !isIdentifier)
			{
				std::string check;
				check = program.at(i);

				token t;
				t.name = chartypeof(check);
				t.value = C;
				t.vector.line = line;
				t.vector.numspaces = spaces;
				t.vector.offset = offset;
				t.precedence = getprecedence(check);
				tokens.push_back(t);
			}
			else {
			}

			offset++;
		}
	}

	std::vector<token> lex(std::string program, std::map<std::string, std::string> lexmap)
	{
		std::vector<token> tokens;
		std::string        builder = "";

		program = program + " ";

		//#define N (hasNext(program, i) ? getNext(program, i) : '\0')
		//#define L (hasNext(program, i) ? (getNext(program, i) + "") : "")
		//#define C program.at(i)

		int line = 0;
		int offset = 0;
		int spaces = 0;
		bool countspaces = true;

		bool isIdentifier = false;

		for (int i = 0; i < program.size(); i++)
			loop(tokens, program, builder, i, offset, spaces, line, countspaces, isIdentifier);
		//#undef N
		//#undef L
		//#undef C

		return tokens;
	}

#define token_stack std::vector<token>

	void parse(token_stack& tokens)
	{
		token_stack tokenout;
		TokenStream stream(tokens);

		while (stream.remaining() > 0)
		{
			//token& t = tokens[tokens.size() - 1];

			for (int i = 0; i < grammar.size(); i++)
			{
				GRAMMAR_RULE& rule = grammar[i];

				if (rule.checkMatch(stream));
			}
		}
	}

#undef token_stack

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
			if (index == -1) index = stline.length();
			string.append(stline.substr(0, index) + '\n');
		}

		return string;
	}

	std::string loadSpecials(std::string location)
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
			if (stline.length() == 0) continue;

			int index = stline.find(" ");
			if (index == -1) index = stline.length();
			specials[stline.substr(0, index)] = stline.substr(index + 1);

			string.append(stline.substr(0, index) + '\n');
		}

		return string;
	}

	std::string loadKeywords(std::string location)
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
			if (stline.length() == 0) continue;

			keywords.push_back(stline);
		}

		return string;
	}

	std::string loadPrecedence(std::string location)
	{
		std::string string("");
		std::string stline("");
		std::ifstream file;

		file.open(location.c_str());
		if (!file.is_open())
			return "";

		std::string arg;
		std::string nam;
		std::string pnc;

		file >> arg;
		file >> nam;
		file >> pnc;

		while (file.good())
		{
			file >> arg;
			file >> nam;
			file >> pnc;

			precedence[arg] = std::stoi(pnc);
			types[arg] = nam;
		}

		return string;
	}

	std::string loadncheck(std::string& s, std::ifstream& f)
	{
		f >> s;
		return s;
	}

	void loadGrammarFile(std::string location)
	{
		using namespace std;
		ifstream file;

		file.open(location.c_str());
		if (!file.is_open())
			return;

		string arg;
		string name;
		string version;

		file >> version;

		while (file.good())
		{
			vector<string> grammar_rule;
			file >> name;

			while (loadncheck(arg, file) != "[stop]")
			{
				grammar_rule.push_back(arg);
			}

			GRAMMAR_RULE rule(name, grammar_rule);
			grammar.push_back(rule);
		}
	}
}

#endif !MOCHA_H