#pragma once

#include <optional>
#include <string>

namespace Async
{
	struct Field
	{
		Field(const char* apData);

		template<class T>
		[[nodiscard]] std::optional<T> As() const noexcept;

	private:
		std::string m_data;
	};
}

template<>
std::optional<uint64_t> Async::Field::As<uint64_t>() const noexcept;

template<>
std::optional<int64_t> Async::Field::As<int64_t>() const noexcept;

template<>
std::optional<uint32_t> Async::Field::As<uint32_t>() const noexcept;

template<>
std::optional<int32_t> Async::Field::As<int32_t>() const noexcept;

template<>
std::optional<double> Async::Field::As<double>() const noexcept;

template<>
std::optional<float> Async::Field::As<float>() const noexcept;

template<>
std::optional<std::string> Async::Field::As<std::string>() const noexcept;

template<>
std::optional<bool> Async::Field::As<bool>() const noexcept;