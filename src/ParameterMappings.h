#include <unordered_map>
#include <string>

#include "BiquadCoeff.h"
#include "ParamIDs.h"

namespace cw::Filter {

	std::unordered_map<std::string, FilterType> mapFilterTypes {
		{MAPLPName, FilterType::BiquadLP},
		{MAPHPName, FilterType::BiquadHP},
		{MAPBPName, FilterType::BiquadBP},
		{MAPBRName, FilterType::BiquadBR}
	};

} // cw::Filter