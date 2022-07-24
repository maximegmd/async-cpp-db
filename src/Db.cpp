#include "Db.hpp"

#include <mariadb/mysql.h>
#include <thread>
#include <iostream>
#include <utility>

Async::Db::Db() noexcept
	: m_db(std::make_unique<MYSQL>())
{
	mysql_init(m_db.get());
}

Async::Db::Db(Db&& aOther) noexcept
	: m_db(std::exchange(aOther.m_db, {}))
{
}

Async::Db& Async::Db::operator=(Db&& aOther) noexcept
{
	std::swap(m_db, aOther.m_db);
	return *this;
}

Async::Db::~Db() noexcept
{
	if (m_db)
		mysql_close(m_db.get());
}

std::optional<std::string> Async::Db::Connect(const std::string& acHost, uint16_t aPort, const std::string& acUsername, const std::string& acPassword, const std::string& acDatabase) noexcept
{
	auto status = mysql_real_connect(m_db.get(), acHost.c_str(), acUsername.c_str(), acPassword.c_str(), acDatabase.c_str(), aPort, nullptr, 0);

	if (!status)
		return std::make_optional(std::string(mysql_error(m_db.get())));

	my_bool reconnect = 1;
	mysql_options(m_db.get(), MYSQL_OPT_RECONNECT, &reconnect);

	return std::nullopt;
}

std::optional<Async::Result> Async::Db::Fetch(const std::string& aQuery) noexcept
{
	auto res = mysql_query(m_db.get(), aQuery.c_str());
	if (res != 0)
		return std::nullopt;

	auto* result = mysql_store_result(m_db.get());

	auto field_count = mysql_field_count(m_db.get());
	auto row_count = mysql_num_rows(result);

	Result r;
	r.reserve(row_count);

	MYSQL_ROW row = nullptr;

	while ((row = mysql_fetch_row(result)))
	{
		Row line;
		line.reserve(field_count);
		for (auto i = 0; i < field_count; i++)
		{
			line.emplace_back(row[i]);
		}

		r.push_back(std::move(line));
	}

	mysql_free_result(result);

	return std::make_optional(std::move(r));
}

std::optional<std::string> Async::Db::Execute(const std::string& aQuery) noexcept
{
	auto res = mysql_query(m_db.get(), aQuery.c_str());
	if(res != 0)
		return std::make_optional(std::string(mysql_error(m_db.get())));

	return std::nullopt;
}
