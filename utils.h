#pragma once

#include <type_traits>
#include <string>

namespace chess::utils
{

inline long long ABS(long long val1, long long val2) { 
	long long val = val1 - val2;
	return val > 0 ? val : val * -1; 
}

enum class Color
{
	WHITE,
	BLACK
};

inline std::string ToString(Color c) { return c == Color::WHITE ? "W" : "B"; }

enum class FigureType
{
	PAWN,
	ROOK,
	HORSE,
	ELEPHANT,
	QUEEN,
	KING
};

struct Position
{
	size_t x = 0;
	size_t y = 0;
	Color color = Color::WHITE;

	Position() = default;
	Position(size_t _x, size_t _y)
	: x(_x), y(_y)
	{}

	Position(size_t _x, size_t _y, Color _color)
	: x(_x), y(_y), color(_color)
	{}


	bool operator<(const Position& right) const
	{
		return x*100 + y < right.x*100 + right.y;
	}
	std::string GetColor() const { return ToString(color); }

	bool operator==(const Position& right) const
	{
		return x == right.x && y == right.y;
	}
	bool operator!=(const Position& right) const
	{
		return !operator==(right);
	}

	static Position Next(const Position& from, const Position& to)
	{
		if (from == to)
			return from;
		if (from.x == to.x && from.y != to.y)
		{
			if (from.y > to.y)
				return Position(from.x, from.y - 1);
			return Position(from.x, from.y + 1);
		}
		if (from.y == to.y && from.x != to.x)
		{
			if (from.x > to.x)
				return Position(from.x - 1 , from.y);
			return Position(from.x + 1, from.y);
		}
		size_t nextX = ((int)to.x - (int)from.x) > 0 ? from.x + 1 : from.x - 1;
		size_t nextY = ((int)to.y - (int)from.y) > 0 ? from.y + 1 : from.y - 1;
		return Position(nextX, nextY);
	}
};


} //namespace chess::utils
