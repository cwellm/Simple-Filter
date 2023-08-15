#include "BinaryConversion.h"

namespace cw::utils {
	void BinaryConversion::pngToJuceFriendlyCharFormat(std::string pathToPng, std::string pathToHeader,
		std::string nameOfCharVar) {
		juce::File pngFile{ pathToPng };
		juce::File headerFile{ pathToHeader };

		juce::MemoryBlock pngMemBlock{};
		if (!pngFile.loadFileAsData(pngMemBlock)) {
			throw 1;
		}
		auto pngInpStream = juce::MemoryInputStream{ pngMemBlock, true };

		juce::MemoryBlock headerMmBlock{};
		auto outStream = juce::MemoryOutputStream{ headerMmBlock, false };

		outStream.writeText("#pragma once\r\n\r\n const char " + nameOfCharVar 
			+ "[" + std::to_string(pngMemBlock.getSize())
			+ "] = {\r\n", false, false, "\r\n");

		size_t mSize = pngMemBlock.getSize();
		for (size_t i = 0; i < mSize - 1; ++i) {
			if (i % 40 != 39) {
				outStream.writeText(std::to_string(pngInpStream.readByte()) + ", ", false, false, "\r\n");
			}
			else {
				outStream.writeText(std::to_string(pngInpStream.readByte()) + ",\r\n", false, false, "\r\n");
			}
		}
		outStream.writeText(std::to_string(pngInpStream.readByte()) + "\r\n", false, false, "\r\n");
		outStream.writeText("};\r\n", false, false, "\r\n");

		headerFile.appendText(headerMmBlock.toString());
	}

	void BinaryConversion::loadBinaryIntoMemoryBlock(juce::MemoryBlock& block, const char* binaryData, size_t arraySize) {
		auto outStream = juce::MemoryOutputStream{ block, false };
		for (int i = 0; i < arraySize; ++i) {
			outStream.writeByte(binaryData[i]);
		} 
	}
} // cw::utils