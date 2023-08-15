#pragma once

#include "GenericChain.h"
#include "Chainable.h"

namespace cw::Filter {
	template <class FirstChainable, class... OtherChainables>
	class EffectChain : public GenericChain<Chainable, FirstChainable, OtherChainables> {

	};

} // cw::Filter