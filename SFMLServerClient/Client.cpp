#include "Network.h"
#include <string.h>
#include <iostream>
#include <thread>

#include <Windows.h>

Client::Client(ClientEventHandler* clientEventHandler) :
	m_clientEventHandler(clientEventHandler)
{

}

Client::~Client()
{
	stopListen();
}

bool Client::connect(const std::string & ipAddres, unsigned short port)
{
	sf::Socket::Status status = m_tcpSocket.connect(ipAddres, port);
	if (status != sf::Socket::Done)
	{
		return false;
	}
	return true;
}

void Client::disconnect()
{
	m_tcpSocket.disconnect();
}

void Client::send(Packet& packet)
{
	m_tcpSocket.send(packet.data,packet.size);
}

void Client::listen()
{
	m_allowedToListen = true;
	m_threadIsAlive = true;
	std::thread listener(&Client::_listen, this);
	listener.detach();
}

void Client::stopListen()
{
	m_allowedToListen = false;
	while (m_threadIsAlive)
	{
		Sleep(100);
	}
}

void Client::_listen()
{
	while (m_allowedToListen&&m_threadIsAlive)
	{
		char buf[MAX_PACKET_SIZE];
		size_t receivedSize;
		
		if (m_tcpSocket.receive(buf, MAX_PACKET_SIZE, receivedSize) != sf::Socket::Done)
		{
			m_clientEventHandler->onError("something Bad");
			break;
		}
		Packet receivedPacket;
		receivedPacket.size = receivedSize;
		receivedPacket.data = buf;
		m_clientEventHandler->packetReceiver(receivedPacket);
	}
	m_threadIsAlive = false;
}




