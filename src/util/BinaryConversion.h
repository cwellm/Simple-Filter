#include <JuceHeader.h>

#include <string>

namespace cw::utils {
	class BinaryConversion {
	public:
		static void pngToJuceFriendlyCharFormat(std::string, std::string, std::string);
		static void loadBinaryIntoMemoryBlock(juce::MemoryBlock&, const char*, size_t);
	};
} // cw::utils	

