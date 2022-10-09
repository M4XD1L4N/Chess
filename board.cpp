#include "board.h"
#include <sstream>
#include "figure.h"
#include "king.h"
#include "rook.h"
#include "command_converter.h"
#include "utils.h"
#include <iostream>

namespace chess
{

Board::Board(const BoardMap& map)
: map_(map)
{}

void Board::subscribe(std::shared_ptr<Figure> figure)
{
	figures_[figure->Position()] = figure;
	std::shared_ptr<King> king = std::dynamic_pointer_cast<King>(figure);
	if (king)
	{
		if (king->Color() == utils::Color::WHITE)
			wKing_ = king;
		else
			bKing_ = king;
	}
}

Board::MoveResult Board::move(const std::string& comm)
{
	utils::Position from, to;
	if (!utils::CommandConverter::convert(comm, from, to))
	{
		return MoveResult::INCORRECT_COMM;
	}
	if (!figures_.contains(from))
		return MoveResult::INCORRECT_MOVE;
	auto figure = figures_.at(from);
	if (figure->Color() != step_)
	{
		return MoveResult::INCORRECT_COLOR;
	}
	return figure->move(to)
		 ? MoveResult::OK
		 : MoveResult::INCORRECT_MOVE;
}

std::string Board::ToString() const
{
	std::ostringstream oss;
	for (size_t idY = 0; idY < map_.size(); ++idY)
	{
		for (size_t idX = 0; idX < map_.size(); ++idX)
		{
			auto& pos = map_[idX][idY];
			oss << pos.GetColor();
			if (figures_.contains(pos))
			{
				oss << figures_.at(pos)->ToString();
			}
			oss << "\t";
		}
		oss << std::endl;
	}
	return oss.str();
}

bool Board::outOfBound(const utils::Position& to) const
{
	return to.x >= map_.size() || to.y >= map_.size();
}

bool Board::isEmptyPosition(const utils::Position& to) const
{
	return !figures_.contains(to);
}

bool Board::canKillFigure(const utils::Position& to,
						  const Figure& figure,
						  bool ignoreKing) const
{
	if (isEmptyPosition(to))
		return false;
	auto& figureOnPos = figures_.at(to);
	if (ignoreKing || figureOnPos->Type() != utils::FigureType::KING)
	{
		return figure.Color() != figureOnPos->Color();
	}
	//todo: what we do if our figure is king???
	return false;
}

bool Board::isPathEmpty(const utils::Position& from,
						const utils::Position& to) const
{
	utils::Position pos = utils::Position::Next(from, to);
	while (pos != to)
	{
		if (figures_.contains(pos))
		{
			return false;
		}
		pos = utils::Position::Next(pos, to);
	}
	return true;
}

bool Board::isNeigborKings(const King* _king, const utils::Position& to) const
{
	size_t diffX = 0;
	size_t diffY = 0;
	if (_king->Color() == utils::Color::WHITE)
	{
		diffX = utils::ABS(bKing_->Position().x, to.x);
		diffY = utils::ABS(bKing_->Position().y, to.y);
	}
	else
	{
		diffX = utils::ABS(wKing_->Position().x, to.x);
		diffY = utils::ABS(wKing_->Position().y, to.y);
	}
	return diffX<=1 && diffY<=1;
}

bool Board::canCastling(const King* _king, const utils::Position& to) const
{
	if (!isPathEmpty(_king->Position(), to))
	{
		return false;
	}

	std::shared_ptr<Figure> rook;
	if (to.x == 2 && figures_.contains(utils::Position(0, to.y)))
	{
		rook = figures_.at(utils::Position(0, to.y));
		if (!isPathEmpty(rook->Position(), to))
			return false;
	}
	else if(figures_.contains(utils::Position(7, to.y)))
	{
		rook = figures_.at(utils::Position(7, to.y));
	}
	std::shared_ptr<Rook> rook_t = std::dynamic_pointer_cast<Rook>(rook);
	if (rook_t && rook_t->Color() == _king->Color() && rook_t->isFirstStep())
	{
		return true;
	}
	return false;
}

void Board::castling(const King*, const utils::Position& to)
{
	std::shared_ptr<Figure> rook;
	if (to.x == 2 && figures_.contains(utils::Position(0, to.y)))
	{
		rook = figures_.at(utils::Position(0, to.y));
	}
	else if (figures_.contains(utils::Position(7, to.y)))
	{
		rook = figures_.at(utils::Position(7, to.y));
	}
	std::shared_ptr<Rook> rook_t = std::dynamic_pointer_cast<Rook>(rook);
	rook_t->castling();
}

void Board::onStepEnded(const utils::Position& from,
						const utils::Position& to,
						bool isSuccess)
{
	if (!isSuccess)
		return;
	updateBoard(from, to);
	updateGameState();
	step_ = step_ == utils::Color::WHITE
		  ? utils::Color::BLACK
		  : utils::Color::WHITE;
}

void Board::updateBoard(const utils::Position& from, const utils::Position& to)
{
	auto figureFromPos = figures_.at(from);
	std::shared_ptr<Figure> figureToPos;
	if(figures_.contains(to))
		figureToPos = figures_.at(to);
	if (figureToPos)
	{
		figures_.erase(to);
	}
	figures_.erase(from);
	figures_[to] = figureFromPos;
}

void Board::updateGameState()
{
	auto king = step_ == utils::Color::WHITE
			  ? bKing_ : wKing_;
	gameState_ = GameState::OK;
	if (IsPat(king->Color()))
	{
		gameState_ = GameState::PAT;
		return;
	}
	for (auto figure : figures_)
	{
		if (figure.second->Color() == king->Color())
			continue;
		king->updateShahState(*figure.second);
		if (king->IsShah())
		{
			gameState_ = GameState::SHAH;
			break;
		}
	}
}

}//namespace chess