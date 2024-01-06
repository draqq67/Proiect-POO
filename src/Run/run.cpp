#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "run.h"
using namespace std;

void Run::setDataPath(string dataPath)
{
    this->dataPath = dataPath+"/Flows";
    this->flow_statistics = dataPath+"/flow_statistics.csv";
}
void Run::setRunDataFlow(string username, string flow)
{
    this->username = username;
    this->flow = this->dataPath + "/"+ flow;
    insights->setInsights(flow,this->flow_statistics);
}
void Insights::setInsights(string csvFile, string flow_statistics)
{
    fstream statsInput;
     try
     {
         statsInput.open(flow_statistics, ios::in);
         cout<<flow_statistics;
    if (!statsInput.is_open()) {
        throw "Error: Unable to open flow statistics file\n";
    }
    string line;
    getline(statsInput, line);  // Skip header line
    bool ok = 0;
    // Read data from the flow_statistics file and update insights
    while (getline(statsInput, line)) {
        stringstream ss(line);
        string flowname, startedStr, completedStr, screenskipsStr, errorStr, avgerrorsStr;

        getline(ss, flowname, ',');       
        getline(ss, startedStr, ',');     
        getline(ss, completedStr, ',');    
        getline(ss, screenskipsStr, ','); 
        getline(ss, errorStr, ',');       
        getline(ss, avgerrorsStr, ','); 

        // Check if the current row matches the desired CSV file
        if (flowname == csvFile) {
            this->started = stoi(startedStr);
            this->completed = stoi(completedStr);
            this->screenskips = stoi(screenskipsStr);
            this->error = stoi(errorStr);
            this->avgerrors = stof(avgerrorsStr);
            break; 
            ok = 1;
        }
    }
    if(ok == 0)
       cout<<" File not found\n";
         statsInput.close();
    }catch(const char * msg)
    {
    cout<<msg;
    }
}
void Insights::uploadInsightsToStatistics(string flow, string dataPath)
{
    ifstream inputFile(dataPath+"/flow_statistics.csv");
    ofstream tempFile(dataPath+"/temp.csv");

    string line;
    while (getline(inputFile, line)) {
        istringstream ss(line);
        string token;
        getline(ss, token, ',');
        if (token == flow) {
            tempFile << flow << "," << started << "," << completed << "," << screenskips << "," << error << "," << avgerrors << "\n";
        } else {
            tempFile << line << "\n";
        }
    }

    inputFile.close();
    tempFile.close();

    string datastatistics = dataPath + "/flow_statistics.csv";
    string datatemp = dataPath + "/temp.csv";
    remove(datastatistics.c_str());
    rename(datatemp.c_str(), datastatistics.c_str());
}

Insights* Run::getInsights()
{
    Insights* insights_get = this->insights;
    this->insights = new Insights();
    return insights_get; 
}

void Insights::printInsights()
{
    cout<<"Started : "<<this->started<<"\n";
    cout<<"Completed :"<< this->completed<<"\n";
    cout<<"ScreenSkips :"<<this->screenskips<<"\n";
    cout<<"Errors :"<<this->error<<"\n";
    cout<<"Average Errors/Flow: "<<this->avgerrors<<"\n";
}
Run::Run()
{
    cout<<"Running session starting\n";
    this->insights = new Insights();
}
Run::~Run()
{
    cout<<"Running session finished\n";
    delete insights;
}
void Run::showFlow()
{
    fstream file;
    file.open(this->flow, ios::in | ios::binary);
    string file_content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    cout<<file_content;
    file.close();
}
void Run::uploadInsights(string step_outcome)
{
    if(step_outcome == "skip")
        insights->screenskips+=1;
    else if(step_outcome =="final")
    {
        insights->started+=1;
        if(insights->screenskips == 0 && insights->error == 0)
        insights->completed+=1;
        insights->avgerrors = float(insights->error)/float(insights->started); 
    }
    else if(step_outcome != "done")
    insights->error+=1;
}
void Run::steps(string antet_up, string antet_down)
{
    fstream flow;
    cout<<"Step output :\n";
    flow.open(this->flow,ios::in);
    if (!flow.is_open()) {
        cout << "Error: Unable to open file " << this->flow << "\n";
        return;
    }
    string line;
    bool inside_range = false;
    bool ok = false;

    while (getline(flow, line)) {
        if (line.find(antet_up) != std::string::npos) {
            inside_range = true;
            continue;
        } else if (line.find(antet_down) != std::string::npos) {
            inside_range = false;
            break;
        }

        if (inside_range) {
            cout << line << "\n";
            ok = true;
        }
    }
    if(ok == false)
    cout<<"No matching step";

    flow.close();
}
