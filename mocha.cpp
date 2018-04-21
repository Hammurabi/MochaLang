#include "stdafx.h"
#include "mocha.h"

#define token_stack std::vector<token*>
#define previewP   (vector_index > 0 ? vector_index - 1 : 0)
#define previewN   (vector_index < (tokens.size() - 1) ? vector_index + 1 : tokens.size() - 1)
#define Token(x) token* x = new token()

bool MochaOpcodeProvider::Parser::parse(token_stack * tokns, token_stack * tokenout, int & vector_index)
{
	if (parseBody(tokns, tokenout, vector_index)) {}
	else {
		token_stack tokens = *tokns;

		token* t = (tokens)[vector_index];
		tokenout->push_back(t);
	}

	return true;
}

token_stack MochaOpcodeProvider::Parser::parse(token_stack & tokens)
{
	token_stack tokenout;

	int vector_index = 0;

	while (vector_index < tokens.size())
	{
		using namespace std;
		token* t = tokens[vector_index];
		token* next = tokens[previewN];
		token* last = tokens[previewP];

		parse(&tokens, &tokenout, vector_index);

		vector_index++;
	}

#undef remaining

	std::cout << "---------------------------------------------------\n";

	for (int i = 0; i < tokenout.size(); i++)
		tokenout[i]->debug();

	std::cout << "---------------------------------------------------\n";

	return tokenout;
}

bool MochaOpcodeProvider::Parser::parseBody(token_stack * tns, token_stack * tokenout, int & vector_index)
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
			/*if (parseBODY(tns, &(n->tokens), vector_index)) {}
			else n->tokens.push_back(t);*/
			parse(tns, &(n->tokens), vector_index);
			//std::cout << vector_index << " " << tns->size() << std::endl;
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
}