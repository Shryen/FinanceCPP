#include "FileController.h"
#include "Entry/Entry.h"
#include <fstream>

FileController::FileController(std::string FilePath)
{
	if (FilePath.empty())
		throw std::runtime_error("Invalid FilePath!");

	FileName = FilePath;
	std::ifstream Readfile{ FileName };
	// if file doesn't exist create one!
	if (!Readfile) {
		std::ofstream OutFile(FileName);
		OutFile.close();
	}
}

std::vector<Entry> FileController::ReadEntriesFromFile(std::vector<Entry>& Entries)
{
	Entries.clear(); // make sure the vector is empty before reading the file, no duplicates
	std::ifstream InputFile(FileName);
	if(!InputFile) 
		throw std::runtime_error("Couldn't open file: " + FileName);

	if (InputFile.fail()) 
		std::cout << "Failed parsing line" << '\n';
	
	Entry RowEntry;
	std::string TypeString;
	std::cout << "Reading entries from file: " << FileName << std::endl;
	while (InputFile >> RowEntry.id
		>> RowEntry.DateofRecord
		>> RowEntry.amount
		>> RowEntry.Person
		>> TypeString) {
		RowEntry.TypeOfEntry = StringToType(TypeString);
		Entries.push_back(RowEntry);
	}
	if (Entries.empty()) {
		std::cout << "File is empty, no entries to read.\n";
		std::cout << "Filename: " << FileName;
		FileEmpty = true;
	}
	std::cout << "Entries read: " << Entries.size() << '\n';
	return Entries;
}

void FileController::WriteEntriesToFile(const std::vector<Entry>& Entries)
{
	std::ofstream OutputFile(FileName);
	if (!OutputFile)
		throw std::runtime_error("Couldn't open file: " + FileName);

	/* Entry.amount.GetAmount() looks stupid
	 * Entry is the struct that has a currency datatype named amount
	 * the class named amount this case has a function called GetAmount
	 * If i wouldn't call GetAmount the euro would be stored instead of cents
	 * I don't want that
	 */

	for (const Entry& Entry : Entries)
			OutputFile << Entry.id << " "
			<< Entry.DateofRecord << " "
			<< Entry.amount.GetAmount() << " "
			<< Entry.Person << " "
			<< TypeToString(Entry.TypeOfEntry) << '\n';
}


std::string FileController::TypeToString(type t)
{
	switch (t) {
	case type::payin: return "payin";
	case type::withdraw: return "withdraw";
	}
	throw std::logic_error("Invalid type");
}

type FileController::StringToType(const std::string& s)
{
	if (s == "payin") return type::payin;
	if (s == "withdraw") return type::withdraw;
	throw std::runtime_error("Invalid Type string: " + s);
}

bool FileController::IsFileEmpty()
{
	return FileEmpty;
}
