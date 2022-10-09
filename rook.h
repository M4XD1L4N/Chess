#pragma once

#include "figure.h"

namespace chess
{

class Rook : public Figure
{
public:
	Rook(Board* _board,
		utils::Color _color,
		const utils::Position& _position);
	Rook() = delete;
	Rook(const Rook&) = delete;
	Rook(Rook&&) = delete;
	virtual ~Rook() = default;

	Rook& operator=(const Rook&) = delete;
	Rook& operator=(Rook&&) = delete;

	virtual bool move(const utils::Position& to);
	void castling();
	virtual std::string ToString() const;

	bool isFirstStep() const { return isFirstStep_; }

protected:
	virtual bool canMove(const utils::Position& to) const { return canAttack(to, false); }
	virtual bool canAttack(const utils::Position& to, bool ignoreKing) const;
	virtual void move_(const utils::Position& to) { attack_(to); }
	virtual void attack_(const utils::Position& to);
private:
	bool isFirstStep_ = true;
};

} //namespace chess