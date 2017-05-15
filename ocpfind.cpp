//OCPAlgorithm
//Alexander J. Schmidbauer

#include <iostream>
#include <fstream>

using namespace std;

const int size=1376; //nodes, my system can't handle 1400+ nodes.. change to amount of nodes wished to be calculated for
const int cap=2147483647; //we assume the graphs handled have no edges>=cap, so this is similiar to setting edges to infinity for the sake of calculations
int calculations=0;

struct node{
int edge[size];
int linked1;
int linked2;
int nlinks;
};

void sayEdges(node sayNode[size]){
    for(int j=0;j<size;j++){
        for(int i=0;i<size;i++)
            cout<<sayNode[j].edge[i]<<' ';
        cout<<endl;
        }
}

void initialize(node initnode[size]){
    ifstream input;
    input.open("input.text");
    for(int j=0;j<size;j++){
        for(int i=0;i<size;i++)
            input>>initnode[j].edge[i];
        initnode[j].linked1=0;
        initnode[j].linked2=0;
        initnode[j].nlinks=0;
        initnode[j].edge[j]=cap;
    }
    input.close();
    //cout<<"Initialized!"<<endl;
    //sayEdges(initnode);
}

//finds min()
int nodeMin(node &fnode){
    int smallestEdge=0;
    for(int i=1;i<size;i++){
    calculations++;//deepest loop I think, this gives a rough estimate of total calculations
        if(fnode.edge[i]<fnode.edge[smallestEdge])
            smallestEdge=i;
    }
    //cout<<"Smallest Edge: "<<smallestEdge<<' '<<fnode.edge[smallestEdge]<<endl;
    return smallestEdge;
}

//determines if node is full
bool canLink(node &fnode,int id){
    if(fnode.nlinks==2){
        //cout<<"Cannot link"<<endl;
        return false;
    }
    //cout<<"Can link "<<id<<endl;
    //cin>>id;
    return true;
}

//connects nodes
void link(node fnode[size], int x,int id){
    if(fnode[id].nlinks==0)
        fnode[id].linked1=x;
    else
        fnode[id].linked2=x;
    fnode[id].edge[x]=cap;
    fnode[id].nlinks=fnode[id].nlinks+1;
    if(fnode[id].nlinks==2){
        for(int i=0;i<size;i++){
            fnode[id].edge[i]=cap;
            fnode[i].edge[id]=cap;
        }
    }
    //cout<<"Linked:"<<id<<" to "<<fnode.linked1<<" and "<<fnode.linked2<<endl;
}

//similiar to canLink, uses different syntax for easy code
bool fullLink(node &fnode){
    if(fnode.nlinks==2)
        return true;
    return false;
}

//considers an edge INVALID, similiar to infinity
void removeLink(node &fnode, int linkid){
    fnode.edge[linkid]=cap;
}

//used in noLoop, finds next edge in mini path
int nextLink(node fnode, int linkid){
    //cout<<fnode.linked1<<' '<<fnode.linked2<<' '<<linkid<<endl;
    if(fnode.nlinks==1)
        return fnode.linked1;
    if(fnode.linked1==linkid){
        return fnode.linked2;
    }
    else{
        return fnode.linked1;
    }
}

//determines if there is a loop formed by action
bool noLoop(node fNode[size],int startNode,int endNode,int totalLinks){
    int count=0;
    //cout<<"checking for loop: "<<startNode<<' '<<endNode<<endl;
    if(fNode[startNode].nlinks==0||fNode[endNode].nlinks==0||totalLinks==size-1){
        //cout<<"THERE IS NO LOOP"<<endl;
        return true;
    }
    //int currentNode=fNode[startNode].linked1;
    int currentNode=nextLink(fNode[startNode],startNode);
    int previousNode=startNode;
    int switchNode=currentNode;
    while(fullLink(fNode[currentNode])){
        switchNode=currentNode;
        currentNode=nextLink(fNode[currentNode],previousNode);
        previousNode=switchNode;
        if(currentNode==startNode) {
            //cout<<"THERE IS A LOOP"<<endl;
            removeLink(fNode[startNode],endNode);
            removeLink(fNode[endNode],startNode);
            return false;
        }
        count++;
        //cout<<count<<' '<<currentNode<<endl;
    }
    if(currentNode==endNode&&count>0){
        //cout<<"THERE IS A LOOP"<<startNode<<' '<<endNode<<endl;
        removeLink(fNode[startNode],endNode);
        removeLink(fNode[endNode],startNode);
        return false;
    }
        //cout<<"THERE IS NO LOOP"<<endl;
    return true;
}

int main()
{
    ofstream output;
    output.open("output.text");
    node mNode[size];
    initialize(mNode);
    //sayEdges(mNode);
    int totalLinks=0;
    int cMin;

    while(totalLinks<size){
        for(int j=0;j<size;j++){
            cMin=nodeMin(mNode[j]);
            if(mNode[j].edge[cMin]==mNode[cMin].edge[nodeMin(mNode[cMin])]&&canLink(mNode[j],j)&&canLink(mNode[cMin],cMin)&&noLoop(mNode,cMin,j,totalLinks)){
                link(mNode,cMin,j);
                link(mNode,j,cMin);
                totalLinks++;
                output<<j<<' '<<cMin<<endl;
            }
        }
    }
    cout<<"calculations: "<<calculations; //debug
    return 0;
}
