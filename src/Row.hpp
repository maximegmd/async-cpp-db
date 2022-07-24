#pragma once

#include <vector>
#include "Field.hpp"

namespace Async
{
	struct Row : std::vector<Field>
	{
	};
}