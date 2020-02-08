#pragma once
#include <vector>
#include <SFML/Network.hpp>

struct Packet
{
	size_t size;
	void* data;
};

const size_t MAX_PACKET_SIZE = 512;

class Sender
{
public:
	Sender() = default;
	virtual ~Sender() = default;
	virtual void send(Packet& packet) = 0;
};

class ServerEventHandler
{
public:
	ServerEventHandler() = default;
	virtual ~ServerEventHandler() = default;

	virtual void handleNewConnection(Sender& newClient) = 0;
	virtual void clientHasBeenDisconected() = 0;
private:

};

class Server final
{
public:
	Server(unsigned short port, ServerEventHandler* handler);
	~Server();
	void listen();
	void stopListen();
	std::vector<std::string> ipAddreses();

private:	
	unsigned short m_port;
	bool m_allowedToListen;
	bool m_threadIsAlive;
	void _listen();
	void _handleNewConnection();
	void _handleConnections();
	void _handleDisconnection(size_t clientIndex);
	void _broadcast(char* message, size_t messageSize);
	
	ServerEventHandler* m_handler;
	sf::TcpListener m_tcpListener;
	std::vector<sf::TcpSocket*> m_clients;
	sf::SocketSelector m_selector;
};

class ClientEventHandler
{
public:
	ClientEventHandler() = default;
	virtual ~ClientEventHandler() = default;
	virtual void packetReceiver(Packet& packet) = 0;
	virtual void onError(const std::string& message) = 0;
};



class Client final: public Sender
{
public:
	Client(ClientEventHandler* clientEventHandler);
	~Client();
	
	bool connect(const std::string& ipAddres, unsigned short port);
	void disconnect();

	virtual void send(Packet& packet) override;
	
	void listen();
	void stopListen();

private:
	void _listen();
	bool m_allowedToListen;
	bool m_threadIsAlive;

	ClientEventHandler* m_clientEventHandler;
	sf::TcpSocket m_tcpSocket;
};