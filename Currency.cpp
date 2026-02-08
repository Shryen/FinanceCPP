#include "Currency.h"
#include <iostream>

Currency::Currency(int Amount)
{
	this->Amount = Amount;
}

Currency::Currency(std::string Amount)
{
	int Result{ 0 };
	int Euro{ 0 };
	int Cent{ 0 };
	bool DecimalFound{ false };
	for (int i = 0; i < Amount.size(); ++i) { 
		if (Amount[i] == '.' || Amount[i] == ',') { // remove decimal point if exists
			Amount.erase(i, 1);
			DecimalFound = true;
		}
		if (!DecimalFound) 
			Euro = Euro * 10 + (Amount[i] - '0');
		else
			Cent = Cent * 10 + (Amount[i] - '0');
		// convert char to it's ASCII value
		// for example '5' - '0' = 53-48 = 5
		// then we shift the result to the left (result*10)
		Result = Result * 10 + (Amount[i] - '0'); 
	}
	if (Cent > 99) {
		Euro = Euro + Cent / 100;
		Cent = Cent % 100;
	}
	if (Cent == 0) 
		Result = Euro * 100;
	else
		Result = Euro * 100 + Cent;
	
	this->Amount = Result;
}

bool Currency::Empty()
{
	if (Amount == 0)
		return true;
	return false;
}

std::ostream& operator<<(std::ostream& os, const Currency& Currency)
{
	os << std::fixed << std::setprecision(2) << (Currency.Amount / 100.0);
	return os;
}
