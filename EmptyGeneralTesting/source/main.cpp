#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	ofstream outputFile;
	outputFile.open("output.txt");

	outputFile << argc;
	outputFile.close();

	return 0;
}