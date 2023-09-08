#pragma once
#include <fstream>
class archReader
{
private:
	const unsigned char bufSize = 10;
	unsigned char* buf;
	unsigned char* oneByte;
	unsigned char bitsCount;
	unsigned char bytesCount;
	unsigned char byteIdx;
	std::ifstream fs;

	bool readByte();

public:
	archReader(std::string fileName);
	bool readBit(unsigned char&);
	void finish();

};

