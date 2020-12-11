#include "huffman.h"
#include <iostream>
using namespace std;

HuffmanTree:: HuffmanTree()
	: numChars(0), built(false) {}

void HuffmanTree:: insert(char ch, int weight) {
    HNode newNode = {ch, weight, -1, -1}; 
    built = false;
    nodes.push_back(newNode);
    numChars++;
}

bool HuffmanTree:: inTree(char ch) {

    for(int x=0; x<nodes.size(); x++)
    {
        if(nodes[x].ch==ch)
        {
            return true;
        }
    }
}

int HuffmanTree:: GetFrequency(char ch) {

    for(int x=0; x<nodes.size(); x++)
    {
        if(nodes[x].ch==ch)
        {
            return GetFrequency(x);
        }
    }
}

int HuffmanTree:: GetFrequency(int i) {

    return nodes[i].weight;    
}

int HuffmanTree:: lookUp(char ch) {
    
    for(int x=0; x<numChars; x++)
        {
            if(nodes[x].ch==ch)
            {
                return x;
            }
        }
    return -1;

}

string HuffmanTree:: GetCode(char ch) 
{
    return GetCode(lookUp(ch));
}


string HuffmanTree:: GetCode(int i) 
{
    if(nodes[i].parent==-1)
    {
        return "";
    }
    else 
    {
        
        return (GetCode(nodes[i].parent)+(char)(nodes[i].childType+'0'));
    }
}

void HuffmanTree:: PrintTable() {

    cout<<endl<<"\t +++ Encoding Table ++++"<<endl;
    cout<<"Index \t Char \t Weight\tParent \tChildType"<<endl;
    int i=0;
    for(int x=0; x<nodes.size();x++)
    {
        if(nodes[x].ch==' ')
            cout<<x<<" \t sp"<<" \t "<<nodes[x].weight<<" \t "<<nodes[x].parent<<" \t "<<nodes[x].childType<<endl;
        else if(nodes[x].ch=='\n')
            cout<<x<<" \t nl " << " \t "<<nodes[x].weight<<" \t "<<nodes[x].parent<<" \t "<<nodes[x].childType<<endl;
        else if(nodes[x].ch=='\0')
        {
            i++;
            cout<<x<<" \t  T"<<i<< " \t "<<nodes[x].weight<<" \t "<<nodes[x].parent<<" \t "<<nodes[x].childType<<endl;
        }
        else
        {
            cout<<x<<" \t "<< nodes[x].ch << " \t "<<nodes[x].weight<<" \t "<<nodes[x].parent<<" \t "<<nodes[x].childType<<endl;
        }
    }

}

int HuffmanTree:: numNodes() {

    return nodes.size();

}

void HuffmanTree:: build() {

    int ssmallest = 0; //second smallest node in the tree
    int smallest = 0;   // smallest node in the tree
   for(int p=0;p<(2*numChars-2);p++)
   {
       if(nodes[smallest].parent==-1) //node without parent
       {
       // combine the forests
        for(int x=0; x<nodes.size(); x++)
        {
            if((nodes[x].weight<nodes[smallest].weight)&& (nodes[x].parent==-1))
            {
                smallest=x;
            }
        }
        while(ssmallest==smallest || nodes[ssmallest].parent!=-1) 
        {   
            ssmallest++;
        }
        for(int x=0;x<nodes.size();x++)
        {
            if((nodes[x].weight < nodes[ssmallest].weight) && x!=smallest && nodes[x].parent==-1)
            {
                ssmallest=x;
            } 
        }
            HNode parentNode = {'\0', nodes[ssmallest].weight+nodes[smallest].weight, -1, -1};
            nodes.push_back(parentNode);
            nodes[smallest].parent=nodes.size()-1;
            nodes[ssmallest].parent=nodes.size()-1;
            nodes[smallest].childType=0;
            nodes[ssmallest].childType=1;

            
       }
        
        smallest=p+1;
        ssmallest=0;
        
   }
    
}




 