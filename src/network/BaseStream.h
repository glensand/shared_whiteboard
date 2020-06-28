//------------------------------------------------------------------------------
// BaseStream.h
//
// BaseStream implements...
//
// Copyright (c) 2020 glensand
// All rights reserved.
//
// Date: 27.02.2020
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------

#pragma once

#include "Stream.h"
#include <sstream>

namespace Net
{
	
class BaseStream : public Stream
{
public:

	BaseStream() = default;
	virtual ~BaseStream() = default;

	// Stream implementation
	void	Write(const void* data, size_t count) override;

	void	Read(void* data, size_t count) override;

protected:
    [[nodiscard]] std::string	GetString() const;
	std::stringstream			m_stream;
};

}

