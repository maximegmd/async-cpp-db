#pragma once

#include <memory>
#include <future>
#include <optional>
#include <mutex>
#include <stack>

#include "Db.hpp"

namespace Async
{
	struct DbPool
	{
		DbPool(std::string acHost, uint16_t aPort, std::string acUsername, std::string acPassword, std::string acDatabase, uint32_t aCount = 5);
		DbPool(const DbPool&) noexcept = delete;
		DbPool& operator=(const DbPool&) noexcept = delete;

		[[nodiscard]] std::future<std::optional<Result>> Fetch(const std::string& aQuery) noexcept;
		[[nodiscard]] std::future<std::optional<std::string>> Execute(const std::string& aQuery) noexcept;
		void ExecuteAndForget(const std::string& aQuery) noexcept;

	private:

		std::optional<std::string> DoExecute(const std::string& aQuery) noexcept;
		std::shared_ptr<Db> Connect() noexcept;

		std::mutex m_lock;
		std::stack<std::shared_ptr<Db>> m_dbs;

		std::string m_host;
		uint16_t m_port;
		std::string m_username;
		std::string m_password;
		std::string m_database;
	};
}