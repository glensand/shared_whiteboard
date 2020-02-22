#include "WbSignalBoost.h"

namespace wboard
{
//------------------------------------------------------------------------------
void WbSignalBoost::Connect(const std::function<void()>& slot)
{
	m_sig.connect(slot);
}
//------------------------------------------------------------------------------
void WbSignalBoost::Emit()
{
	m_sig();
}
//------------------------------------------------------------------------------
}

