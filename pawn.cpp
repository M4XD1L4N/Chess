#include "pawn.h"
#include "board.h"
#include <sstream>
#include <cstdlib>

namespace chess
{

Pawn::Pawn(Board* _board, utils::Color _color, const utils::Position& _position)
: Figure(_board, utils::FigureType::PAWN, _color, _position)
{}

bool Pawn::move(const utils::Position& to)
{
	utils::Position from = position;
	if (canMove(to) || canAttack(to, false))
	{
		move_(to);
		isFirstStep_ = false;
		board->onStepEnded(from, to, true);
		return true;
	}
	board->onStepEnded(from, to, false);
	return false;
}

std::string Pawn::ToString() const
{
	std::ostringstream oss;
	oss << utils::ToString(Color()) << "P";
	return oss.str();
}

bool Pawn::canMove(const utils::Position& to) const
{
	if (board->outOfBound(to))
	{
		return false;
	}
	size_t diffX = utils::ABS(position.x , to.x);
	size_t diffY = utils::ABS(position.y, to.y);
	bool isRightDirection = Color() == utils::Color::WHITE 
						  ? to.y > position.y
						  : to.y < position.y;
	if (!isRightDirection)
		return false;
	if (isFirstStep_)
	{
		if (diffY == 2 && position.x == to.x)
		{
			if (!board->isPathEmpty(position, to))
			{
				return false;
			}
			return board->isEmptyPosition(to);
		}
	}
	if (diffY == 1 && position.x == to.x)
	{
		return board->isEmptyPosition(to);
	}
	return false;
}

bool Pawn::canAttack(const utils::Position& to, bool ignoreKing) const
{
	if (board->outOfBound(to))
	{
		return false;
	}
	size_t diffX = utils::ABS(position.x , to.x);
	size_t diffY = utils::ABS(position.y, to.y);
	bool isRightDirection = Color() == utils::Color::WHITE
						  ? to.y > position.y
						  : to.y < position.y;
	if (!isRightDirection)
		return false;
	if (diffY == 1 && diffX == 1)
	{
		return board->canKillFigure(to, *this, ignoreKing);
	}
	return false;
}

void Pawn::attack_(const utils::Position& to)
{
	position = to;
}

} //namespace chess