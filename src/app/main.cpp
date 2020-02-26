#include "sharedWhiteboard/SharedWhiteboardClient.h"
#include "whiteboard/WhiteBoardCV.h"
#include "network/BoostTcpServer.h"

#include <iostream>

int main(int argc, char* argv[])
{	
	if(argc < 2)
	{
		std::cout << "use:" << "[mode = {-server, -client}]" << std::endl;
		std::cout << "if client mode enabled, also should be written server ip";

		return -1;
	}

	const std::string mode = argv[1];
	const std::string serverMode = "-server";
	
	if(mode == serverMode)
	{	
		// Server

		std::cout << "Server" << std::endl;
		
		Net::BoostTcpServer server(1111);
		server.Run();

		std::cout << "Server finished" << std::endl;
	}
	else
	{
		// Client

		std::cout << "Client" << std::endl;
		
		wboard::shared::SharedWhiteboardClient board(wboard::WhiteBoard(new wboard::WhiteBoardCv()), argv[2], "1111");
		board.Run();

		std::cout << "Client finished" << std::endl;
	}

	int t;
	std::cin >> t;
}
