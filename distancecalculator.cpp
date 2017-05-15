#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
//converts node coordinate list to distance graph
using namespace std;
const int size=1376;

int main()
{
    int currentNode;
    int xNode[size];
    int yNode[size];
    int xDistance;
    int yDistance;
    int Distance;
    //int nodeDistance[size][size];

    ifstream myFile;
    myFile.open("supplied.text");
    ofstream myFile2;
    myFile2.open("input.text");

//input node coordinates
for(int i=0;i<size;i++){
    myFile>>currentNode;
    myFile>>xNode[i];
    myFile>>yNode[i];
    //cout<<xNode[i]<<' '<<yNode[i]<<endl;
}
//consider all nodes

for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            xDistance=xNode[j]-xNode[i];
            xDistance=xDistance*xDistance;
            yDistance=yNode[j]-yNode[i];
            yDistance=yDistance*yDistance;
            Distance=xDistance+yDistance;
            Distance=sqrt(Distance);
            //nodeDistance[i][j]=nodeDistance[j][i]=Distance;
            myFile2<<Distance<<' ';
        }
        myFile2<<endl;

}
//find the distance from this node to all others
    return 0;
}
