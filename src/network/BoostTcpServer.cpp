#include "BoostTcpServer.h"
#include <iostream>

namespace Net
{
//------------------------------------------------------------------------------	
BoostTcpServer::BoostTcpServer(size_t port)
	: m_acceptor(m_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    m_OnWriteCallback = [this](size_t count)
    {
        std::cout << "m_OnWriteCallback count: " << count << std::endl;
        OnWrite();
    };
}
//------------------------------------------------------------------------------
void BoostTcpServer::Run()
{
    Accept();
	
    m_service.run();
}
//------------------------------------------------------------------------------
void BoostTcpServer::OnWrite()
{
    std::cout << "BoostTcpServer::OnWrite" << std::endl;
}
//------------------------------------------------------------------------------	
void BoostTcpServer::Accept()
{
	// Это какой-то блин лямбда ад
	// ну нельзя так делать
    auto session = new BoostTcpSession(m_service);
    m_sessions.emplace_back(session);
	
    std::cout << "BoostTcpServer::Accept()" << std::endl;
	
    m_acceptor.async_accept(session->GetSocket(),
        [this, session](boost::system::error_code ec)
        {
            if (!ec)
            {
                std::cout << "Accepted" << std::endl;
                session->SetInitialized(true);
                session->GetSocket().set_option(boost::asio::ip::tcp::no_delay(true));
            	
                session->AwaitData(
                    [this, session](size_t count)
                    {
                        std::cout << "Await read_async count: " << count << std::endl;
                        Receive(session, count);
                    });
            }

            Accept();
        }
    );
}
//------------------------------------------------------------------------------
void BoostTcpServer::Receive(BoostTcpSession* client, size_t count)
{
    std::cout << "BoostTcpServer::Receive" << std::endl;
	
    std::lock_guard<std::mutex> guard(m_receiveLock);
	
    std::stringstream stream;
    client->Receive(stream, count);
    m_bufStream = stream.rdbuf()->str();
	
	for(const auto& session : m_sessions)
	{
		// TODO:: Добавить сравнение в сессию
		if(session->IsInitialized()/* && 
            client->GetSocket().local_endpoint() != session->GetSocket().local_endpoint()*/)
		{
            session->WriteAsync(reinterpret_cast<const char*>(m_bufStream.c_str()), m_bufStream.size(), m_OnWriteCallback);

            std::cout << "BoostTcpServer::Receive session->WriteAsync" << std::endl;
		}
	}

	// Копипаста
    client->AwaitData([this, client](size_t count)
        {
            Receive(client, count);
        });
}
//------------------------------------------------------------------------------		
}
