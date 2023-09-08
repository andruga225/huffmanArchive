#include "huffmanTree.h"

huffmanTree::huffmanTree(std::string value, double freq)
{
	this->value = value;
	this->freq = freq;
}

huffmanTree::huffmanTree(huffmanTree* left, huffmanTree* right)
{
	this->freq = left->freq + right->freq;
	this->value = left->value + right->value;
	this->left = left;
	this->right = right;
}

huffmanTree::huffmanTree(std::unordered_map<std::string, double> dict)
{
	auto temp=buildTree(dict);
	this->freq = temp->freq;
	this->value = temp->value;
	this->left = temp->left;
	this->right = temp->right;
	delete temp;
}

huffmanTree* huffmanTree::buildTree(std::unordered_map<std::string, double> dict)
{
	/*
	Выбираются два свободных узла дерева с наименьшими весами.
	Создается их родитель с весом, равным их суммарному весу.
	Родитель добавляется в список свободных узлов, а два его потомка удаляются из этого списка.
	Одной дуге, выходящей из родителя, ставится в соответствие бит 1, другой — бит 0. Битовые значения ветвей, исходящих от корня, не зависят от весов потомков.
	*/

	std::vector<huffmanTree*> nodes;

	for (auto elem : dict)
	{
		nodes.push_back(new huffmanTree(elem.first, elem.second));
	}

	//printf("%d", nodes.size());

	while (nodes.size() > 1)
	{
		int min1=findMin(nodes);
		huffmanTree* left = nodes[min1];
		
		nodes.erase(nodes.begin()+min1);

		int min2 = findMin(nodes);
		huffmanTree* right = nodes[min2];
		
		nodes.erase(nodes.begin() + min2);

		nodes.push_back(new huffmanTree(left, right));
	}

	return nodes[0];
}

int huffmanTree::findMin(std::vector<huffmanTree*> nodes)
{
	int minIndex = 0;

	for (int i = 1; i < nodes.size(); ++i)
	{
		if ((nodes[i]->freq+1E-10)<nodes[minIndex]->freq)
			minIndex = i;
	}

	return minIndex;
}

void huffmanTree::print(huffmanTree* root, int level, std::ofstream& out)
{
	if (root)
	{
		print(root->right, level + 5, out);
		out <<root->freq << std::endl;
		print(root->left, level + 5, out);
	}
}

void huffmanTree::createCodes(std::unordered_map<std::string, std::string>& codes, std::string code = "")
{
	if (this->left && this->right)
	{
		this->left->createCodes(codes, code + "0");
		this->right->createCodes(codes, code + "1");
	}
	else {
		codes[this->value] = code;
	}
}

void huffmanTree::compress(std::string fileName, std::unordered_map<std::string, std::string> codes)
{
	std::ifstream in(fileName);
	archWriter* writer = new archWriter("compressed " + fileName);
	std::string line = "";

	while (!in.eof())
	{
		std::getline(in, line);
		for (int i = 0; i < line.size(); ++i)
		{
			std::string symb = "";
			symb.push_back(line[i]);
			writer->writeWord(codes[symb]);
		}
		writer->writeWord(codes["\n"]);
	}

	in.close();
	writer->writeWord(codes["\0"]);
	writer->finish();
}

void huffmanTree::decompress(std::string fileName)
{
	archReader* reader = new archReader(fileName);
	std::ofstream out("decompressed" + fileName);

	unsigned char bit;
	huffmanTree* curNode = this;

	while (reader->readBit(bit))
	{
		if (!curNode->left && !curNode->right)
		{
			std::string symbol = curNode->value;

			if (symbol == "\n")
			{
				out << std::endl;
				curNode = this;
			}
			else if(symbol!="\0")
			{
				out << symbol;
				curNode = this;
			}
			else {
				reader->finish();
				out.close();
				return;
			}
		}

		if (bit == 0)
		{
			curNode = curNode->left;
		}

		if (bit == 1)
		{
			curNode = curNode->right;
		}

	}

	reader->finish();
	out.close();
}

huffmanTree::~huffmanTree()
{
}

