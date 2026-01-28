#pragma once
#include <string>
#include <vector>
#include "Entry.h"

class CurrencyManager
{
public:
	int ConvertToCents(double euros);
	double ConvertToEuros(int cents);
	double GetEuroOutput() { return EuroOutput; };

	double Summarize(std::vector<Entry> Entries);
	double GetWithdrawnAmount(std::vector<Entry> Entries);
	double GetPayedInAmount(std::vector<Entry> Entries);

private:
	double EuroOutput{ 0.0 };
};

