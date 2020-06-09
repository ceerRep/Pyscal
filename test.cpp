#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include <variant>
#include <sstream>
#include <fstream>

#include "block.h"
#include "instruction.h"

std::string to_string(const std::variant<std::monostate, int, double, std::string>& s)
{
	switch (s.index())
	{
	case 0:
		return "None";

	case 1:
		return std::to_string(std::get<int>(s));

	case 2:
		return std::to_string(std::get<double>(s));

	case 3:
		return "\"" + std::get<std::string>(s) + "\"";

	case 4:
		return "None";

	default:
		throw std::logic_error("Unknown type");
	}
}

std::string to_string(const std::variant<std::variant<std::monostate, int, double, std::string>, std::shared_ptr<Block::Block>>& c)
{
	if (c.index() == 0)
	{
		auto &&s = std::get<0>(c);

		switch (s.index())
		{
		case 0:
			return "None";

		case 1:
			return std::to_string(std::get<int>(s));

		case 2:
			return std::to_string(std::get<double>(s));

		case 3:
			return "\"" + std::get<std::string>(s) + "\"";

		default:
			throw std::logic_error("Unknown type");
		}
	}
	else
	{
		std::stringstream ss;

		auto&& block = std::get<1>(c);

		ss << "@(codetype\n";
		ss << "'(argcount " << block->argument_count << ")\n";
		ss << "'(nlocals " << block->argument_count << ")\n";
		ss << "'(stacksize 64)\n";
		
		ss << "'(consts (";

		for (auto&& c : block->consts)
			ss << to_string(c) << "\n";
		ss << "))\n";

		ss << "'(names (";
		for (auto&& name : block->names)
			ss << '"' << name << "\" ";
		ss << "))\n";

		ss << "'(varnames (";
		for (auto&& arg : block->arg_name)
			ss << '"' << arg << "\" ";
		ss << "))\n";

		ss << "'(freevars (";
		for (auto&& free : block->freevars)
			ss << '"' << free->name->name << "\" ";
		ss << "))\n";

		ss << "'(cellvars (";
		for (auto&& cell : block->cellvars)
			ss << '"' << cell->name->name << "\" ";
		ss << "))\n";

		ss << "'(code @(compilecode '(\n";
		for (auto&& instruction : block->instructions)
		{
			ss << instruction.instruction;
			if (instruction.param)
				ss << ' ' << *(instruction.param);
			ss << '\n';
		}
		ss << ")))\n";

		ss << ")";

		return ss.str();
	}
}

/*
'(argcount 0)
    '(nlocals 0)
    '(stacksize 10)
    '(consts (0 1 21 None))
    '(names ("lib" "range" "writeln"))
    '(varnames ())
    '(cellvars ("" "" "" ""))
*/

void naive(YYSTYPE s, char* fout)
{
	std::ofstream of;
	std::ostream* pos;

	if (fout)
	{
		of.open(fout);
		pos = &of;
	}
	else
	{
		pos = &std::cerr;
	}


	try
	{
		auto block = Block::buildBlockFromAST(s, nullptr);

		block->resolve();

		block->instructions.emplace_back("LOAD_CONST", Block::getConst(block.get(), 0));
		block->instructions.emplace_back("BUILD_TUPLE", 0);
		block->instructions.emplace_back("IMPORT_NAME", Block::getName(block.get(), "lib"));
		block->instructions.emplace_back("IMPORT_STAR");
		
		compile(block.get());

		(*pos) << to_string(block) << std::endl;
	}
	catch (std::exception e)
	{
		std::cout << "!!!" << e.what() << std::endl;
	}

	std::cout << "end" << std::endl;

	exit(0);
}
