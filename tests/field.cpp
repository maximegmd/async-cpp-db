#include <catch2/catch.hpp>
#include "Field.hpp"

using Async::Field;

TEST_CASE("Field", "db.field")
{
	WHEN("Using a string")
	{
		Field f("hello world!");

		REQUIRE(f.As<std::string>() == "hello world!");
		REQUIRE(f.As<uint64_t>() == std::nullopt);
		REQUIRE(f.As<double>() == std::nullopt);
	}

	WHEN("Using an integer")
	{
		Field f("12345678");

		REQUIRE(f.As<std::string>() == "12345678");
		REQUIRE(f.As<uint64_t>() == 12345678);
		REQUIRE(f.As<double>() == 12345678);
	}

	WHEN("Using a double")
	{
		Field f("12345678.9");

		REQUIRE(f.As<std::string>() == "12345678.9");
		REQUIRE(f.As<uint64_t>() == 12345678);
		REQUIRE(f.As<double>() == 12345678.9);
	}

	WHEN("Using a bool")
	{
		Field f("true");

		REQUIRE(f.As<std::string>() == "true");
		REQUIRE(f.As<uint64_t>() == std::nullopt);
		REQUIRE(f.As<double>() == std::nullopt);
		REQUIRE(f.As<bool>() == true);
	}
}