#include "CurrencyManager.h"

Currency CurrencyManager::Summarize(std::vector<Entry> Entries) {
    Currency sum{ "0.0" };

    for (const Entry& Entry : Entries) {
        if (Entry.TypeOfEntry == type::payin) 
            sum += Entry.amount;
        else if (Entry.TypeOfEntry == type::withdraw) 
            sum -= Entry.amount;
    }

    EuroOutput = sum;
    return EuroOutput;
}


Currency CurrencyManager::GetWithdrawnAmount(std::vector<Entry> Entries)
{
    Currency totalWithdrawn{ "0" };

    for (const Entry& Entry : Entries) 
        if (Entry.TypeOfEntry == type::withdraw)
            totalWithdrawn += Entry.amount;
 
	return totalWithdrawn;
}

Currency CurrencyManager::GetPayedInAmount(std::vector<Entry> Entries)
{
    Currency TotalPayedIn{ "0" };

    for (const Entry& Entry : Entries) 
        if(Entry.TypeOfEntry == type::payin)
			TotalPayedIn += Entry.amount;

    return TotalPayedIn;
}

bool CurrencyManager::IsValidAmount(Currency& Input)
{
    return !Input.Empty() && Input.GetAmount()>0;
}
