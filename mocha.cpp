#include "stdafx.h"
#include "mocha.h"

#define token_stack std::vector<token*>
#define previewP   (vector_index > 0 ? vector_index - 1 : 0)
#define previewN   (vector_index < (tokens.size() - 1) ? vector_index + 1 : tokens.size() - 1)
#define Token(x) token* x = new token()

bool parseIf(token_stack * tns, token_stack * tokenout, int & vector_index)
{
	token_stack&tokens = *tns;

	token* t = (tokens)[vector_index];
	token* next = (tokens)[previewN];
	token* last = (tokens)[previewP];

	using namespace std;
	if ((t->name == "IDENTIFIER") && (t->value == "if"))
	{
		vector_index++;
		t = (tokens)[vector_index++];

		Token(n);
		n->name = "IF_STATEMENT";
		n->precedence = 0;
		n->value = "IF_STATEMENT";
		n->vector = t->vector;

		n->tokens.push_back(t);

		bool finished = false;

		while ((!finished) && (vector_index < tokens.size()))
		{
			token* t = (tokens)[vector_index];

			if (parseIf(tns, &(n->tokens), vector_index)) {}
			else if (t->name == "BODY")
			{
				finished = true;

				n->tokens.push_back(t);
			}
			else n->tokens.push_back(t);
			vector_index++;
		}

		tokenout->push_back(n);

		//*t = *empty;
		//*next = *empty;
		//*last = *empty;
		return true;
	}
	else
		return false;

	//token_stack&tokens = *tns;

	//token* t = (tokens)[vector_index];
	//token* next = (tokens)[previewN];
	//token* last = (tokens)[previewP];

	//using namespace std;
	//if ((t->name == "IDENTIFIER") && (t->value == "if") && tns->size() >= vector_index + 2)
	//{
	//	int numspaces = t->vector.numspaces;
	//	Token(n);
	//	n->name = "IF_STATEMENT";
	//	n->precedence = 0;
	//	n->value = "IF_STATEMENT";
	//	n->vector = t->vector;

	//	vector_index++;
	//	
	//	n->tokens.push_back(tokens[vector_index++]);
	//	n->tokens.push_back(tokens[vector_index++]);

	//	tokenout->push_back(n);
	//	return true;
	//}
	//else
	//	return false;
}

bool parseBody_(token_stack*tns, token_stack*tokenout, int& vector_index)
{
	token_stack&tokens = *tns;

	token* t = (tokens)[vector_index];
	token* next = (tokens)[previewN];
	token* last = (tokens)[previewP];

	using namespace std;
	if (last->vector.numspaces < t->vector.numspaces)
	{
		vector_index++;

		int numspaces = t->vector.numspaces;
		Token(n);
		n->name = "BODY";
		n->precedence = 0;
		n->value = "BODY";
		n->vector = t->vector;

		n->tokens.push_back(t);

		bool finished = false;

		while ((!finished) && (vector_index < tokens.size()))
		{
			token* t = (tokens)[vector_index];
			token* next = (tokens)[previewN];
			token* last = (tokens)[previewP];

			if (next->vector.numspaces < numspaces)
				finished = true;

			vector_index++;
			parseBody_(tns, tokenout, vector_index);
		}

		tokenout->push_back(n);

		//*t = *empty;
		//*next = *empty;
		//*last = *empty;
		return true;
	}
	else
		return false;
}

bool parseAssertion(token_stack * tns, token_stack * tokenout, int & vector_index)
{
	token_stack&tokens = *tns;

	token* t = (tokens)[vector_index];
	token* next = (tokens)[previewN];
	token* last = (tokens)[previewP];

	using namespace std;
	if (next->name == "ASSERT_EQUALS" && tns->size() >= vector_index + 2)
	{
		vector_index++;
		vector_index++;
		int numspaces = t->vector.numspaces;
		Token(n);
		n->name = "ASSERT_EQUALS_EXPRESSION";
		n->precedence = 0;
		n->value = "ASSERT_EQUALS_EXPRESSION";
		n->vector = t->vector;

		n->tokens.push_back(t);
		n->tokens.push_back(tokens[vector_index]);
		tokenout->push_back(n);
		return true;
	}
	else
		return false;
}

bool parse_8(token_stack * tokns, token_stack * tokenout, int & vector_index)
{
	if (parseAssertion(tokns, tokenout, vector_index)) {} //8
	else {
		token_stack tokens = *tokns;

		token* t = (tokens)[vector_index];
		tokenout->push_back(t);
	}

	return true;
}

bool parse_ifs(token_stack * tokns, token_stack * tokenout, int & vector_index)
{
	if (parseIf(tokns, tokenout, vector_index)) {} //8
	else {
		token_stack tokens = *tokns;

		token* t = (tokens)[vector_index];
		tokenout->push_back(t);
	}

	return true;
}

