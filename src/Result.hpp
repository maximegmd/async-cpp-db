#pragma once

#include <memory>
#include <optional>
#include <vector>

#include "Row.hpp"

namespace Async
{
	struct Result : public std::vector<Row>
	{
	};
}