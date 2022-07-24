#include "Field.hpp"

template<>
std::optional<uint64_t> Async::Field::As<uint64_t>() const
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
std::optional<int64_t> Async::Field::As<int64_t>() const
{
	try
	{
		return std::stoll(m_data);
	}
	catch (...)
	{
		return std::nullopt;
	}
}

template<>
std::optional<uint32_t> Async::Field::As<uint32_t>() const
{
	try
	{
		return std::stoul(m_data);
	}
	catch (...)
	{
		return std::nullopt;
	}
}

template<>
std::optional<int32_t> Async::Field::As<int32_t>() const
{
	try
	{
		return std::stol(m_data);
	}
	catch (...)
	{
		return std::nullopt;
	}
}

template<>
std::optional<double> Async::Field::As<double>() const
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
std::optional<float> Async::Field::As<float>() const
{
	try
	{
		return std::stof(m_data);
	}
	catch (...)
	{
		return std::nullopt;
	}
}

template<>
std::optional<std::string> Async::Field::As<std::string>() const
{
	return m_data;
}

template<>
std::optional<bool> Async::Field::As<bool>() const
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
