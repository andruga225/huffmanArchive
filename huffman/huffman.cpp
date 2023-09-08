// huffman.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "archReader.h"
#include "ArchWriter.h"
#include "huffmanTree.h"

using namespace std;

int main()
{
    //setlocale(LC_ALL, "");
    ifstream freqDict("freq.txt");

    unordered_map<string, double> dict;

    string symb;
    double fr;

    freqDict >> fr;
    dict["\n"] = fr;

    freqDict >> fr;
    dict[" "] = fr;

    while (!freqDict.eof())
    {
        freqDict >> symb >> fr;
        dict[symb] = fr;
    }

    dict["\0"] = 0;

    huffmanTree* root = new huffmanTree(dict);

    ofstream table("table.txt");

    unordered_map<string, string> codes;

    root->createCodes(codes, "");

    for (auto elem : codes)
    {
        table << elem.first << " " << elem.second << endl;
    }

    table.close();
    freqDict.close();

    root->compress("etalon2.txt", codes);
    root->decompress("compressed etalon2.txt");
}
