#pragma once

#include <string>
#include <vector>

namespace chess::utils
{

struct Position;

class CommandConverter final
{
public:
	static bool convert(const std::string& comm, Position& from, Position& to);
	static bool convertPosition(const std::string& txt, Position& pos);
	static void splitCommand(const std::string& comm,
							 std::vector<std::string>& items,
							 const std::string& delimiter);
	static Position convertPosition(const std::string& txt);
};

} //namespace chess::utils