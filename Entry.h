#pragma once
#include "Date.h"
enum class type {
	payin,
	withdraw
};

struct Entry {
	int id{ 0 };
	Date DateofRecord = Date();
	int amount{ 0 };
	std::string Person{ "" };
	type TypeOfEntry{ type::payin };
	double OldValue{ 0.0 };
};