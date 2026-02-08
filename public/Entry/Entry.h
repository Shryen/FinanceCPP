#pragma once
#include "Date.h"
#include "Currency/Currency.h"
enum class type {
	payin,
	withdraw
};
struct Entry {
	int id{ 0 };
	Date DateofRecord = Date();
	Currency amount{ "0" };
	std::string Person{ "" };
	type TypeOfEntry{ type::payin };
	Currency OldValue{ "0" };
};