#include "global.h"

#include <map>
#include <string>

inline std::map<std::string, std::shared_ptr<Block::Type>> globals;

std::shared_ptr<Block::Type> resolveGlobalSymbol(std::string s)
{
	if (globals.count(s) != 0)
		return globals[s];
	return std::make_shared<Block::NullType>();
}

inline int _ = []() -> int{
	globals["read"] = Block::buildTypeFromString("s(0");
	globals["readln"] = Block::buildTypeFromString("s(0");
	globals["int"] = Block::buildTypeFromString("*i(1");
	globals["real"] = Block::buildTypeFromString("*r(1");
	globals["string"] = Block::buildTypeFromString("*s(1");
	globals["write"] = Block::buildTypeFromString("*n(1");
	globals["writeln"] = Block::buildTypeFromString("*n(1");

	globals["bytecode"] = Block::buildTypeFromString("*");
	globals["None"] = Block::buildTypeFromString("*");

	return 0;
}();
