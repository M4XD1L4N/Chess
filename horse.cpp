#include "horse.h"
#include "board.h"
#include <sstream>
#include <cstdlib>
//#undef abs()
namespace chess
{

Horse::Horse(Board* _board, utils::Color _color, const utils::Position& _position)
: Figure(_board, utils::FigureType::HORSE, _color, _position)
{}

bool Horse::move(const utils::Position& to)
{
	utils::Position from = position;
	bool isMoved = canMove(to);
	if (isMoved)
	{
		move_(to);
	}
	board->onStepEnded(from, to, isMoved);
	return isMoved;
}

std::string Horse::ToString() const
{
	std::ostringstream oss;
	oss << utils::ToString(Color()) << "H";
	return oss.str();
}

bool Horse::canAttack(const utils::Position& to, bool ignoreKing) const
{
	if (board->outOfBound(to))
	{
		return false;
	}
	size_t diffX = utils::ABS(position.x , to.x);
	size_t diffY = utils::ABS(position.y, to.y);
	if ((diffX == 2 && diffY == 1)
		|| (diffY == 2 && diffX == 1)
	)
	{
		return board->isEmptyPosition(to) || board->canKillFigure(to, *this, ignoreKing);
	}
	return false;
}

void Horse::attack_(const utils::Position& to)
{
	position = to;
}

} //namespace chess