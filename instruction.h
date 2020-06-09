#ifndef _INSTRUCTION_H

#define _INSTRUCTION_H

#include <memory>
#include <optional>
#include <string>

#include "ast.h"


namespace Block {
struct Block;
struct Type;
}

struct Instruction {
	std::string instruction;
	std::optional<int> param;

	Instruction(std::string ins)
		: instruction(ins)
		, param(std::nullopt)
	{ }

	Instruction(std::string ins, int par)
		: instruction(ins)
		, param(par)
	{ }
};

void compile(Block::Block* block);

#endif
