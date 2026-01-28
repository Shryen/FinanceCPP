#include "CurrencyManager.h"

int CurrencyManager::ConvertToCents(double euros)
{
	return euros * 100;
}

double CurrencyManager::ConvertToEuros(int cents)
{
    // TODO: Seperate euros and cents and if cents over 100 add to euros
	EuroOutput = cents / 100.0;
	return EuroOutput;
}

double CurrencyManager::Summarize(std::vector<Entry> Entries) {
    double sum{ 0.0 };

    for (const Entry& Entry : Entries) {
        if (Entry.TypeOfEntry == type::payin) 
            sum += Entry.amount;
        else if (Entry.TypeOfEntry == type::withdraw) 
            sum -= Entry.amount;
    }

    EuroOutput = sum / 100.0;
    return EuroOutput;
}

double CurrencyManager::GetWithdrawnAmount(std::vector<Entry> Entries)
{
    int totalWithdrawn{ 0 };

    for (const Entry& Entry : Entries) 
        if (Entry.TypeOfEntry == type::withdraw)
            totalWithdrawn += Entry.amount;
 
	return ConvertToEuros(totalWithdrawn);
}

double CurrencyManager::GetPayedInAmount(std::vector<Entry> Entries)
{
    int TotalPayedIn{ 0 };

    for (const Entry& Entry : Entries) 
        if(Entry.TypeOfEntry == type::payin)
			TotalPayedIn += Entry.amount;

    return ConvertToEuros(TotalPayedIn);
}
