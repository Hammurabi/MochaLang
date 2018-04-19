// MochaLang.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stack>
#include <vector>

#include "mocha.h"

int main()
{
	std::map<std::string, std::string> map;
	MochaOpcodeProvider::loadSpecials(".\\lang\\mochalang_specials.lex");
	MochaOpcodeProvider::loadKeywords(".\\lang\\mochalang_keywords.lex");
	MochaOpcodeProvider::loadPrecedence(".\\lang\\mochalang_tokens.lex");
	MochaOpcodeProvider::loadGrammarFile(".\\lang\\Mochalang.gr");
	//std::cout << MochaOpcodeProvider::loadText(".\\lang\\sample.ma");

	//for (int i = 0; i < MochaOpcodeProvider::grammar.size(); i++)
	//{
	//	MochaOpcodeProvider::GRAMMAR_RULE rule = MochaOpcodeProvider::grammar[i];

	//	for (int j = 0; j < rule.rules.size(); j++)
	//	{
	//		std::cout << rule.name << " " << rule.rules[j] << std::endl;
	//	}
	//}

	std::vector<token> tokens = MochaOpcodeProvider::lex(MochaOpcodeProvider::loadText(".\\lang\\sample.ma"), map);

	MochaOpcodeProvider::parse(tokens);

	for (int i = 0; i < tokens.size(); i++)
	{
		tokens[i].print();
	}

	while (true) {}

	return 0;
}