/* Copyright (C) 2020 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/visual-studio-compatibility
 */

#pragma once

#include "ISerializerInner.h"

namespace wboard
{

class ShapeSerializerBase : public ISerializerInner
{
public:
	void				Serialize(Net::Stream& stream, const Shape& shape) const final;
	Shape				Deserialize(Net::Stream& stream) const final;

	void				AddNext(Serializer&& ser) final;
	const Serializer&	GetNext() const final;
	
protected:
	Shape				Deserialize(Net::Stream& stream, ShapeType type) const final;
	
	static ShapeType	DeserializeType(Net::Stream& stream);
	static void			SerializeType(Net::Stream& stream, ShapeType type);
	
	virtual	bool		CanBeProcessed(ShapeType type) const = 0;

	virtual void		SerializeImpl(Net::Stream& stream, const Shape& shape) const = 0;
	virtual Shape		DeserializeImpl(Net::Stream& stream) const = 0;

private:
	Serializer			m_next;
};
	
}
