#pragma once

#include "figure.h"

namespace chess
{

class Horse : public Figure
{
public:
	Horse(Board* _board,
		  utils::Color _color,
		  const utils::Position& _position);

	Horse() = delete;
	Horse(const Horse&) = delete;
	Horse(Horse&&) = delete;
	virtual ~Horse() = default;

	Horse& operator=(const Horse&) = delete;
	Horse& operator=(Horse&&) = delete;

	virtual bool move(const utils::Position& to);
	virtual std::string ToString() const;

protected:
	virtual bool canMove(const utils::Position& to) const { return canAttack(to, false); }
	virtual bool canAttack(const utils::Position& to, bool ignoreKing) const;
	virtual void move_(const utils::Position& to) { attack_(to); }
	virtual void attack_(const utils::Position & to);
};

} //namespace chess