#pragma once
#include <cstddef>
#include <fstream>

class archWriter
{
private:
	const unsigned char bufSize = 10;
	unsigned char* buf;
	unsigned char oneByte;
	unsigned char bitsCount;
	unsigned char bytesCount;
	std::ofstream fs;

	void writeByte();

public:
	archWriter(std::string);
	void writeBit(unsigned char);
	void writeWord(std::string);
	void finish();

};

