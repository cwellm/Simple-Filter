#pragma once

#include <map>
#include <vector>
#include <stdexcept>

#include "BiquadFilter.h"
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
	class BiquadFilterChain : public GenericChain<BiquadFilter, FirstChainable, OtherChainables...> {
		using GenericChain = GenericChain<BiquadFilter, FirstChainable, OtherChainables...>;

		// std::map<int, std::vector<int>> as first arg. then I need a traversing algorithm - probably put this into
		// an extra class? or put it here??? 
		// then template <std::map, Chainable...> or so?
	public:
		explicit BiquadFilterChain(std::map<int, std::vector<int>> filterGraph) : filterGraph(filterGraph) {
			Chainable::isChain = true;
			
		}
		explicit BiquadFilterChain() : BiquadFilterChain(std::map<int, std::vector<int>>{ {0, {} } }) {}

		std::string name() override { return "BiquadFilterChain"; }
		void processBlock(float*, const int&) override;
		void reserveMemory(const int&) override;

	protected:
		std::map<int, std::vector<int>> filterGraph;

	private:
		std::unique_ptr<float[]> copyOrig{ nullptr };
	};

	// ------------------------------- Definitions -------------------------------
	template <class FirstChainable, class... OtherChainables>
	void BiquadFilterChain<FirstChainable, OtherChainables...>::reserveMemory(const int& size) {
		auto it = GenericChain::chainables->begin();
		while (it != GenericChain::chainables->end()) {
			(*it)->reserveMemory(size);
			++it;
		}
		copyOrig = std::make_unique<float[]>(size);
		for (int i = 0; i < size; ++i) {
			copyOrig[i] = 0;
		}

		BiquadFilter::temporary = std::make_unique<float[]>(size);
		for (int i = 0; i < size; ++i) {
			BiquadFilter::temporary[i] = 0;
		}
	}

	template <class FirstChainable, class... OtherChainables>
	void BiquadFilterChain<FirstChainable, OtherChainables...>::processBlock(float* inMemBlock, const int& inBlockSize) {
		auto it = GenericChain::chainables->begin();

		if (!GenericChain::isParallel) {
			while (it != GenericChain::chainables->end()) {
				(*it)->processBlock(inMemBlock, inBlockSize);
				++it;
			}
		}
		else {
			int chainSize = GenericChain::chainables->size();		
			for (int i = 0; i < inBlockSize; ++i) {
				BiquadFilter::temporary[i] = 0;
			}
			while (it != GenericChain::chainables->end()) {
				for (int i = 0; i < inBlockSize; ++i) {
					copyOrig[i] = inMemBlock[i];
				}
				(*it)->processBlock(copyOrig.get(), inBlockSize);
				
				for (int i = 0; i < inBlockSize; ++i) {
					BiquadFilter::temporary[i] += copyOrig[i]*1./chainSize;
				}
				++it;
			}

			for (int i = 0; i < inBlockSize; ++i) {
				inMemBlock[i] = BiquadFilter::temporary[i];
			}
		}
	}

} // cw::Filter
