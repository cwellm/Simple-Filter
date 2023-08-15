#pragma once

#include <map>
#include <vector>
#include <stdexcept>

#include "Filter.h"
#include "Chainable.h"
#include "GenericChain.h"

/*
* TODO: Implement full graph algorithm!!! Up to now, ONLY LINEAR CHAIN IS IMPLEMENTED!!!
*/
namespace cw::Filter {

	/*
	* This is a common base class for all types of filters which consist of multiple elementary filters, in row and
	* in parallel. For instance, a BP filter is usually a combination of a biquad LP and HP. The FilterChain shall itself
	* be chainable, so it inherits from Chainable. It is not a filter itself, since it does not possess an own ring
	* buffer (it doesn't need to), so does not have a filter state itself.
	*/
	template <class FirstChainable, class... OtherChainables>
	class FilterChain : public GenericChain<Filter, FirstChainable, OtherChainables...> {

		// std::map<int, std::vector<int>> as first arg. then I need a traversing algorithm - probably put this into
		// an extra class? or put it here??? 
		// then template <std::map, Chainable...> or so?
	public:
		explicit FilterChain(std::map<int, std::vector<int>> filterGraph): filterGraph(filterGraph) {
			isChain = true;
		}

		explicit FilterChain() : FilterChain(std::map<int, std::vector<int>>{ {0, {} } }) {}
		void processBlock(float*, const int&) override;

		std::string name() override { return "FilterChain"; }

	protected:
		std::map<int, std::vector<int>> filterGraph;

	private:
		template <class C1, class... CRest> void initChain(C1, CRest...);
	};

	// ------------------------------------------- Definitions -----------------------------------------------------------


	template <class FirstChainable, class... OtherChainables>
	void FilterChain<FirstChainable, OtherChainables...>::processBlock(float* inMemBlock, const int& inBlockSize) {
		auto it = chainables->begin();
		while (it != chainables->end()) {
			(*it)->processBlock(inMemBlock, inBlockSize);
			++it;
		}
	}

} // cw::Filter
