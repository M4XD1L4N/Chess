#pragma once

#include "figure.h"

namespace chess
{

class Queen : public Figure
{
public:
	Queen(Board* _board,
		  utils::Color _color,
		  const utils::Position& _position);
	Queen() = delete;
	Queen(const Queen&) = delete;
	Queen(Queen&&) = delete;
	virtual ~Queen() = default;

	Queen& operator=(const Queen&) = delete;
	Queen& operator=(Queen&&) = delete;

	virtual bool move(const utils::Position& to);
	virtual std::string ToString() const;

protected:
	virtual bool canMove(const utils::Position& to) const { return canAttack(to, false); }
	virtual bool canAttack(const utils::Position& to, bool ignoreKing) const;
	virtual void move_(const utils::Position& to) { attack_(to); }
	virtual void attack_(const utils::Position& to);
};

} //namespace chess
