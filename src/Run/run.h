
#ifndef RUN_H
#define RUN_H
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Insights{

    public:
    int started;
    int completed;
    int screenskips;
    int error;
    float avgerrors;

    void setInsights(string csvFile, string flow_statistics, bool &ok);
    void printInsights();
    void uploadInsightsToStatistics(string flow,string dataPath);
};
class Run{

    private :
    
    Insights * insights;
    string username;
    string flow_statistics;
    string flow;
    string dataPath;

    public:
    Run();
    ~Run();
    void setDataPath(string dataPath);
    void setRunDataFlow(string username, string flow, bool &ok);
    void showFlow();
    void uploadInsights(string step_outcome);
    void steps(string antet_up, string antet_down);
    Insights* getInsights();
};
#endif