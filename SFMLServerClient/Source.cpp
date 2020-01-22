#include <SFML/Network.hpp>
#include <iostream>
#include "Network.h"
#include <thread>
using namespace std;

void coutHandler(Packet& packet)
{
	cout << "received " << packet.size << "bytes" << endl;
	char* data = (char*)(packet.data);
	cout << string(data) << endl;
}

void listen(Client& client)
{
	bool rdy = true;
	client.listen(coutHandler, rdy);
}

int main()
{
	Server server(5000);
	bool rdy = true;
	server.listen(rdy);
	/*Client client;
	if (!client.connect("192.168.127.216", 5000))
	{
		cout << "Can not connect" << endl;
		return -1;
	}
	
	std::thread list(listen, std::ref(client));
	while (true)
	{
		char buf[10];
		cin >> buf;
		client.send(buf, 10);
	}
	list.join();*/


	return 0;
}
