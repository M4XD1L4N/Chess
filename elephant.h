#pragma once

#include "figure.h"

namespace chess
{

class Elephant : public Figure
{
public:
	Elephant(Board* _board,
		utils::Color _color,
		const utils::Position& _position);
	Elephant() = delete;
	Elephant(const Elephant&) = delete;
	Elephant(Elephant&&) = delete;
	virtual ~Elephant() = default;

	Elephant& operator=(const Elephant&) = delete;
	Elephant& operator=(Elephant&&) = delete;

	virtual bool move(const utils::Position& to);
	virtual std::string ToString() const;

protected:
	virtual bool canMove(const utils::Position& to) const { return canAttack(to, false); }
	virtual bool canAttack(const utils::Position& to, bool ignoreKing) const;
	virtual void move_(const utils::Position& to) { attack_(to); }
	virtual void attack_(const utils::Position& to);
};

} //namespace chess
