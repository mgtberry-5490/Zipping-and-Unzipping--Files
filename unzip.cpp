#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;




bool checkNumsArgs(int argc);
bool checkZip(string argv1);
void unzip(string argv1, char** argv);
int main(int argc, char** argv)
{
    string argv1 = argv[1]; //converts the cstring into a string
    if(checkNumsArgs(argc))     //checks the number of arguments inout
    {
        
       if(checkZip(argv1)) //makes sure user inputs a zip file
       {
            unzip(argv1, argv);   
            
       }       
    }
    
}

bool checkNumsArgs(int argc)
{
    if(argc==2) 
    {
        return true;
    }
    else 
    {
        cout<<"Please enter the correct amount of arguments."<<endl;
        return false;
    }
}

bool checkZip(string argv1)
{
    if(argv1.substr(argv1.length()-4, 4)==".zip")
    {
        return true;
    }
    else 
    {
           cout<<"Your file is not a .zip file"<<endl;
           return false;  
    }
}


void unzip(string argv1, char** argv)
{
    map<string,char> M;  
    int numChars;
    string zip;
    ifstream zipfile;
    ofstream unzipfile;
    zipfile.open(argv[1]); //opens the zipfile
        unzipfile.open(argv1.substr(0, (argv1.length()-4)).c_str()); //creates the unzip file
        if(zipfile.is_open()) //makes sure the zipfile exists
        {   
            zipfile>>numChars; //gets the number of chars in the file
            int val;    //used as the ascii val
            string code;    
            for(int x=0; x<numChars; x++)
            {
                    zipfile>>val;
                    zipfile>>code;
                    M[code]= (char)val; //stores each ascii character at their given code
            }
            zipfile>>zip; //stores the last line of the zipfile into a string
            string final="";
            code="";
            for(int p=0; p<zip.length(); p++)
            {   code+=zip[p]; //adds the next binary digit to code and will check if the code equals the code of one of the chars
                if((M.find(code))!= M.end())
                {
                    final= final+ M[code] ; //adds the chars to the final string
                    code=""; //resets the code being checked
                }
            }
            unzipfile<<final; //copies the string to the new unzipped file
            unzipfile.close(); //closes the unzipped file
            zipfile.close();    // closes the zip file
        }
        else
        {
            cout<<"File could not be opened"<<endl;
        }   
}