#include "sharedWhiteboard/SharedWhiteboardClient.h"
#include "whiteboard/WhiteBoardCV.h"
#include "sharedWhiteboard/WhiteboardServer.h"
#include "network/BoostTcpStream.h"

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
		
		Net::WhiteboardServer server(1111);
		server.Run();

		std::cout << "Server finished" << std::endl;
	}
	else
	{
		// Client

		std::cout << "Client" << std::endl;
		
		wboard::SharedWhiteboardClient board(std::make_unique<wboard::WhiteBoardCv>(), 
			Net::StreamPtr(new Net::BoostTcpStream(argv[2], "1111")));
		
		board.Run();

		std::cout << "Client finished" << std::endl;
	}

	int t;
	std::cin >> t;
}
