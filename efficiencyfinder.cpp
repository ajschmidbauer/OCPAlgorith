#include <iostream>
#include <fstream>

//finds path lengths
using namespace std;

int main()
{
    const int size=1376;
    int totalDistance=0;
    ifstream myFile;
    ifstream myFile2;
    int input1;
    int input2;
    int nodeTable[size][size];
    myFile.open("input.text");
    myFile2.open("output.text");

    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            myFile>>nodeTable[i][j];
        }
    }

    for(int i=0;i<size;i++){
        myFile2>>input1;
        myFile2>>input2;
        totalDistance=totalDistance+nodeTable[input1][input2];
    }


    cout << totalDistance << endl;
    return 0;
}
