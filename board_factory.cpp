#include "board_factory.h"
#include "horse.h"
#include "rook.h"
#include "elephant.h"
#include "queen.h"
#include "pawn.h"
#include "king.h"
#include "command_converter.h"

namespace chess
{

std::shared_ptr<Board> BoardFactory::MakeBoard()
{
	Board::BoardMap map;
	MakeMap(map);
	auto result = std::make_shared<Board>(map);
	MakeHorses(result);
	MakeRooks(result);
	MakeElephants(result);
	MakeQueens(result);
	MakeKings(result);
	MakePawns(result);
	return result;
}

void  BoardFactory::MakeMap(Board::BoardMap& map)
{
	for (size_t idY = 0; idY < map.size(); ++idY)
	{
		for (size_t idX = 0; idX < map[idY].size(); ++idX)
		{
			map[idY][idX] = {idX,
							 idY,
							 (idX + idY) % 2 == 0
							 ? utils::Color::WHITE
							 : utils::Color::BLACK};
		}
	}
}

void BoardFactory::MakeHorses(std::shared_ptr<Board> board)
{
	auto horse1 = std::make_shared<Horse>(board.get(),
										  utils::Color::WHITE,
										  utils::CommandConverter::convertPosition("b1"));
	auto horse2 = std::make_shared<Horse>(board.get(),
										  utils::Color::WHITE,
										  utils::CommandConverter::convertPosition("g1"));
	auto horse3 = std::make_shared<Horse>(board.get(),
										  utils::Color::BLACK,
										  utils::CommandConverter::convertPosition("b8"));
	auto horse4 = std::make_shared<Horse>(board.get(),
										  utils::Color::BLACK,
										  utils::CommandConverter::convertPosition("g8"));
	board->subscribe(horse1);
	board->subscribe(horse2);
	board->subscribe(horse3);
	board->subscribe(horse4);

}

void BoardFactory::MakeRooks(std::shared_ptr<Board> board)
{
	auto rook1 = std::make_shared<Rook>(board.get(),
										utils::Color::WHITE,
										utils::CommandConverter::convertPosition("a1"));
	auto rook2 = std::make_shared<Rook>(board.get(),
										utils::Color::WHITE,
										utils::CommandConverter::convertPosition("h1"));
	auto rook3 = std::make_shared<Rook>(board.get(),
										utils::Color::BLACK,
										utils::CommandConverter::convertPosition("a8"));
	auto rook4 = std::make_shared<Rook>(board.get(),
										utils::Color::BLACK,
										utils::CommandConverter::convertPosition("h8"));
	board->subscribe(rook1);
	board->subscribe(rook2);
	board->subscribe(rook3);
	board->subscribe(rook4);
}

void BoardFactory::MakeElephants(std::shared_ptr<Board> board)
{
	auto eleph1 = std::make_shared<Elephant>(board.get(),
											 utils::Color::WHITE,
											 utils::CommandConverter::convertPosition("c1"));
	auto eleph2 = std::make_shared<Elephant>(board.get(),
											 utils::Color::WHITE,
											 utils::CommandConverter::convertPosition("f1"));
	auto eleph3 = std::make_shared<Elephant>(board.get(),
											 utils::Color::BLACK,
											 utils::CommandConverter::convertPosition("c8"));
	auto eleph4 = std::make_shared<Elephant>(board.get(),
											 utils::Color::BLACK,
											 utils::CommandConverter::convertPosition("f8"));
	board->subscribe(eleph1);
	board->subscribe(eleph2);
	board->subscribe(eleph3);
	board->subscribe(eleph4);
}

void BoardFactory::MakeQueens(std::shared_ptr<Board> board)
{
	auto queen1 = std::make_shared<Queen>(board.get(),
										  utils::Color::WHITE,
										  utils::CommandConverter::convertPosition("d1"));
	auto queen2 = std::make_shared<Queen>(board.get(),
										  utils::Color::BLACK,
										  utils::CommandConverter::convertPosition("d8"));
	board->subscribe(queen1);
	board->subscribe(queen2);
}

void BoardFactory::MakeKings(std::shared_ptr<Board> board)
{
	auto king1 = std::make_shared<King>(board.get(),
										utils::Color::WHITE,
										utils::CommandConverter::convertPosition("e1"));
	auto king2 = std::make_shared<King>(board.get(),
										utils::Color::BLACK,
										utils::CommandConverter::convertPosition("e8"));
	board->subscribe(king1);
	board->subscribe(king2);
}

void BoardFactory::MakePawns(std::shared_ptr<Board> board)
{
	for (int i = 0; i <= 7; ++i)
	{
		std::string sym(1, ('a' + i));
		auto pawnW = std::make_shared<Pawn>(board.get(),
											utils::Color::WHITE,
											utils::CommandConverter::convertPosition(sym+"2"));
		board->subscribe(pawnW);

		auto pawnB = std::make_shared<Pawn>(board.get(),
											utils::Color::BLACK,
											utils::CommandConverter::convertPosition(sym + "7"));
		board->subscribe(pawnB);
	}
}

} // namespace chess