#include "Field.hpp"

template<>
std::optional<uint64_t> Async::Field::As<uint64_t>() const noexcept
{
	try 
	{
		return std::stoull(m_data);
	}
	catch (...)
	{
		return std::nullopt;
	}
}

template<>
std::optional<double> Async::Field::As<double>() const noexcept
{
	try 
	{
		return std::stod(m_data);
	}
	catch (...)
	{
		return std::nullopt;
	}
}

template<>
std::optional<std::string> Async::Field::As<std::string>() const noexcept
{
	return m_data;
}

template<>
std::optional<bool> Async::Field::As<bool>() const noexcept
{
	try
	{
		return m_data == "1" || strcmpi(m_data.c_str(), "true") == 0;
	}
	catch (...)
	{
		return std::nullopt;
	}
}

Async::Field::Field(const char* apData)
	: m_data(apData)
{
}
