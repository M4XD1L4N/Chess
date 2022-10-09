#pragma once

#include "figure.h"

namespace chess
{

class Pawn : public Figure
{
public:
	Pawn(Board* _board,
		 utils::Color _color,
		 const utils::Position& _position);
	Pawn() = delete;
	Pawn(const Figure&) = delete;
	Pawn(Figure&&) = delete;
	virtual ~Pawn() = default;

	Pawn& operator=(const Pawn&) = delete;
	Pawn& operator=(Pawn&&) = delete;

	virtual bool move(const utils::Position& to);
	virtual std::string ToString() const;

	bool isFirstStep() const { return isFirstStep_; };
protected:
	virtual bool canMove(const utils::Position& to) const;
	virtual bool canAttack(const utils::Position& to, bool ignoreKing) const;
	virtual void move_(const utils::Position& to) { attack_(to); }
	virtual void attack_(const utils::Position& to);
private:
	bool isFirstStep_ = true;
};

} //namespace chess