bool Parser::parse(token_stack * tokns, token_stack * tokenout, int & vector_index)
{
	////if (parseAssertion(tokns, tokenout, vector_index)) {} //8
	////else 
	//	if (parseBody(tokns, tokenout, vector_index)) {}
	//	//else if (parseIf(tokns, tokenout, vector_index)) {} //8
	//else {
	//	//token_stack tokens = *tokns;

	//	token* t = (*tokns)[vector_index];
	//	tokenout->push_back(t);
	//}

	return true;
}

void call(token_stack&tokens, token_stack&tokenout, int& vector_index, bool(*mt)(token_stack*, token_stack*, int&))
{
	while (vector_index < tokens.size())
	{
		using namespace std;
		token* t = tokens[vector_index];
		token* next = tokens[previewN];
		token* last = tokens[previewP];

		mt(&tokens, &tokenout, vector_index);

		vector_index++;
	}

	for (auto t : tokens)
	{
		token_stack out;
		int i = 0;

		while (i < t->tokens.size())
		{
			mt(&(t->tokens), &out, i);
			i++;
		}

		t->tokens = token_stack(out);
	}

	tokens = token_stack(tokenout);
	tokenout.clear();

	vector_index = 0;
}

void parse_(token_stack & tokens, token_stack& out)
{
	token_stack tokenout;

	int vector_index = 0;

	call(tokens, tokenout, vector_index, parseBody_);

	//while (vector_index < tokens.size())
	//{
	//	using namespace std;
	//	token* t = tokens[vector_index];
	//	token* next = tokens[previewN];
	//	token* last = tokens[previewP];

	//	parse(&tokens, &tokenout, vector_index);

	//	vector_index++;
	//}

	//tokens = token_stack(tokenout);
	//tokenout.clear();

	//vector_index = 0;

	//call(tokens, tokenout, vector_index, parse_8); //check assertions
	//call(tokens, tokenout, vector_index, parse_ifs); //check ifs



#undef remaining

	std::cout << "---------------------------------------------------\n";

	for (int i = 0; i < tokens.size(); i++)
		tokens[i]->debug();

	std::cout << "---------------------------------------------------\n";
}

token_stack Parser::parse(token_stack & tokens)
{
	token_stack tokenout;

	int vector_index = 0;

	std::map<unsigned int, token_stack*> refMap;
	refMap[0] = &tokenout;

	//THIS IS RECURSIVE
	while (vector_index < tokens.size())
	{
		parseBody(&tokens, &tokenout, vector_index, refMap);
		vector_index++;
	}

	tokens = token_stack(tokenout);
	tokenout.clear();

	vector_index = 0;

	//call(tokens, tokenout, vector_index, parse_8); //check assertions
	//call(tokens, tokenout, vector_index, parse_ifs); //check ifs

	

#undef remaining

	std::cout << "---------------------------------------------------\n";

	for (int i = 0; i < tokens.size(); i++)
		tokens[i]->debug();

	std::cout << "---------------------------------------------------\n";

	return tokens;
}

//std::map<std::string, std::string>				MochaOpcodeProvider::specials;
//std::vector<std::string>							MochaOpcodeProvider::keywords;
//std::map<std::string, std::string>				MochaOpcodeProvider::types;
//std::map<std::string, int>						MochaOpcodeProvider::precedence;

bool Parser::parseBody(token_stack * tns, token_stack * tokenout, int & vector_index, std::map<unsigned int, token_stack*>& referenceMap)
{
	token_stack&tokens = *tns;
	token* t = (tokens)[vector_index];
	token* next = (tokens)[previewN];

	using namespace std;
	
	if (t->vector.numspaces < next->vector.numspaces)
	{
		tokenout->push_back(t);

		vector_index++;
		token* t = (tokens)[vector_index];
		token* next = (tokens)[previewN];

		int numspaces = t->vector.numspaces;
		Token(n);
		n->name = "BODY";
		n->precedence = 0;
		n->value = "BODY";
		n->vector = t->vector;

		n->tokens.push_back(t);
		referenceMap[numspaces] = &n->tokens;

		bool keep = true;

		vector_index++;

		while ((vector_index < tokens.size()) && keep)
		{
			token* t = (tokens)[vector_index];
			token* next = (tokens)[previewN];

			if (t->vector.numspaces < next->vector.numspaces)
				parseBody(tns, &(n->tokens), vector_index, referenceMap);
			else if (t->vector.numspaces < numspaces)
			{
				int current = t->vector.numspaces;

				vector<unsigned int> sortedList;

				for (auto& i : referenceMap)
					sortedList.push_back(i.first);

				std::reverse(sortedList.begin(), sortedList.end());

				for(auto i : sortedList)
					if (i <= current)
					{
						referenceMap[i]->push_back(n);
						referenceMap[i]->push_back(t);
					}

				keep = false;
			}
			else
				n->tokens.push_back(t);

			if(keep)
			vector_index++;
		}

		referenceMap.erase(numspaces);

		return true;
	}
	else
	{
		tokenout->push_back(t);

		return false;
	}

	
	
	//if (last->vector.numspaces < t->vector.numspaces)
	//{
	//	tokenout->push_back(t);
	//	vector_index++;

	//	int numspaces = t->vector.numspaces;
	//	Token(n);
	//	n->name = "BODY";
	//	n->precedence = 0;
	//	n->value = "BODY";
	//	n->vector = t->vector;

	//	n->tokens.push_back(t);

	//	bool finished = false;

	//	while ((!finished) && (vector_index < tokens.size()))
	//	{
	//		t = (tokens)[vector_index];
	//		next = (tokens)[previewN];

	//		if (next->vector.numspaces < numspaces)
	//		{
	//			t->print();
	//			next->print();
	//			cout << "-----------------\n";
	//			finished = true;
	//		}
	//		
	//		vector_index++;
	//		if(t->vector.numspaces > numspaces) parseBody(tns, &(n->tokens), vector_index);
	//		else
	//			n->tokens.push_back(t);
	//		//std::cout << vector_index << " " << tns->size() << std::endl;
	//	}

	//	tokenout->push_back(t);
	//	tokenout->push_back(n);

	//	//*t = *empty;
	//	//*next = *empty;
	//	//*last = *empty;
	//	return true;
	//}
	//else
	//	return false;
}

