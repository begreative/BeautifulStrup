#include <iostream>
#include <iomanip>
#include <fstream>
#define MAX_LINE 256

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2){
        cout << "enter ast_*.txt file/s to parse" << endl;
        exit(0);
    }
    ifstream inFile("test.txt");
    char oneline[MAX_LINE];

    while (inFile.getline(oneline, MAX_LINE))
    {
        cout << oneline << endl;
    }

    inFile.close();
    return 0;
}