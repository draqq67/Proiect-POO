#include <iostream>
#include "flow.h"
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

// constructori si destructori initializati pentru fiecare clasa
TextRelatedStepsBuilder::~TextRelatedStepsBuilder()
{
    delete text;
}
TextRelatedStepsBuilder::TextRelatedStepsBuilder()
{
    this->text = new TextRelatedSteps();
}
NumberRelatedStepsBuilder::~NumberRelatedStepsBuilder()
{
    delete number;
}
NumberRelatedStepsBuilder::NumberRelatedStepsBuilder()
{
    this->number = new NumberRelatedSteps();
}
DisplayStepsBuilder::~DisplayStepsBuilder()
{
    delete display;
}
DisplayStepsBuilder::DisplayStepsBuilder()
{
    this->display = new DisplaySteps();
}
// initializarea metodei de getData pentru fiecare obiectbuilder

TextRelatedSteps* TextRelatedStepsBuilder::getData()
{
    TextRelatedSteps* result = this->text;
    this->text = new TextRelatedSteps();
    return result;
}
NumberRelatedSteps* NumberRelatedStepsBuilder::getData()
{
    NumberRelatedSteps* result = this->number;
    this->number = new NumberRelatedSteps();
    return result;
}
DisplaySteps* DisplayStepsBuilder::getData()
{
    DisplaySteps* result = this->display;
    this->display = new DisplaySteps();
    return result;
}

// initializarea metodelor clasei TextRelatedSteps and Builder

void TextRelatedStepsBuilder::addTitle(string title, string subtitle)
{
    text->title.push_back(title);
    text->subtitle.push_back(subtitle);
}
void TextRelatedStepsBuilder::addText(string title, string copy)
{
    text->flow_title.push_back(title);
    text->text.push_back(copy);
}
void TextRelatedStepsBuilder::addTextInput(string description, string text_input)
{
    text->description.push_back(description);
    text->text_input.push_back(text_input);
}

void TextRelatedSteps::printData()
{
    cout<<"---Titles---\n";
    for(int i = 0 ; i <title.size();i++)
        cout<<title[i]<<" "<<subtitle[i]<<"\n";
        cout<<"\n---Text---\n";
    for(int i = 0 ; i <flow_title.size();i++)
        {
            cout<<flow_title[i]<<"\n";
            cout<<text[i]<<"\n";
        }
    for(int i = 0 ;i < description.size();i++)
        {
            cout<<description[i]<<":\n";
            cout<<text_input[i]<<"\n";
        }
    
}

//initializarea metodelor pentru NumberRelated Steps and Builder

void NumberRelatedStepsBuilder::numberInputStep(string description, float number)
{
    this->number->descriptions.push_back(description);
    this->number->numbers.push_back(number);
}

void NumberRelatedStepsBuilder::calculusStep(std::vector<int> steps_index, std::vector<string> operators, string calculusdescription)
{
    this->number->calculus_description.push_back(calculusdescription);
    float rasp = 0;
    vector<float> numbers = this->number->numbers;
    try{
        if(*max_element(steps_index.begin(),steps_index.end()) > numbers.size())
            throw "Number Steps doesnt exist";
    rasp = operations(numbers[steps_index[0]],numbers[steps_index[1]],operators[0]);
    
      for ( int i = 1; i < operators.size(); i++ )
        rasp += operations(rasp,numbers[steps_index[i+1]],operators[i]);
    
    this->number->calculus.push_back(rasp);
    rasp = 0;
    }catch(const char* msg)
    {
        cout<<msg;
    }
}

float NumberRelatedStepsBuilder::operations(float a, float b,string operation)
{
    if( operation == "+")
    return a+b;
    else if( operation == "-")
    return a-b;
    else if( operation == "*")
    return a*b;
    else if( operation == "/")
    return a/b;

}

void NumberRelatedSteps::printData()
{
    cout<<"\n---NumberSteps---\n";
    for(int i = 0 ; i < descriptions.size();i++)
        cout<<descriptions[i]<<": "<<numbers[i]<<"\n";
    cout<<"\n---CalculusSteps---\n";
    for(int i = 0 ; i < calculus.size(); i++)
        cout<<calculus_description[i]<<":"<<calculus[i]<<"\n";
}
// Display Steps 
void DisplayStepsBuilder::chooseAndDisplayStep( string index, TextRelatedStepsBuilder* textsteps, NumberRelatedStepsBuilder* numbersteps)
{
     if(index == "text")
                {
                    TextRelatedSteps* text = textsteps->getData();
                    text->printData();
                }
                else if(index == "number")
                {
                    NumberRelatedSteps* number = numbersteps->getData();
                    number->printData();
                }
                else if(index == "1")
                {
                    TextRelatedSteps* text = textsteps->getData();
                    cout<<"----Titles&Subtitles---";
                    for(int i = 0 ; i <text->title.size();i++)
                         cout<<text->title[i]<<" "<<text->subtitle[i]<<"\n";
                }
                else if(index =="2")
                {
                    TextRelatedSteps* text = textsteps->getData();
                      cout<<"\n---Flows---\n";
                    for(int i = 0 ; i <text->flow_title.size();i++)
                    {
                        cout<<text->flow_title[i]<<"\n";
                        cout<<text->text[i]<<"\n";
                    }
                }
                else if(index == "3")
                    {
                        cout<<"\n---Text Input---\n";
                        TextRelatedSteps* text = textsteps->getData();
                        for(int i = 0 ;i < text->description.size();i++)
                        {
                            cout<<text->description[i]<<":\n";
                            cout<<text->text_input[i]<<"\n";
                        }
                    }
                else if(index == "4")
                {
                    cout<<"\n---Number Steps---\n";
                    NumberRelatedSteps* number = numbersteps->getData();
                    for(int i = 0 ; i < number->descriptions.size();i++)
                        cout<<number->descriptions[i]<<": "<<number->numbers[i]<<"\n";  
                }
                else {
                    cout<<"Invalid Name. Try Again\n";
                }
}

