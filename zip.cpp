#include "huffman.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <string>

using namespace std;

void createTree(int Letters[], HuffmanTree &zipT);
void CountLetters (int Letters[], ifstream& unzip, char** argv, string unzips);
bool checkNumsArgs(int argc);
int checkArg(string argv1);
void dashT(string argv2, ofstream& zipped, char** argv, HuffmanTree zipT );
void zip(ifstream &unzip, ofstream &zipped, int Letters[], HuffmanTree& zipT, char** argv, string argv1);
void getCompressionRatio(ifstream& unzip, ofstream& zipped, char** argv, string argv1, string zips);
void compressionRatio(int Letters[], HuffmanTree & zipT, string unzips);
int main(int argc, char** argv)
{
    ifstream unzip;
    ofstream zipped;
    string unzipname="";
    HuffmanTree zipT;
    string argv1 = argv[1]; //converts the cstring into a string
    if(checkNumsArgs(argc))     //checks the number of arguments inout
    {                              
       if(checkArg(argv1)==3) //user inputted --help
       {
            cout<<"If you would like to be shown the encoding table of a zip, type ./a.out --t filename"<<endl;
            cout<<"If you would like to zip a file, type ./a.out filename"<<endl;
       }       
       if(checkArg(argv1)==2) //user inputted --t
       {   
           string argu = argv[2];
           dashT(argu, zipped, argv, zipT );
       }
       else if(checkArg(argv1)==-1) //user wants to zip a file
       {
           int Letters[256];
           if(checkNumsArgs(argc))
           {              
            
                unzip.open(argv[1]); //opens the zipfile
                zipped.open((argv1+".zip").c_str()); //creates the unzip file
                zip(unzip, zipped, Letters, zipT, argv, argv1);
               
        
                compressionRatio(Letters, zipT,argv1);
           }
       }
    }
}

void zip(ifstream &unzip, ofstream &zipped, int Letters[], HuffmanTree & zipT, char** argv, string argv1)
{
    string zipString="";
    if(unzip.is_open())
    {
            CountLetters(Letters, unzip, argv, argv1);
            createTree(Letters,zipT);
    
        zipped<<zipT.numNodes()<<"\n";
        
        zipT.build();
        //need to get the chars' ascii, get the Code, next line
        int ch;
        for(int x=0; x<126;x++)
        {
            if(Letters[x]!=0)
            {
                
                ch = x;
                zipped<<ch<<" "<<zipT.GetCode((char)ch)<<"\n";
                
            }
        }
        while(unzip)
        {
            char s;
            unzip.get(s);
            zipped<<zipT.GetCode(s);
            

        }
        unzip.close();
        zipped.close();
        
    }
}




void compressionRatio(int Letters[], HuffmanTree & zipT, string unzips)
{
    
   int inBits=0;
   float outBits=0;
   for(int x=0; x<126; x++)
   {
       if(Letters[x]!=0)
       {
           outBits+= zipT.GetCode((char)x).length() * zipT.GetFrequency((char)x);
           inBits+=Letters[x];
       }

   }

    int ratio= (1-(outBits/(inBits*8)))*100;

   cout<<"File Successfully Compressed To "<<outBits<<" Bits ("<<ratio<<char(37)<<" Less) "<<endl; 

} 


void dashT(string argv2, ofstream& zipped, char** argv, HuffmanTree zipT )
{
    ifstream unzipped;
    unzipped.open(argv2.c_str());
    int Letters[256];
    CountLetters(Letters, unzipped, argv, argv2);
    createTree(Letters,zipT);
    zipT.build();
    zipT.PrintTable();
}

bool checkNumsArgs(int argc)
{
    if(argc<=3) 
    {
        return true;
    }
    else 
    {
        //cout<<"Please enter the correct amount of arguments."<<endl;
        return false;
    }
}

int checkArg(string argv1) //checks the user's input
{
    if(argv1.substr(argv1.length()-3, 3)=="--t")
    {
        return 2;
    }
    else if(argv1.substr(argv1.length()-6, 6)=="--help")
    {
        return 3;
    }
    else 
    {
        return -1;
    }
}

void CountLetters (int Letters[], ifstream& unzip, char** argv, string unzips)
{

    ifstream unzipped;
    unzipped.open(unzips.c_str());
	char ch;
	for (char ch = char(0);  ch <= char(126);  ch++)
    {
		Letters[ch] = 0;
    }
	unzipped.get(ch);
    while (unzipped)
	{
		Letters[ch] += 1;
		unzipped.get(ch);
	}
    
}

void createTree(int Letters[], HuffmanTree &zipT)
{
    for(int x=0; x<126;x++)
    {

        if(Letters[x]!=0)
        {
            zipT.insert((char)x, Letters[x]);
        }
    }

}