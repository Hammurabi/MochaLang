#include "stdafx.h"
#include "mocha.h"

#define token_stack std::vector<token*>
#define previewP   (vector_index > 0 ? vector_index - 1 : 0)
#define previewN   (vector_index < (tokens.size() - 1) ? vector_index + 1 : tokens.size() - 1)
#define Token(x)   token* x = new token()

std::string vectorinfo(filevector v)
{
	return std::string("at line '" + std::to_string(v.line) + "' offset '" + std::to_string(v.offset) + "'");
}

void exit_(int num)
{
	while (true)
	{
	}
}

bool parseClasses(token_stack * tns, token_stack * tokenout, int & vector_index)
{
	token_stack&tokens = *tns;
	token* t = (tokens)[vector_index];
	token* Class = t;

	if (t->name == "CLASS")
	{
		vector_index++;
		t = tokens[vector_index];
		while (vector_index < tokens.size())
		{
			t = tokens[vector_index++];

			if(t->name == "BODY")
			{
				Class->tokens.push_back(t);
				tokenout->push_back(Class);
				return true;
			}
			//else if (t->name == "CLASS") parseClasses(tns, tokenout, vector_index);
			else Class->tokens.push_back(t);
		}

		if (vector_index >= tokens.size())
		{
			Class->tokens.push_back(t);
			tokenout->push_back(Class);
			return true;
		}
		return true;
	}
	else tokenout->push_back(t);

	return false;
}

bool parseStatements(token_stack * tns, token_stack * tokenout, int & vector_index, std::map<unsigned int, token_stack>& referenceMap)
{
	token_stack&tokens = *tns;
	token* t = (tokens)[vector_index];

	while (vector_index < tokens.size())
	{
		token* t = (tokens)[vector_index];
		referenceMap[t->vector.line].push_back(t);

		vector_index++;
	}

	for (auto i : referenceMap)
	{
		Token(statement);

		statement->name = "STATEMENT";
		statement->value = "STATEMENT";

		statement->vector = i.second[0]->vector;
		
		if (i.second[0]->name == "IDENTIFIER" && i.second[0]->value == "if")
		{
				Token(statement2);

				statement2->name = "STATEMENT";
				statement2->value = "STATEMENT";

				statement2->vector = i.second[1]->vector;

				for (int j = 1; j < i.second.size(); j++)
					statement2->tokens.push_back(i.second[j]);

				tokenout->push_back(i.second[0]);
				tokenout->push_back(statement2);

				delete statement;
		}
		else if (i.second[0]->name == "IDENTIFIER" && i.second[0]->value == "class")
		{
			if (i.second.size() > 2)
			{
				Token(statement2);

				statement2->name = "STATEMENT";
				statement2->value = "STATEMENT";

				statement2->vector = i.second[1]->vector;

				if (i.second[1]->name != "IDENTIFIER")
				{
					std::cerr << "class must have an IDENTIFIER type name " << vectorinfo(i.second[0]->vector) << std::endl;
					std::cerr << "current type: " << i.second[1]->name << std::endl;
					exit_(0);
				}

				for (int j = 2; j < i.second.size(); j++)
					statement2->tokens.push_back(i.second[j]);

				i.second[0]->name = "CLASS";
				i.second[0]->value = i.second[1]->value;
				
				tokenout->push_back(i.second[0]);
				tokenout->push_back(statement2);

				delete statement;
			}
			else
			{
				if (i.second.size() < 2)
				{
					std::cerr << "class must have a name" << vectorinfo(i.second[0]->vector) << std::endl;
					exit_(0);
				}
					
				if (i.second[1]->name != "IDENTIFIER")
				{
					std::cerr << "class must have an IDENTIFIER type name " << vectorinfo(i.second[0]->vector) << std::endl;
					std::cerr << "current type: " << i.second[1]->name << std::endl;
					exit_(0);
				}

				i.second[0]->name = "CLASS";
				i.second[0]->value = i.second[1]->value;
				tokenout->push_back(i.second[0]);

				delete statement;
			}
		}
		else
		{
			for (token * t : i.second) statement->tokens.push_back(t);

			tokenout->push_back(statement);
		}
	}

	return true;
}

