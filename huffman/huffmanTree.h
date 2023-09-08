#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include "ArchWriter.h"
#include "archReader.h"

class huffmanTree
{
private:
	double freq;
	std::string value;
	huffmanTree* left;
	huffmanTree* right;

	//return symb with min frequency
	int findMin(std::vector<huffmanTree*>);

public:
	huffmanTree(std::unordered_map<std::string, double>);
	huffmanTree(std::string, double);
	huffmanTree(huffmanTree*, huffmanTree*);

	//return pointer to tree
	huffmanTree* buildTree(std::unordered_map<std::string, double>);
	void print(huffmanTree*, int, std::ofstream&);
	void createCodes(std::unordered_map<std::string, std::string>&, std::string);
	void compress(std::string, std::unordered_map<std::string, std::string>);
	void decompress(std::string);
	~huffmanTree();
};

