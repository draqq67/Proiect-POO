
#include <iostream>
#include "user.h"
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include "../Flow/flow.h"
#include <regex>
#include <chrono>
#include <ctime>
using namespace std;

string User::getCurrentTimestamp()
{
    auto now = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(now);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", localtime(&time));
    return string(timestamp);
}
void User::greeting()
{
    string optiune;
    bool logged = 0;
    while(optiune != "0")
    {
        cout<<"\nHello\nselect 1 for authentification or 2 for login\n";
        cin>>optiune;
        
        if(optiune == "1")
        {
            User::authentif();
            optiune = "3";
        }
        else if(optiune == "2")
        {
            User::login(logged);
            if(logged == 1)
            optiune = "0";
        }
        else 
        cout<<"Optiune invalida. Incearca din nou. Apasa 0 daca vrei sa iesi\n";
    }
    if(logged == 1)
        User::startFlows();
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
        relativePath="../FlowSystemDataBase/" + username +'/';
        filesystem::create_directory(relativePath+"CsvAndTextInputStep");
        filesystem::create_directory(relativePath+"Flows");
    }
    
    catch(char const* msg)
    {
        cout<<msg;
    }

}
}

void User::login( bool &logged)
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
                logged = 1;
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

void User::startFlows()
{
    string optiune ;
    while(optiune!="0")
    {
        cout<<"\nApasa 1 daca vrei sa creezi un now flow, 2 daca vrei sa accesezi unul deja existent.\n";
        
        cin>>optiune;
        if(optiune == "1")
        User::createNewFlow();
        // else if(optiune == 2)
        // {
        //     string flow;
        //     cout<<"\nCe flow vrei sa accesezi?\n";
        //     cin>>flow;
        //     User::accessExistingFlows(name,flow);
        // }
        else
        cout<<"\nOptiune invalida. Try again\n";
    }
}
void User::createNewFlow()
{
    
    cout<<"\n----Welcome to Flow creation----\n";
    cout<<"The steps are:\n";
    vector<string> steps ={ 
    "0. End Step\n",
    "1. Add a Title and a new Subtitle.\n", 
    "2. Add a title of the flow and a description of the flow.\n",
    "3. Add a description and an expected output.\n",
    "4. Add a description for a number input\n",
    "5. Add a Calculus step Between different number steps\n",
    "6. Display Previous Steps \n",
    "7. Add a txt file\n",
    "8. Add a csv file\n",
    "9. Create an Output for the flow\n"
    };
    for( int i = 0 ; i < steps.size(); i++ )
         cout<<steps[i];
    TextRelatedStepsBuilder* textsteps = new TextRelatedStepsBuilder();
    NumberRelatedStepsBuilder* numbersteps = new NumberRelatedStepsBuilder();
    DisplayStepsBuilder* display = new DisplayStepsBuilder();
    string optiune = "1";
    while(optiune != "0")
    {    
        cout<<"\nPentru a alege un pas, apasa indexul acestuia. Pentru a termina flowul apasa 0\n";
        cin>>optiune;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        string title;
        string subtitle;
        string text;
        string description;
        string text_input;
        string number_input;
        float number;
        regex floatRegex("^[+-]?[0-9]*\\.?[0-9]+$");
        int optiune_int;
        if(regex_match(optiune,floatRegex))
         optiune_int = stoi(optiune);
        else optiune_int = 100;
        switch (optiune_int)
        {
            case 0:
                break;
            case 1:{
                cout<<steps[1];
                cout<<"Add a title: \n";
                getline(cin,title);
                cout<<"Add a subtitle :\n";
                getline(cin,subtitle);
                textsteps->addTitle(title,subtitle);
                break;
            }
            case 2:{
                cout<<steps[2];
                cout<<"Add a title: \n";
                getline(cin,title);
                cout<<"Add text\n";
                getline(cin,text);
                textsteps->addText(title,text);
                break;
            }
            case 3:{
                cout<<steps[3];
                cout<<"Add a description: \n";
                getline(cin,description);
                cout<<"Add text input :\n";
                getline(cin,text_input);
                textsteps->addTitle(title,subtitle);
                break;
            }
            case 4:{
                cout<<steps[4];
                cout<<"Add a description of the expected number input:\n";
                getline(cin,description);
                cout<<"Add a number input : ";
                cin>>number_input;
                if(regex_match(number_input,floatRegex)){
                number = stof(number_input);
                numbersteps->numberInputStep(description,number);
                } else
                {
                    cout<<"Number invalid. Try Again";
                }
                break;
            }
            case 5:{
                cout<<steps[5];
                string calculusdescription;
                vector <string> operators;
                vector <int> steps_index;
                regex naturalNumberRegex("^[0-9]+$");
                string word;
                cout<<"Tell which number steps to calculate with the following format.";
                cout<<"Valid format : step 3 + step 5 / step 7 * step 1....\n";
                getline(cin,calculusdescription);
                
                stringstream s(calculusdescription);
                operators.clear();
                steps_index.clear();
                
                try{
                    
                    while(getline(s,word,' '))
                    {
                        if(regex_match(word,naturalNumberRegex))
                        {
                            int step = stoi(word);
                            steps_index.push_back(step);
                        }
                        else if(word == "/" || word == "*" || word == "+" || word == "-")
                        {
                            operators.push_back(word);
                        }
                        else if(word != "step")
                            throw "\ninvalid format please Type Again";                    
                    }
                    if(operators.size()+1 != steps_index.size())
                        throw "\ninvalid format please Type Again";
                    
                    numbersteps->calculusStep(steps_index,operators, calculusdescription);
                }catch(const char* msg){
                    cout<<msg;
                }

                break;
            }
            case 6:{
                cout<<steps[6];
                string index;
                cout<<"Type the index of the step you want to display.\n If u want to display text related steps press text.\n If u want to display number related steps, type number :\n";
                cin>>index;
                display->chooseAndDisplayStep(index,textsteps,numbersteps);
                break;
            }
            case 7:{
                cout<<steps[7];
                cout<<"Tell the description of the txt file you want to add : \n";
                string description;
                string path;
                string initial_path = "/home/dragos/Desktop/Proiect-POO/FlowTests/Text/";
                getline(cin,description);
                cout<<"Now tell the name with the path of the file: ";
                getline(cin,path);
                path = initial_path + path;
                display->csvAndTxtStep(description,this->name,path,0);
                break;
            }
            case 8:{
                cout<<steps[8];
                cout<<"Tell the description of the csv file you want to add : \n";
                string description;
                string path;
                string initial_path="/home/dragos/Desktop/Proiect-POO/FlowTests/Csv/";
                getline(cin,description);
                cout<<"Now tell the name with the path of the file: ";
                getline(cin,path);
                path = initial_path+path;
                display->csvAndTxtStep(description,this->name,path,1);
                break;
            }
            case 9:{
                cout<<steps[9];
                cout<<"Name your output file\n";
                string file_name;
                getline(cin,file_name);
                string file_title;
                cout<<"Provide a title for the flow\n";
                getline(cin,file_title);
                string file_description;
                cout<<"Provide a description for the flow\n";
                getline(cin,file_description);
                string file_path = "../FlowSystemDataBase/"+this->name+"/"+"Flows/";
                file_name += ".txt";
                file_path += file_name;
                ofstream output_file(file_path);
                if (output_file.is_open())
                {
                    // Write content to the file
                    output_file<< "Timestamp: "<< getCurrentTimestamp()<<"\n";
                    output_file << "File Title: " << file_title << "\n";
                    output_file << "File Description: " << file_description << "\n";

                    cout << "File created successfully at: " << file_path << "\n";
                    TextRelatedSteps* text = textsteps->getData();
                    NumberRelatedSteps* number = numbersteps->getData();
                    DisplaySteps * displayed = display->getData();
                    output_file.close();
                    text->setToFile(file_path);
                    number->setToFile(file_path);
                    displayed->setToFile(file_path);
                   
                }
                else
                {
                    cout << "Unable to open file for writing.\n";
                }
            }
            default:
                cout<<"Optiune Invalida. Incearca din nou";
                break;
        }
    }
    TextRelatedSteps* text = textsteps->getData();
    NumberRelatedSteps* number = numbersteps->getData();
    DisplaySteps * displayed = display->getData();
    text->printData();
    number->printData();
    displayed->printData();
    delete textsteps;
    delete numbersteps;
    delete display;



}
