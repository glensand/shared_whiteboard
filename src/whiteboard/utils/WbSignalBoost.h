//------------------------------------------------------------------------------
// WbSlotBoost.h
//
// WbSlotBoost implements...
//
// Copyright (c) 2020 Afti
// All rights reserved.
//
// Date: dd.mm.2020
// Author: glensand
//------------------------------------------------------------------------------
#pragma once

#include "WbSignal.h"
#include <boost/signals2.hpp>

namespace wboard
{
	
class WbSignalBoost final : public IWbSignal
{
public:
	WbSignalBoost() = default;
	virtual ~WbSignalBoost() = default;

	void	Connect(const std::function<void()>& slot) override;

	void	Emit() override;

private:
	boost::signals2::signal<void()>		m_sig;
};

}
