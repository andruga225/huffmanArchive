#include "archReader.h"

archReader::archReader(std::string fileName)
{
	buf = new unsigned char[bufSize];
	oneByte = new unsigned char[8];
	bitsCount = bytesCount = byteIdx = 0;
	fs = std::ifstream(fileName, std::ios::binary);
}

bool archReader::readByte()
{
	bool st = false;
	std::string str = "";
	if (bytesCount == byteIdx)
	{
		fs.read(reinterpret_cast<char*>(buf), bufSize);
		st = fs.fail();
		bytesCount=fs.gcount();
		byteIdx = 0;
	}

	if (bytesCount == 0)
		return false;

	unsigned char onebyte = buf[byteIdx++];
	for (int i = 0; i < 8; ++i)
	{
		oneByte[i] = onebyte & 1;
		onebyte = onebyte >> 1;
	}
	bitsCount = 8;
	return true;
}

bool archReader::readBit(unsigned char& bit)
{
	bool res = true;
	if (bitsCount == 0)
		res = readByte();
	if (res)
		bit = oneByte[--bitsCount];
	else
		bit = 0;
	return res;
}

void archReader::finish()
{
	fs.close();

	delete[] buf;
	delete[] oneByte;
}