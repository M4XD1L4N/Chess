#ifdef  RUN_UNIT_TESTS

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "board_factory.h"
#include "command_converter.h"
#include "utils.h"
#include "figure.h"

using namespace chess;
using namespace chess::utils;

Board& GetGlobalBoard()
{
	static auto globalBoard = BoardFactory::MakeBoard();
	return *globalBoard;
}


TEST_CASE("CommandConverter", "Test")
{
	Position from, to;
	CommandConverter::convert("e2,e4", from, to);
	REQUIRE(from == Position(4, 1));
	REQUIRE(to == Position(4, 3));
	REQUIRE(CommandConverter::convert("e2e4", from, to) == false);
}

struct Test
{
	std::string command;
	chess::Board::MoveResult result;
	FigureType figureType;
	utils::Color color;
	Board::GameState state;
};

void RunOkResult(std::shared_ptr<Board> board, const Test& test, chess::Board::MoveResult result)
{
	if (result == chess::Board::MoveResult::OK)
	{
		Position from, to;
		CommandConverter::convert(test.command, from, to);
		REQUIRE(board->Get(from) == nullptr);
		REQUIRE(board->Get(to) != nullptr);
		REQUIRE(board->Get(to)->Type() == test.figureType);
		REQUIRE(board->Get(to)->Color() == test.color);
		REQUIRE(board->State() == test.state);
	}
}

void RunTest(std::shared_ptr<Board> board, const Test& test)
{
	auto result = board->move(test.command);
	Position from, to;
	CommandConverter::convert(test.command, from, to);
	REQUIRE(result == test.result);
	RunOkResult(board, test, result);
}

void RunTests(const std::vector<Test>& tests)
{
	auto board = chess::BoardFactory::MakeBoard();
	for (auto test : tests)
	{
		RunTest(board, test);
	}
}

