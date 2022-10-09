#pragma once

#include "figure.h"

namespace chess
{

class King : public Figure
{
public:
	King(Board* _board,
		utils::Color _color,
		const utils::Position& _position);
	King() = delete;
	King(const Figure&) = delete;
	King(Figure&&) = delete;
	virtual ~King() = default;

	King& operator=(const King&) = delete;
	King& operator=(King&&) = delete;

	virtual bool move(const utils::Position& to);
	virtual std::string ToString() const;
	
	bool IsShah() const { return isShah; }
	void updateShahState(const Figure& figure);

	bool isFirstStep() const { return isFirstStep_; };
protected:
	bool canCastling(const utils::Position& to) const;
	virtual bool canMove(const utils::Position& to) const { return canAttack(to, false); }
	virtual bool canAttack(const utils::Position& to, bool ignoreKing) const;
	virtual void move_(const utils::Position& to) { attack_(to); }
	virtual void attack_(const utils::Position& to);
private:
	bool isFirstStep_ = true;
	bool isShah = false;
};

} //namespace chess
