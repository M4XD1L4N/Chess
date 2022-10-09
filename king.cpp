#include "king.h"
#include "board.h"
#include <sstream>
#include <cstdlib>

namespace chess
{

King::King(Board* _board, utils::Color _color, const utils::Position& _position)
: Figure(_board, utils::FigureType::KING, _color, _position)
{}

bool King::move(const utils::Position& to)
{
	utils::Position from = position;
	if (canMove(to))
	{
		move_(to);
		isFirstStep_ = false;
		board->onStepEnded(from, to, true);
		return true;
	}
	else if (canCastling(to))
	{
		move_(to);
		isFirstStep_ = false;
		board->castling(this, to);
		board->onStepEnded(from, to, true);
		return true;
	}

	board->onStepEnded(from, to, false);
	return false;
}

std::string King::ToString() const
{
	std::ostringstream oss;
	oss << utils::ToString(Color()) << "K";
	return oss.str();
}

void King::updateShahState(const Figure& figure)
{
	if (figure.Type() == utils::FigureType::KING)
		return;
	if (figure.Color() != Color())
		isShah = figure.canAttack(position, true);
}

bool King::canCastling(const utils::Position& to) const
{
	if (board->outOfBound(to))
	{
		return false;
	}
	size_t diffX = utils::ABS(position.x , to.x);
	size_t diffY = utils::ABS(position.y, to.y);
	if (diffX == 2 && diffY == 0 && isFirstStep_)
	{
		return !board->isNeigborKings(this, to) && board->canCastling(this, to);
	}

	return false;
}

bool King::canAttack(const utils::Position& to, bool ignoreKing) const
{
	if (board->outOfBound(to))
	{
		return false;
	}
	size_t diffX = utils::ABS(position.x , to.x);
	size_t diffY = utils::ABS(position.y, to.y);
	//ifFirstStep we can do castling
	if (diffX <= 1 && diffY <= 1)
	{
		return !board->isNeigborKings(this, to)
			&& (board->isEmptyPosition(to) || board->canKillFigure(to, *this, false));
	}
	return false;
}

void King::attack_(const utils::Position& to)
{
	position = to;
}

} //namespace chess