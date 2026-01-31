#pragma once
#include <string>
#include <vector>
#include "Entry.h"

class CurrencyManager
{
public:
	Currency Summarize(std::vector<Entry> Entries);
	Currency GetWithdrawnAmount(std::vector<Entry> Entries);
	Currency GetPayedInAmount(std::vector<Entry> Entries);
	bool IsValidAmount(Currency& Input);
private:
	Currency EuroOutput{ "0.0" };
};

