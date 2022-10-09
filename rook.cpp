#include "rook.h"
#include "board.h"
#include <sstream>
#include <cstdlib>

namespace chess
{

Rook::Rook(Board* _board, utils::Color _color, const utils::Position& _position)
	:Figure(_board, utils::FigureType::ROOK, _color, _position)
{}

bool Rook::move(const utils::Position& to)
{
	utils::Position from = position;
	if (canMove(to))
	{
		move_(to);
		isFirstStep_ = false;
		board->onStepEnded(from, to, true);
		return true;
	}
	board->onStepEnded(from, to, false);
	return false;
}

void Rook::castling()
{
	auto from = Position();
	if (Position().x == 0)
	{
		position.x += 3;
	}
	else
		position.x -= 2;
	isFirstStep_ = false;
	board->updateBoard(from, position);
}

std::string Rook::ToString() const
{
	std::ostringstream oss;
	oss << utils::ToString(Color()) << "R";
	return oss.str();
}

bool Rook::canAttack(const utils::Position& to, bool ignoreKing) const
{
	if (board->outOfBound(to))
	{
		return false;
	}
	size_t diffX = utils::ABS(position.x , to.x);
	size_t diffY = utils::ABS(position.y, to.y);
	if ((diffX > 0 && position.y == to.y) || (diffY > 0 && position.x == to.x))
	{
		if (!board->isPathEmpty(position, to))
		{
			return false;
		}
		return board->isEmptyPosition(to) || board->canKillFigure(to, *this, ignoreKing);
	}
	return false;
}

void Rook::attack_(const utils::Position& to)
{
	position = to;
}

} //namespace chess