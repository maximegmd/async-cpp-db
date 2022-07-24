#pragma once

#include <memory>
#include <future>
#include <optional>

#include "Result.hpp"

struct st_mysql;
typedef st_mysql MYSQL;

namespace Async
{
	struct Db
	{
		Db() noexcept;
		Db(const Db&) noexcept = delete;
		Db(Db&&) noexcept;
		Db& operator=(const Db&) noexcept = delete;
		Db& operator=(Db&&) noexcept;
		~Db() noexcept;

		std::future<std::optional<std::string>> Connect(const std::string& acHost, uint16_t aPort, const std::string& acUsername, const std::string& acPassword, const std::string& acDatabase) noexcept;
		std::future<std::optional<Result>> Fetch(const std::string& aQuery) noexcept;
		std::future<std::optional<std::string>> Execute(const std::string& aQuery) noexcept;

	private:
		std::unique_ptr<MYSQL> m_db;
	};
}