
#include <iostream>
#include "user.h"
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
using namespace std;

void User::greeting()
{
    int optiune = 1;
    
    while(optiune != 0)
    {
        cout<<"\nHello\nselect 1 for authentification or 2 for login\n";
        cin>>optiune;
        if(optiune == 1)
        {
            User::authentif();
            optiune = 3;
        }
        else if(optiune == 2)
        {
            User::login();
            optiune = 0;
        }
        else 
        cout<<"Optiune invalida. Incearca din nou. Apasa 0 daca vrei sa iesi\n";
    }
}
void User::authentif()
{

    string username;
    bool ok = 1;
    while(ok != 0){
    cout<<"\nType your name:\n";
    cin>>username;
    try{
        fstream userBd;
        userBd.open("userBd.csv",ios::in);
        vector<string> row;
        string line;
        string word;
        while(getline(userBd,line))
        {
            row.clear();
            stringstream s(line);
            while(getline(s,word,','))
            {
                row.push_back(word);
            }
            if(username == row[0])
                throw "user is already in use. Try Again";
        }
        userBd.close();
        userBd.open("userBd.csv",ios::out|ios::app);
        userBd<<"\n";
        userBd<<username;
        cout<<"\nAuthentification succesful. Come back to Login\n";
        ok = 0;

        string relativePath="../FlowSystemDataBase/";
        filesystem::create_directory(relativePath+username);

    }
    
    catch(char const* msg)
    {
        cout<<msg;
    }

}
}

void User::login()
{
    bool ok = 1;
    string username;
    while(ok != 0){
      try{ 
        cout<<"\nType your username\n";
        cin>>username;
        fstream userBd;
        userBd.open("userBd.csv",ios::in);
        string line,word;
        vector<string> row;
        while(getline(userBd,line))
        {
            row.clear();
            stringstream s(line);
            while(getline(s,word,','))
            {
                row.push_back(word);
            }
            if(username == row[0] )
            {
                cout<<"\n----Succesful login----\n";
                this->name = username;
                ok = 0;
                break;
            }
        }

         userBd.close();
            if(ok == 1)
                throw "\n-----Insuccesful Login Try Again----\n"; 
       }
       catch(const char* msg)
       {
            cout<<msg;
       }

}
}