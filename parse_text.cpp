#include <iostream>
#include <iomanip>
#include <fstream>
#define MAX_LINE 256

using namespace std;

int main()
{
    ifstream inFile("test.txt");
    char oneline[MAX_LINE];

    while (inFile.getline(oneline, MAX_LINE))
    {
        cout << oneline << endl;
    }

    inFile.close();
    return 0;
}