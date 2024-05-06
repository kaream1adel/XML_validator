#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<time.h>
#include<stdlib.h>
using namespace std;
//Functions to Initialize and Create Min Heap:
//Structure of tree nodes
struct Node {
	char character;
	long long freq;
	struct Node* left;
	struct Node* right;
};

//Structure for min heap
struct Min_Heap {
	int size;
	struct Node** array;
};

// newNode is a function to initialize new node
struct Node* newNode(char c, long long f, Node* l = NULL, Node* r = NULL) {
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->character = c;
	temp->freq = f;
	temp->left = l;
	temp->right = r;
	return temp;
}
//Swap function
void swapMinHNode(struct Node** a, struct Node** b) {
	struct Node* t = *a;
	*a = *b;
	*b = t;
}
//standard function to heap creation
void Heapify(vector <Node*> &Heap, int i, int txtsize) {
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if (left <= txtsize && Heap[left]->freq < Heap[i]->freq)
	{
		smallest = left;
		if (right <= txtsize && Heap[right]->freq < Heap[left]->freq)
			smallest = right;

	}
	if (right <= txtsize && Heap[right]->freq < Heap[i]->freq)
		smallest = right;
	if (smallest != i) {
		swap(Heap[i], Heap[smallest]);
		Heapify(Heap, smallest, txtsize);
	}
}
//Function to create min heap
void createAndBuildMin_Heap(vector <Node*> &Heap, int txtsize)
{
	int n = (txtsize - 1) / 2;
	for (int i = n; i >= 0; i--) {
		Heapify(Heap, i, txtsize);
	}

}
// check if size is 1
int isSizeOne(struct Min_Heap* MinHeap) {
	return (MinHeap->size == 1);
}
//extract the min
struct Node* extractMin(vector <Node*> &MinHeap) {
	if (MinHeap.size() < 1)
		return NULL;
	Node* minimum = MinHeap[0];
	MinHeap[0] = MinHeap.back();
	MinHeap.pop_back();
	Heapify(MinHeap, 0, MinHeap.size() - 1);
	cout << minimum -> character << " : " << minimum->freq << "\n";
	return minimum;
}
// Insertion
void insertIntoMinHeap(vector<Node*> &MinHeap, struct Node* HeapNode) {
	MinHeap.push_back(HeapNode);
	int i = MinHeap.size() - 1;
	while (i > 0 && MinHeap[(i - 1)/2]->freq > MinHeap[i] -> freq) {
		swap(MinHeap[i], MinHeap[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}


//structure to store codes in compressed file
typedef struct code {
	char k;
	int l;
	int code_arr[16];
	struct code* p;
}code;
int isLeaf(struct Node* root) {
	return !(root->left) && !(root->right);
}
void printArray(int arr[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		cout << arr[i];
	}
	cout << "\n";
}
struct Tree {
	char g;
	int len;
	int dec;
};
//Function to sore codes into vector
void CodeStoring(struct Node* root, char single_code[], vector <long long>& HuffmanMap, int top = 0) {
	int i;
	if (root -> left) {
		single_code[top] = '0';
		CodeStoring(root->left, single_code, HuffmanMap, top + 1);
	}
	if (root->right) {
		single_code[top] = '1';
		CodeStoring(root->right, single_code, HuffmanMap, top + 1);
	}
	if (isLeaf(root)) {
		for (int i = top; i >= 0; i--) {
			if (i != top)
			{
				HuffmanMap[root->character] *= 10;
				HuffmanMap[root->character] += single_code[i] - '0';
			}
			else
			{
				HuffmanMap[root->character] = 1;
			}
		}
	}

}
//write tree to file
void TreeStoring(ofstream &input, Node* root) {
	if (isLeaf(root)) {
		input<<'1';
		input<<root->character;
	}
	else
	{
		input << '0';
		TreeStoring(input, root->left);
		TreeStoring(input, root->right);
	}
}
Node* Huffman(long long Count[])
{
	vector <Node*> MinHeap;
	for (int i = 0; i < 256; i++)
	{
		if (Count[i] != 0)
			MinHeap.push_back(newNode(i, Count[i]));
	}
	createAndBuildMin_Heap(MinHeap, MinHeap.size() - 1);
	while (MinHeap.size() != 1)
	{
		Node* Z = newNode(-1, 0, extractMin(MinHeap), extractMin(MinHeap));
		Z->freq = Z->left->freq + Z->right->freq;
		insertIntoMinHeap(MinHeap, Z);
	}
	return(MinHeap[0]);
}

void WriteInCompressed(ifstream& input, ofstream& output, vector<long long> &HuffmanMap)
{
	char c;
	unsigned char bits_8 = 0;
	long long counter = 0;
	while (input.get(c))
	{
		long long temp = HuffmanMap[static_cast<unsigned char> (c)];
		while (temp != 1)
		{
			bits_8 <<= 1;
			if ((temp % 10) != 0)
				bits_8 |= 1;
			temp /= 10;
			counter++;
			if (counter == 8)
			{
				output << bits_8;
				counter = bits_8 = 0;
			}
		}
	}
	while (counter != 8)
	{
		bits_8 <<= 1;
		counter++;
	}
	output << bits_8;
	output.close();
}
void compress(string inputFile)
{
	vector <long long> HuffmanMap;   //Double dimensional vector to store Huffman codes in codemap
	HuffmanMap.resize(256);
	long long Count[256] = { 0 };    //Initializing character counting array
	string filename = inputFile;	// Naming file
	ifstream input_file(filename.c_str(), ios::binary);		//setting input stream
	if (!input_file.good())		//checking if input file exists
	{
		perror("Error:\t");
		exit(-1);
	}
	clock_t start_time = clock();	//Starting timer
	char c;
	while (input_file.get(c))		//Reading file
		Count[static_cast <unsigned char> (c)]++; //Increasing count
	input_file.clear();		//Resetting pointers
	input_file.seekg(0);
	Node* tree = Huffman(Count);	//creating huffman tree
	ofstream output_file((filename + ".huf").c_str(), ios::binary);	//naming file
	if (!output_file.good())	//Checking if file can be written
	{
		perror("Error:\t");
			exit(-1);
	}
	output_file << tree->freq;	//Write to file
	output_file << ',';
	TreeStoring(output_file, tree);
	output_file << ' ';
	char single_code[16];		//array to store code of one
	CodeStoring(tree, single_code, HuffmanMap, 0);	//store codes in vector
	WriteInCompressed(input_file, output_file, HuffmanMap);	//write to file
	input_file.close();		//close file stream
	output_file.close();
	clock_t stop_time = clock();	//stop timer
	if (remove(filename.c_str()) != 0)		//delete the original uncompressed file
		perror("Error deleteing the compressed file:\t");
	
}

/*int main()
{
	string s = "sample.txt";
	compress(s);
}*/
