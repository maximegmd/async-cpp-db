#include <catch2/catch.hpp>
#include "DbPool.hpp"

TEST_CASE("Pool Insert", "dbpool.insert")
{
	Async::DbPool db("127.0.0.1", 3306, "root", "test", "test");

	WHEN("Connected")
	{
		REQUIRE(!db.Execute("INSERT INTO test_list VALUES(1, 'test');").get());

		THEN("Malformed")
		{
			REQUIRE(db.Execute("INSERT INTO test_list VALUES(1, 'test', 45);").get());
		}
	}
}

TEST_CASE("Pool Select", "dbpool.select")
{
	Async::DbPool db("127.0.0.1", 3306, "root", "test", "test");


	WHEN("Connected")
	{
		// Condition is correct, optional is only set to an error if it fails
		auto res = db.Fetch("SELECT * FROM test_list;").get();
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
			REQUIRE(!db.Fetch("SELECT * FROM test_list 45;").get());
		}
	}
}