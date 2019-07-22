#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void ControlFlippedSectionData(const void* pData1, const void* pData2, const uint16_t& rSectionCount, const uint8_t& rSectionByteLength)
{

	std::cout << "Original data:" << "   " << "Flipped data:" << std::endl;

	///------------------------------------------------------------------------------------------    Control the flipped and non flipped data    ----
	uint8_t* tempBlock = new uint8_t[rSectionByteLength];
	for (uint16_t row = 0; row < (rSectionCount); row++)
	{
		/// Get a pointer to the first row, each iteration go towards the middle.
		std::string pRow0 = (char*)(pData1)+(row * rSectionByteLength);

		/// Get a pointer to the last row, each iteration go towards the middle.
		std::string pRow1 = (char*)(pData2)+((rSectionCount - row - 1) * rSectionByteLength);

		/// Create temporary strings. compare method can return val>0 | val<0 if comparing strings are not the same size.
		std::string r0 = pRow0.substr(0, rSectionByteLength);
		std::string r1 = pRow1.substr(0, rSectionByteLength);

		if (r0.compare(0, rSectionByteLength, r1) != 0) {
			std::cout << r0 << "      " << r1 << "\t Data not flipped correctly" << std::endl;
		}else{
			std::cout << r0 << "      " << r1 << std::endl;
		}
	}
}

// @brief Flip linear memory block [ppData], where each section/entry is [rSectionByteLength] in size with a total of [rSectionCount] members.
// @param ppData - Pointer to mutable memory block containing all data to be flipped.
// @param rSectionCount - Total amount of sections/entries in ppData.
// @param rSectionSize - Size of each section in bytes.
bool FlipSectionData(void** ppData, const uint16_t& rSectionCount, const uint16_t& rSectionSize)
{
	/// Temp memory block large enough to hold one section of data.
	void* tempBlock = calloc(rSectionSize, sizeof(uint8_t));
		/// Loop over each section until you are at the mid point of amount of sections ([rSectionCount] >> 1).
	for (uint16_t row = 0; row < (rSectionCount >> 1); row++)
	{
		/// Get a pointer to the first row, each iteration go towards the middle.
		uint8_t* pRow0 = static_cast<uint8_t*>(*ppData) + (row * rSectionSize);
		/// Get a pointer to the (_begining_ of the) last row, each iteration go towards the middle.
		uint8_t* pRow1 = static_cast<uint8_t*>(*ppData) + ((rSectionCount - row - 1) * rSectionSize);
		/// Copy row0 onto row1 and vice versa.
		memcpy(tempBlock, pRow0, rSectionSize);
		memcpy(pRow0, pRow1, rSectionSize);
		memcpy(pRow1, tempBlock, rSectionSize);
	}
	delete tempBlock;

	return true;
}

int main()
{
	size_t bytesPerEntry = 2;
	const uint8_t rWidth = 5;
	const uint8_t rHeight = 5;
	const uint8_t totalEntries = rWidth * rHeight * bytesPerEntry;

	/// Memory to be flipped.
	void* pMemBlock = calloc(totalEntries, bytesPerEntry);
	/// Memory of original (non-flipped) data.
	/// Used for debugging/controlling that it flipped correctly.
	void* pMemBlock2 = calloc(totalEntries, bytesPerEntry);

	/// Populating memory block with data.
	char k = '1';
	for (unsigned int entry = 0; entry < totalEntries; entry++)
	{
		*((char*)pMemBlock + (sizeof(char) * entry)) = k++;
	}
	/// Copying data to separate memory block to compare (flipped) result against.
	memcpy(pMemBlock2, pMemBlock, totalEntries);
	/// Calculating bytes per section based on previous input.
	uint8_t bytesPerSection = bytesPerEntry * rWidth;
	/// Flip data.
	FlipSectionData(&pMemBlock, rHeight, bytesPerSection);

	/// Uncomment either line will change an entry in a memory block.
	/// The error will be picked up in the control function.
		//*(char*)pMemBlock = '2';
		//*((char*)pMemBlock2 + (rWidth * (rHeight-1))) = '[';
	
	/// Tests are conducted for each section inside function.
	ControlFlippedSectionData(pMemBlock, pMemBlock2, rHeight, bytesPerSection);

	return 0;
}
