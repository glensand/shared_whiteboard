#include "BoostTcpServer.h"
#include <iostream>

namespace Net
{
//------------------------------------------------------------------------------	
BoostTcpServer::BoostTcpServer(size_t port)
	: m_acceptor(m_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    m_OnWriteCallback = [this](const boost::system::error_code&, size_t count)
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
                    [this, session](const boost::system::error_code&, size_t)
                    {
                        Receive(session);
                    });
            }

            Accept();
        }
    );
}
//------------------------------------------------------------------------------
void BoostTcpServer::Receive(BoostTcpSession* client)
{
    std::cout << "BoostTcpServer::Receive" << std::endl;
	
    std::lock_guard<std::mutex> guard(m_receiveLock);
	
    m_bufStream = std::stringstream();
    client->Receive(m_bufStream);
	
	for(const auto& session : m_sessions)
	{
		// TODO:: Добавить сравнение в сессию
		if(session->IsInitialized()/* && 
            client->GetSocket().local_endpoint() != session->GetSocket().local_endpoint()*/)
		{
            std::cout << m_bufStream.rdbuf();
            session->WriteAsync(reinterpret_cast<const char*>(m_bufStream.rdbuf()), m_bufStream.tellp(), m_OnWriteCallback);
           // session->WriteAsync(b, 1000, m_OnWriteCallback);

            std::cout << "BoostTcpServer::Receive session->WriteAsync" << std::endl;
		}
	}

	// Копипаста
    client->AwaitData([this, client](const boost::system::error_code&, size_t)
        {
            Receive(client);
        });
}
//------------------------------------------------------------------------------		
}
