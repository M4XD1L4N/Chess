#include "elephant.h"
#include "board.h"
#include <sstream>
#include <cstdlib>

namespace chess
{

Elephant::Elephant(Board* _board, utils::Color _color, const utils::Position& _position)
	:Figure(_board, utils::FigureType::ELEPHANT, _color, _position)
{}

bool Elephant::move(const utils::Position& to)
{
	utils::Position from = position;
	if (canMove(to))
	{
		move_(to);
		board->onStepEnded(from, to, true);
		return true;
	}
	board->onStepEnded(from, to, false);
	return false;
}

std::string Elephant::ToString() const
{
	std::ostringstream oss;
	oss << utils::ToString(Color()) << "E";
	return oss.str();
}

bool Elephant::canAttack(const utils::Position& to, bool ignoreKing) const
{
	if (board->outOfBound(to))
	{
		return false;
	}
	size_t diffX = utils::ABS(position.x , to.x);
	size_t diffY = utils::ABS(position.y, to.y);
	if (diffX == diffY)
	{
		if (!board->isPathEmpty(position, to))
		{
			return false;
		}
		return board->isEmptyPosition(to) || board->canKillFigure(to, *this, ignoreKing);
	}
	return false;
}

void Elephant::attack_(const utils::Position& to)
{
	position = to;
}

} //namespace chess