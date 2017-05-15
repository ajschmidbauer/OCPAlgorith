#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
    int spot=1;
    const int number=50;
    ifstream myFile;
    myFile.open("supplied.text");

    unsigned long int board[number][number];
    for(int j=0;j<number;j++){
        for(int i=0;i<spot;i++){
        myFile>>board[i][j];
        board[j][i]=board[i][j];
        }
        spot++;
    }
    myFile.close();

    ofstream myFile2;
    myFile2.open("input.text");
    for(int j=0;j<number;j++){
        for(int i=0;i<number;i++){
            myFile2<<board[i][j]<<' ';
        }
        myFile2<<endl;
        }
    return 0;
}