bool parseIf(token_stack * tns, token_stack * tokenout, int & vector_index)
{
	token_stack&tokens = *tns;

	token* t = (tokens)[vector_index];

	using namespace std;
	if (t-(t->name == "IDENTIFIER") && (t->value == "if"))
	{
		vector_index++;

		Token(n);
		n->name = "IF_STATEMENT";
		n->precedence = 0;
		n->value = "IF_STATEMENT";
		n->vector = t->vector;

		bool keep = true;

		while ((keep) && (vector_index < tokens.size()))
		{
			token* t = (tokens)[vector_index];

			if (t->name == "IDENTIFIER" && t->value == "if")
			{
				parseIf(tns, &(n->tokens), vector_index);
			}
			else if (t->name == "BODY")
			{
				keep = false;
				n->tokens.push_back(t);
			}
			else
				n->tokens.push_back(t);

			if(keep)
			vector_index++;
		}

		tokenout->push_back(n);
		return true;
	}
	else tokenout->push_back(t);
	
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

void call(token_stack&tokens, token_stack&tokenout, int& vector_index, bool(*mt)(token_stack*, token_stack*, int&))
{
	while (vector_index < tokens.size())
	{
		using namespace std;
		token* t = tokens[vector_index];

		mt(&tokens, &tokenout, vector_index);

		vector_index++;
	}


	tokens = token_stack(tokenout);
	tokenout.clear();

	for (auto& t : tokens)
	{
		token_stack out;
		int i = 0;

		call((t->tokens), out, i, mt);
	}

	vector_index = 0;
}

#include <algorithm>

token_stack Parser::parse(token_stack & tokens)
{
	token_stack tokenout;

	int vector_index = 0;

	std::map<unsigned int, token_stack*> refMap;
	std::map<unsigned int, token_stack>  lynMap;
	refMap[0] = &tokenout;

	parseStatements(&tokens, &tokenout, vector_index, lynMap);

	tokens = token_stack(tokenout);
	tokenout.clear();

	vector_index = 0;

	//THIS IS RECURSIVE
	//while (vector_index < tokens.size())
	//{
		parseBody(&tokens, &tokenout, vector_index, refMap);
	//	vector_index++;
	//}

	std::map<unsigned int, token_stack> lmap;

	std::vector<unsigned int> sorter;

	for (token* t : tokenout)
		lmap[t->vector.line].push_back(t);

	for (auto const i : lmap) sorter.push_back(i.first);

	std::sort(sorter.begin(), sorter.end());

	tokenout.clear();

	for (unsigned int i : sorter)
	for (token* t : lmap[i])
	tokenout.push_back(t);
	tokens = token_stack(tokenout);
	tokenout.clear();

	vector_index = 0;

	call(tokens, tokenout, vector_index, parse_8); //check assertions
	//call(tokens, tokenout, vector_index, parseIf); //check ifs

	//while (vector_index < tokens.size())
	//{
	//	parseClasses(&tokens, &tokenout, vector_index);
	//	vector_index++;
	//}

	//vector_index = 0;
	//tokens = token_stack(tokenout);
	//tokenout.clear();

#undef remaining

std::cout << "---------------------------------------------------\n";

for (int i = 0; i < tokens.size(); i++)
	tokens[i]->debug();

std::cout << "---------------------------------------------------\n";

return tokens;
}

bool parseBody2(token_stack * tns, token_stack * tokenout, int & vector_index, std::map<unsigned int, token_stack*>& referenceMap)
{
	token_stack&tokens = *tns;
	token* t = (tokens)[vector_index];
	token* next = (tokens)[previewN];

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
				parseBody2(tns, &(n->tokens), vector_index, referenceMap);
			else if (t->vector.numspaces < numspaces)
			{
				int current = t->vector.numspaces;

				std::vector<unsigned int> sortedList;

				for (auto& i : referenceMap)
					sortedList.push_back(i.first);

				std::reverse(sortedList.begin(), sortedList.end());

				for (auto i : sortedList)
					if (i <= current)
					{
						if (n->vector.line > t->vector.line)
						{
							referenceMap[i]->push_back(t);
							tokenout->push_back(n);
						}
						else
						{
							tokenout->push_back(n);
							referenceMap[i]->push_back(t);
						}
					}

				keep = false;
			}
			else
				n->tokens.push_back(t);

			if(keep)
			vector_index++;
		}

		if (keep)
		{
			if (t->vector.numspaces < numspaces)
			{
				int current = t->vector.numspaces;

				std::vector<unsigned int> sortedList;

				for (auto& i : referenceMap)
					sortedList.push_back(i.first);

				std::reverse(sortedList.begin(), sortedList.end());

				for (auto i : sortedList)
					if (i <= current)
					{
						if (n->vector.line > t->vector.line)
						{
							tokenout->push_back(n);
						}
						else
						{
							tokenout->push_back(n);
						}
					}

				keep = false;
			}
			else tokenout->push_back(n);
		}

		referenceMap.erase(numspaces);

		return true;
	}
	else
	{
		tokenout->push_back(t);

		return false;
	}
}

bool Parser::parseBody(token_stack * tns, token_stack * tokenout, int & vector_index, std::map<unsigned int, token_stack*>& referenceMap)
{
	if (!tns || !tokenout || !&referenceMap) return false;
	if (tns->size() <= 0) return false;
	token_stack&tokens = *tns;
	token* t = (tokens)[vector_index];
	token* next = (tokens)[previewN];

	int last = 0;

	Token(global);
	global->name = "GLOBAL";
	global->value = "GLOBAL";

	global->vector.line = 0;
	global->vector.offset = 0;
	global->vector.numspaces = 1000000000;

	token_stack* out = &global->tokens;

	using namespace std;

	while (vector_index < tokens.size())
	{
		t = tokens[vector_index];

		if (t->vector.numspaces < last)
		{
			tokenout->push_back(global);

			global = new token();
			global->name = "BODY";
			global->value = "BODY";

			global->vector = t->vector;
			out = &global->tokens;
			last = t->vector.numspaces;
		}
		else out->push_back(t);

		vector_index++;
	}

	if (out->size() > 0)
	{
		if (t->vector.numspaces > last)
			tokenout->push_back(global);
	}

	vector_index = 0;
	tokens = token_stack(*tokenout);
	tokenout->clear();

	while (vector_index < tokens.size())
	{
		t = tokens[vector_index];
		int i = 0;

		while (i < t->tokens.size())
		{
			parseBody2(&(t->tokens), tokenout, i, referenceMap);

			i++;
		}

		vector_index++;
	}

	//while (true) {}

	//std::cout << "lol?\n";

	return false;
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
	for (auto const& key : types)
		if (key.first == c) return key.second;

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

	int line = 1;
	int offset = 0;
	int spaces = 0;
	bool countspaces = true;

	bool isIdentifier = false;

	for (int i = 0; i < program.size(); i++)
		loop(tokens, program, builder, i, offset, spaces, line, countspaces, isIdentifier);

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
