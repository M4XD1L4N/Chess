#include "command_converter.h"
#include "utils.h"
#include <stdexcept>

namespace chess::utils
{

bool CommandConverter::convert(const std::string& comm, Position& from, Position& to)
{
	std::vector<std::string> items;
	splitCommand(comm, items, ",");
	if(items.size() != 2)
		return false;
	return convertPosition(items[0], from) && convertPosition(items[1], to);
}

bool CommandConverter::convertPosition(const std::string& txt, Position& pos)
{
	static std::string skippedChars = " \t\n";
	static std::string allowedSymbols = "abcdefgh";
	static std::string allowedNums = "12345678";
	bool isSetupedSym = false;
	bool isSetupedNum = false;
	for (auto sym : txt)
	{
		sym = tolower(sym);
		if (skippedChars.find(sym) != std::string::npos)
			continue;
		else if (allowedSymbols.find(sym) != std::string::npos)
		{
			if (isSetupedSym)
				return false;
			pos.x = sym - 'a';
			isSetupedSym = true;
			continue;
		}
		else if (allowedNums.find(sym) != std::string::npos)
		{
			if (isSetupedNum)
				return false;
			pos.y = sym - '1';
			isSetupedNum = true;
			continue;
		}
		else
			return false;
	}
	return isSetupedSym && isSetupedNum;
}

void CommandConverter::splitCommand(const std::string& comm, std::vector<std::string>& items, const std::string& delimiter)
{
	size_t prevPos = 0;
	for (size_t pos = comm.find(delimiter); pos != std::string::npos; pos = comm.find(delimiter, prevPos))
	{
		std::string str = comm.substr(prevPos, pos - prevPos);
		if (!str.empty())
			items.push_back(str);
		prevPos = pos + delimiter.length();
	}
	std::string str = comm.substr(prevPos, comm.length() - prevPos);
	if (!str.empty())
		items.push_back(str);
}

Position CommandConverter::convertPosition(const std::string& txt)
{
	Position result;
	if (!convertPosition(txt, result))
		throw new std::runtime_error("Incorrect convert position" + txt);
	return result;
}

} //namespace chess::utils