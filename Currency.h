#pragma once
#include <string>
#include <iostream>
#include <iomanip> 

class Currency
{
public:
	// Basic functions START #####
	Currency(int Amount);
	Currency(std::string Amount);	

	int GetAmount() const { return Amount; }
	// just for display purposes
	double ToEuros() const { return Amount / 100.0; };
	bool Empty();
	// Basic functions END #####


	// Operator Overloads START #####
	Currency operator+(const Currency& other) const {
		return Currency(std::to_string(Amount + other.Amount));
	}
	Currency operator-(const Currency& other) const {
		return Currency(std::to_string(Amount - other.Amount));
	}
	Currency operator*(float multiplier) const {
		return Currency(std::to_string(Amount * multiplier));
	}
	Currency operator/(float divisor) const {
		return Currency(std::to_string(Amount / divisor));
	}

	Currency& operator+=(const Currency& other) {
		Amount += other.Amount;
		return *this;
	}
	Currency& operator-=(const Currency& other) {
		Amount -= other.Amount;
		return *this;
	}
	Currency& operator*=(float multiplier) {
		Amount = static_cast<int>(Amount * multiplier);
		return *this;
	}
	Currency& operator/=(float divisor) {
		Amount = static_cast<int>(Amount / divisor);
		return *this;
	}

	bool operator==(int value) const { return Amount == value; }
	bool operator!=(int value) const { return Amount != value; }
	bool operator==(const Currency& other) const { return Amount == other.Amount; }
	bool operator!=(const Currency& other) const { return Amount != other.Amount; }
	bool operator>(const Currency& other) const { return Amount > other.Amount; }
	bool operator<(const Currency& other) const { return Amount < other.Amount; }
	bool operator>=(const Currency& other) const { return Amount >= other.Amount; }
	bool operator<=(const Currency& other) const { return Amount <= other.Amount; }

	friend std::ostream& operator<<(std::ostream& os, const Currency& Currency);
	friend std::istream& operator>>(std::istream& is, Currency& Currency);
	// Operator Overloads END #####

private:
	long long Amount{ 0 };
};


//Inline so it doesn't break the one definition rule
std::ostream& operator<<(std::ostream& os, const Currency& Currency);
std::ostream& operator<<(std::ostream& os, const Currency& Currency);

inline std::istream& operator>>(std::istream& is, Currency& CurrencyObj) {
	try {
		std::string input;
		is >> input;
		for(int i=0; i<input.size(); ++i)
			if ((input[i] < '0' || input[i] > '9') && (input[i] != '.' && input[i] != ','))
				throw std::invalid_argument("Invalid character in currency input");
		Currency temporary = Currency(input);
		CurrencyObj = temporary;
	}
	catch (const std::exception& e) {
		std::cerr << "Error reading currency: " << e.what() << std::endl;
		is.setstate(std::ios::failbit);
	}
	return is;
}

