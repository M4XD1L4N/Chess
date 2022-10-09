#pragma once

#include "utils.h"
#include <array>
#include <string>
#include <memory>
#include <map>

namespace chess
{

class Figure;
class King;

class Board
{
public:
	using BoardLine = std::array<utils::Position, 8>;
	using BoardMap  = std::array<BoardLine, 8>;
	using Figures = std::map<utils::Position, std::shared_ptr<Figure>>;//, utils::HashPosition, utils::HashPosition>;
	
	enum class MoveResult
	{
		INCORRECT_COMM,
		INCORRECT_MOVE,
		INCORRECT_COLOR,
		OK
	};

	enum class GameState
	{
		SHAH,
		MAT,
		PAT,
		OK  

	};

public:
	Board(const BoardMap& map);
	~Board() = default;

	void subscribe(std::shared_ptr<Figure>);

	MoveResult move(const std::string& comm);

	std::string ToString() const;
	bool outOfBound(const utils::Position& to) const;
	bool isEmptyPosition(const utils::Position& to) const;
	bool canKillFigure(const utils::Position& to, const Figure&, bool ignoreKing) const;
	bool isPathEmpty(const utils::Position& from,
					 const utils::Position& to) const;
	bool isNeigborKings(const King*,
						const utils::Position& to) const;
	bool canCastling(const King*,
					 const utils::Position& to) const;
	void castling(const King*,
				  const utils::Position& to);
	void onStepEnded(const utils::Position& from,
					 const utils::Position& to,
					 bool isSuccess);
	void updateBoard(const utils::Position& from,
					 const utils::Position& to);
	void updateGameState();

	std::shared_ptr<Figure> Get(const utils::Position& pos) { return figures_.contains(pos)
																   ? figures_.at(pos)
																   : nullptr;
	}

	bool IsGameEnded() const { return gameState_ == GameState::PAT
								   || gameState_ == GameState::MAT; }


	GameState State() const { return gameState_; }
private:
	bool IsPat(utils::Color) const { return false; }

private:
	BoardMap map_;
	Figures figures_;
	std::shared_ptr<King> wKing_;
	std::shared_ptr<King> bKing_;
	GameState gameState_ = GameState::OK;
	utils::Color step_ = utils::Color::WHITE;
};

} //namespace chess