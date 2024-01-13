
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
    strftime(timestamp, sizeof(timestamp), "%d/%m/%Y %H:%M:%S", localtime(&time));
    return string(timestamp);
}
void User::greeting()
{
    string optiune;
    bool logged = 0;
    while(optiune != "0")
    {
        cout<<"\nHello\nselect 1 for authentification or 2 for login\n";
        getline(cin,optiune);        
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
        else if(optiune!="0")
        cout<<"Optiune invalida. Incearca din nou. Apasa 0 daca vrei sa iesi\n";
        else{
            cout<<"\nGoodbye\n";
        }
    }
    if(logged == 1)
        User::startFlows();
}
void User::authentif()
{

    string username;
    bool ok = 1;
    while(ok != 0){
    cout<<"\nType your name. Press 0 if u want to go back:\n";
    getline(cin,username);
    if(username == "0")
    break;
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
        ofstream csvFile(relativePath + "flow_statistics.csv");
        if (csvFile.is_open())
        {
        csvFile << "flowname, started, completed, screenskips, error, avgerrors\n";
        csvFile.close();
        }
        else
        {
        throw "Unable to open CSV file for writing.\n";
        }
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
        cout<<"\nType your username. If u want to go back press 0\n";
        getline(cin,username);
        if(username=="0")
            break;
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
        cout<<"\nApasa 1 daca vrei sa creezi un now flow, 2 daca vrei sa accesezi unul deja existent,3 daca vrei sa stergi un flow.Apasa 0 daca vrei sa inchizi\n";
        
        getline(cin,optiune);
        if(optiune == "1")
        User::createNewFlow();
        else if(optiune == "2")
        {
            User::accessExistingFlows();
        }
        else if(optiune == "3")
        {
            User::deleteFlows();
        }
        else if(optiune!="0")
        cout<<"\nOptiune invalida. Try again\n";
        else 
        cout<<"\nGoodbye\n";
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
    "9. Create an Output for the flow\n",
    "10. Show All Steps Again\n"
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
        getline(cin,optiune);
        // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
                textsteps->addTextInput(description,text_input);
                break;
            }
            case 4:{
                cout<<steps[4];
                cout<<"Add a description of the expected number input:\n";
                getline(cin,description);
                cout<<"Add a number input : ";
                getline(cin,number_input);
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
                vector <string> min_max;
                vector <string> parantheses;
                vector <int> steps_index;
                regex naturalNumberRegex("^[0-9]+$");
                string word;
                cout<<"Tell which number steps to calculate with the following format.";
                cout<<"Valid format : step 3 + step 5 / step 7 * step 1....\n or max( step 3 , step 5 + step 0)\n or min( step 3 , step 5 + step 0)\n";
                getline(cin,calculusdescription);
                
                stringstream s(calculusdescription);
                operators.clear();
                steps_index.clear();
                vector <string> just_operators;
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
                            just_operators.push_back(word);
                        }
                        else if(word == "min(" || word=="max(")
                        {
                            min_max.push_back(word);
                            operators.push_back(word);
                        }
                        else if(word == ")")
                        {
                            parantheses.push_back(word);
                            operators.push_back(word);
                        }
                        else if(word==",")
                        {
                            operators.push_back(word);
                        }
                        else if(word != "step")
                            throw "\ninvalid format please Type Againa";                    
                    }
                    if( min_max.size() != parantheses.size() )
                        throw "\ninvalid format please Type Againb";
                    else if( min_max.size() == parantheses.size() && min_max.size() == 0 && just_operators.size() != steps_index.size()-1)
                    {
                            throw "\ninvalid format please Type Againc";
                    }
                    else if (min_max.size() == parantheses.size() && min_max.size() != 0)
                    {
                        if(operators.size()-1 != steps_index.size())
                            throw "\ninvalid format please Type Againd";
                    }
                    else if(min_max.size() > 1)
                     throw "\ninvalid format please Type Againf";
                    numbersteps->calculusStep(steps_index,operators,calculusdescription,min_max,just_operators);
                }catch(const char* msg){
                    cout<<msg;
                }

                break;
            }
            case 6:{
                cout<<steps[6];
                string index;
                cout<<"Type the index of the step you want to display.\n If u want to display text related steps press text.\n If u want to display number related steps, type number :\n";
                getline(cin,index);
                display->chooseAndDisplayStep(index,textsteps,numbersteps);
                break;
            }
            case 7:{
                cout<<steps[7];
                cout<<"Tell the description of the txt file you want to add : \n";
                string description;
                string path;
                string initial_path = "/home/dragos/Desktop/Proiect-POO/";
                getline(cin,description);
                cout<<"Now tell the name with the path of the file, initial path is ../Proiect-Poo/: ";
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
                string initial_path="/home/dragos/Desktop/Proiect-POO/";
                getline(cin,description);
                cout<<"Now tell the name with the path of the file, initial path is ../Proiect-Poo/: ";
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
                string file_path_BD = "../FlowSystemDataBase/" + this->name +"/" +"flow_statistics.csv";
                int i = 0;
                for (const auto& entry : filesystem::directory_iterator(file_path))
                {
                    string filename = entry.path().filename().string();
                    size_t pos = filename.find('(');
                    if (pos != std::string::npos) {
                        filename = filename.substr(0, pos);
                    }
                    if (filename == file_name)
                        i++;
                }
                if(i != 0)
                file_name += "(" + to_string(i-1) + ").txt";
                file_name += ".txt";
                file_path += file_name;
                string new_file_path = file_path;
                ofstream output_file(new_file_path);
                if (output_file.is_open())
                {
                    // Write content to the file
                    output_file<< "Timestamp: "<< getCurrentTimestamp()<<"\n";
                    output_file << "File Title: " << file_title << "\n";
                    output_file << "File Description: " << file_description << "\n\n";

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
                fstream csvFile;
                csvFile.open(file_path_BD,ios::out|ios::app);
                if (csvFile.is_open())
                {   
                    csvFile<< file_name<<", 0, 0, 0, 0, 0";
                    csvFile.close();
                    cout<<"CSV file opened\n";
                }
                else
                cout<<"CSV Statistics couldn't load";
            break;
            }
            case 10:
                for(int i = 0 ; i < steps.size(); i++)
                    cout<<steps[i];
                break;
            default:
                cout<<"Optiune Invalida. Incearca din nou";
                break;
        }
    }
    delete textsteps;
    delete numbersteps;
    delete display;



}
void User::accessExistingFlows()
{
    Run * run = new Run();
    cout<<"Pick Up a flow from your file :\n";
    string dataPath = "../FlowSystemDataBase/" + name ;
    string directoryPath="../FlowSystemDataBase/" + name + "/Flows/" ;
    try
    {
        for (const auto& entry : filesystem::directory_iterator(directoryPath))
        {
            cout << entry.path().filename() << " ";
        }
        cout<<"\n What do u want to pick?\n";
        string filename;
        getline(cin,filename);

        run->setDataPath(dataPath);
        bool ok = 0;
        run->setRunDataFlow(name,filename,ok);
        if(ok == 0)
            throw "File not found";
        cout<<"---Run the steps---\n\n";
        vector <string> steps;
        steps ={"0. Show the flow\n",
        "1.Title step\n",
        "2.Title text step\n",
        "3.Text input step\n",
        "4.Number input step\n",
        "5.Calculus step\n",
        "6.TxtFiles step\n",
        "7.CsvFiles step\n",
        "8.End step\n"};

        cout<<"All Steps would be in a linear way. Starting from 0 to 8\n\n";
        string rules ="\nThe rules of the step are simple when you have done a step.\nYou type done else you type not done.\nTo skip a step press skip\n";
        cout<<rules;
        cout<<"\nPress start to start the flow: \n";
        string start;
        int optiune = 0;

        string step_outcome;
        getline(cin,start);
        if(start == "start")
        {
         while(optiune != 9)
         {
            switch (optiune)
            {
            case 0:{
                cout<<steps[0];
                run->showFlow();
                cout<<rules;
                getline(cin,step_outcome);
                optiune +=1;
                run->uploadInsights(step_outcome);
                break;
            }
            case 1:{
                cout<<steps[1];
                run->steps("---Titles---","---Text---");
                cout<<rules;
                getline(cin,step_outcome);
                run->uploadInsights(step_outcome);
                optiune +=1;
                break;
            }
            case 2:{
                cout<<steps[2];
                run->steps("---Text---","---Descriptions---");
                cout<<rules;
                getline(cin,step_outcome);
                run->uploadInsights(step_outcome);
                optiune +=1;
                break;
            }
            case 3:{
                cout<<steps[3];
                run->steps("---Descriptions---","---NumberSteps---");
                cout<<rules;
                getline(cin,step_outcome);
                run->uploadInsights(step_outcome);
                optiune +=1;
                break;
            }
            case 4:{
                cout<<steps[4];
                run->steps("---NumberSteps---","---CalculusSteps---");
                cout<<rules;
                getline(cin,step_outcome);
                run->uploadInsights(step_outcome);
                optiune +=1;
                break;
            }
            case 5:{
                cout<<steps[5];
                run->steps("---CalculusSteps---","---Txt files---");
                cout<<rules;
                getline(cin,step_outcome);
                run->uploadInsights(step_outcome);
                optiune +=1;
                break;
            }
            case 6:{
                cout<<steps[6];
                run->steps("---Txt files---","---Csv files---");
                cout<<rules;
                getline(cin,step_outcome);
                run->uploadInsights(step_outcome);
                optiune +=1;
                break;
            }
            case 7:{
                cout<<steps[7];
                run->steps("---Csv files---","---End---");
                cout<<rules;
                getline(cin,step_outcome);
                run->uploadInsights(step_outcome);
                optiune +=1;
                break;
            }
            case 8:{
            cout<<steps[8];
            step_outcome = "final";
            run->uploadInsights(step_outcome);
            Insights* insights = run->getInsights();
            insights->printInsights();
            insights->uploadInsightsToStatistics(filename,dataPath);
            optiune+=1;    
                break;
            }  
            default :
                break;
            }
         }
        }
        else cout<<"Try Again";

        delete run;
        
    }
    catch (const char* msg)
    {
        cout<<msg;
    }
}
void User::deleteFlows()
{
     try
    {
        string directoryPath="../FlowSystemDataBase/" + name + "/Flows/" ;
        string filename;
        for (const auto& entry : filesystem::directory_iterator(directoryPath))
        {
            cout << entry.path().filename() << " ";
        }
        cout<<"\n What do u want to pick?\n";
        cout<<"Tell which file you want to delete:\n";
        getline(cin,filename);
         int ok = 0;
         if(std::filesystem::directory_iterator(directoryPath) == std::filesystem::directory_iterator{})
            throw "Directory is empty.\n";
         for (const auto& entry : filesystem::directory_iterator(directoryPath))
        {
            if(entry.path().filename() == filename)
            {
                 filesystem::remove(directoryPath + filename);
                cout << "File '" << filename << "' deleted successfully.\n";
                ok = 1;
                
                string csvFilePath = "../FlowSystemDataBase/" + name + "/flow_statistics.csv";
                vector<string> csvContent;
                ifstream csvFile(csvFilePath);
                if (csvFile.is_open())
                {
                    string line;
                    while (getline(csvFile, line))
                    {
                        // Exclude the row corresponding to the file being deleted
                        if (line.find(filename) == string::npos)
                        {
                            csvContent.push_back(line);
                        }
                    }
                    csvFile.close();

                    ofstream updatedCsvFile(csvFilePath);
                    if (updatedCsvFile.is_open())
                    {
                        for (const string& row : csvContent)
                        {
                            updatedCsvFile << row << "\n";
                        }
                        updatedCsvFile.close();
                        cout << "Row corresponding to file '" << filename << "' deleted from '" << csvFilePath << "'.\n";
                    }
                    else
                    {
                        throw "Unable to open CSV file for writing.\n";
                    }
                }
                else
                {
                    throw "Unable to open CSV file for reading.\n";
                }

                } 
                
            }
            if(ok == 0)
                throw "File not found\n";
        }catch (const exception& e)
        {
            cerr << "Error: " << e.what() << endl;
        }catch(const char * msg)
        {
            cout<<msg;
        }
}