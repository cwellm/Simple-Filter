#pragma once

#include <stdexcept>
#include <string>
#include <sstream>

namespace cw::Filter {
	template <class Inheritable, class FirstChainable, class... OtherChainables>
	class GenericChain : public Inheritable {
	public:
		GenericChain() {
			chainables = std::make_unique<std::vector<std::unique_ptr<Inheritable>>>();
			initChain();
		}
		Inheritable* operator[](int index) {
			if (index < 0 || index >= chainables->size()) {
				throw std::invalid_argument("Error: Index out of bounds (must not be larger than "
					+ std::to_string(chainables->size()) + ").");
			}

			return chainables->at(index).get();
		}

		int getNoOfKnots() { return noOfKnots; }

		std::stringstream printKnotsInOrder() {
			std::stringstream resultStream{};
			auto it = chainables->begin();
			std::cout << "Size of chainables = " << chainables->size() << std::endl;
			while (it != chainables->end()) {
				std::cout << "Chainable: " << (*it)->name() << std::endl;
				resultStream << "Chainable: " << (*it)->name() << std::endl;
				++it;
			}
			return resultStream;
		}

		bool getIsParallel() { return isParallel; }
		void setIsParallel(bool isParallel) { this->isParallel = isParallel; }

	protected:
		std::unique_ptr<std::vector<std::unique_ptr<Inheritable>>> chainables;
		bool isParallel{ false };

	private:
		int noOfKnots{ 0 };

		template <class C1, class... CRest> void initChain(C1, CRest...) {
			chainables->push_back(std::make_unique<C1>());
			if constexpr (sizeof...(CRest) > 0) {
				initChain(CRest()...);
			}
			++noOfKnots;
		}

		void initChain() {
			initChain(FirstChainable(), OtherChainables()...);
		}

	};

} // cw::Filter
