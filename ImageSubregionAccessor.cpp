#include <iostream>
#include <vector>
#include <string>

/// [*1] - Stream output for visualization purposes.

struct FaceElem {
	FaceElem() { std::cout << "\t\t\tface constructor." << std::endl; };
	FaceElem(const FaceElem& rObj) { std::cout << "\t\t\tface copy constr." << std::endl; this->_data = rObj._data; this->_dataSize = rObj._dataSize;}
	FaceElem& operator=(const FaceElem& rObj)
	{
		if (this != &rObj)
		{
			std::cout << "\t\t\tFace elem assign oper." << std::endl;
			this->_data = rObj._data;
			this->_dataSize = rObj._dataSize;
		}
		return *this;
	}
	void*	 _data;
	uint32_t _dataSize;
	void PrintData() { for (uint32_t i = 0; i < _dataSize / sizeof(char); i++) { std::cout << *((char*)_data + i); } std::cout << std::endl; }
};

struct TextureElem {
	friend class Image;
	TextureElem() { std::cout << "\t\ttextureElem constructor." << std::endl; } /// [*1]
	TextureElem(const TextureElem& rObj)
	{
		std::cout << "\t\ttextureElem copy constr." << std::endl; /// [*1]
		this->_data = rObj._data;
		this->_dataSize = rObj._dataSize;
		this->_faceElemBlock = rObj._faceElemBlock;
	};
	void*	 _data;
	uint32_t _dataSize;

	void PrintData() { for (uint32_t i = 0; i < _dataSize / sizeof(char); i++) { std::cout << *((char*)_data + i); } std::cout << std::endl; }
	FaceElem& operator[](const uint32_t& rIndex)
	{
		std::cout << "\t\tFaceElem[" << rIndex << "]\n"; /// [*1]
		return _faceElemBlock[rIndex];
	}
private:
	std::vector<FaceElem> _faceElemBlock;
};

struct MipElem {
	friend class Image;
	MipElem() { std::cout << "\tmip constructor." << std::endl; } /// [*1]
	MipElem(const MipElem& rObj)
	{
		std::cout << "\tmip copy constr." << std::endl; /// [*1]
		this->_data = rObj._data;
		this->_dataSize = rObj._dataSize;
		this->_textureElemBlock = rObj._textureElemBlock;
	}
	void*	 _data;
	uint32_t _dataSize = 2;

	void PrintData() { for (uint32_t i = 0; i < _dataSize / sizeof(char); i++) { std::cout << *((char*)_data + i); } std::cout << std::endl; }
	TextureElem& operator[](const uint32_t& rIndex)
	{
		std::cout << "\tTextureElem[" << rIndex << "]\n"; /// [*1]
		return _textureElemBlock[rIndex];
	}
private:
	std::vector<TextureElem> _textureElemBlock;
};

class Image
{
public:
	/// Upon initialization Image will call GenerateStructureFromData which will use the constructor parameters to generate the hierarchy.
	Image(void* data, const uint32_t& dataSize) { std::cout << "image constructor." << std::endl; RegenerateStructure(data, dataSize); } /// [*1]


	///----------------------------------------------------------------------------------------------------------    Functions    ----
	MipElem& operator[](const uint32_t& rIndex)	{
		std::cout << "MipElem[" << rIndex << "]\n"; /// [*1]
		return _mipBlock[rIndex];
	};
	// Generate data structure based on [pData] and internal [variables].
	void RegenerateStructure(void* pData, const uint32_t& rDataSize);
	// Convenience function for printing the entire data string.
	void PrintData() { for (uint32_t i = 0; i < _dataSize / sizeof(char); i++) { std::cout << *((char*)_data + i); }std::cout << std::endl; }
	// Convenience function for printing all mip data.
	void PrintMips() { for (uint32_t i = 0; i < _mipCount; i++) { _mipBlock[i].PrintData(); } }
	void* Data() { return _data; };
	uint32_t Size() { return _dataSize; };
private:
	/// Pointer to image/subregion data.
	void*	 _data;
	/// Image/subregion data size.
	uint32_t _dataSize;
	/// The following three variables are typically given in the image file's header section or calculated inside by importer.
		/// Since we use no image loader/parser we will hard-code the values.
	uint32_t _mipCount = 3;
	uint32_t _elemCount = 2;
	uint32_t _faceCount = 3;
	uint32_t _mipSize = 46;
	uint32_t _elemSize = 21;
	uint32_t _faceSize = 5;
private:
	std::vector<MipElem> _mipBlock;
};