void DisplayStepsBuilder::csvAndTxtStep(string description,string name,string path, bool ok)
{
    try
    {
        // Open the specified file
        fstream file;
        file.open(path, ios::in | ios::binary);
        if (!file.is_open())
        {
            throw "\nUnable to open file: " + path + "\n";
        }
        // Read the content of the file into a string
        size_t last_slash = path.find_last_of("/\\");
        string original_filename = (last_slash != string::npos) ? path.substr(last_slash + 1) : path;
        
        string file_content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

        // Create a new file in the user's directory and save the content
        string user_directory = "/home/dragos/Desktop/Proiect-POO/FlowSystemDataBase/" + name + "/" +"CsvAndTextInputStep" + "/";
        string new_file_path = user_directory + original_filename ;
        ofstream new_file(new_file_path, ios::out | ios::binary);
        new_file << file_content;
        if(ok == 0)
        {
            display->txtFileName.push_back(new_file_path);
            display->descriptionTxt.push_back(description);
        }
        else 
        {
            display->csvFileName.push_back(new_file_path);
            display->descriptionCsv.push_back(description);
        }
        file.close();
        new_file.close();

        cout << "\nFile saved successfully in user's directory: " << new_file_path << "\n";
        ifstream read_file(new_file_path);
        if (read_file.is_open())
        {
            cout << "\nContent of the file:\n";
            cout << file_content << "\n";

            // Close the file after reading
            read_file.close();
        }
        else
        {
            throw "Unable to open the newly created file for reading.\n";
        }
    }
    catch (const char *msg)
    {
        cout << msg;
    }
}

void DisplaySteps::printData()
{
    cout<<"\n---Txt files---\n";
    if(txtFileName.size() == 0)
    {
        cout<<"No text files\n";
    }
    for(int i=0 ; i< txtFileName.size(); i++)
        cout<<descriptionTxt[i]<<":"<<txtFileName[i]<<"\n";
    if(csvFileName.size() == 0)
    {
        cout<<"No csv files\n";
    }
    for ( int i = 0 ; i< csvFileName.size();i++)
    {
        cout<<descriptionCsv[i]<<":"<<txtFileName[i]<<"\n";
    }
    
}
//Set to file for every step
void TextRelatedSteps::setToFile(string file)
    {
        fstream out;
        out.open(file,ios::out|ios::app);
         out<<"---Titles---\n";
    for(int i = 0 ; i <title.size();i++)
        out<<title[i]<<" "<<subtitle[i]<<"\n";
        out<<"---Text---\n";
    for(int i = 0 ; i <flow_title.size();i++)
        {
            out<<flow_title[i]<<"\n";
            out<<text[i]<<"\n";
        }
        out<<"---Descriptions---\n";
    for(int i = 0 ;i < description.size();i++)
        {
            out<<description[i]<<":";
            out<<text_input[i]<<"\n";
        }
        out.close();

    }
void DisplaySteps::setToFile(string file)
    {
         fstream out;
        out.open(file,ios::out|ios::app);
        out<<"\n---Txt files---\n";
    if(txtFileName.size() == 0)
    {
        out<<"No text files\n";
    }
    for(int i=0 ; i< txtFileName.size(); i++)
        out<<descriptionTxt[i]<<":"<<txtFileName[i]<<"\n";
        out<<"\n---Csv files---\n";
    if(csvFileName.size() == 0)
    {
        out<<"No csv files\n";
    }
    for ( int i = 0 ; i< csvFileName.size();i++)
    {
        out<<descriptionCsv[i]<<":"<<txtFileName[i]<<"\n";
    }
        out<<"\n\n---End---";
        out.close();
    }
void NumberRelatedSteps::setToFile(string file)
    {
         fstream out;
         out.open(file,ios::out|ios::app);
         out<<"\n---NumberSteps---\n";
    for(int i = 0 ; i < descriptions.size();i++)
        out<<descriptions[i]<<": "<<numbers[i]<<"\n";
        out<<"\n---CalculusSteps---\n";
    for(int i = 0 ; i < calculus.size(); i++)
        out<<calculus_description[i]<<":"<<calculus[i]<<"\n";
        out.open(file,ios::out|ios::app);
    }

