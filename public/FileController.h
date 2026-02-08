#pragma once
#include <string>
#include <vector>

struct Entry;
enum class type;

class FileController
{
public:
	FileController(std::string FilePath);
	std::vector<Entry> ReadEntriesFromFile(std::vector<Entry>& Entries);
	void WriteEntriesToFile(const std::vector<Entry>& Entries);

	// convert type enum to string for representation
	std::string TypeToString(type t);
	// convert string to type enum from user input
	type StringToType(const std::string& s);

	bool IsFileEmpty();

private:
	std::string FileName{""};
	bool FileEmpty{ false };
};

