#include "queen.h"
#include "board.h"
#include <sstream>
#include <cstdlib>

chess::Queen::Queen(Board* _board, utils::Color _color, const utils::Position& _position)
:Figure(_board, utils::FigureType::QUEEN, _color, _position)
{}

bool chess::Queen::move(const utils::Position& to)
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

std::string chess::Queen::ToString() const
{
	std::ostringstream oss;
	oss << utils::ToString(Color()) << "Q";
	return oss.str();
}

bool chess::Queen::canAttack(const utils::Position& to, bool ignoreKing) const
{
	if (board->outOfBound(to))
	{
		return false;
	}
	size_t diffX = utils::ABS(position.x , to.x);
	size_t diffY = utils::ABS(position.y, to.y);
	if ((diffX == diffY)
		|| (diffX > 0 && position.y == to.y)
		|| (diffY > 0 && position.x == to.x)
	)
	{
		if (!board->isPathEmpty(position, to))
		{
			return false;
		}
		return board->isEmptyPosition(to) || board->canKillFigure(to, *this, ignoreKing);
	}
	return false;
}

void chess::Queen::attack_(const utils::Position& to)
{
	position = to;
}
