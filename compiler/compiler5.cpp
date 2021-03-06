// compiler5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "tokenizer.h"
#include <iostream>
#include "parser.h"
#include "prettyprinter.hpp"
#include "compiler.hpp"

struct CompiledCode {
	bool success;
	char* error;
	unsigned int local_var_count;
	const char** strings;
	unsigned int* string_positions;
	unsigned int strings_len;
	unsigned int* call_positions;
	const char** function_names;
	unsigned int function_names_len;
	unsigned int* bytecode;
	unsigned int bytecode_len;
};

extern "C" __declspec(dllexport) CompiledCode* compile(const char* code)
{
	CompiledCode* cc = new CompiledCode();
	std::string s(code);
	if (s.at(s.size() - 1) != '\n') s += '\n';
	Tokenizer t(s);
	std::vector<Token> tokens;
	try
	{
		tokens = t.tokenize();
	}
	catch(TokenizerError& t)
	{
		cc->success = false;
		cc->error = new char[t.msg.size()+1];
		strcpy_s(cc->error, t.msg.size() + 1, t.msg.c_str());
		return cc;
	}
	Parser p(s, tokens);
	std::cout << "Constructing parse tree..." << std::endl;
	Block* proc_body;
	try
	{
		proc_body = p.parse_block();
	}
	catch(ParserError& p)
	{
		cc->success = false;
		cc->error = new char[p.msg.size() + 1];
		strcpy_s(cc->error, p.msg.size() + 1, p.msg.c_str());
		return cc;
	}
	AstPrinter ast;
	std::cout << std::endl;
	ast.pprint(proc_body);
	std::cout << std::endl;
	CodeGenerator* codegen = new CodeGenerator();
	std::cout << "Generating code..." << std::endl;
	codegen->generate(proc_body);
	cc->success = true;
	cc->local_var_count = codegen->localvars.size();
	cc->strings = codegen->strings.data();
	cc->string_positions = codegen->string_positions.data();
	cc->strings_len = codegen->strings.size();
	cc->function_names = codegen->function_names.data();
	cc->function_names_len = codegen->function_names.size();
	cc->call_positions = codegen->call_positions.data();
	cc->bytecode = codegen->bytecode.data();
	cc->bytecode_len = codegen->bytecode.size();
	return cc;

}

int main()
{
	std::string code = "var/x = src.name";
	Tokenizer t(code);
	std::vector<Token> tokens;
	try {
		tokens = t.tokenize();
	} catch(TokenizerError& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	Parser p(code, tokens);
	Block* tree;
	try {
		tree = p.parse_block();
	}
	catch (ParserError& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	AstPrinter astp;
	astp.pprint(tree);
	CodeGenerator c;
	c.generate(tree);
	for (unsigned int& i : c.bytecode)
	{
		std::cout << "0x" << std::hex << i << ", ";
	}
    return 0;
}

