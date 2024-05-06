#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<time.h>
#include<stdlib.h>
using namespace std;

struct Node
{
	unsigned char character;
	Node* left;
	Node* right;
	Node(char c, Node* l = NULL, Node* r = NULL)
	{
		character = c;
		left = l;
		right = r;
	}
};
//Making tree with the compressed xml file
Node* MakingHuffmanTree(ifstream &input)
{
	char ch;
	input.get(ch);
	if (ch == '1')
	{
		input.get(ch);
		return(new Node(ch));
	}
	else
	{
		Node* left = MakingHuffmanTree(input);
		Node* right = MakingHuffmanTree(input);
		return(new Node(-1, left, right));
	}
}
//Decoding binary symbols with the given tree
void decode(ifstream &input, string filename, Node* r, long long int TotalFreq)
{
	ofstream output((filename.erase(filename.size() - 4)).c_str(), ios::binary);
	if (!output.good())
	{
		perror("Error:\t");
		exit(-1);
	}
	bool eof_flag = false;
	char bits_8;
	Node* indicator = r;
	while (input.get(bits_8))
	{
		int counter = 7;
		while (counter >= 0) 
		{
			if (!indicator->left && !indicator->right)
			{
				output << indicator->character;
				TotalFreq--;
				if (!TotalFreq)
				{
					eof_flag = true;
					break;
				}
				indicator = r;
				continue;
			}
			if ((bits_8&(1 << counter)))
			{
				indicator = indicator->right;
				counter--;
			}
			else
			{
				indicator = indicator->left;
				counter--;
			}
		}
		if (eof_flag)
			break;
	}
	output.close();
}
void decompress(string inputFile) {
	string filename = inputFile;
	ifstream input_file(filename.c_str(), ios::binary);		//Open File
	if (!input_file.good())					//Checking if stream is opened
	{
		perror("Error:\t");
		exit(-1);
	}
	if (filename.find(".huf") == string::npos)				//Seeing if the file is compressed (has '.huf')
	{
		cout << "Error: File doesn't need decompression\n";
		exit(-1);
	}
	clock_t start_time = clock();
	long long int TotalFreq = 0;
	char ch;
	while (input_file.get(ch))									//Reading of total frequency
	{
		if (ch == ',')
			break;
		TotalFreq *= 10;
		TotalFreq += ch - '0';
	}
	Node* HuffmanTree = MakingHuffmanTree(input_file);
	input_file.get(ch);										//Remake huffman tree from the file
	decode(input_file, filename, HuffmanTree, TotalFreq);			//Read added space between compressed data and tree from file
	input_file.close();
	clock_t stop_time = clock();
	if (remove(filename.c_str()) != 0)				//Deleting the unneeded compressed file
		perror("Error deleting the compressed file: \t");
}

/*int main()
{
	string s = "sample.txt.huf";
	decompress(s);
}*/