TEST_CASE("PawnTest", "Pawn Move")
{
	std::vector<Test> tests
		= { {"e2,e4", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
			{"d2,d4", chess::Board::MoveResult::INCORRECT_COLOR },
			{"e7,e5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK },
			{"d7,d5", chess::Board::MoveResult::INCORRECT_COLOR },
			{"d2,e4", chess::Board::MoveResult::INCORRECT_MOVE },
			{"a2,a3", chess::Board::MoveResult::OK,FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK },
			{"d7,d5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
			{"e4,d5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK }
	};
	RunTests(tests);
}

TEST_CASE("RookTest", "Rook Move")
{
	std::vector<Test> tests
	{
		{"h1,h3", chess::Board::MoveResult::INCORRECT_MOVE},
		{"h2,h4", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"h7,h5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"h1,h3", chess::Board::MoveResult::OK, FigureType::ROOK, utils::Color::WHITE, Board::GameState::OK},
		{"d7,d5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"h3,e3", chess::Board::MoveResult::OK, FigureType::ROOK, utils::Color::WHITE, Board::GameState::OK},
		{"a7,a5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"e3,e5", chess::Board::MoveResult::OK, FigureType::ROOK, utils::Color::WHITE, Board::GameState::OK},
		{"e7,e6", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"e5,e6", chess::Board::MoveResult::OK, FigureType::ROOK, utils::Color::WHITE, Board::GameState::SHAH},
	};

	RunTests(tests);

}
TEST_CASE("HorseTest", " Horse Move")
{
	std::vector<Test> tests
	{
		{"b1,c3", chess::Board::MoveResult::OK, FigureType::HORSE, utils::Color::WHITE, Board::GameState::OK},
		{ "b8,c6", chess::Board::MoveResult::OK, FigureType::HORSE, utils::Color::BLACK, Board::GameState::OK },
		{"c3,d3", chess::Board::MoveResult::INCORRECT_MOVE},
		{ "c3,a4", chess::Board::MoveResult::OK, FigureType::HORSE, utils::Color::WHITE, Board::GameState::OK },
		{ "c6,e5", chess::Board::MoveResult::OK, FigureType::HORSE, utils::Color::BLACK, Board::GameState::OK },
		{ "a4,c5", chess::Board::MoveResult::OK, FigureType::HORSE, utils::Color::WHITE, Board::GameState::OK },
		{ "e5,g4", chess::Board::MoveResult::OK, FigureType::HORSE, utils::Color::BLACK, Board::GameState::OK },
		{ "c5,a6", chess::Board::MoveResult::OK, FigureType::HORSE, utils::Color::WHITE, Board::GameState::OK },
		{ "g4,f6", chess::Board::MoveResult::OK, FigureType::HORSE, utils::Color::BLACK, Board::GameState::OK },
		{"a6,c7", chess::Board::MoveResult::OK, FigureType::HORSE, utils::Color::WHITE, Board::GameState::SHAH},
	};
	RunTests(tests);
}

TEST_CASE("KingTest", "King Move")
{

	std::vector<Test> tests
	{

		{ "e1,a2", chess::Board::MoveResult::INCORRECT_MOVE },
		{ "e1,a4", chess::Board::MoveResult::INCORRECT_MOVE },
		{ "e2,e4", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK },
		{ "e7,e5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK },
		{ "e1,e2", chess::Board::MoveResult::OK, FigureType::KING, utils::Color::WHITE, Board::GameState::OK },
		{ "e8,e7", chess::Board::MoveResult::OK, FigureType::KING, utils::Color::BLACK, Board::GameState::OK },
		{ "e2,d3", chess::Board::MoveResult::OK, FigureType::KING, utils::Color::WHITE, Board::GameState::OK },
		{ "e7,e6", chess::Board::MoveResult::OK, FigureType::KING, utils::Color::BLACK, Board::GameState::OK },
		//d3,d4 - bug
		{ "d3,c3", chess::Board::MoveResult::OK, FigureType::KING, utils::Color::WHITE, Board::GameState::OK }, //bug
		{ "e6,e5", chess::Board::MoveResult::INCORRECT_MOVE },
		{ "e6,f6", chess::Board::MoveResult::OK, FigureType::KING, utils::Color::BLACK, Board::GameState::OK },
	};
	RunTests(tests);
}


TEST_CASE("BlackPawnMove", "Black Move")
{
	std::vector<Test> tests
	{
		{"d2,d4", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"e7,e5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"d4,d5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"e5,e3", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e5,d4", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e5,f4", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e5,d5", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e5,f5", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e5,e6", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e5,d6", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e5,f6", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e5,e4", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"d5,d6", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"d7,d5", chess::Board::MoveResult::INCORRECT_MOVE},
	};

	RunTests(tests);
}

TEST_CASE("BlackPawnAttack", "Black Attack")
{
	std::vector<Test> tests
	{
		{"a2,a3", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"e7,e5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"a3,a4", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"e5,e4", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"a4,a5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"e4,e3", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"a5,a6", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"e3,e2", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e3,d2", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::SHAH},
		{"b2,b3", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"g7,g5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::SHAH},
		{"b3,b4", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"g5,g4", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::SHAH},
		{"b4,b5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"g4,g3", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::SHAH},
		{"b5,b6", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"g3,h2", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::SHAH},
	};

	RunTests(tests);
}


TEST_CASE("WhitePawnMove", "White Move")
{
	std::vector<Test> tests
	{
		{"e2,e4", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"a7,a5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"e4,e6", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e4,d4", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e4,f4", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e4,d5", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e4,f5", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e4,e3", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e4,d3", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e4,f3", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e4,e5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"a5,a4", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"e5,e6", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"a4,a3", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"a2,a4", chess::Board::MoveResult::INCORRECT_MOVE},
	};

	RunTests(tests);
}

TEST_CASE("WhitePawnAttack", "White Attack")
{
	std::vector<Test> tests
	{
		{"e2,e4", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"a7,a6", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"e4,e5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"a6,a5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"e5,e6", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::OK},
		{"a5,a4", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"e6,e7", chess::Board::MoveResult::INCORRECT_MOVE},
		{"e6,d7", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::SHAH},
		{"a4,a3", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"g2,g4", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::SHAH},
		{"b7,b6", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"g4,g5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::SHAH},
		{"b6,b5", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"g5,g6", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::SHAH},
		{"b5,b4", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
		{"g6,h7", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::WHITE, Board::GameState::SHAH},
		{"b4,b3", chess::Board::MoveResult::OK, FigureType::PAWN, utils::Color::BLACK, Board::GameState::OK},
	};

	RunTests(tests);
}


#endif //  RUN_UNIT_TESTS