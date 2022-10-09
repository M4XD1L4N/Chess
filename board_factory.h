#pragma once

#include "board.h"
#include <memory>

namespace chess
{

class BoardFactory
{
public:
	static std::shared_ptr<Board> MakeBoard();

private:
	static void MakeMap(Board::BoardMap&);
	static void MakeHorses(std::shared_ptr<Board>);
	static void MakeRooks(std::shared_ptr<Board>);
	static void MakeElephants(std::shared_ptr<Board>);
	static void MakeQueens(std::shared_ptr<Board>);
	static void MakeKings(std::shared_ptr<Board>);
	static void MakePawns(std::shared_ptr<Board>);
};

} // namespace chess