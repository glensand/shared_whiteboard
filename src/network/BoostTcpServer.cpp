#include "BoostTcpServer.h"
#include <iostream>

namespace Net
{
//------------------------------------------------------------------------------	
BoostTcpServer::BoostTcpServer(size_t port)
	: m_acceptor(m_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    m_OnWriteCallback = [this](const boost::system::error_code&, size_t)
    {
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
    std::cout << "written" << std::endl;
}
//------------------------------------------------------------------------------	
void BoostTcpServer::Accept()
{
	// Это какой-то блин лямбда ад
	// ну нельзя так делать
    m_sessions.emplace_back();
    auto &session = *m_sessions.back();
    m_acceptor.async_accept(session.GetSocket(),
        [this, &session](boost::system::error_code ec)
        {
            if (!ec)
            {

                std::cout << "Accepted" << std::endl;
            	
                session.AwaitData(
                    [this, &session](const boost::system::error_code&, size_t)
                    {
                        std::cout << "Received" << std::endl;
                        Receive(session);
                    });
            }

            Accept();
        }
    );
}
//------------------------------------------------------------------------------
void BoostTcpServer::Receive(BoostTcpClient& client)
{
    std::lock_guard<std::mutex> guard(m_receiveLock);
	
    m_bufStream.clear();
    client.Receive(m_bufStream);
	
	for(const auto& session : m_sessions)
	{
		// TODO:: Добавить сравнение в клиент
		if(client.GetSocket().local_endpoint() != session->GetSocket().local_endpoint())
		{
            session->WriteAsync(m_bufStream, m_OnWriteCallback);
		}
	}
}
//------------------------------------------------------------------------------		
}
