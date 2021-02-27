/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

#pragma once

#include "whiteboard/Whiteboard.h"
#include "network/Stream.h"
#include <thread>

namespace wboard
{

class SharedWhiteboardClient
{
public:

	SharedWhiteboardClient(WhiteBoard&& wb, Net::StreamPtr&& stream);
	virtual ~SharedWhiteboardClient();

	void	Run();
	
private:
	void	Send(const Shape&);
	void	RunStreamListening();

	std::thread							m_listenerThread;
	std::function<void(const Shape&)>	m_onDrawCallback;
	WhiteBoard							m_whiteBoard;

	Net::StreamPtr						m_stream;
};

}
