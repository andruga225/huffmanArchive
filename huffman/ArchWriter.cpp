#include "ArchWriter.h"

void archWriter::writeByte()
{
	buf[bytesCount++] = oneByte;
	oneByte = 0;
	bitsCount = 0;
	if (bytesCount == bufSize) {
		fs.write(reinterpret_cast<char*>(buf), bufSize);
		bytesCount = 0;
	}
}

archWriter::archWriter(std::string fileName)
{
	buf = new unsigned char[bufSize];
	oneByte = 0;
	bitsCount = bytesCount = 0;
	fs = std::ofstream(fileName, std::ios::binary);
}

void archWriter::writeBit(unsigned char bit) 
{
	oneByte=((oneByte << 1) + bit);
	bitsCount++;
	if (bitsCount == 8)
		writeByte();
}

void archWriter::writeWord(std::string w)
{
	for (int i = 0; i < w.length(); ++i)
	{
		if (w[i] == '0')
			writeBit(0);
		else if (w[i] == '1')
			writeBit(1);
	}
}

void archWriter::finish()
{
	while (bitsCount > 0)
		writeBit(0);
	if (bytesCount > 0)
		fs.write(reinterpret_cast<char*>(buf), bytesCount);
	fs.close();

	delete[] buf;
}
