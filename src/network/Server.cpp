#include <iostream>
#include "Network.h"
#include "TcpSender.h"
#include <assert.h>
#include <thread>
#include <Windows.h>
TcpSender::TcpSender(sf::TcpSocket * tcpSocket):
	m_tcpSocket(tcpSocket)
{

}

void TcpSender::send(Packet & packet)
{
	m_tcpSocket->send(packet.data, packet.size);
}

Server::Server(unsigned short port, ServerEventHandler* handler) :
	m_handler(handler),
	m_allowedToListen(false),
	m_threadIsAlive(false),
	m_port(port)
{}

Server::~Server()
{
	stopListen();
}

void Server::listen()
{
	if (m_tcpListener.listen(m_port) != sf::Socket::Done)
	{
		return;
	}
	m_selector.add(m_tcpListener);
	m_allowedToListen = true;
	m_threadIsAlive = true;
	std::thread listener(&Server::_listen,this);
	listener.detach();
}
void Server::stopListen()
{
	m_allowedToListen = false;
	while (m_threadIsAlive)
	{
		Sleep(100);
	}
	m_tcpListener.close();
	m_clients.clear();
}

std::vector<std::string> Server::ipAddreses()
{
	std::vector<std::string> ipAdreses;
	for (const auto& i : m_clients)
		ipAdreses.push_back(i->getRemoteAddress().toString());
	return ipAdreses;
}

void Server::_handleNewConnection()
{
	sf::TcpSocket* client = new sf::TcpSocket;
	sf::Socket::Status status = m_tcpListener.accept(*client);
	if (status == sf::Socket::Done) 
	{
		m_clients.push_back(client);
		m_selector.add(*client);
		TcpSender newClient(client);
		m_handler->handleNewConnection(newClient);
	
	} else
		delete client;
	
}

void Server::_handleConnections()
{
	for (int i = 0; i < m_clients.size(); i++)
	{
		sf::TcpSocket& client = *m_clients[i];
		if (m_selector.isReady(client))
		{
			char buf[MAX_PACKET_SIZE];
			size_t receivedSize;
			if (client.receive(buf, MAX_PACKET_SIZE, receivedSize) != sf::Socket::Done)
			{
				_handleDisconnection(i);
				i--;
				continue;
			}
			_broadcast(buf, receivedSize);
		}
	}
}

void Server::_handleDisconnection(size_t clientIndex)
{
	sf::TcpSocket& client = *m_clients[clientIndex];
	m_selector.remove(client);
	m_clients.erase(m_clients.begin() + clientIndex);
	m_handler->clientHasBeenDisconected();
}

void Server::_broadcast(char * message, size_t messageSize)
{
	for (int j = 0; j < m_clients.size(); j++)
	{
		sf::TcpSocket& client = *m_clients[j];
		if (client.send(message, messageSize) != sf::Socket::Done)
			assert(false);
	}
}




void Server::_listen()
{
	while (m_allowedToListen && m_threadIsAlive)
	{
		if (m_selector.wait(sf::milliseconds(100)))
		{
			if (m_selector.isReady(m_tcpListener))
			{
				_handleNewConnection();
			}
			else
			{
				_handleConnections();
			}
		}
	}
	m_threadIsAlive = false;
}