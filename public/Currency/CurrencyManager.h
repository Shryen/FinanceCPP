#pragma once
#include <string>
#include <vector>
#include "Entry/Entry.h"

class CurrencyManager
{
public:
	Currency Summarize(const std::vector<Entry>& Entries);
	Currency GetWithdrawnAmount(const std::vector<Entry>& Entries);
	Currency GetPayedInAmount(const std::vector<Entry>& Entries);
	bool IsValidAmount(Currency& Input);
};

