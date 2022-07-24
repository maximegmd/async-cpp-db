#pragma once

#include <optional>
#include <string>

namespace Async
{
	struct Field
	{
		Field(const char* apData);

		template<class T>
		std::optional<T> As() const noexcept;

	private:
		std::string m_data;
	};
}

extern template std::optional<uint64_t> Async::Field::As<uint64_t>() const noexcept;

extern template std::optional<double> Async::Field::As<double>() const noexcept;

extern template std::optional<std::string> Async::Field::As<std::string>() const noexcept;

extern template std::optional<bool> Async::Field::As<bool>() const noexcept;