#include <catch2/catch.hpp>
#include "Db.hpp"

TEST_CASE("Connect", "db.connect")
{
	Async::Db db;
	// Condition is correct, optional is only set to an error if it fails
	REQUIRE(!db.Connect("127.0.0.1", 3306, "root", "test", "test"));
	
}

TEST_CASE("Insert", "db.insert")
{
	Async::Db db;

	WHEN("not connected")
	{
		REQUIRE(db.Execute("INSERT INTO test_list VALUES(1, 'test');"));
	}

	WHEN("Connected")
	{
		// Condition is correct, optional is only set to an error if it fails
		REQUIRE(!db.Connect("127.0.0.1", 3306, "root", "test", "test"));
		REQUIRE(!db.Execute("INSERT INTO test_list VALUES(1, 'test');"));

		THEN("Malformed")
		{
			REQUIRE(db.Execute("INSERT INTO test_list VALUES(1, 'test', 45);"));
		}
	}
}

TEST_CASE("Select", "db.select")
{
	Async::Db db;

	WHEN("not connected")
	{
		REQUIRE(!db.Fetch("SELECT * FROM test_list;"));
	}

	WHEN("Connected")
	{
		// Condition is correct, optional is only set to an error if it fails
		REQUIRE(!db.Connect("127.0.0.1", 3306, "root", "test", "test"));
		auto res = db.Fetch("SELECT * FROM test_list;");
		REQUIRE(res);
		if (res) 
		{
			auto result = res.value();
			REQUIRE(result.size() > 0);
			REQUIRE(result[0].size() == 2);
			REQUIRE(result[0][0].As<uint64_t>() == 1);
			REQUIRE(result[0][1].As<std::string>() == "test");
		}	

		THEN("Malformed")
		{
			REQUIRE(!db.Fetch("SELECT * FROM test_list 45;"));
		}
	}
}