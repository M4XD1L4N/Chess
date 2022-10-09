#pragma once

#include "utils.h"
#include <string>

namespace chess
{

class Board;

class Figure
{
public:
	Figure(Board* _board,
		   utils::FigureType _type,
		   utils::Color _color,
		   const utils::Position& _position)
	: board(_board)
	, type(_type)
	, color(_color)
	, position(_position)
	{}
	Figure() = delete;
	Figure(const Figure&) = delete;
	Figure(Figure&&) = delete;
	virtual ~Figure() = default;

	Figure& operator=(const Figure&) = delete;
	Figure& operator=(Figure&&) = delete;

	virtual bool move(const utils::Position& to) = 0;
	virtual std::string ToString() const = 0;

	const utils::Position& Position() const { return position; }
	utils::FigureType Type() const { return type; }
	utils::Color Color() const { return color; }

	virtual bool canAttack(const utils::Position& to, bool ignoreKing) const = 0;
protected:
	virtual bool canMove(const utils::Position& to) const = 0;
	virtual void move_(const utils::Position& to) = 0;
	virtual void attack_(const utils::Position& to) = 0;

protected:
	Board* board = nullptr;
	const utils::FigureType type = utils::FigureType::PAWN;
	const utils::Color color = utils::Color::WHITE;
	utils::Position position;
};

} //namespace chess