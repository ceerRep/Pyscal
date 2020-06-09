#ifndef _GLOBAL_H

#define _GLOBAL_H

#include <memory>

#include "block.h"

std::shared_ptr<Block::Type> resolveGlobalSymbol(std::string);

#endif