void Image::RegenerateStructure(void* pData, const uint32_t& rDataSize)
{
	/// Only regenerate structure, and populate internal data if the data or size is not the same.
	if (pData != _data || rDataSize != _dataSize)
	{
		///-------------------------------------    Populate internal data  ----
		_data = pData; _dataSize = rDataSize;

		///-------------------------------------     Regenerate structure   ----

		/// Mips
			/// Resize vector to fit no more or less than _mipCount elements.
		if (_mipBlock.capacity() != _mipCount)
			_mipBlock.resize(_mipCount);
		for (uint32_t level = 0; level < _mipCount; level++)
		{
			/// Mips
			_mipBlock[level]._data = (void*)((uint8_t*)_data + (_mipSize * level));
			_mipBlock[level]._dataSize = sizeof(char) * _mipSize;

			/// Texture Elements
			if (_mipBlock[level]._textureElemBlock.capacity() != _elemCount)
				_mipBlock[level]._textureElemBlock.resize(_elemCount);
			for (uint32_t elem = 0; elem < _elemCount; elem++)
			{
				_mipBlock[level]._textureElemBlock[elem]._data = (void*)((uint8_t*)_data + 4 + (_elemSize * elem));
				_mipBlock[level]._textureElemBlock[elem]._dataSize = sizeof(char) * _elemSize;

				/// Faces
				if (_mipBlock[level]._textureElemBlock[elem]._faceElemBlock.capacity() != _faceCount)
					_mipBlock[level]._textureElemBlock[elem]._faceElemBlock.resize(_faceCount);
				for (uint32_t face = 0; face < _faceCount; face++)
				{
					_mipBlock[level]._textureElemBlock[elem]._faceElemBlock[face]._data = (void*)((uint8_t*)_data + 10 + (_faceSize * face));
					_mipBlock[level]._textureElemBlock[elem]._faceElemBlock[face]._dataSize = sizeof(char) * _faceSize;
				}
			}
		}
	}
}

int main()
{
	/// Sample string of data.
	/// Typical example of data following the hierarchy found in a KTX (Khronos Texture) file; Mip->TextureArray->Face.
	std::string text = { "mip0array0face0face1face2array1face0face1face2mip1array0face0face1face2array1face0face1face2mip2array0face0face1face2array1face0face1face2" };

	/// Image data type will generate the data structure and allow for easy access of data's sub-elements.
	Image img = {(void*)text.data(), text.size()};

	/// Functions:
	///img.GenerateStructureFromData(pData, rDataSize).
		/// - Ensured to only regenerate data when a new memory-block (pData) or size is given.
		/// - Called implicitly when Image is constructed.
	///img.PrintMips().
		/// - Convenient function for debugging.
	///PrintData().
		/// - Convenient function for debugging.
	///Data().
		/// - return a pointer to the memory block of data contained in the image/subregion.
	///Size().
		/// - return the size of the memory block contained in the image/subregion.
	
	///Accessing a subregion of data is conveniently done by using the subscript operator. E.g.
	/// img[0] - Mip 0
	/// img[0][0] - Mip 0, texture element 0.
	/// img[0][0][0] - Mip 0, texture element 0, face 0.

	/// Print all data in the first face of the first texture element, at mip 0.
	img[0][0][0].PrintData();

	return 0;
}