bool Parser::parseAssertion(token_stack * tns, token_stack * tokenout, int & vector_index)
{
	token_stack&tokens = *tns;

	token* t = (tokens)[vector_index];
	token* next = (tokens)[previewN];
	token* last = (tokens)[previewP];

	using namespace std;
	if (next->name == "ASSERT_EQUALS" && tns->size() >= vector_index + 2)
	{
		vector_index++;
		vector_index++;
		int numspaces = t->vector.numspaces;
		Token(n);
		n->name = "ASSERT_EQUALS_EXPRESSION";
		n->precedence = 0;
		n->value = "ASSERT_EQUALS_EXPRESSION";
		n->vector = t->vector;

		n->tokens.push_back(t);
		n->tokens.push_back(tokens[vector_index]);
		tokenout->push_back(n);
		return true;
	}
	else
		return false;
}

void token::print(std::string pre)
{
	std::cout << pre.c_str() << "TOKEN(" << tokens.size() << "): " << name << " " << value << " vector{line: " << vector.line << " offset: " << vector.offset << " spaces: " << vector.numspaces << "}" << std::endl;
}

std::string token::spacing(int i)
{
	std::string string = "";

	for (int s = 0; s < i; s++)
		string.append("\t");

	return string;
}

void token::debug(int spcing)
{
	print(spacing(spcing));

	for (int i = 0; i < tokens.size(); i++)
		tokens[i]->debug(spcing + 1);
}

token::token()
{
}

token::~token()
{
	for each (auto var in tokens)
		delete(var);
}

bool MochaLexer::hasNext(const std::string string, int index)
{
	return string.size() > (index + 1);
}

char MochaLexer::getNext(const std::string string, int index)
{
	return string.at(index + 1);
}

bool MochaLexer::isSpecial(const std::string str, std::vector<token*>& tokens, const int line, const int offset, const int spaces)
{
	if (specials.find(str) != specials.end())
	{
		token t;
		t.name = specials[str];
		t.value = str;
		t.vector.line = line;
		t.vector.numspaces = spaces;
		t.vector.offset = offset;
		tokens.push_back(new token(t));
		return true;
	}

	return false;
}

bool MochaLexer::isKeyword(const std::string str, std::vector<token*>& tokens)
{
	for (int i = 0; i < keywords.size(); i++)
		if (str == keywords[i]) return true;

	return false;
}

std::string MochaLexer::typeof(std::string & str)
{
	if (isalpha(str.at(0))) return "IDENTIFIER";
	for (int i = 0; i < str.length(); i++) if (isalpha(str.at(i))) return "IDENTIFIER";

	std::string number;
	for (int i = 0; i < str.length(); i++) if (!isalpha(str.at(i)) && isalnum(str.at(i))) number += str.at(i);
	str = number;

	return "NUMBER";
}

std::string MochaLexer::chartypeof(std::string & c)
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

int MochaLexer::getprecedence(std::string & c)
{
	for (auto const& key : precedence)
		if (key.first == c) return key.second;

	return 0;
}

void MochaLexer::loop(std::vector<token*>& tokens, std::string & program, std::string & builder, int & i, int & offset, int & spaces, int & line, bool & countspaces, bool & isIdentifier)
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

			tokens.push_back(new token(t));

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

			tokens.push_back(new token(t));

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

		tokens.push_back(new token(t));

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

			tokens.push_back(new token(t));

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
			tokens.push_back(new token(t));
		}
		else {
		}

		offset++;
	}
}

std::vector<token*> MochaLexer::lex(std::string program, std::map<std::string, std::string> lexmap)
{
	std::vector<token*> tokens;
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

void MochaLexer::compile(std::string program)
{
}

std::string MochaLexer::loadText(std::string location)
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

std::string MochaLexer::loadSpecials(std::string location)
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

std::string MochaLexer::loadKeywords(std::string location)
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

std::string MochaLexer::loadPrecedence(std::string location)
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

std::string MochaLexer::loadncheck(std::string & s, std::ifstream & f)
{
	f >> s;
	return s;
}
