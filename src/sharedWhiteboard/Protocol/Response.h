﻿/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

#pragma once

namespace Net
{
class Stream;
}

namespace wboard
{
namespace shared
{
	
class Response
{
public:

	virtual ~Response() = default;

	void	SerializeTo(Net::Stream& stream);

	void	DeserializeFrom(Net::Stream& stream);
};

}
}
