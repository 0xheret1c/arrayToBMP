#include <iostream>
#include <fstream>
#include <string>
//#ifdef __ARRAY_TO_BMP_DEFINED
#define __ARRAY_TO_BMP_DEFINED

/* typedefs */
typedef unsigned char byte_t;
typedef unsigned int rgb24_t;

class arrayToBMP
{
private:
	static inline size_t bytesNeeded(size_t data)
	{
		int s = 1;
		while (s < 8 && data >= (1L << (s * 8))) 
			s++;
		return s;
		
	}

	static inline void writeToByteArray(size_t data, size_t at, byte_t* destArray)
	{
		size_t length = bytesNeeded(data);
		size_t currentPosition = 0;
		size_t bitMask = 0x000000FF;
		//little endian
		for (size_t i = at; i < length + at; i++)
		{
			destArray[i] = (data & bitMask) >> (currentPosition * 8);
			std::cout << std::hex << (size_t)destArray[i] << std::endl;
			currentPosition++;
			bitMask <<= 8;
		}
	}

	/* Functions for writing the BMP file */
	static inline void writeFileHeader(byte_t* destArray,size_t fileSize)
	{
		const size_t FILEHEADER_SIZE = 0x0E;
		const size_t INFOHEADER_SIZE = 0x28;
		size_t offBits = FILEHEADER_SIZE + INFOHEADER_SIZE; // bfOffbits

		writeToByteArray(0x424D,   0x00, destArray);	// bfType
		writeToByteArray(fileSize, 0x02, destArray);	// bfSize
		writeToByteArray(0x0,      0x06, destArray);	// bfReserved	
		writeToByteArray(offBits,  0x0A, destArray);	// bfOffbits

	}
	static inline void writeInfoHeader(byte_t* destArray,size_t width, size_t height)
	{
		const size_t INFOHEADER_SIZE = 0x28;
		const size_t IMAGESIZE = width * height;
		const size_t BITCOUNT = 0x18;
		writeToByteArray(INFOHEADER_SIZE,	0x0E, destArray);	// biSize 
		writeToByteArray(width,				0x12, destArray);	// biWidth
		writeToByteArray(height,			0x16, destArray);	// biHeight
		writeToByteArray(0x01,				0x1A, destArray);	// biPlanes
		writeToByteArray(BITCOUNT,			0x1C, destArray);	// biBitCount
		writeToByteArray(0x00,				0x1E, destArray);	// biCompression
		writeToByteArray(IMAGESIZE,			0x22, destArray);	// biSizeImage
		writeToByteArray(0x00,				0x26, destArray);	// biXPelsPerMeter
		writeToByteArray(0x00,				0x2A, destArray);	// biYPelsPerMeter
		writeToByteArray(0x00,				0x2E, destArray);	// biClrUsed 
		writeToByteArray(0x00,				0x32, destArray);	// biClrImportant 
	
	}
	static inline void writeImageData(byte_t* destArray, rgb24_t* colorArray, size_t width, size_t height)
	{
		const size_t FILEHEADER_SIZE = 0x0E;
		const size_t INFOHEADER_SIZE = 0x28;
		const size_t length = width * height * 3;
		size_t offBits = FILEHEADER_SIZE + INFOHEADER_SIZE;
		int index = 0;
		for (size_t i = offBits; i < offBits + length; i = i + 3)
		{
			//byte_t R = colorArray[index];
			//byte_t G = colorArray[index + 1];
			//byte_t B = colorArray[index + 2];
			rgb24_t color = colorArray[index++];
			byte_t R = (color & 0xFF0000) >> 16;
			byte_t G = (color & 0x00FF00) >> 8;
			byte_t B = (color & 0x0000FF);
			destArray[i]	 = B;
			destArray[i + 1] = G;
			destArray[i + 2] = R;
			std::cout << "Wrote R:" << std::hex << (size_t)R << " G:" << std::hex << (size_t)G << " B:" << std::hex << (size_t)B << std::endl;
		}
	}

	/* Functions for writing files byte-wise */

	static inline bool fileExists(const char *filename)
	{
		std::ifstream ifile(filename);
		return (bool)ifile;
	}

	static std::string correctFileName(std::string fileName)
	{
		size_t lastIndex = fileName.length() - 1;
		std::string extention = fileName.substr(fileName.length() - 4, 4);
		if (extention == ".bpm")
		{
			fileName += ".bpm";
		}
		size_t i = 1;
		std::string toCheck = fileName;
		std::string temp = fileName;
		while (fileExists(toCheck.c_str()))
		{
			toCheck = temp.insert(temp.length() - 4, std::to_string(i));
			temp = fileName;
			i++;
		}
		return toCheck;
	}

	static inline void writeOut(byte_t* toWrite,size_t length,const char* path)
	{
		std::string correctedPath = correctFileName(path);
		std::cout << correctedPath << std::endl;
		std::ofstream fileStream;
		fileStream.open(correctedPath,std::ios::binary);
		for (size_t i = 0; i < length; i++)
		{
			fileStream << toWrite[i];
		}
		fileStream.close();
	}
public:
	
	static inline rgb24_t getColor(byte_t R, byte_t G, byte_t B)
	{
		rgb24_t ret = 0x000000;

		ret = (ret | R) << 8;
		ret = (ret | G) << 8;
		ret = (ret | B);
		return ret;
	}

	static inline inline int ArrayToBMP(rgb24_t* colorArray, size_t width, size_t height, const char* path)
	{
		size_t arrayLength = width * height;
		size_t fileHeaderSize = 14;
		size_t infoHeaderSize = 40;
		size_t fileSize = infoHeaderSize + fileHeaderSize + (arrayLength * 3);
		byte_t* bitmap = new byte_t[fileSize];
		for (size_t i = 0; i < fileSize; i++)
		{
			bitmap[i] = 0x00;
		}


		writeFileHeader(bitmap, fileSize);
		writeInfoHeader(bitmap, width, height);
		writeImageData(bitmap, colorArray, width, height);
		writeOut(bitmap, fileSize, path);
		//delete[] bitmap;
		std::cout << "finished" << std::endl;
		return 0;
	}
};
//#endif