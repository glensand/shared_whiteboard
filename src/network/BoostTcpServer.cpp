#include "BoostTcpServer.h"

#include "Configure.h"

#include <iostream>

namespace Net
{
//------------------------------------------------------------------------------	
BoostTcpServer::BoostTcpServer(const std::string& port)
	: m_acceptor(m_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), std::stoi(port)))
{
}
//------------------------------------------------------------------------------	
void BoostTcpServer::AwaitConnections(const ServerOnActionCallback& connectionHandler)
{
    auto session = new BoostTcpSession(m_service);
    m_sessions.emplace(m_sessionCounter, session);

    if constexpr (DEBUG_PRINT)
        std::cout << "BoostTcpServer::Accept()" << std::endl;

    m_acceptor.async_accept(session->GetSocket(),
        [=](boost::system::error_code ec)
        {
            if (!ec)
            {
                if constexpr (DEBUG_PRINT)
                    std::cout << "Accepted" << std::endl;

                session->SetInitialized(true);
                session->GetSocket().set_option(boost::asio::ip::tcp::no_delay(true));

                connectionHandler(m_sessionCounter - 1);
            }
        }
    );

    ++m_sessionCounter;
}
//------------------------------------------------------------------------------
void BoostTcpServer::AwaitData(int clientId, const OnActionCallback& dataReceiveHandler)
{
    const auto& session = FindSession(clientId);
    session->AwaitData(dataReceiveHandler);
}
//------------------------------------------------------------------------------
void BoostTcpServer::Receive(std::ostream& stream, size_t count, int clientId)
{
    const auto& session = FindSession(clientId);
	session->Receive(stream, count);
}
//------------------------------------------------------------------------------
void BoostTcpServer::Send(const void* data, size_t size, int clientId)
{
    const auto& session = FindSession(clientId);
    session->Write(data, size);
}
//------------------------------------------------------------------------------
void BoostTcpServer::SendAsync(const void* data, size_t size, int clientId, const OnActionCallback& callback)
{
    const auto& session = FindSession(clientId);
    session->WriteAsync(data, size, callback);
}
//------------------------------------------------------------------------------
void BoostTcpServer::Send(const void* data, size_t size)
{
    for (const auto& [id, session] : m_sessions)
        session->Write(data, size);	
}
//------------------------------------------------------------------------------
void BoostTcpServer::SendAsync(const void* data, size_t size, const OnActionCallback& callback)
{
    for (const auto& [id, session] : m_sessions)
        session->WriteAsync(data, size, callback);
}
//------------------------------------------------------------------------------	
const Session& BoostTcpServer::FindSession(size_t id) const
{
    const auto session = m_sessions.find(id);
    if (session == m_sessions.end()) throw std::exception("session doesn't exist");
    return session->second;
}
//------------------------------------------------------------------------------	
}
