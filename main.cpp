#ifndef RUN_UNIT_TESTS

#include "board_factory.h"
#include "command_converter.h"
#include "utils.h"
#include <iostream>

int main()
{
	auto board = chess::BoardFactory::MakeBoard();
	std::string command;
	while (!board->IsGameEnded())
	{
		std::cout << board->ToString() << std::endl;
		getline(std::cin, command);
		auto result = board->move(command);
		system("cls");
		switch (result)
		{
		case chess::Board::MoveResult::INCORRECT_COMM: std::cout << "Invalid command. try again" << std::endl; break;
		case chess::Board::MoveResult::INCORRECT_MOVE: std::cout << "Invalid move. try again" << std::endl; break;
		case chess::Board::MoveResult::INCORRECT_COLOR: std::cout << "Invalid color. try again" << std::endl; break;
		case chess::Board::MoveResult::OK: std::cout << "Step \""<< command <<"\" provided" << std::endl; break;
		}
	}

	return 0;
}



#endif //RUN_UNIT_TESTS
